#ifndef _VIEWCOMPONENT_H
#define _VIEWCOMPONENT_H

#pragma interface

#include "canvas.hpp"
/*#include "form.hpp"*/


/*********************************************************
*所有可视组件的基类
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
  /*x, y为组件的横, 纵坐标, 单位:点; */
  ViewComponent(int x = 0, int y = 0, bool enabled = false, bool visible = true);
 protected:
  class Canvas *canv;
 private:
  struct Point pst; /*组件的坐标结构化值*/
  bool isenabled ;
  bool isvisible;
};

typedef void ( ViewComponent::*CompActive )();

#endif /*_VIEWCOMPONENT_H*/
