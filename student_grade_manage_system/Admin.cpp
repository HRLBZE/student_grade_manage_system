#include "Admin.h"
#include<iostream>
#include"Pre_page.h"
#include<fstream>
#include<sstream>


using namespace std;

Student::Student()
{
	readFile("./res/student.txt");
	::loadimage(&pic_s, "./picture/4.png", Window::width(), Window::height());
	::settextstyle(20, 0, "宋体");

	menu.emplace_back(new Button("show all students"));
	menu.emplace_back(new Button("find student"));

	menu.emplace_back(new Button("add student"));
	menu.emplace_back(new Button("delete student"));
	menu.emplace_back(new Button("modify student"));
	menu.emplace_back(new Button("exit system"));

	for (int i = 0; i < 3; i++)
	{
		if (i == 2)
		{
			menu[5]->setFixSize(250, 50);
			int bx = (Window::width() - menu[5]->width()) / 2;
			int vspace = (Window::height() - 3 * menu[5]->height()) / 2;
			int by = vspace + 2 * menu[5]->height();
			menu[5]->mov(bx, by);
		}
		else
		{
			menu[i]->setFixSize(250, 50);
			int bx = (Window::width() - menu[i]->width()) / 2;
			int vspace = (Window::height() - 3 * menu[i]->height()) / 2;
			int by = vspace + i * menu[i]->height();
			menu[i]->mov(bx, by);
		}
	}

	m_showTable.reset(new Table);
	m_showTable->setRow(16);
	m_showTable->setHeard(m_header);

	updateShowtable();
	m_showTable->mov((Window::width() - m_showTable->width()) / 2, 80);

	m_addBtn.reset(new Button("添加", 670, 360));
	m_addEdit.reset(new LineEdit(200, 260, 550, 50));
	m_addEdit->setTitle("请输入学生信息");
	m_addEdit->setHitText("<学号 姓名 班级 数学 语文 英语>");

	m_dlBtn.reset(new Button("删除", 670, 360));
	m_dlEdit.reset(new LineEdit(200, 260, 550, 50));
	m_dlEdit->setTitle("请输入学生学号");
	m_dlEdit->setHitText("学号为：");

	m_dlTable.reset(new Table);
	m_dlTable->setHeard(m_header);
	m_dlTable->mov(m_dlEdit->x(), m_dlEdit->y() + 120);
	m_dlTable->setRow(1);

	m_fdEdit.reset(new LineEdit(200, 260, 550, 50));
	m_fdEdit->mov((Window::width() - m_fdEdit->width()) / 2, 260);

	m_fdTable.reset(new Table);
	m_fdTable->setHeard(m_header);
	m_fdTable->mov(m_fdEdit->x(), m_fdEdit->y() + 120);
	m_fdTable->setRow(1);

	m_modifyEdit.reset(new LineEdit(150, 260, 500, 40));
	m_modifyEdit->mov((Window::width() - m_modifyEdit->width()) / 2, 260);
	int x = (Window::width() - 100 * 6) / 2;
	for (int i = 0; i < 6; i++)
	{
		m_stuEdits.emplace_back(new LineEdit);
		m_stuEdits[i]->setFixSize(100, 40);
		m_stuEdits[i]->mov(x + i * m_stuEdits[i]->width(), m_modifyEdit->y() + 50);
	}
	m_modifyIt = vec_stu.end();


}

void Student::run_student()
{
	int derm = 0;
	i = menu_st();
	Window::beginDraw();
	while (true)
	{
		Window::clear();
		drawBack_s();

		if (Window::hasMsg())
		{
			switch (Window::getMsg().message)
			{
			case WM_KEYDOWN:
			{
				if (Window::getMsg().vkcode == VK_ESCAPE)
				{
					i = menu_st();
				}
				if (Window::getMsg().vkcode == VK_BACK)
				{
					derm = 1;
				}
				break;
			}
			default:
				event();
				break;

			}

		}
		switch (i)
		{

		case Student::show_all:
		{
			display();
			break;
		}
		case Student::find:
		{
			search();
			break;
		}
		case Student::nsexit:
		{
			saveFile("./res/test.txt");
			exit(666);
			break;
		}
		case Student::menu_st_num:
		{
			i = menu_st();
			break;
		}
		default:
			break;
		}
		Window::flushDraw();

		if (derm == 1)
		{
			Pre_page a;
			a.run();
		}
	}
	Window::endDraw();
}

