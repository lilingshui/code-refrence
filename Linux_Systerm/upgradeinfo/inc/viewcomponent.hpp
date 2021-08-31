#ifndef _VIEWCOMPONENT_H
#define _VIEWCOMPONENT_H

#pragma interface

#include "canvas.hpp"
/*#include "form.hpp"*/


/*********************************************************
*���п�������Ļ���
**********************************************************/
class ViewComponent {
 public:
  virtual ~ViewComponent();
  virtual void show();
  virtual void enable();
  virtual void disable();
  virtual void setvisible( bool visible );
  virtual bool visible();
  virtual void click();
  virtual void setfocus( bool state );
  virtual void setcanvas( class Canvas * );
  /*  virtual void SetOwner( ViewComponent * owner );*/
  virtual void setposition( struct Position pst );
  virtual int GetHight();
  virtual struct Point getposition() { return pst; };
  /*x, yΪ����ĺ�, ������, ��λ:��; */
  ViewComponent(int x = 0, int y = 0, bool enabled = false, bool visible = true);
 protected:
  class Canvas *canv;
 private:
  struct Point pst; /*���������ṹ��ֵ*/
  bool isenabled ;
  bool isvisible;
};

typedef void ( ViewComponent::*CompActive )();

#endif /*_VIEWCOMPONENT_H*/
