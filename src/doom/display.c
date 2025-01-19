#ifdef HAVE_BAGL
#include "doom/display.h"

uint8_t const bit_mask[] = {128, 64, 32, 16, 8, 4, 2, 1};

unsigned char *get_bitmap_buffer(uint8_t x) {
    if (x < DOOM_BITMAP_WIDTH)
        return DOOM_BITMAP1;
    else if (x < DOOM_BITMAP_WIDTH * 2)
        return DOOM_BITMAP2;
    else if (x < DOOM_BITMAP_WIDTH * 3)
        return DOOM_BITMAP3;
    else
        return DOOM_BITMAP4;
}

void fps() {
    lastFrameTime += 100;
}

double getActualFps() {
    return 1000 / (FRAME_TIME * delta);
}

void drawBitmap(int8_t x, int8_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint8_t color) {
    int16_t byteWidth = (w + 7) / 8;  // Bitmap scanline pad = whole byte
    uint8_t b = 0;

    for (int16_t j = 0; j < h; j++, y++) {
        for (int16_t i = 0; i < w; i++) {
            if (i & 7)
                b <<= 1;
            else
                b = bitmap[j * byteWidth + i / 8];
            if (b & 0x80) {
                drawPixel(x + i, y, color);
            }
        }
    }
}

bool getGradientPixel(uint8_t x, uint8_t y, uint8_t i) {
    if (i == 0) return 0;
    if (i >= GRADIENT_COUNT - 1) return 1;

    uint8_t index =
        MAX(0, MIN(GRADIENT_COUNT - 1, i)) * GRADIENT_WIDTH * GRADIENT_HEIGHT  // gradient index
        + y * GRADIENT_WIDTH % (GRADIENT_WIDTH * GRADIENT_HEIGHT)              // y byte offset
        + x / GRADIENT_HEIGHT % GRADIENT_WIDTH;                                // x byte offset

    // return the bit based on x
    return READ_BIT(gradient[index], x % 8);
}

void fadeScreen(uint8_t intensity, bool color) {
    for (uint8_t x = 0; x < BAGL_WIDTH; x++) {
        for (uint8_t y = 0; y < BAGL_HEIGHT; y++) {
            if (getGradientPixel(x, y, intensity)) drawPixel(x, y, color);
        }
    }
}

void drawPixel(uint8_t x, uint8_t y, bool color) {
    // prevent write out of screen buffer
    if (x < 0 || x >= BAGL_WIDTH || y < 0 ||
        y >= RENDER_HEIGHT) {
        return;
    }

    unsigned char *bitmap = get_bitmap_buffer(x);
    int pixel_index = GET_PIXEL_INDEX(x,y);

    if (color) {
        bitmap[pixel_index] |= (1 << (x % 8));
    } else {
        bitmap[pixel_index] &= ~(1 << (x % 8));
    }
}

void drawVLine(uint8_t x, int8_t start_y, int8_t end_y, uint8_t intensity) {
    int8_t y;
    int8_t lower_y = MAX(MIN(start_y, end_y), 0);
    int8_t higher_y = MIN(MAX(start_y, end_y), RENDER_HEIGHT - 1);
    uint8_t c;

    y = lower_y;
    while (y <= higher_y) {
        for (c = 0; c < RES_DIVIDER; c++) {
            // bypass black pixels
            if (getGradientPixel(x + c, y, intensity)) {
                drawPixel(x + c, y, true);
            }
        }

        y++;
    }
}

void drawSprite(int8_t x,
                int8_t y,
                const uint8_t bitmap[],
                const uint8_t mask[],
                int16_t w,
                int16_t h,
                uint8_t sprite,
                double distance) {
    uint8_t tw = (double) w / distance;
    uint8_t th = (double) h / distance;
    uint8_t byte_width = w / 8;
    uint8_t pixel_size = fmax(1, 1.0 / distance);
    uint16_t sprite_offset = byte_width * h * sprite;

    bool pixel;
    bool maskPixel;

    // Don't draw the whole sprite if the anchor is hidden by z buffer
    // Not checked per pixel for performance reasons
    if (zbuffer[MIN(MAX(x, 0), ZBUFFER_SIZE - 1) / Z_RES_DIVIDER] <
        distance * DISTANCE_MULTIPLIER) {
        return;
    }

    for (uint8_t ty = 0; ty < th; ty += pixel_size) {
        // Don't draw out of screen
        if (y + ty < 0 || y + ty >= RENDER_HEIGHT) {
            continue;
        }

        uint8_t sy = ty * distance;  // The y from the sprite

        for (uint8_t tx = 0; tx < tw; tx += pixel_size) {
            uint8_t sx = tx * distance;  // The x from the sprite
            uint16_t byte_offset = sprite_offset + sy * byte_width + sx / 8;

            // Don't draw out of screen
            if (x + tx < 0 || x + tx >= BAGL_WIDTH) {
                continue;
            }

            maskPixel = READ_BIT(mask[byte_offset], sx % 8);

            if (maskPixel) {
                pixel = READ_BIT(bitmap[byte_offset], sx % 8);
                for (uint8_t ox = 0; ox < pixel_size; ox++) {
                    for (uint8_t oy = 0; oy < pixel_size; oy++) {
                        drawPixel(x + tx + ox, y + ty + oy, pixel);
                    }
                }
            }
        }
    }
}

#endif
