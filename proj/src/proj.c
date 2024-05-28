// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

// Any header files included below this line should have been created by you
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "model/board.h"
#include "model/tile.h"
//#include "controller/video_gr.h"

uint32_t irq_set_kbd;
uint32_t irq_set_mouse;
uint32_t irq_set_timer;

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

int start(){
  uint8_t bit_no_kbd;
  uint8_t bit_no_timer;
  uint8_t bit_no_mouse;

  if(keyboard_subscribe_int(&bit_no_kbd)){
    return 1;
  }

  if(timer_subscribe_int(&bit_no_timer)){
    return 1;
  }

  if(mouse_subscribe_int(&bit_no_mouse)){
    return 1;
  }

  /*
  if (vg_init(GAME_MODE) == NULL){
    return 1;
  }
  */

  irq_set_kbd = BIT(bit_no_kbd);
  irq_set_mouse = BIT(bit_no_mouse);
  irq_set_timer = BIT(bit_no_timer);

  return 0;
}

int end(){
  if(keyboard_unsubscribe_int()){
    return 1;
  }

  if(timer_unsubscribe_int()){
    return 1;
  }

  if(mouse_unsubscribe_int()){
    return 1;
  }

  if (vg_exit() != OK){
    return 1;
  }

  return 0;
}

int loop(){
  message msg;
  int ipc_status;
  int r;

  while( true ) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:	
          if (msg.m_notify.interrupts & irq_set_mouse) {mouse_ih();} //antes do interrupt handler deve chamar função para lidar com lógica
          if (msg.m_notify.interrupts & irq_set_kbd) {kbc_ih();}
          if (msg.m_notify.interrupts & irq_set_timer) {timer_int_handler();}
          break;
        default:
          break;
      }
    } 
  }
}

int (proj_main_loop)(int argc, char **argv) {

  Board* b = construct_board(0, 0, 5);

  print_board(b);

  toggle_board_tile(1, 1, b);

  printf("---------------------------\n");

  printf("Check (%d)\n", check_win(b));

  destroy_board(b);

  return 0;
}
