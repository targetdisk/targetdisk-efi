#include <errno.h>
#include "uefi/uefi.h"
#include "gfx.h"

#ifndef RLE1_ONLY
void rle_decompress(pixmap_t *pixmap) {
  uint32_t *rledata = pixmap->data;
  uint32_t *rawdata = malloc(sizeof(uint32_t) * pixmap->n_pixels);
  if (rawdata) {
    pixmap->data = rawdata;
    uint32_t *pixel;
    for (size_t pi = 0; pi < pixmap->n_pixels; rledata++) {
      pixel = rledata++;
      for (uint32_t pi_end = pi + *rledata; pi < pi_end; pi++) {
        *rawdata++ = *pixel;
      }
    }
  } else {
    fprintf(stderr, "ERROR: malloc failed on pixmap data!!\n");
    exit(ENOMEM);
  }
}
#endif /* RLE1_ONLY */

static inline uint32_t *rle1_put_pixels(uint32_t pixel, size_t reps, uint32_t *rawdata) {
  for (size_t n = 0; n < reps; n++)
    *rawdata++ = pixel;
  return rawdata;
}

void rle1_decompress(pixmap_t *pixmap) {
  uint32_t *rledata = pixmap->data;
  uint32_t *fgcolor = rledata++;
  uint32_t *rawdata = malloc(sizeof(uint32_t) * pixmap->n_pixels);
  if (rawdata) {
    pixmap->data = rawdata;
    unsigned char byte;
    size_t reps;
    unsigned char packlocat = 24;
    for (size_t pi = 0; pi < pixmap->n_pixels;) {
      byte = (unsigned char)(*rledata >> packlocat);
      reps = (size_t)(byte & 127);
      pi += reps;
      rawdata = rle1_put_pixels((byte >> 7 ? *fgcolor : 0), reps, rawdata);
      if (!packlocat) {
        packlocat = 24;
        rledata++;
      } else {
        packlocat -= 8;
      }
    }
  } else {
    fprintf(stderr, "ERROR: malloc failed on pixmap data!!\n");
    exit(ENOMEM);
  }
}

void decompress(pixmap_t *pixmap) {
  switch (pixmap->datatype) {
    case RAW:
      return;
#ifndef RLE1_ONLY
    case RLE:
      rle_decompress(pixmap);
      return;
#endif /* RLE1_ONLY */
    case RLE1:
      rle1_decompress(pixmap);
      return;
    default:
      fprintf(stderr, "ERROR: image data type not implemented!!\n");
      exit(EPROTONOSUPPORT);
  }
}
