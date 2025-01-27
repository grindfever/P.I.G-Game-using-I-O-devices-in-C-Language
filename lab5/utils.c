#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  
  if(lsb == NULL) {
    return 1;
  }

  *lsb = val;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb == NULL) {
    return 1;
  }

  *msb = val >> 8;

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if(value == NULL){
    printf("NUll pointer");
    return 1;
  }

  uint32_t temp; 

  if(sys_inb(port, &temp)){
    printf("error sys_inb");
    return 1;
  }

  *value = temp;

  return 0;
}
