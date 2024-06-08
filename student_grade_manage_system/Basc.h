#pragma once
#include"Panorama.h"
#include"Window.h"

class Basc
{
protected:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	COLORREF cur_c = RGB(232, 232, 236);
	COLORREF hover_c = RED;
	COLORREF normal_c = RGB(232, 232, 236);
public:

	Basc(int x, int y, int w, int h);
	virtual ~Basc() {};
	int width();
	int height();
	void setFixSize(int w, int h);
	int x();
	int y();
	void mov(int x, int y);
	bool isin();
	bool isClicked();
	virtual void event();
	virtual void show() = 0;
	void setBack(COLORREF c);
	void setHover(COLORREF c);
};

