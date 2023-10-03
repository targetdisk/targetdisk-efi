#ifndef CODEC_H
#define CODEC_H

#include "uefi/uefi.h"
#include "gfx.h"

#define RGBA2ARGB_32(pixel)  ( ( pixel << 24 ) + ( pixel >> 8 ) )

void rle_decompress(pixmap_t *pixmap);
void rle1_decompress(pixmap_t *pixmap);
void decompress(pixmap_t *pixmap);

#endif /* CODEC_H */