int Student::menu_st()
{
	for (int i = 0; i < 3; i++)
	{
		if (i == 2)
		{
			i = 5;
			menu[i]->show();
			menu[i]->event();
			if (menu[i]->isClicked())
			{
				return 2;
			}
		}
		else
		{
			menu[i]->show();
			menu[i]->event();
			if (menu[i]->isClicked())
			{
				return i;
			}
		}
	}
	return menu_st_num;
}

void Student::display()
{
	m_showTable->show();
}

void Student::search()
{

	const char* title = "请输入学生学号";
	settextstyle(20, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);
	m_fdEdit->show();
	if (m_fdTable->rowCount() != 0)
		m_fdTable->show();
	auto& str = m_fdEdit->text();
	if (!str.empty())
	{
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student_data& stu)
			{
				return std::to_string(stu.number) == str;
			});
		if (it == vec_stu.end())
		{
			outtextxy(m_fdEdit->x(), m_fdEdit->y() + 50, std::string("对不起，没找到学号为" + str + "的学生").data());
		}
		else
		{
			m_fdTable->insertD(it->formatIn());


		}
		m_fdEdit->clear();
	}

}

void Student::drawBack_s()
{
	::putimage(0, 0, &pic_s);
}

void Student::readFile(const std::string& filename)
{
	fstream read(filename, ios::in);
	if (!read.is_open())
	{
		return;
	}
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;

	while (!read.eof())
	{
		char data[1024] = { 0 };
		read.getline(data, 1024);

		if (strlen(data) == 0)
			break;

		Student_data stu;
		stringstream ss(data);
		ss >> stu.number >> stu.name >> stu.grade >> stu.math >> stu.chinese >> stu.english;
		vec_stu.push_back(stu);
	}
	read.close();
}

void Student::saveFile(const std::string& filename)
{
	fstream write(filename, ios::out | ios::trunc);
	if (!write.is_open())
	{
		cerr << filename << "fail to open";
		return;
	}
	m_header += "\n";
	write.write(m_header.c_str(), m_header.size());

	for (auto& val : vec_stu)
	{
		std::string info = val.formatIn();
		write.write(info.c_str(), info.size());
	}
	write.close();
}

void Student::event()
{
	m_showTable->event();
	m_fdEdit->event();
	m_fdTable->event();
}

void Student::updateShowtable()
{
	m_showTable->clear();
	for (auto& val : vec_stu)
	{
		m_showTable->insertD(val.formatIn());
	}
}

Teacher::Teacher()
{
	::loadimage(&pic_t, "./picture/3.png", Window::width(), Window::height());
	for (int i = 0; i < menu.size(); i++)
	{
		menu[i]->setFixSize(250, 50);

		int bx = (Window::width() - menu[i]->width()) / 2;
		int vspace = (Window::height() - menu.size() * menu[i]->height()) / 2.;
		int by = vspace + i * menu[i]->height();
		menu[i]->mov(bx, by);
	}
}

void Teacher::run_teacher()
{
	int derm = 0;
	i = menu_te();
	Window::beginDraw();
	while (true)
	{
		Window::clear();
		drawBack_t();
		if (Window::hasMsg())
		{
			switch (Window::getMsg().message)
			{
			case WM_KEYDOWN:
			{
				if (Window::getMsg().vkcode == VK_ESCAPE)
				{
					i = menu_te();
				}
				if (Window::getMsg().vkcode == VK_BACK)
				{
					derm = 1;
				}
				break;
			}
			default:
				event();
				break;
			}

		}
		switch (i)
		{

		case Teacher::ndisplay:
		{
			display();
			break;
		}
		case Teacher::nsearch:
		{
			search();
			break;
		}
		case Teacher::nadd:
		{
			add();
			break;
		}
		case Teacher::nmodify:
		{
			modify();
			break;
		}
		case Teacher::nerase:
		{
			erase();
			break;
		}
		case Teacher::menu_te_n:
		{
			i = menu_te();
			break;
		}
		case Teacher::nexit:
		{
			saveFile("./res/test.txt");
			exit(666);
			break;
		}
		default:
			break;
		}
		Window::flushDraw();
		Window::getMsg().message = 0;
		if (derm == 1)
		{
			Pre_page a;
			a.run();
		}
	}
	Window::endDraw();
}

