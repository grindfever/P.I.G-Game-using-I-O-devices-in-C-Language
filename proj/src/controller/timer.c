
#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>
#include "i8254.h"

/** @brief Hook ID for timer interrupts */
int hook_id;

/** @brief Counter for the number of timer interrupts */
uint32_t counter = 0;

/**
 * @brief Sets the frequency of the specified timer.
 * 
 * @param timer The timer to set the frequency for (0, 1, or 2).
 * @param freq The desired frequency in Hz.
 * @return 0 on success, 1 on failure (e.g., invalid timer or frequency).
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t old_conf; 

  if(freq < 19 || freq > TIMER_FREQ) {
    return 1;
  }

  if(timer_get_conf(timer, &old_conf)) {
    return 1;
  }

  uint8_t port;
  uint8_t control_word = old_conf & (BIT(1) | BIT(2) | BIT(3) | TIMER_BCD);
  control_word |= (TIMER_LSB_MSB | (timer << 6));

  switch(timer) {
    case 0:
        port = TIMER_0;
        break;
    case 1:
        port = TIMER_1;
        break;
    case 2:
        port = TIMER_2;
        break;
    default:
        return 1;
  }
  
  if(sys_outb(TIMER_CTRL, control_word)) {
    return 1;
  }

  uint16_t div = TIMER_FREQ / freq;
  uint8_t div_lsb, div_msb;

  if(util_get_LSB(div, &div_lsb)) {
    return 1;
  }

  if(util_get_MSB(div, &div_msb)) {
    return 1;
  }
  
  if(sys_outb(port, div_lsb) || sys_outb(port, div_msb)) {
    return 1;
  }

  return 0;
}

/**
 * @brief Subscribes to timer interrupts.
 * 
 * @param bit_no Pointer to store the bit number to be set in the mask returned upon an interrupt.
 * @return 0 on success, 1 on failure.
 */
int (timer_subscribe_int)(uint8_t *bit_no) {
  hook_id = TIMER0_IRQ;
  *bit_no = TIMER0_IRQ;

  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id)) {
    return 1;
  }

  return 0;
}

/**
 * @brief Unsubscribes from timer interrupts.
 * 
 * @return 0 on success, 1 on failure.
 */
int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook_id)) {
    return 1;
  }

  return 0;
}

/**
 * @brief Timer interrupt handler that increments the counter.
 */
void (timer_int_handler)() {
  counter += 1;
}

/**
 * @brief Gets the configuration of the specified timer.
 * 
 * @param timer The timer to get the configuration of (0, 1, or 2).
 * @param st Pointer to store the status byte.
 * @return 0 on success, 1 on failure (e.g., invalid timer or NULL pointer).
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(st == NULL) {
    printf("NULL Pointer\n");
    return 1;
  }

  int port; 

  switch (timer) {
    case 0:
      port = TIMER_0;
      break;
    case 1:
      port = TIMER_1;
      break;
    case 2:
      port = TIMER_2;
      break;
    default:
      printf("Invalid timer\n");
      return 1;
  }

  uint8_t read_back_command = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_;

  if(sys_outb(TIMER_CTRL, read_back_command)) {
    printf("sys_out error\n");
    return 1;
  }

  if(util_sys_inb(port, st)) {
    printf("sys_in error\n");
    return 1;
  }

  return 0;
}

/**
 * @brief Displays the configuration of the specified timer.
 * 
 * @param timer The timer to display the configuration of (0, 1, or 2).
 * @param st The status byte of the timer.
 * @param field The field to interpret from the status byte.
 * @return 0 on success, 1 on failure (e.g., invalid field).
 */
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val values;
  uint8_t temp;
  
  switch(field) {
    case tsf_all:
      values.byte = st;
      break;
    case tsf_initial:
      switch(st & (BIT(5) | BIT(4))) {
        case TIMER_LSB:
          values.in_mode = LSB_only;
          break;
        case TIMER_MSB:
          values.in_mode = MSB_only;
          break;
        case TIMER_LSB_MSB:
          values.in_mode = MSB_after_LSB;
          break;
        default:
          values.in_mode = INVAL_val;
      }
      break;
    case tsf_mode:
      temp = (st & (BIT(1) | BIT(2) | BIT(3))) >> 1;
      if(temp == 2 || temp == 6) {
        values.count_mode = 2;
      } else if(temp == 3 || temp == 7) {
        values.count_mode = 3;
      } else {
        values.count_mode = temp;
      }
      break;
    case tsf_base:
      values.bcd = st & TIMER_BCD;
      break;
  }

  if(timer_print_config(timer, field, values)) {
    printf("error printing config\n");
    return 1;
  }

  return 0;
}
