/*********************************************************************************
*
*    form.cpp  WFET1000 Project V1.0
*    2003/06/10	V1.0	Fanlvu
*    2003/09/02   V1.1	Fanlvu	WFET2000S�����밴�����ӵ�6��: ��������+ȷ��+�˳�
*    2004/04/01   V1.2 Fanlvu WFET1000D�Ľ���֧��
*    Note: Ҫ��ÿ�����ڿؼ��İ��������������Ӷ���, �Ұ����Ĵ���
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
*�������: ������������豸��Ϣ, �������������Ϊ
* 2003/09/02 ���Ӵ������Ұ����ĺ���, tableft(), tabright()
****************************************************/
class Form : public ViewComponent {
public:
  Form(Form* = NULL);
  virtual ~Form();
  virtual void show();
  virtual void fresh(){};            /*��ʾˢ��*/
  /*  virtual void close();*/
  virtual void enable();           /*����ʹ�ܺ���*/
  virtual void disable();          /*�˻ص��ϼ�����*/
  virtual void keydown( enum KEYS ); /*������Ϣ������*/
  virtual void key_enter();			   /*"ȷ��"������Ӧ���� */
  virtual bool IsLastShow();
  virtual bool IsFirstShow();
  void addcomponent( ViewComponent *  cmpnt, bool tab); /*������, tab Ϊ��ʱ, ��ӵ�������Գ��ڱ�ѡ��״̬*/
  void delcomponent( ViewComponent *  cmpnt); /*ɾ�����*/
  void clearcomponents();                   /*���������� */
  void setparent( Form *  );                    /*���ø�����*/
  Form * getparent()
  {
    return parent;
  };
  void settaborder( unsigned int order );     /*���ô��ڴ��ڱ�ѡ��״̬�����, order: ������*/
  void nofocus();                          /*ʹ������������������ڷ�ѡ��״̬*/
  unsigned int gettaborder();              /*��ô��ڱ�ѡ��״̬��������*/
  ViewComponent * getfocusObj();            /*��ô��ڱ�ѡ��״̬���������ָ��*/
  Canvas canvas;                           /*���ڻ���*/
  static class Form* current;              /*��ǰ����ڶ���ָ��*/
  bool isfromchild;                        /*isformchild Ϊ��ʱ ��ʾ�������Ӵ����л�����*/
  bool succeeded;

  void sethint( const char * txt );        /* ���ô��ڵ���ʾ��Ϣ*/
  const char * gethint( )		   /* ��ô��ڵ���ʾ��Ϣ*/
  {
    return hint;
  }


  static  int iKeyNullCount  ;
protected:
  Form* parent;                           /*�����ڶ���ָ��*/
  virtual void key_down();                          /*"��"������Ӧ����*/
  virtual void key_up();                            /*"��"������Ӧ����*/
  virtual void key_left();			   /*"��"������Ӧ���� */
  virtual void key_right();			   /*"��"������Ӧ����*/
  virtual void key_cancel();			   /*"ȡ��"������Ӧ����*/
  virtual void key_null(){ iKeyNullCount ++; };			   /*"��Ч"������Ӧ���� */
  static void CloseForm( Form * form );	/* �رմ��岢��form ��ռ�ռ��ͷŵ�*/
private:
  unsigned int taborder;
  std::vector< ViewComponent *  > components;
  std::vector< ViewComponent *  > tabcomponents;
  char hint[MAX_HINT_LEN];                           /*���ڵ���ʾ��Ϣ*/
  /*  void JudgeAndSetWindow();*/

};


#endif /*_FORM_H */
