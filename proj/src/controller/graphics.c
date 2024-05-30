#include <lcom/lcf.h>
#include <stdint.h>

#include "graphics.h"

static void *vbe_mem;

static uint16_t XRes;
static uint16_t YRes;
static uint8_t clr_depth;

static uint8_t RMaskSize;
static uint8_t GMaskSize;
static uint8_t BMaskSize;

void *(vg_init)(uint16_t mode) {

  vbe_mode_info_t ModeInfo;
  if (vbe_get_mode_info(mode, &ModeInfo) != OK)
    return NULL;

  clr_depth = ModeInfo.BitsPerPixel;
  XRes = ModeInfo.XResolution;
  YRes = ModeInfo.YResolution;

  RMaskSize = ModeInfo.RedMaskSize;
  GMaskSize = ModeInfo.GreenMaskSize;
  BMaskSize = ModeInfo.BlueMaskSize;

  int ReturnVal;
  struct minix_mem_range MemoryRange;
  MemoryRange.mr_base = ModeInfo.PhysBasePtr;
  unsigned int VramSize = XRes * YRes * bytes_per_pixel();
  MemoryRange.mr_limit = MemoryRange.mr_base + VramSize;

  if ((ReturnVal = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &MemoryRange)) != OK) {
    panic("sys_privctl (ADD_MEM) failed: %d\n", ReturnVal);
    return NULL;
  }
  
  /* map memory */
  vbe_mem = vm_map_phys(SELF, (void *)MemoryRange.mr_base, VramSize);
  if(vbe_mem == MAP_FAILED)
    panic("couldn't map video memory");

  reg86_t Reg86;
  memset(&Reg86, 0, sizeof(Reg86)); // zero the structure

  /* specify the appropriate register values */
  Reg86.intno = 0x10; 
  Reg86.ah = 0x4F; 
  Reg86.al = 0x02; 
  Reg86.bx = mode | BIT(14); 
 
  if (sys_int86(&Reg86) != OK) {
    printf("set_vbe_mode: sys_int86() failed\n");
    return NULL;
  }

  return vbe_mem;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    if (generate_pixel(x + i, y, color) != OK)
      return 1;
  }

  return 0;
}
  
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int i = 0; i < height; i++)
    if (vg_draw_hline(x, y + i, width, color) != OK)
      return 1;

  return 0;
}

uint16_t (get_hres)() {
  return XRes;
}

uint16_t (get_vres)() {
  return YRes;
}

int (bytes_per_pixel)() {
  int BitsPerPixel = (int)clr_depth;
  int BytesPerPixel = (BitsPerPixel / 8) + ((BitsPerPixel % 8) ? 1 : 0);
  return BytesPerPixel;
}

int (generate_pixel)(uint16_t posX, uint16_t posY, uint32_t clr) {
  if (clr_depth == 8) { // mode 0x105
    if (clr > UINT8_MAX) {
      printf("invalid color\n");
      return 1;
    }

    uint8_t *pixelPtr;
    pixelPtr = (uint8_t *)vbe_mem + (posY * XRes + posX) * bytes_per_pixel();
    *pixelPtr = 0xFF & clr;  
  }
  else if (clr_depth == 24) { // mode 0x115
    uint8_t *pixelPtr;
    pixelPtr = (uint8_t *)vbe_mem + (posY * XRes + posX) * bytes_per_pixel();
    *(pixelPtr + 2) = 0xFF & (clr >> 16);
    *(pixelPtr + 1) = 0xFF & (clr >> 8);
    *pixelPtr = 0xFF & clr;
  }

  return 0;
}

uint32_t (get_color)(uint8_t rectangles, uint32_t first_color, uint8_t step_size, uint8_t row_index, uint8_t col_index) {
  uint32_t calculatedColor = 0;

  if (clr_depth == 8) { // mode 0x105
    uint32_t baseColor = (first_color + (row_index * rectangles + col_index) * step_size) % (1 << clr_depth);
    calculatedColor = (baseColor << 16) | (baseColor << 8) | baseColor;
  }
  else if (clr_depth == 24) { // mode 0x115
    uint32_t red = ((0xFF & (first_color >> 16)) + col_index * step_size) % (1 << RMaskSize);
    uint32_t green = ((0xFF & (first_color >> 8)) + row_index * step_size) % (1 << GMaskSize);
    uint32_t blue = ((0xFF & first_color) + (col_index + row_index) * step_size) % (1 << BMaskSize);

    calculatedColor = ((0xFF & red) << 16) | ((0xFF & green) << 8) | (0xFF & blue); // color = RGB
  }

  return calculatedColor;
}
