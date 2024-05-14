
#include <lcom/lcf.h>
#include <stdint.h>

/**
 * @brief Initializes the video graphics mode.
 * 
 * @param mode The video mode to be set.
 * @return Pointer to the video memory if successful, NULL otherwise.
 */
void *(vg_init)(uint16_t mode);

/**
 * @brief Draws a horizontal line on the screen.
 * 
 * @param x X-coordinate of the starting point.
 * @param y Y-coordinate of the starting point.
 * @param len Length of the line.
 * @param color Color of the line.
 * @return 0 upon success, non-zero otherwise.
 */
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a rectangle on the screen.
 * 
 * @param x X-coordinate of the top-left corner.
 * @param y Y-coordinate of the top-left corner.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color of the rectangle.
 * @return 0 upon success, non-zero otherwise.
 */
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Gets the horizontal resolution of the screen.
 * 
 * @return The horizontal resolution.
 */
uint16_t (get_hres)();

/**
 * @brief Gets the vertical resolution of the screen.
 * 
 * @return The vertical resolution.
 */
uint16_t (get_vres)();

/**
 * @brief Gets the number of bytes per pixel.
 * 
 * @return The number of bytes per pixel.
 */
int (bytes_per_pixel)();

/**
 * @brief Generates a pixel at the specified position with the given color.
 * 
 * @param posX X-coordinate of the pixel.
 * @param posY Y-coordinate of the pixel.
 * @param clr Color of the pixel.
 * @return 0 upon success, non-zero otherwise.
 */
int (generate_pixel)(uint16_t posX, uint16_t posY, uint32_t clr);

/**
 * @brief Gets the color at the specified position based on a pattern.
 * 
 * @param rectangles Number of rectangles.
 * @param first_color First color.
 * @param step_size Step size.
 * @param row_index Row index.
 * @param col_index Column index.
 * @return The calculated color.
 */
uint32_t (get_color)(uint8_t rectangles, uint32_t first_color, uint8_t step_size, uint8_t row_index, uint8_t col_index);


