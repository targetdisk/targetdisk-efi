#include "uefi/uefi.h"

#include "gfx.h"

void fillScreen( uint32_t color, efi_gop_mode_t *mode )
{
  uint32_t *a = (uint32_t*)mode->FrameBufferBase;

  efi_physical_address_t max_addr = mode->FrameBufferBase + mode->FrameBufferSize;
  for ( ; (void *)a < (void *)max_addr; a++ )
    *a = color;
}

static
inline void putPixel_32bpp( int x, int y, uint32_t pixel, efi_gop_mode_t *mode)
{
  *((uint32_t*)(mode->FrameBufferBase + 4 * mode->Information->PixelsPerScanLine * y + 4 * x))
    = pixel;
}

static
inline int boundedRand( int lower, int upper )
{
  return ( rand() % ( upper - lower + 1 ) ) + lower;
}

void blitPixmap( uint32_t x, uint32_t y, efi_gop_mode_t *mode, pixmap_t *pixmap )
{
  uint32_t *pixel = pixmap->data;
  size_t pixcount = 0;
  while ( pixcount < pixmap->n_pixels )
  {
    if ( *pixel & 0xff )
        putPixel_32bpp( ( pixcount % pixmap->width + x ), y, 0xffe400, mode );

    pixcount++;
    pixel++;

    if ( pixcount % pixmap->width == 0 )
      y++;
  }
}

void drawTrident( efi_gop_mode_t *mode, pixmap_t *pixmap )
{
  int x = (uint32_t)boundedRand( 0, mode->Information->HorizontalResolution - pixmap->width ),
      y = (uint32_t)boundedRand( 0, mode->Information->VerticalResolution - pixmap->height );


  blitPixmap( x, y, mode, pixmap );
}
