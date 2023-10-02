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
inline int bounded_rand( int lower, int upper )
{
  return ( rand() % ( upper - lower + 1 ) ) + lower;
}

void blitPixmap( uint32_t x, uint32_t y, efi_gop_mode_t *mode, pixmap_t *pixmap )
{
  uint32_t nlines,
           *src = pixmap->data,
           *dst = (uint32_t *)mode->FrameBufferBase
                  + ( y * mode->Information->PixelsPerScanLine * sizeof(uint32_t) )
                  + ( x * sizeof(uint32_t) );

  size_t npixels = ( ( x + pixmap->width ) < mode->Information->PixelsPerScanLine )
                           ? pixmap->width
                           : mode->Information->PixelsPerScanLine - ( x + pixmap->width );

  size_t nbytes = sizeof(uint32_t) * npixels;

  for ( nlines = ( ( y + pixmap->width ) < mode->Information->VerticalResolution )
                          ? pixmap->width : ( mode->Information->VerticalResolution - y );
        nlines; nlines-- )
  {
    memcpy((void *)dst, (void *)src, nbytes);
    dst += ( mode->Information->PixelsPerScanLine - npixels );
  }
}

void drawTrident( efi_gop_mode_t *mode, pixmap_t *pixmap )
{
  int x = (uint32_t)bounded_rand( 0, mode->Information->HorizontalResolution - pixmap->width ),
      y = (uint32_t)bounded_rand( 0, mode->Information->VerticalResolution - pixmap->height );


  blitPixmap( x, y, mode, pixmap );
}
