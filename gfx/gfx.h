#ifndef GFX_H
#define GFX_H
#include "uefi/uefi.h"

#include "pixmap.h"

void fillScreen( uint32_t color, efi_gop_mode_t *mode );
void drawTrident( efi_gop_mode_t *mode, pixmap_t *pixmap );
void blitPixmap( uint32_t x, uint32_t y, efi_gop_mode_t *mode, pixmap_t *pixmap );

#endif /* GFX_H */
