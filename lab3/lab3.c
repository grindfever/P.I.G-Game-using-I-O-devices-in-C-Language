#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include "I8042.h"

extern bool complete;
extern struct scan_code_stats scan_code;
extern uint32_t counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {

  message msg;
  int ipc_status;
  int r;
  uint8_t bit_no;

  if(keyboard_subscribe_int(&bit_no)){
    return 1;
  }

  uint32_t irq_set = BIT(bit_no);

  while( scan_code.code[scan_code.size - 1] != KBC_BREAK_ESC) { /* You may want to use a different condition */
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */		
            // timer		
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                  kbc_ih();
              }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }

  if(keyboard_unsubscribe_int()){
    return 1;
  }

  return 0;
}

int(kbd_test_poll)() {
  while( scan_code.code[scan_code.size - 1] != KBC_BREAK_ESC) {
    kbc_ih();
    if(complete){
      kbd_print_scancode(scan_code.make_break, scan_code.size, scan_code.code); 
    }
  }

  if(keyboard_enable_interrupts()){
    return 1;
  }

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  
  message msg;
  int ipc_status;
  int r;
  uint8_t bit_no_kbd;
  uint8_t bit_no_timer;


  if(keyboard_subscribe_int(&bit_no_kbd)){
    return 1;
  }

  if(timer_subscribe_int(&bit_no_timer)){
    return 1;
  }

  uint32_t irq_set_kbd = BIT(bit_no_kbd);
  uint32_t irq_set_timer = BIT(bit_no_timer);

  while(scan_code.code[scan_code.size - 1] != KBC_BREAK_ESC && counter/60 < n) { /* You may want to use a different condition */
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */		
            // timer		
                if (msg.m_notify.interrupts & irq_set_kbd) { /* subscribed interrupt */
                  kbc_ih();
                  if(complete){
                    kbd_print_scancode(scan_code.make_break, scan_code.size, scan_code.code); 
                    counter = 0;
                  }
                }
                if (msg.m_notify.interrupts & irq_set_timer) {
                  timer_int_handler();
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }

  if(keyboard_unsubscribe_int()){
    return 1;
  }

  if(timer_unsubscribe_int()){
    return 1;
  }

  return 0;
}
