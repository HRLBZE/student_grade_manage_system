#pragma once

#include "Window.h"
#include"Button.h"
#include<vector>
#include"Basc.h"
#include"Student_data.h"
#include"Table.h"
#include<memory>
#include"LineEdit.h"
#include<algorithm>

class Student
{
	IMAGE pic_s;
	enum number
	{
		show_all,
		find,
		nsexit,
		menu_st_num
	};

public:
	int i;
	std::string m_header;
	std::vector<std::unique_ptr<Button>>menu;
	std::vector<Student_data> vec_stu;
	std::unique_ptr<Table> m_showTable;
	std::unique_ptr<Button> m_addBtn;
	std::unique_ptr<LineEdit>m_addEdit;
	std::vector<std::unique_ptr<LineEdit>> m_stuEdits;
	std::vector<Student_data>::iterator m_modifyIt;
	std::unique_ptr<Button> m_dlBtn;
	std::unique_ptr<LineEdit>m_dlEdit;
	std::unique_ptr<Table> m_dlTable;
	std::unique_ptr<LineEdit>m_fdEdit;
	std::unique_ptr<Table> m_fdTable;
	std::unique_ptr<LineEdit>m_modifyEdit;

	Student();
	void run_student();
	int menu_st();
	void display();
	void search();
	void drawBack_s();
	void readFile(const std::string& filename);
	void saveFile(const std::string& filename);
	void event();
	void updateShowtable();
	bool isFind = false;


};

class Teacher :public Student
{
	IMAGE pic_t;
	enum number
	{
		ndisplay,
		nsearch,
		nadd,
		nerase,
		nmodify,
		nexit,
		menu_te_n
	};
public:
	Teacher();
	void run_teacher();
	void dispaly();
	void add();
	void erase();
	void modify();
	void search();
	void drawBack_t();
	int menu_te();
	void event();


};
