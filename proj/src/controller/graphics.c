#include <lcom/lcf.h>
#include <stdint.h>

#include "graphics.h"

static void *vbe_mem_buf;
static void *video_buffer;
static unsigned int VramSize;
vbe_mode_info_t VModeInfo;

static uint16_t XResolution;
static uint16_t YResolution;
static uint8_t color_depth;

static uint8_t RedMaskSize;
static uint8_t GreenMaskSize;
static uint8_t BlueMaskSize;

void *(vg_init)(uint16_t mode) {

  if (vbe_get_mode_info(mode, &VModeInfo) != OK)
    return NULL;

  color_depth = VModeInfo.BitsPerPixel;
  XResolution = VModeInfo.XResolution;
  YResolution = VModeInfo.YResolution;

  RedMaskSize = VModeInfo.RedMaskSize;
  GreenMaskSize = VModeInfo.GreenMaskSize;
  BlueMaskSize = VModeInfo.BlueMaskSize;

  int ReturnVal;
  struct minix_mem_range MemoryRange;
  MemoryRange.mr_base = VModeInfo.PhysBasePtr;
  VramSize = XResolution * YResolution * calculate_bytes_per_pixel();
  MemoryRange.mr_limit = MemoryRange.mr_base + VramSize;

  if ((ReturnVal = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &MemoryRange)) != OK) {
    panic("sys_privctl (ADD_MEM) failed: %d\n", ReturnVal);
    return NULL;
  }
  
  /* map memory */
  vbe_mem_buf = vm_map_phys(SELF, (void *)MemoryRange.mr_base, VramSize);
  if(vbe_mem_buf == MAP_FAILED)
    panic("couldn't map video memory");

  if (map_graphics_memory(mode))
    return NULL;


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

  return vbe_mem_buf;
}


int (map_graphics_memory)(uint16_t mode) {
  int r;
  struct minix_mem_range mr;
  mr.mr_base = VModeInfo.PhysBasePtr;
  VramSize = XResolution * YResolution * calculate_bytes_per_pixel();
  mr.mr_limit = mr.mr_base + VramSize;

  if ((r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) != OK) {
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return 1;
  }
  
  /* map memory */
  vbe_mem_buf = vm_map_phys(SELF, (void *)mr.mr_base, VramSize);
  if(vbe_mem_buf == MAP_FAILED) {
    panic("couldn't map video memory\n");
    return 1;
  }

  video_buffer = malloc(VramSize);

  return 0;
}


int (draw_horizontal_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    if (generate_pixel(x + i, y, color) != OK)
      return 1;
  }

  return 0;
}
  
int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int i = 0; i < height; i++)
    if (draw_horizontal_line(x, y + i, width, color) != OK)
      return 1;

  return 0;
}

uint16_t (get_horizontal_resolution)() {
  return XResolution;
}

uint16_t (get_vertical_resolution)() {
  return YResolution;
}

int (calculate_bytes_per_pixel)() {
  int BitsPerPixel = (int)color_depth;
  int BytesPerPixel = (BitsPerPixel / 8) + ((BitsPerPixel % 8) ? 1 : 0);
  return BytesPerPixel;
}

int (generate_pixel)(uint16_t posX, uint16_t posY, uint32_t clr) {
  uint8_t *ptr;
  ptr = (uint8_t *)video_buffer + (posY * XResolution + posX) * calculate_bytes_per_pixel();
  for (int i = 0; i < calculate_bytes_per_pixel(); i++) {
    *(ptr + i) = clr;
    clr = clr >> 8;
  }

  return 0;

}

void (clear_graphics_screen)() {
  memset(video_buffer, 0, VramSize);
}

void (draw_graphics_content)() {
  memcpy(vbe_mem_buf, video_buffer, VramSize);
}

uint8_t *(read_pixmap)(xpm_row_t *pixmap, uint16_t *width, uint16_t *height) {
  if (width == NULL || height == NULL) {
    printf("null pointer\n");
    return NULL;
  }

  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t *sprite = xpm_load((xpm_map_t)pixmap, type, &img);

  if (sprite == NULL) {
    printf("null pointer\n");
    return NULL;
  }

  *width = img.width;
  *height = img.height;

  return sprite;
}

int (draw_sprite)(uint8_t *sprite, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
  if (sprite == NULL) {
    printf("null pointer\n");
    return 1;
  }

  for (uint16_t i = 0; i < width; i++)
    for (uint16_t j = 0; j < height; j++)
      if (generate_pixel(x + i, y + j, sprite[j * width + i]) != OK)
        return 1;

  return 0;
}

int (draw_element)(xpm_row_t *pixmap, uint16_t x, uint16_t y) {
  uint16_t width = 0, height = 0;
  uint8_t *sprite = read_pixmap(pixmap, &width, &height);
  if (sprite == NULL)
    return 1;
    
  if (draw_sprite(sprite, x, y, width, height))
    return 1;
  
  return 0;
}
