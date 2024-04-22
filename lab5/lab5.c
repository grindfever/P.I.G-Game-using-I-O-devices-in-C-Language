
#include <lcom/lcf.h>
#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "graphics.h"
#include "keyboard.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if (delay < 0) {
    printf("invalid delay\n");
    return 1;
  }

  if (vg_init(mode) == NULL)
    return 1;

  int mic_sec = delay * 1e6; // microseconds = seconds x 10^6
  tickdelay(micros_to_ticks(mic_sec));

  if (vg_exit() != OK)
    return 1;

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  if (x < 0 | y < 0 | width < 0 | height < 0) {
    printf("invalid coordinates\n");
    return 1;
  }

  if (vg_init(mode) == NULL)
    return 1;

  uint16_t xres = get_hres(), yres = get_vres();
  if (x + width >= xres || y + height >= yres) {
    printf("rectangle exceeds screen boundaries\n");
    if (vg_exit() != OK)
      return 1;
    return 1;
  }

  if (vg_draw_rectangle(x, y, width, height, color) != OK) {
    if (vg_exit() != OK)
      return 1;
    return 1;
  }

  /* wait for ESC break code */

  int ipc_status, r;
  message msg;

  uint8_t bit_no = 0;
  if (kbc_subscribe_int(&bit_no)) // subscribe keyboard interrupts
    return 1;
  int irq_set = BIT(bit_no); 
  
  int process = 1;
  while (process) {
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { // received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_set) { // subscribed interrupt
            kbc_ih();
            if (!keyboard_inc_code())
              process = keyboard_esc_break();
          }
          break;
        default:
          break; // no other notifications expected: do nothing
      }
    }
    else { // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  if (kbc_unsubscribe_int()) // unsubscribe keyboard at the end
    return 1;

  if (vg_exit() != OK)
    return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  if (vg_init(mode) == NULL)
    return 1;

  uint16_t xres = get_hres(), yres = get_vres();
  if ((uint16_t)no_rectangles > xres || (uint16_t)no_rectangles > yres) {
    if (vg_exit() != OK)
      return 1;
    printf("number of rectangles exceeds screen dimensions\n");
    return 1;
  }

  uint16_t rWidth = xres / (uint16_t)no_rectangles;
  uint16_t rHeight = yres / (uint16_t)no_rectangles;
  uint32_t color;

  for (uint8_t i = 0; i < no_rectangles; i++) {
    for (uint8_t j = 0; j < no_rectangles; j++) {
      color = get_color(no_rectangles, first, step, i, j);
      if (vg_draw_rectangle(rWidth * j, rHeight * i, rWidth, rHeight, color)) {
        if (vg_exit() != OK)
          return 1;
        return 1;
      }
    }
  }

  /* wait for ESC break code */

  int ipc_status, r;
  message msg;

  uint8_t bit_no = 0;
  if (kbc_subscribe_int(&bit_no)) // subscribe keyboard interrupts
    return 1;
  int irq_set = BIT(bit_no); // ...01000 (bit 3)
  
  int process = 1;
  while (process) {
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { // received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_set) { // subscribed interrupt
            kbc_ih();
            if (!keyboard_inc_code())
              process = keyboard_esc_break();
          }
          break;
        default:
          break; // no other notifications expected: do nothing
      }
    }
    else { // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  if (kbc_unsubscribe_int()) // unsubscribe keyboard at the end
    return 1;

  if (vg_exit() != OK)
    return 1;

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  uint16_t mode = 0x105; // indexed mode
  if (vg_init(mode) == NULL)
    return 1;

  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t *sprite = xpm_load(xpm, type, &img);

  if (sprite == NULL) {
    printf("failed to load sprite\n");
    return 1;
  }

  uint16_t xres = get_hres(), yres = get_vres();
  uint16_t width = img.width, height = img.height;

  if (x + width >= xres || y + height >= yres) {
    printf("xpm exceeds screen dimensions\n");
    if (vg_exit() != OK)
      return 1;
    return 1;
  }

  for (uint16_t i = 0; i < width; i++) {
    for (uint16_t j = 0; j < height; j++) {
      if (generate_pixel(x + i, y + j, sprite[j * width + i]) != OK) {
        if (vg_exit() != OK)
          return 1;
        return 1;
      }
    }
  }

  /* wait for ESC break code */

  int ipc_status, r;
  message msg;

  uint8_t bit_no = 0;
  if (kbc_subscribe_int(&bit_no)) // subscribe keyboard interrupts
    return 1;
  int irq_set = BIT(bit_no); // ...01000 (bit 3)
  
  int process = 1;
  while (process) {
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { // received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_set) { // subscribed interrupt
            kbc_ih();
            if (!keyboard_inc_code())
              process = keyboard_esc_break();
          }
          break;
        default:
          break; // no other notifications expected: do nothing
      }
    }
    else { // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  if (kbc_unsubscribe_int()) // unsubscribe keyboard at the end
    return 1;

  if (vg_exit() != OK)
    return 1;

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
