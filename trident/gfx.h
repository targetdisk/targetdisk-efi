#ifndef GFX_H
#define GFX_H
#include "uefi/uefi.h"
enum imgdata_type { RAW, RLE, RLE1 };

typedef struct pixmap_s {
  uint32_t width;
  uint32_t height;
  size_t n_pixels;
  char datatype;
  uint32_t *data;
} pixmap_t;

void fillScreen( uint32_t color, efi_gop_mode_t *mode );
void drawTrident( efi_gop_mode_t *mode, pixmap_t *pixmap );
void blitPixmap( uint32_t x, uint32_t y, efi_gop_mode_t *mode, pixmap_t *pixmap );

#endif /* GFX_H */
