#include <ctype.h>
#include <assert.h>
#include "messageform.hpp"

MessageForm::MessageForm(Form *parent):
  Screen( parent ),
  warnLbl( 64, 0, (char *)"提示" )
{
  warnLbl.setcanvas(&canvas);
  addcomponent(&warnLbl, false);

  struct Point pst;
  pst.y = 18;
  pst.x = 0;
  for (int i = 0; i < LINE_LABELS; i ++){
    infoLbl[i].setposition(pst);
    infoLbl[i].settext("");
    infoLbl[i].setcanvas(&canvas);
    addcomponent(&(infoLbl[i]), false);
    pst.y += 16;
  }

  ismessageshow = false;
  _info = 0;
  page_count = 0;
  m_bQuickQuit = true;
}

void MessageForm::SetInfo()
{
  char tmp[30];
  unsigned int max_labelsize = 20;

  /*sender->canvas.clear();*/

  for (int i = 0; i < LINE_LABELS; i ++) {
    infoLbl[i].settext("");
  }


  char * tmp_str = _info + page_count * MAX_CHARS_PAGE;

  if ( ( GetLastASCIIPst( _info, page_count * MAX_CHARS_PAGE ) & 0x1 ) == 0
       && isascii( _info[page_count * MAX_CHARS_PAGE - 1] ) == 0 )
    {
      tmp_str --;
    }

  for (int i = 0;i < LINE_LABELS; i ++){
    strncpy(tmp, tmp_str, max_labelsize);
    if (strlen(tmp_str) > max_labelsize)
      {
	tmp[max_labelsize] = '\0';
	if ( ( GetLastASCIIPst( tmp, strlen( tmp ) ) & 0x1 ) == 0
	     &&	isascii( tmp[max_labelsize - 1] ) == 0 )
	  {
	    tmp[max_labelsize - 1 ] = '\0';

	    /* to inser ' ' a space char after ( max_lablesize )th chars*/
	    for ( unsigned int j = strlen( tmp_str ) + 1; j >= max_labelsize; j -- )
	    {
		    tmp_str[j] = tmp_str[j - 1];
	    }
	    tmp_str[max_labelsize - 1] = ' ';
	  }

	  tmp_str += max_labelsize;
      }
    else {
      infoLbl[i].settext(tmp);
      break;
    }
    infoLbl[i].settext(tmp);
  }

  ismessageshow = true;
}

void MessageForm::setmessage(const char *info)
{
  if ( _info != 0 )
    {
      delete[] _info;
    }

  _info = new char[strlen( info ) + ( strlen( info ) / MAX_CHARS_PAGE ) * LINE_LABELS + 20];

  strcpy( _info, "    " );

  strcat( _info, info );
  page_count = 0;
}

void MessageForm::key_up()
{
  if ( page_count > 0 )
    page_count --;

  SetInfo();
  show();
}

void MessageForm::key_down()
{
  if ( ( page_count + 1 ) * MAX_CHARS_PAGE < strlen( _info ) )
    {
      page_count ++;
    }
  SetInfo();
  show();
}


void MessageForm::keydown(enum KEYS keystate)
{

  switch (keystate) {
  case KEY_CANCEL:
  case KEY_ENTER:
    disable();
    break;
  default:
    Form::keydown( keystate );
    break;
  }
}

void MessageForm::DisableQuickQuit()
{
	m_bQuickQuit = false;
}


void MessageForm::enable()
{
  /*  canvas.set(0, 32, 160, 96);*/
  ismessageshow = false;
  if ( Form::current != NULL &&
       Form::current != this )
    {

      setparent( Form::current );
    }

	SetInfo();
	Form::enable();

	if (m_bQuickQuit)
	{
		return;
	}

	m_bQuickQuit = true;
	enum KEYS key;
	for( ;; )
    {
		key = keyboard->OnKeyDown();
		if (KEY_ENTER == key || KEY_CANCEL == key)
		{
			disable();
			break;
		}
		else
		{
			Form::current->keydown( key );
		}
    }
}

void MessageForm::show()
{
  /* canvas.drawline(0, -1, 160, -1, BLACK);*/
  /* canvas.drawline(0, 97, 160, 97, BLACK);*/
  Form::show();
}

void MessageForm::settitle(const char * info )
{
  if ( strlen( info ) < 20 )
    {
      warnLbl.setposition( ( 160 - 8 * strlen( info )) / 2, 0 );
    }
  else
    {
      warnLbl.setposition( 0, 0 );
    }
  warnLbl.settext( info );
}

void MessageForm::disable()
{
  delete[] _info;
  _info = 0;
  Form::current = parent;
  Form::current->show();
}


/************************************************************
* 获得最后一个ASCII码字符所在的位置
* 如果该字符串不存在ASCII字符，返回-1，
************************************************************/
int GetLastASCIIPst( char * const str, unsigned int chars )
{
  assert( str != 0 );

  int i;
  for ( i = chars - 1; i >= 0; i -- )
    {
      if ( isascii( str[i] ) != 0 )
	break;
    }

  return i;
}


MessageForm messagebox;
