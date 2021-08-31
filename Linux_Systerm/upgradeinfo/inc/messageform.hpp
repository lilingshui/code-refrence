#ifndef _MESSAGEFORM_HPP
#define _MESSAGEFORM_HPP

#include "label.hpp"
#include "screen.hpp"

/************************************************************
* ������һ��ASCII���ַ����ڵ�λ��
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
  *��ֹmessagebox������ҳ����ռ������������
  *Ĭ�������˵ģ�
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
