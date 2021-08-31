/*********************************************************************************
*
*    form.cpp  WFET1000 Project V1.0
*    2003/06/10	V1.0	Fanlvu
*    2003/09/02   V1.1	Fanlvu	WFET2000S的输入按键增加到6个: 上下左右+确认+退出
*    2004/04/01   V1.2 Fanlvu WFET1000D的界面支持
*    Note: 要在每个窗口控件的按键处理涵数中增加对左, 右按键的处理
*
**********************************************************************************/

#ifndef _FORM_H
#define _FORM_H

#pragma interface

#include <vector>
#include <string>

#include "viewcomponent.hpp"

#include "types.hpp"
#include "label.hpp"
#include "canvas.hpp"
#include "keyboardManage.hpp"


const int MAX_HINT_LEN = 30;

/***************************************************
*窗口组件: 负责接收输入设备消息, 管理所属组件行为
* 2003/09/02 增加处理左右按键的涵数, tableft(), tabright()
****************************************************/
class Form : public ViewComponent {
public:
  Form(Form* = NULL);
  virtual ~Form();
  virtual void show();
  virtual void fresh(){};            /*显示刷新*/
  /*  virtual void close();*/
  virtual void enable();           /*窗口使能函数*/
  virtual void disable();          /*退回到上级窗口*/
  virtual void keydown( enum KEYS ); /*键盘消息处理函数*/
  virtual void key_enter();			   /*"确认"按键响应涵数 */
  virtual bool IsLastShow();
  virtual bool IsFirstShow();
  void addcomponent( ViewComponent *  cmpnt, bool tab); /*添加组件, tab 为真时, 添加的组件可以出于被选择状态*/
  void delcomponent( ViewComponent *  cmpnt); /*删除组件*/
  void clearcomponents();                   /*清除所有组件 */
  void setparent( Form *  );                    /*设置父窗口*/
  Form * getparent()
  {
    return parent;
  };
  void settaborder( unsigned int order );     /*设置窗口处于被选中状态的组件, order: 组件序号*/
  void nofocus();                          /*使窗口中所有组件都出于非选中状态*/
  unsigned int gettaborder();              /*获得处于被选择状态的组件序号*/
  ViewComponent * getfocusObj();            /*获得处于被选择状态的组件对象指针*/
  Canvas canvas;                           /*窗口画布*/
  static class Form* current;              /*当前激活窗口对象指针*/
  bool isfromchild;                        /*isformchild 为真时 表示窗口由子窗口切换而来*/
  bool succeeded;

  void sethint( const char * txt );        /* 设置窗口的提示信息*/
  const char * gethint( )		   /* 获得窗口的提示信息*/
  {
    return hint;
  }


  static  int iKeyNullCount  ;
protected:
  Form* parent;                           /*父窗口对象指针*/
  virtual void key_down();                          /*"上"按键响应涵数*/
  virtual void key_up();                            /*"下"按键响应涵数*/
  virtual void key_left();			   /*"左"按键响应涵数 */
  virtual void key_right();			   /*"右"按键响应涵数*/
  virtual void key_cancel();			   /*"取消"按键响应涵数*/
  virtual void key_null(){ iKeyNullCount ++; };			   /*"无效"按键响应函数 */
  static void CloseForm( Form * form );	/* 关闭窗体并将form 所占空间释放掉*/
private:
  unsigned int taborder;
  std::vector< ViewComponent *  > components;
  std::vector< ViewComponent *  > tabcomponents;
  char hint[MAX_HINT_LEN];                           /*窗口的提示信息*/
  /*  void JudgeAndSetWindow();*/

};


#endif /*_FORM_H */
