#pragma once
#include "Basc.h"
#include "Panorama.h"
#include<vector>
#include "Button.h"

class Table :
	public Basc
{
	int m_gridW;
	int m_gridH;
	int m_tw;
	int m_th;
	int m_curPage;
	int m_maxPage;
	int m_extraData;
	Button* m_prevBtn;
	Button* m_nextBtn;
	Button* m_firstBtn;
	Button* m_lastBtn;



	int m_rows;
	int m_cols;
	std::string m_header;
	std::vector<std::string> m_datas;
public:
	Table(int row = 0, int col = 0);
	~Table();
	void setRow(int row);
	void setCol(int col);
	void show();
	void setHeard(const std::string& head);
	void drawTableG();
	void drwaTableD();
	void updatePage();
	void drawButton();
	void drawHeader();
	int rowCount()const { return m_datas.size(); }
	int colCount()const { return m_cols; }
	void clear() { m_datas.clear(); }
	std::vector<std::string> split(std::string str, char separator = '\t');
	void insertD(const std::string& data);
	void event() override;
};

