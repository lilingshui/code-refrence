#ifndef _MESSAGEFORM_HPP
#define _MESSAGEFORM_HPP

#include "label.hpp"
#include "screen.hpp"

/************************************************************
* 获得最后一个ASCII码字符所在的位置
************************************************************/
int GetLastASCIIPst( char * const str, unsigned int chars );

int const MAX_CHARS_PAGE = 20 * 6;
int const LINE_LABELS = 6;

class MessageForm : public Screen {
public:
  MessageForm(Form *parent = NULL);
  void setmessage(const char *info);
  void settitle(const char *info );
  void keydown(enum KEYS keystate);
  void enable();
  void disable();
  void show();
  void key_down();
  void key_up();
  /*
  *禁止messagebox被其他页面抢占，类似于闪退
  *默认是闪退的，
  */
  void DisableQuickQuit();

  bool ismessageshow;

protected:
  void SetInfo();

private:


  class Label warnLbl;
  class Label infoLbl[LINE_LABELS];
  char * _info;
  unsigned int page_count;
  bool		m_bQuickQuit;
};

extern class MessageForm messagebox;

#endif /*_MESSAGEFORM_HPP*/