void Teacher::dispaly()
{
	display();
}

void Teacher::add()
{
	const char* title = "请输入学生信息<学号 姓名 班级 数学 语文 英语>";
	settextstyle(20, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);
	m_addBtn->show();
	m_addEdit->show();
	auto str = m_addEdit->text();
	if (m_addBtn->isClicked() && !str.empty())
	{
		vec_stu.push_back(Student_data::fromString(str));
		std::replace(str.begin(), str.end(), ' ', '\t');
		m_showTable->insertD(str);
		m_addEdit->clear();
	}
}

void Teacher::erase()
{
	const char* title = "请输入学生学号";
	settextstyle(20, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_dlBtn->show();
	m_dlEdit->show();

	if (m_dlTable->rowCount() != 0)
		m_dlTable->show();
	auto& str = m_dlEdit->text();

	if (m_dlEdit->textChange())
	{
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student_data& stu)
			{
				return std::to_string(stu.number) == str;
			});
		if (it == vec_stu.end())
		{
			outtextxy(m_dlEdit->x(), m_dlEdit->y() + 50, std::string("对不起，没找到学号为" + str + "的学生").data());
		}
		else
		{
			m_dlTable->insertD(it->formatIn());


		}
	}

	if (m_dlBtn->isClicked())
	{
		auto it = std::remove_if(vec_stu.begin(), vec_stu.end(), [=](const Student_data& stu)
			{
				return std::to_string(stu.number) == str;
			});
		if (it != vec_stu.end())
		{
			m_dlEdit->clear();
			m_dlTable->clear();
		}

		vec_stu.erase(it, vec_stu.end());

		updateShowtable();

	}
}

void Teacher::modify()
{
	const char* title = "请输入学生学号";
	settextstyle(20, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_modifyEdit->show();

	if (isFind)
	{
		for (auto& e : m_stuEdits)
		{
			e->show();
		}
	}


	if (m_modifyEdit->textChange())
	{
		auto& str = m_modifyEdit->text();
		std::stringstream ss(str);
		uint32_t number;
		ss >> number;
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student_data& stu)
			{
				return stu.number == number;
			});
		if (it == vec_stu.end())
		{
			m_modifyIt = vec_stu.end();
			isFind = false;
		}
		else
		{
			m_stuEdits[0]->setText(std::to_string(it->number));
			m_stuEdits[1]->setText(it->name);
			m_stuEdits[2]->setText(it->grade);
			m_stuEdits[3]->setText(std::to_string(it->chinese));
			m_stuEdits[4]->setText(std::to_string(it->math));
			m_stuEdits[5]->setText(std::to_string(it->english));

			isFind = true;
			m_modifyIt = it;

		}
	}
	if (isFind && m_modifyIt != vec_stu.end())
	{
		for (int i = 0; i < m_stuEdits.size(); i++)
		{
			if (m_stuEdits[i]->textChange())
			{
				switch (i)
				{
				case 0:
					m_modifyIt->number = atoi(m_stuEdits[i]->text().data());
					break;
				case 1:
					m_modifyIt->name = m_stuEdits[i]->text();
					break;

				case 2:
					m_modifyIt->grade = m_stuEdits[i]->text();
					break;
				case 3:
					m_modifyIt->chinese = atoi(m_stuEdits[i]->text().data());
					break;
				case 4:
					m_modifyIt->math = atoi(m_stuEdits[i]->text().data());
					break;
				case 5:
					m_modifyIt->english = atoi(m_stuEdits[i]->text().data());
					break;
				default:
					break;
				}
				updateShowtable();
			}
		}
	}


}

void Teacher::search()
{
	Student::search();
}

void Teacher::drawBack_t()
{
	::putimage(0, 0, &pic_t);
}

int Teacher::menu_te()
{
	for (int i = 0; i < menu.size(); i++)
	{
		menu[i]->show();
		menu[i]->event();
		if (menu[i]->isClicked())
		{
			return i;
		}
	}
	return menu_te_n;
}

void Teacher::event()
{
	m_showTable->event();
	m_addBtn->event();
	m_addEdit->event();

	m_dlBtn->event();
	m_dlEdit->event();

	m_modifyEdit->event();
	for (auto& e : m_stuEdits)
	{
		e->event();
	}
}
