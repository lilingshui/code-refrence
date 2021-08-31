#include "graphics.hpp"
#pragma implementation "font.hpp"
#include "font.hpp"

/* Font ASCII168Font, ASCII128Font;*/
/* Font HZ1616Font, HZ1212Font;*/
/* Font ASCII168Font( ASCII16 );*/
/* Font ASCII128Font( ASCII12 );*/
/* Font ASCII88Font( ASCII8 );*/
/* Font HZ1616Font( HZ16 );*/
/* Font HZ1212Font( HZ12 );*/


Font Font16( FONT16 );
Font Font12( FONT12 );

struct FontAttr Font::attrib[] = {
  { 16, 16, 8, (char *)"/usr/fonts/myhzk1616", (char *)"/usr/fonts/myascii168" }, 
  { 12, 12, 8, (char *)"/usr/fonts/myhzk1212", (char *)"/usr/fonts/myascii128" }, 
};

Font::Font( enum FONTTYPE type ):
  asciibit( 12, 8 ),
  hzbit( 12, 12 )
{
  SetType( type );
}

bool Font::SetType(  enum FONTTYPE type )
{
  _type = type;
  hz_x = attrib[type].hz_width;
  ascii_x = attrib[type].ascii_width;
  y = attrib[type].hight;

  hzbit.SetXYBits( hz_x, y );
  hzbit.SetFile( attrib[type].hz_filename );
  asciibit.SetXYBits( ascii_x, y );
  asciibit.SetFile( attrib[type].ascii_filename );
/*   switch ( type ) {*/
/*   case ASCII8:*/
/*     X = 8, Y = 8;*/
/*     matrixbit.SetXYBits( 8, 8 );*/
/*     matrixbit.SetFile( "/usr/fonts/myascii88" );*/
/*     break;*/
/*   case ASCII16:*/
/*     X = 8, Y = 16;*/
/*     matrixbit.SetXYBits( 8, 16 );*/
/*     matrixbit.SetFile( "/usr/fonts/myascii168" );*/
/*     break;*/
/*   case HZ16:*/
/*     X = 16, Y = 16;*/
/*     matrixbit.SetXYBits( 16, 16 );*/
/*     matrixbit.SetFile( "/usr/fonts/myhzk1616" );*/
/*     break;*/
/*   case ASCII12:*/
/*     X = 8, Y = 12;*/
/*     matrixbit.SetXYBits( 8, 12 );*/
/*     matrixbit.SetFile( "/usr/fonts/myascii128" );*/
/*     break;*/
/*   default:*/
/*     X = 12, Y = 12;*/
/*     matrixbit.SetXYBits( 12, 12 );*/
/*     matrixbit.SetFile( "/usr/fonts/myhzk1212" );*/
/*     break;*/
/*   }*/

  return true;
}

bool Font::TextOut( int x, int y, char *ptext, bool isBlack )
{
  int offset = 0;

  if ( !ptext ) {
    /*printf( "text is null \n" );*/
    return false;
  }

  while( *ptext ) {
    if ( ptext[0] < 128 ) {
      offset = ptext[0];
      asciibit.SetOffset( offset );
      asciibit.Draw( x, y, isBlack );
      x += ascii_x;
    }
    else {

      if ( !ptext[1] ) {
	return false;
      }
      offset = ( ptext[0] - 1 - 0xa0 ) * 94L + ptext[1] - 1 - 0xa0 ;
      ptext ++;
      hzbit.SetOffset( offset );
      hzbit.Draw( x, y, isBlack );
      x += hz_x;
    }
/*     if ( _type == ASCII12 || _type == ASCII16 || _type == ASCII8 ) {*/
/*       offset = ptext[0];*/
/*     }*/
/*     else {*/
/*       if ( !ptext[1] ) {*/
/* 	return false;*/
/*       } */
/*       offset = ( ptext[0] - 1 - 0xa0 ) * 94L + ptext[1] - 1 - 0xa0 ;*/
/*       ptext ++;*/
/*     }*/
/*    matrixbit.SetOffset( offset );*/
/*    matrixbit.Draw( x, y, isBlack );*/

/*    x += X;*/
    ptext ++;
  }

  return true;
}

bool Font::SetFile( char * ascii_filename, char * hz_filename )
{
    return ( asciibit.SetFile( ascii_filename ) && hzbit.SetFile( hz_filename ) );
}
