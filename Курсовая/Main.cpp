#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <Windows.h> 
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <iomanip>
#include "Classes.h"
#include "Read_write.h"
#include "Menu.h"

using namespace std;
using namespace User;

Computer *computer;
Printer *printer;
Monitor *monitor;
Laptop *laptop;

int q_computer = -1;
int q_printer = -1;
int q_monitor = -1;
int q_laptop = -1;

string Item::m_log = ""; // ������ �������
int Item::m_nn = 0; // ��������� ���������� ����� �� �������

Spravochnik <double> Spr_diagonal(8);
Spravochnik <string> Spr_brand(9);
Spravochnik <int> Spr_resolution(6);

int main() {
	setlocale(LC_ALL, "Rus");
	system("color E");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	computer = new Computer[111];
	printer = new Printer[111];
	monitor = new Monitor[111];
	laptop = new Laptop[111];

	Spr_diagonal.Add(0, 13.3);
	Spr_diagonal.Add(1, 14.5);
	Spr_diagonal.Add(2, 15.6);
	Spr_diagonal.Add(3, 16);
	Spr_diagonal.Add(4, 18.4);
	Spr_diagonal.Add(5, 23.4);
	Spr_diagonal.Add(6, 26);
	Spr_diagonal.Add(7, 28);

	Spr_brand.Add(0, "HP");
	Spr_brand.Add(1, "Lenovo");
	Spr_brand.Add(2, "Asus");
	Spr_brand.Add(3, "Dell");
	Spr_brand.Add(4, "Apple");
	Spr_brand.Add(5, "Samsung");
	Spr_brand.Add(6, "Canon");
	Spr_brand.Add(7, "Xiaomi");
	Spr_brand.Add(8, "LG");

	Spr_resolution.Add(0, 720);
	Spr_resolution.Add(1, 1080);
	Spr_resolution.Add(2, 1440);
	Spr_resolution.Add(3, 1800);
	Spr_resolution.Add(4, 2190);
	Spr_resolution.Add(5, 2560);
	
	try {
		if (Read_computer() != 0) throw 1;
		if (Read_printer() != 0) throw 2;
		if (Read_monitor() != 0) throw 3;
		if (Read_laptop() != 0) throw 4;

		register int choise;
		register int who_user = -1; // �������� �� ���������������

		while (who_user < 0) {  // ���� �������� �� ���������������
			who_user = Login(); // ����� � ������
			system("cls");
			if (who_user >= 0) {
				while (who_user == 1) {
					system("cls");
					cout << "1. ������\n";
					cout << "2. ����� � ����������\n";
					cout << "3. ����������\n";
					cout << "4. ����������\n";
					cout << "5. ��������������\n";
					cout << "6. ��������\n";
					cout << "7. ���������� ��������������\n";
					cout << "8. ����� � ������� �� ������\n";
					cout << "9. ����� � ��������\n";
					cout << "10. ��� ����������� �������\n";
					cout << "11. ����� � ���� ������� ������\n";
					cout << "0. ����� �� ���������.\n\n";
					cout << "��� �����: ";

					Get_number(choise);
					cout << "\n";

					switch (choise) {
					case 1:
						Look_all();
						break;
					case 2: Filtering();
						break;
					case 3: Sorting();
						break;
					case 4: Adding();
						break;
					case 5: Editing();
						break;
					case 6: Deleting();
						break;
					case 7: Users();
						break;
					case 8: Report_store();
						break;
					case 9: Report_sold();
						break;
					case 10: Report_best();
						break;
					case 11: system("cls");
						who_user=-1;
						break;
					case 0:
						Write_printer();
						Write_monitor();
						Write_laptop();
						Write_computer();
						delete[] computer;
						delete[] printer;
						delete[] monitor;
						delete[] laptop;
						break;
					default: cout << "��� ������ ��������!\n";
						system("pause");
						break;
					}
					if (choise == 0) break;
				}
				while (who_user == 2) {
					system("cls");
					cout << "1. ������\n";
					cout << "2. ����� � ����������\n";
					cout << "3. ����������\n";
					cout << "4. ����������\n";
					cout << "5. ��������������\n";
					cout << "6. ��������\n";
					cout << "7. ���������� ������\n";
					cout << "8. ����� � ������� �� ������\n";
					cout << "9. ����� � ���� ������� ������\n";
					cout << "0. ����� �� ���������.\n\n";
					cout << "��� �����: ";

					Get_number(choise);
					cout << "\n";

					switch (choise) {
					case 1:
						Look_all();
						break;
					case 2: Filtering();
						break;
					case 3: Sorting();
						break;
					case 4: Adding();
						break;
					case 5: Editing();
						break;
					case 6: Deleting();
						break;
					case 7: Order();
						system("pause");
						break;
					case 8: Report_store();
						break;
					case 9: system("cls");
						who_user = -1;
						break;
					case 0:
						Write_printer();
						Write_monitor();
						Write_laptop();
						Write_computer();
						delete[] computer;
						delete[] printer;
						delete[] monitor;
						delete[] laptop;
						break;
					default: cout << "��� ������ ��������!\n";
						system("pause");
						break;
					}
					if (choise == 0) break;
				}
			}
		}
	}
	catch (int exc) {
		if (exc == 1) cerr << "������, ���� Computer.txt �� ��������!" << endl;
		if (exc == 2) cerr << "������, ���� Printer.txt �� ��������!" << endl;
		if (exc == 3) cerr << "������, ���� Monitor.txt �� ��������!" << endl;
		if (exc == 4) cerr << "������, ���� Laptop.txt �� ��������!" << endl;
		system("pause");
	}
}

