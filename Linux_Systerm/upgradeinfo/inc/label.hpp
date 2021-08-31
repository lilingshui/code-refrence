#ifndef _LABEL_HPP
#define _LABEL_HPP
#pragma interface

#include "canvas.hpp"
#include "viewcomponent.hpp"
#include "canvas.hpp"

#include "font.hpp"

/************************************
*�������, ��ʾ������Ϣ
************************************/
class Label : public ViewComponent {
public:
  Label( unsigned int x = 0, unsigned int y = 0, const char* txt = 0 );
  ~Label();
  void settext( const char* );
  void setfmttext( char *fmt, ... );
  void setvalue( int value);
  void setvalue( long value);
  void setvalue( float value);
  void setvalue( double value);
  char * gettext();
  void SetFont( enum FONTTYPE type );
  void show();
  virtual void enable();
  virtual void disable();
  void setcanvas( Canvas* sender ); /*���û���*/
  void setfocus( bool state );/*ʹ���ַ�����ʾ*/
  void setposition( struct Point pst ); /*��������λ��*/
  void setposition( int x, int y );
  void center();/*������ʾ�ַ�����ֻ����������Ϊ16���ַ���*/
  void right();/*������ʾ*/
  int GetHight()
  {
    return font->GetHight();
  }

  struct Point getposition()
  {
    return startpst;
  };
  void SetFontType( enum FONTTYPE );
  int GetFontHight( )
  {
    return font->GetHight();
  };
  enum FONTTYPE GetFontType()
  {
    return font->GetType();
  };

private:
  struct Point startpst;
  struct Point endpst;
  char * text;
  int maxlen;			/* dynamic allocatimg area length*/
  bool focused;
  Font * font;
  /*  class Canvas* canv;*/
};

#endif /*_LABEL_HPP*/
