#include "uefi/uefi.h"

#include "codec/codec.h"
#include "gfx/gfx.h"
#include "gfx/img_data.h"

int main( int argc, char **argv )
{
  efi_status_t status;
  efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  efi_gop_t *gop = NULL;
  efi_gop_mode_info_t *info = NULL;

  uintn_t isiz = sizeof( efi_gop_mode_info_t ), i;

  status = BS->LocateProtocol( &gopGuid, NULL, (void**)&gop );
  if ( EFI_ERROR( status ) || !gop )
  {
      fprintf( stderr, "unable to get graphics output protocol\n" );
      return 1;
  }

  /* if mode given on command line, set it */
  if ( argc > 1 )
  {
      status = gop->SetMode( gop, atoi( argv[1] ) );
      /* changing the resolution might mess up ConOut and StdErr, better to reset them */
      ST->ConOut->Reset( ST->ConOut, 0 );
      ST->StdErr->Reset( ST->StdErr, 0 );
      if ( EFI_ERROR( status ) )
      {
          fprintf( stderr, "unable to set video mode\n" );
          return 0;
      }
  }
  /* we got the interface, get current mode */
  status = gop->QueryMode( gop, gop->Mode ? gop->Mode->Mode : 0, &isiz, &info );
  if ( status == EFI_NOT_STARTED || !gop->Mode )
  {
      status = gop->SetMode( gop, 0 );
      ST->ConOut->Reset( ST->ConOut, 0 );
      ST->StdErr->Reset( ST->StdErr, 0 );
  }

  if ( EFI_ERROR( status ) )
  {
      fprintf( stderr, "unable to get current video mode\n" );
      return 1;
  }

  decompress(&trident);

  for ( i = 0; i < 24; i++ )
  {
    fillScreen( 0x616db8, gop->Mode );
    drawTrident(gop->Mode, &trident);
    sleep( 1 );
  }

  return 0;
}
