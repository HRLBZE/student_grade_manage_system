#include "Basc.h"

Basc::Basc(int x, int y, int w, int h) :m_x(x), m_y(y), m_w(w), m_h(h)
{

}

int Basc::width()
{
	return m_w;
}

int Basc::height()
{
	return m_h;
}

void Basc::setFixSize(int w, int h)
{
	this->m_h = h;
	this->m_w = w;
}

int Basc::x()
{
	return m_x;
}

int Basc::y()
{
	return m_y;
}

void Basc::mov(int x, int y)
{
	this->m_x = x;
	this->m_y = y;
}


bool Basc::isin()
{
	auto& m_msg = Window::getMsg();
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
		return true;
	return false;
}

bool Basc::isClicked()
{
	if (isin())
	{
		auto& m_msg = Window::getMsg();
		if (m_msg.message == WM_LBUTTONDOWN)
		{
			return true;
		}
	}
	return false;
}

void Basc::event()
{

	if (!isin())
	{
		cur_c = normal_c;
	}
	else
		cur_c = hover_c;
}

void Basc::setBack(COLORREF c)
{
	normal_c = c;
}

void Basc::setHover(COLORREF c)
{
	hover_c = c;
}