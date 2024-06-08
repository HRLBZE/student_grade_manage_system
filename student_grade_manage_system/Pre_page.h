#pragma once
#include"Admin.h"
#include "Window.h"
#include<vector>
#include"Button.h"



class Pre_page
{
	enum number
	{
		teacher,
		student,
		init
	};
	ExMessage m_msg;
	IMAGE pre;
	std::vector<Button*>menu_btns;

public:
	Pre_page();
	void run();

	void drawBack();
	int init_button();
};

