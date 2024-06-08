#include "Pre_page.h"
#include "Admin.h"
#include<conio.h>
#include<iostream>

using namespace std;

Pre_page::Pre_page()
{
	::loadimage(&pre, "./picture/pre.png", Window::width(), Window::height());
	menu_btns.push_back(new Button("teacher"));
	menu_btns.push_back(new Button("student"));

	menu_btns[0]->setFixSize(200, 50);
	menu_btns[1]->setFixSize(200, 50);
	int bx1 = Window::width() / 3;
	int by1 = Window::height() / 3 * 2;
	int bx2 = bx1 * 2;

	menu_btns[0]->mov(bx1 - 180, by1);
	menu_btns[1]->mov(bx2, by1);
}

void Pre_page::run()
{
	int i = init;
	Window::beginDraw();
	while (true)
	{
		Window::clear();
		drawBack();
		::settextstyle(20, 0, "ËÎÌו");
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN:
			{
				if (m_msg.vkcode == VK_ESCAPE)
				{
					i = init_button();
				}
				break;
			}
			default:

				break;
			}

		}

		switch (i)
		{
		case Pre_page::student:
		{
			Student a;
			a.run_student();
			break;
		}
		case Pre_page::teacher:
		{
			Teacher ar;
			ar.run_teacher();
			break;
		}
		case Pre_page::init:
		{
			i = init_button();
			break;
		}
		default:
			break;
		}
		Window::flushDraw();
	}
	Window::endDraw();
}


void Pre_page::drawBack()
{
	::putimage(0, 0, &pre);
}

int Pre_page::init_button()
{

	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	return init;
}

