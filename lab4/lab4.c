// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "mouse.h"
#include "I8042.h"

extern bool complete;
extern struct packet pack;
extern uint32_t counter;
extern uint32_t t_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    
  message msg;
  int ipc_status;
  int r;
  uint8_t bit_no;
  int check;

  for(int i = 0; i < 2; i++){
    check = mouse_send_command(KBC_EN_REP);
    if(check == 0){
      break;
    }
  }

  if(check){
    return 1;
  }

  if(mouse_subscribe_int(&bit_no)){
    return 1;
  }

  uint8_t irq_set = BIT(bit_no);

  while( cnt > 0 ) { /* You may want to use a different condition */
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
                mouse_ih();
                if (complete) {
                  mouse_print_packet(&pack);
                  cnt--;
                }
              }
                break;
            default:
              break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }

  if(mouse_unsubscribe_int()){
    return 1;
  }

  for(int i = 0; i < 2; i++){
    check = mouse_send_command(KBC_DIS_REP);
    if(check == 0){
      break;
    }
  }

  return check;
}

int (mouse_test_async)(uint8_t idle_time) {
        
  message msg;
  int ipc_status;
  int r;
  uint8_t bit_no_mouse;
  uint8_t bit_no_timer;
  int check;

  for(int i = 0; i < 2; i++){
    check = mouse_send_command(KBC_EN_REP);
    if(check == 0){
      break;
    }
  }

  if(check){
    return 1;
  }

  if(mouse_subscribe_int(&bit_no_mouse)){
    return 1;
  }

  if(timer_subscribe_int(&bit_no_timer)){
    return 1;
  }

  uint8_t irq_set_mouse = BIT(bit_no_mouse);
  uint32_t irq_set_timer = BIT(bit_no_timer);

  int freq = sys_hz();

  while( t_counter/freq < idle_time) { /* You may want to use a different condition */
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */		
            // timer		
              if (msg.m_notify.interrupts & irq_set_mouse) { /* subscribed interrupt */
                mouse_ih();
                if (complete) {
                  mouse_print_packet(&pack);
                  t_counter = 0;
                }
              }
              if (msg.m_notify.interrupts & irq_set_timer) { /* subscribed interrupt */
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

  if(mouse_unsubscribe_int()){
    return 1;
  }

  if(timer_unsubscribe_int()){
    return 1;
  }

  for(int i = 0; i < 2; i++){
    check = mouse_send_command(KBC_DIS_REP);
    if(check == 0){
      break;
    }
  }

  return check;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
