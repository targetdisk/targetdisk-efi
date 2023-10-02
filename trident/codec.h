#ifndef CODEC_H
#define CODEC_H

#include "uefi/uefi.h"
#include "gfx.h"

void rle_decompress(pixmap_t *pixmap);
void rle1_decompress(pixmap_t *pixmap);
void decompress(pixmap_t *pixmap);

#endif /* CODEC_H */
