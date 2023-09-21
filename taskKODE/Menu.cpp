#include <iostream>
#include <fstream>
#include <string_view>
#include <Windows.h>
#include <conio.h>
#include <ctime>

#include "Menu.h"

using namespace std::string_view_literals;

void SubMenu(ОbjectListHandler& handler) {
	int digit_submenu;
	std::cout << "Подменю"sv << std::endl;
	std::cout << "1. Группировка по расстоянию"sv << std::endl;
	std::cout << "2. Группировка по имени"sv << std::endl;
	std::cout << "3. Группировка по времени создания"sv << std::endl;
	std::cout << "4. Группировка по типу"sv << std::endl;
	std::cin >> digit_submenu;
	switch (digit_submenu) {
	case 1: {
		handler.GroupByDistance();
		break;
	}
	case 2: {
		handler.GroupByName();
		break;
	}
	case 3: {
		std::time_t t = std::time(nullptr);
		std::tm now;
		localtime_s(&now, &t);
		handler.GroupByCreationTime(now);
		break;
	}
	case 4: {
		int N;
		std::cout << "Введите N: ";
		std::cin >> N;
		handler.GroupByType(N);
		break;
	}
	default:break;
	}
}

void Menu() {
	ОbjectListHandler handler;
	int digit_menu;
	bool exit = false;
	while (!exit) {
		std::cout << "Меню"sv << std::endl;
		std::cout << "1. Прочитать список объектов из файла"sv << std::endl;
		std::cout << "2. Добавить объект в список"sv << std::endl;
		std::cout << "3. Группировать объекты с сортировкой внутри групп"sv << std::endl;
		std::cout << "4. Сохранить результаты в файл"sv << std::endl;
		std::cout << "5. Выход из программы"sv << std::endl;
		std::cout << "Введите пункт из меню: ";
		std::cin >> digit_menu;
		switch (digit_menu) {
		case 1: {
			std::string file_name;
			std::cout << "Введите имя файла в формате name.txt" << std::endl;
			std::cin >> file_name;
			std::ifstream in(file_name);
			if (!in.is_open()) {
				std::cout << "Error open file!"sv;
				std::exit(0);
			}
			handler.Read(in);
			std::cout << "Готово! Нажмите любую кнопку"sv << std::endl;
			_getch();
			system("cls");
			break;
		}
		case 2: {
			handler.AddObject();
			std::cout << "Готово! Нажмите любую кнопку"sv << std::endl;
			_getch();
			system("cls");
			break;
		}
		case 3: {
			SubMenu(handler);
			std::cout << "Готово! Нажмите любую кнопку"sv << std::endl;
			_getch();
			system("cls");
			break;
		}
		case 4: {
			std::ofstream out("file_out.txt");
			handler.Save(out);
			std::cout << "Сохранено! Нажмите любую кнопку"sv << std::endl;
			_getch();
			system("cls");
			break;
		}
		case 5: {
			exit = true;
			system("cls");
			break;
		}
		default:break;
		}
	}
}