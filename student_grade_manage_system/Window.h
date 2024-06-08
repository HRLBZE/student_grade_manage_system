#pragma once
#include "Panorama.h"
#include<string>


class Window
{
	HWND m_handle;
	inline static ExMessage m_msg;
public:
	Window(int w, int h, int flag);
	void setwindowtitle(const std::string& title);
	int exec();

	//窗口函数
	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//按键操作
	inline static bool hasMsg()
	{
		return ::peekmessage(&m_msg, EX_MOUSE | EX_KEY);
	}
	inline static  ExMessage& getMsg()
	{
		return m_msg;
	}


};

