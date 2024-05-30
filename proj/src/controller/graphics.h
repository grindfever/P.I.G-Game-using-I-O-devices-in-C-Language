#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

/**
 * @brief Initializes the graphics mode.
 * 
 * @param mode Graphics mode to initialize.
 * @return Pointer to the mapped video memory or NULL on failure.
 */
void *(vg_init)(uint16_t mode);

/**
 * @brief Maps the graphics memory.
 * 
 * @param mode Graphics mode to map.
 * @return 0 on success, 1 on failure.
 */
int (map_graphics_memory)(uint16_t mode);

/**
 * @brief Draws a horizontal line.
 * 
 * @param x Starting x-coordinate.
 * @param y Starting y-coordinate.
 * @param len Length of the line.
 * @param color Color of the line.
 * @return 0 on success, 1 on failure.
 */
int (draw_horizontal_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a rectangle.
 * 
 * @param x Top-left x-coordinate.
 * @param y Top-left y-coordinate.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color of the rectangle.
 * @return 0 on success, 1 on failure.
 */
int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Gets the horizontal resolution.
 * 
 * @return Horizontal resolution.
 */
uint16_t (get_horizontal_resolution)();

/**
 * @brief Gets the vertical resolution.
 * 
 * @return Vertical resolution.
 */
uint16_t (get_vertical_resolution)();

/**
 * @brief Calculates the bytes per pixel.
 * 
 * @return Bytes per pixel.
 */
int (calculate_bytes_per_pixel)();

/**
 * @brief Generates a pixel at a given position.
 * 
 * @param posX X-coordinate of the pixel.
 * @param posY Y-coordinate of the pixel.
 * @param clr Color of the pixel.
 * @return 0 on success, 1 on failure.
 */
int (generate_pixel)(uint16_t posX, uint16_t posY, uint32_t clr);

/**
 * @brief Clears the graphics screen.
 */
void (clear_graphics_screen)();

/**
 * @brief Draws the content from the buffer to the screen.
 */
void (draw_graphics_content)();

/**
 * @brief Reads a pixmap.
 * 
 * @param pixmap Pixmap to read.
 * @param width Pointer to store the width of the pixmap.
 * @param height Pointer to store the height of the pixmap.
 * @return Pointer to the pixmap data or NULL on failure.
 */
uint8_t *(read_pixmap)(xpm_row_t *pixmap, uint16_t *width, uint16_t *height);

/**
 * @brief Draws a sprite.
 * 
 * @param sprite Pointer to the sprite data.
 * @param x X-coordinate to draw the sprite.
 * @param y Y-coordinate to draw the sprite.
 * @param width Width of the sprite.
 * @param height Height of the sprite.
 * @return 0 on success, 1 on failure.
 */
int (draw_sprite)(uint8_t *sprite, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * @brief Draws an element from a pixmap.
 * 
 * @param pixmap Pixmap to draw.
 * @param x X-coordinate to draw the element.
 * @param y Y-coordinate to draw the element.
 * @return 0 on success, 1 on failure.
 */
int (draw_element)(xpm_row_t *pixmap, uint16_t x, uint16_t y);

/**
 * @brief Loads the digit sprites into memory.
 * 
 * This function loads the digit sprites into memory from the sprite number list.
 * Each digit sprite is loaded and stored in an array for later use.
 * 
 * @return Returns 0 on success, 1 on failure.
 */
int load_digit_sprites();

/**
 * @brief Draws a digit sprite at the specified position.
 * 
 * This function draws a digit sprite at the specified position on the screen.
 * The digit to be drawn is specified by the 'digit' parameter.
 * 
 * @param digit The digit to draw (0-9).
 * @param x The x-coordinate of the top-left corner of the digit sprite.
 * @param y The y-coordinate of the top-left corner of the digit sprite.
 * @return Returns 0 on success, 1 on failure.
 */
int draw_digit(int digit, uint16_t x, uint16_t y);

#endif /* GRAPHICS_H */
