#include<iostream>
#include"Pre_page.h"
#include "Window.h"

int main()
{
	Window win(960, 640, EX_SHOWCONSOLE);
	win.setwindowtitle("ѧ���ɼ�����ϵͳ");
	Pre_page a;
	a.run();
	return 0;
}