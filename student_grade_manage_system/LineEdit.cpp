#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h) :Basc(x, y, w, h)
{

}

void LineEdit::show()
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextcolor(BLACK);
	settextstyle(20, 0, "ËÎÌו");
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;

	::outtextxy(m_x + 5, ty, m_text.c_str());

	if (isClicked())
	{
		char buf[128];
		InputBox(buf, 128, m_hitText.data(), m_title.data());
		if (buf[0] != '\0')
			m_text = buf;
	}
}

bool LineEdit::textChange()
{
	if (m_prevText == m_text)
	{
		return false;
	}
	m_prevText = m_text;
	return true;
}


