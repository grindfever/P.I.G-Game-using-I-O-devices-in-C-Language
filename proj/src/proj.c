// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "./model/menu.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/proj/output/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int proj_main_loop(int argc, char **argv) {
  if (main_menu())
        return 1;
    return 0;
}

/*
extern bool keyboard_complete;
extern struct scan_code_stats scan_code;

int loop(){
  message msg;
  int ipc_status;
  int r;
  //int loop = 0;

  Board* b = construct_board(0,0,5);

  while( scan_code.code[scan_code.size - 1] != KBC_BREAK_ESC ) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:	
          if (msg.m_notify.interrupts & irq_set_mouse) { mouse_game_handler(b); }
          if (msg.m_notify.interrupts & irq_set_kbd) { kbc_ih(); }
          //if (msg.m_notify.interrupts & irq_set_timer) {timer_int_handler();}
          break;
        default:
          break;
      }
    } 
  }

  destroy_board(b);

  return 0;
}


*/


