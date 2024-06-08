#pragma once
#include "Basc.h"
#include<string>
#include"Panorama.h"

class Button :public Basc
{
	std::string  m_text;


public:
	Button(const std::string& text = "Button", int x = 0, int y = 0, int w = 100, int h = 40);
	void show() override;


};

