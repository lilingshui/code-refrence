#pragma implementation "label.hpp"
#include <string.h>
#include <stdarg.h>
#include <sys/wait.h>

#include "label.hpp"

Label::Label(unsigned int x, unsigned int y, const char * txt)
{
  startpst.y = y;
  startpst.x = x;
  endpst.x = x + 2;
  focused = false;
  if (txt) {
    unsigned int wid = strlen(txt);
    text = ( char * ) malloc( wid + 1 );
    maxlen = wid + 1;
    if ( !text ) {
      perror( "can not get free memory in Label init\n" );
      exit( -1 );
    }

    strcpy( text, txt );
    endpst.y = startpst.y + wid;
  }
  else {
    text = NULL;
    maxlen = 0;
    endpst.y = startpst.y;
    endpst.x = startpst.x;
  }

  /* set default font type*/
  font = &Font16;
}

Label::~Label( )
{
  if ( text ) {
    free( text );
  }
}

void Label::SetFontType( enum FONTTYPE type )
{

  switch( type ) {
  case FONT12:
    font = &Font12;
    break;
  case FONT16:
    font = &Font16;
    break;
  default:
    font = &Font16;
    break;
  }

  endpst.y = font->GetHight();
  font->SetCanvas( canv );
}


void Label::settext(const char * txt)
{
	if (!txt)
	{
		return;
	}

	unsigned int wid = strlen(txt);
	if ( text )
	{
		if ( maxlen > (int)wid )
		{
			strcpy(text, txt);
			endpst.x = startpst.x + wid * font->CharWidth();
			return;
		}
		else
		{
			free( text );
		}
	}
	text = ( char * ) malloc( wid + 1 );
	maxlen = wid + 1;
	if ( !text )
	{
		perror( "can not get free memory in Label init\n" );
		exit( -1 );
	}

	strcpy( text, txt );
	endpst.x = startpst.x + wid * font->CharWidth();
	return;
}

void Label::setfmttext( char *fmt, ... )
{
	char txt[64];
	va_list ap;
	memset(txt, '\0', 64);
	va_start( ap, fmt );
	vsprintf( txt, fmt, ap );
	va_end( ap );

	unsigned int wid = strlen(txt);
	if ( text )
	{
		if( maxlen > (int)wid )
		{
			strcpy(text, txt);
			endpst.x = startpst.x + wid * font->CharWidth();
			return;
		}
		else
		{
			free( text );
		}
	}
	text = ( char * ) malloc( wid + 1 );
	maxlen = wid + 1;
	if( !text )
	{
		perror( "can not get free memory in Label init\n" );
		exit( -1 );
	}
	strcpy( text, txt );
	endpst.x = startpst.x + wid * font->CharWidth();
	return;
}

void Label::setvalue( int value)
{
	char tmp[12];
	sprintf(tmp, "%d", value);
	settext(tmp);
}

void Label::setvalue( long value)
{
	char tmp[20];
	sprintf(tmp, "%ld", value);
	settext(tmp);
}

void Label::setvalue( float value)
{
	char tmp[20];
	sprintf(tmp, "%.2f", value);
	settext(tmp);
}

void Label::setvalue( double value)
{
	char tmp[20];
	sprintf(tmp, "%.2f", value);
	settext(tmp);
}

void Label::center()
{
	int x =( 160 - 8*(int)strlen(text) )/2;
	if(x<0||x>159)
	{
		x = 0;
	}
  	endpst.x = x + endpst.x - startpst.x;
  	startpst.x = x;
}

void Label::right()
{
	int x = 160 - 8*(int)strlen(text) ;
	if(x<0||x>159)
	{
		x = 0;
	}
  	endpst.x = x + endpst.x - startpst.x;
  	startpst.x = x;
}

void Label::setfocus(bool state)
{
  focused = state;
}

char * Label::gettext( )
{
  return text;
/*   strcpy(txt, text);*/
}

void Label::setcanvas( Canvas* canvas )
{
  ViewComponent::setcanvas( canvas );
  font->SetCanvas( canvas );
}

void Label::setposition( struct Point pst )
{
  endpst.y = pst.y + endpst.y - startpst.y;
  endpst.x = pst.x + endpst.x - startpst.x;

  startpst.x = pst.x;
  startpst.y = pst.y;
}

void Label::setposition( int x, int y )
{
  endpst.y = y + endpst.y - startpst.y;
  endpst.x = x + endpst.x - startpst.x;

  startpst.x = x;
  startpst.y = y;
}


void Label::show()
{
  if (!canv){
    return;
  }

  font->SetCanvas( canv );
  font->TextOut( startpst.x, startpst.y, text,  focused );
/*   canv->drawfont(startpst, text, BLACK);*/
   if (focused){
     /*canv->Reverse( startpst, endpst);*/
   }

}

void Label::enable()
{
/*   if (!focused) {*/
/*     canv->reverse(startpst, endpst);*/
/*   }*/
  focused = true;
}

void Label::disable()
{
/*   if(focused){*/
/*     canv->reverse(startpst, endpst);*/
/*   }*/

  focused = false;

}

