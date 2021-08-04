#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Classes.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "Menu.h"

using namespace std;

extern FILE *report_file;

extern Computer *computer;
extern Printer *printer;
extern Monitor *monitor;
extern Laptop *laptop;
extern int q_printer;
extern int q_computer;
extern int q_monitor;
extern int q_laptop;

extern Spravochnik <double> Spr_diagonal;
extern Spravochnik <string> Spr_brand;
extern Spravochnik <int> Spr_resolution;

struct about_users {   //������ � �������������   
	char login[20];      
	char password[30];   
	int role;
};
about_users users[100];

string l = "---------------------------------------------------------------------------------------------------";

//------------------------����� ������----------------------------------------------------------------------
int Choise_group(string fraza) {
	int choise = 0;
	while (true) {
		cout << fraza
			<< "\n1. ����������"
			<< "\n2. ��������"
			<< "\n3. ��������"
			<< "\n4. ��������"
			<< "\n0. �����" << endl;

		Get_number(choise);

		if (choise >= 0 && choise <= 4) return choise;
		else  cout << "��� ������ �������" << endl;
	}
}

//------------------------���� �����------------------------------------------------------------------------
template <typename T>
void Get_number(T &chislo) {
	while (true) { // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
		cin >> chislo;
		cin.ignore(32767, '\n');

		if (cin.fail()) { // ���� ���������� ���������� ��������� ����������
			cout << "������ ��� ����� �����. ��������� ����: ";
			cin.clear(); // ���������� cin � '�������' ����� ������
			cin.ignore(32767, '\n');
		}
		else {
			break;
		}
	}
}

//------------------------����� �������� �������------------------------------------------------------------
void Time() {
	time_t now = time(0);
	tm *ltm = localtime(&now);

	cout << "����  " <<
			setw(2) << setfill('0') << right << ltm->tm_mday << "." <<
			setw(2) << setfill('0') << right << ltm->tm_mon+1 << "." <<
			ltm->tm_year+1900 << " " <<
			"\n����� " <<
			setw(2) << setfill('0') << right << ltm->tm_hour << ":" <<
			setw(2) << setfill('0') << right << ltm->tm_min << ":" <<
			setw(2) << setfill('0') << right << ltm->tm_sec << endl;
	cout.fill(' ');
}

//------------------------����� ����� �������---------------------------------------------------------------
void Title() {
	cout << l << endl;
	cout << setw(4) << left << "N/N" << setw(9) << left << "�����" << setw(13) << left << "������" << setw(8) << left
		<< "���� �." << setw(13) << left << "������� ��." << setw(14) << left << "��������������" << endl;
	cout << l << endl;
}

//------------------------���������� ������-----------------------------------------------------------------
void Order() {
	Item *item;
	int choise1 = 0, choise2 = 0, q;
	while (true) {
		choise1 = Choise_group("����� �� ����� ��������� �� ������ �������?");
		if (choise1 == 0) break;
		while (true) {
			system ("cls");
			switch (choise1) {
			case 1: Title();
				Look_computer();
				q = q_computer;
				break;
			case 2: Title();
				Look_monitor();
				q = q_monitor;
				break;
			case 3: Title();
				Look_printer();
				q = q_printer;
				break;
			case 4: Title();
				Look_laptop();
				q = q_laptop;
				break;
			default: cout << "��� ������ ��������:" << endl;
				system("pause");
				continue;
			}

			cout << "������� ����� ������ ��� �������(0-�����): ";
			Get_number(choise2);
			if (choise2 < 0 || choise2 > q+1) {
				cout << "��� ������ ��������:" << endl;
				system("pause");
				continue; 
			}
			if (choise2 == 0) {
				break;
			}

			//������ ����
			cout << "\n";
			int kol = 0, quantity;
			item = &computer[choise2 - 1]; // ��� ���������� ������ "������������ �� ������������������ ����������"
			if (choise1 == 1) item = &computer[choise2 - 1];
			else if (choise1 == 2) item = &monitor[choise2 - 1];
			else if (choise1 == 3) item = &printer[choise2 - 1];
			else if (choise1 == 4) item = &laptop[choise2 - 1];
			quantity = item->Get_quantity();

			while (true) {
				kol = 0;
				cout << "����� ����������?" << endl;
				Get_number(kol);
				if (kol<1 || kol > quantity) {
					cout << "������� ���������� �� 1 �� " << quantity << endl;
				}
				else break;
			}
			
			Time();
			item->Print_order(kol); // ����� ����������� �������
			item->Set_Item(quantity - kol); // ����� ����������
			item->Add_sold(kol); // �������� ���������� ����������
			system("pause");
			break;
		}
	}
}

//------------------------������� ������--------------------------------------------------------------------
void Report_store() {
	double cost_group = 0, cost_all = 0;
	int q_group = 0, q_all = 0;
	system("cls");
	Time();
	cout << "                    ������� �� ������" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "     ������������         ����    ����������   ���������" << endl;
	cout << "                          (���.)  (��.)        (���.)" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "����������" << endl;
	for (int i = 0; i <= q_computer; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << computer[i].Get_brand() << setw(13) << left << computer[i].Get_model()
			<< setw(8) << left << computer[i].Get_price()
			<< setw(13) << left << computer[i].Get_quantity() << setw(10) << left << computer[i].Get_quantity()*computer[i].Get_price() << endl;
		q_group += computer[i].Get_quantity();
		cost_group += computer[i].Get_quantity()*computer[i].Get_price();
	}
	cout << "����� �� �����������: " << q_group << " ��. " << cost_group << " ���." << endl << endl;;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "��������" << endl;
	for (int i = 0; i <= q_monitor; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << monitor[i].Get_brand() << setw(13) << left << monitor[i].Get_model()
			<< setw(8) << left << monitor[i].Get_price()
			<< setw(13) << left << monitor[i].Get_quantity() << setw(10) << left << monitor[i].Get_quantity()*monitor[i].Get_price() << endl;
		q_group += monitor[i].Get_quantity();
		cost_group += monitor[i].Get_quantity()*monitor[i].Get_price();
	}
	cout << "����� �� ���������: " << q_group << " ��. " << cost_group << " ���." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "��������" << endl;
	for (int i = 0; i <= q_printer; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << printer[i].Get_brand() << setw(13) << left << printer[i].Get_model()
			<< setw(8) << left << printer[i].Get_price()
			<< setw(13) << left << printer[i].Get_quantity() << setw(10) << left << printer[i].Get_quantity()*printer[i].Get_price() << endl;
		q_group += printer[i].Get_quantity();
		cost_group += printer[i].Get_quantity()*printer[i].Get_price();
	}
	cout << "����� �� ���������: " << q_group << " ��. " << cost_group << " ���." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "��������" << endl;
	for (int i = 0; i <= q_laptop; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << laptop[i].Get_brand() << setw(13) << left << laptop[i].Get_model()
			<< setw(8) << left << laptop[i].Get_price()
			<< setw(13) << left << laptop[i].Get_quantity() << setw(10) << left << laptop[i].Get_quantity()*laptop[i].Get_price() << endl;
		q_group += laptop[i].Get_quantity();
		cost_group += laptop[i].Get_quantity()*laptop[i].Get_price();
	}
	cout << "����� �� ���������: " << q_group << " ��. " << cost_group << " ���." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	cout << "�����: " << q_all << " ��. " << cost_all << " ���." << endl;
	system("pause");
}

//------------------------��������� ������------------------------------------------------------------------
void Report_sold() {
	double cost_group = 0, cost_all = 0;
	int q_group = 0, q_all = 0;
	system("cls");
	Time();
	cout << "                    ������� ������" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "     ������������         ����    ����������   ���������" << endl;
	cout << "                          (���.)  (��.)        (���.)" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "����������" << endl;
	for (int i = 0; i <= q_computer; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << computer[i].Get_brand() << setw(13) << left << computer[i].Get_model()
			<< setw(8) << left << computer[i].Get_price()
			<< setw(13) << left << computer[i].Get_sold() << setw(10) << left << computer[i].Get_sold()*computer[i].Get_price() << endl;
		q_group += computer[i].Get_sold();
		cost_group += computer[i].Get_sold()*computer[i].Get_price();
	}
	cout << "����� �� �����������: " << q_group << " ��. " << cost_group << " ���." << endl << endl;;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "��������" << endl;
	for (int i = 0; i <= q_monitor; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << monitor[i].Get_brand() << setw(13) << left << monitor[i].Get_model()
			<< setw(8) << left << monitor[i].Get_price()
			<< setw(13) << left << monitor[i].Get_sold() << setw(10) << left << monitor[i].Get_sold()*monitor[i].Get_price() << endl;
		q_group += monitor[i].Get_sold();
		cost_group += monitor[i].Get_sold()*monitor[i].Get_price();
	}
	cout << "����� �� ���������: " << q_group << " ��. " << cost_group << " ���." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "��������" << endl;
	for (int i = 0; i <= q_printer; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << printer[i].Get_brand() << setw(13) << left << printer[i].Get_model()
			<< setw(8) << left << printer[i].Get_price()
			<< setw(13) << left << printer[i].Get_sold() << setw(10) << left << printer[i].Get_sold()*printer[i].Get_price() << endl;
		q_group += printer[i].Get_sold();
		cost_group += printer[i].Get_sold()*printer[i].Get_price();
	}
	cout << "����� �� ���������: " << q_group << " ��. " << cost_group << " ���." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "��������" << endl;
	for (int i = 0; i <= q_laptop; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << laptop[i].Get_brand() << setw(13) << left << laptop[i].Get_model()
			<< setw(8) << left << laptop[i].Get_price()
			<< setw(13) << left << laptop[i].Get_sold() << setw(10) << left << laptop[i].Get_sold()*laptop[i].Get_price() << endl;
		q_group += laptop[i].Get_sold();
		cost_group += laptop[i].Get_sold()*laptop[i].Get_price();
	}
	cout << "����� �� ���������: " << q_group << " ��. " << cost_group << " ���." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	cout << "�����: " << q_all << " ��. " << cost_all << " ���." << endl;
	system("pause");
}

//------------------------������----------------------------------------------------------------------------
template <typename T>
void Filter(T *item, string brand, string model = "", double min_price = 0, double max_price = 0) {
	if (
		(brand == "" || item->Get_brand().find(brand) != string::npos) && // npos=-1
		(model == "" || item->Get_model().find(model) != string::npos) &&
		((min_price == 0 && max_price == 0) || (item->Get_price() >= min_price && item->Get_price() <= max_price))
		) {
		cout << setw(2) << right << Item::Get_nn_plus() << ". " << *item <<  endl; // ����� � ���������� �����
	}
}

//------------------------�������� ������-------------------------------------------------------------------
void Deleting() {
	Item *item;
	int choise1 = 0, choise2 = 0, q;

	cout << "����� ���� ���������:\n" << Item::Get_log() << endl;

	while (true) {
		choise1 = Choise_group("����� �� ����� ��������� �� ������ �������?");
		if (choise1 == 0) break;
		while (true) {
			system("cls");
			switch (choise1) {
				case 1: 
					Title();
					Look_computer();
					q = q_computer;
					break;
				case 2: 
					Title();
					Look_monitor();
					q = q_monitor;
					break;
				case 3: 
					Title();
					Look_printer();
					q = q_printer;
					break;
				case 4: 
					Title();
					Look_laptop();
					q = q_laptop;
					break;
				default: 
					cout << "��� ������ ��������:" << endl;
					system("pause");
					continue;
			}

			cout << "������� ����� ������ ��� ��������(0-�����): ";
			Get_number(choise2);

			if (choise2 == 0) break;
			if (choise2 <= 0 || choise2 > q+1) continue;

			switch (choise1) {
				case 0: 
					break;
				case 1: 
					computer[choise2-1].Show();
					Item::Add_log("�������� ");
					Item::Add_log(((computer[choise2 - 1].Get_brand()).append(" ")).append((computer[choise2 - 1].Get_model()).append("\n"))); // ������ �����
					for (int i = choise2 - 1; i < q_computer; i++) {
						computer[i] = computer[i + 1];
					}
					q_computer--;
					break;
				case 2: 
					monitor[choise2-1].Show();
					Item::Add_log("�������� ");
					Item::Add_log(((monitor[choise2 - 1].Get_brand()).append(" ")).append((monitor[choise2 - 1].Get_model()).append("\n"))); // ������ �����

					for (int i = choise2 - 1; i < q_monitor; i++) {
						monitor[i] = monitor[i + 1];
					}
					q_monitor--;
					break;
				case 3: 
					printer[choise2-1].Show();
					Item::Add_log("�������� ");
					Item::Add_log(((printer[choise2 - 1].Get_brand()).append(" ")).append((printer[choise2 - 1].Get_model()).append("\n"))); // ������ �����
					for (int i = choise2 - 1; i < q_printer; i++) {
						printer[i] = printer[i + 1];
					}
					q_printer--;
					break;
				case 4: 
					laptop[choise2-1].Show();
					Item::Add_log("�������� ");
					Item::Add_log(((laptop[choise2 - 1].Get_brand()).append(" ")).append((laptop[choise2 - 1].Get_model()).append("\n"))); // ������ �����
					for (int i = choise2 - 1; i < q_laptop; i++) {
						laptop[i] = laptop[i + 1];
					}
					q_laptop--;
					break;
				default: 
					cout << "��� ������ ��������:" << endl;
					system("pause");
					continue;
			}
			cout << "\n����� �����" << endl;
			system("pause");
		}
	}
}

//------------------------������� � �������� �����----------------------------------------------------------
char* Upper(char *stroka) {
	char *new_stroka;
	new_stroka = (char*)calloc(strlen(stroka) + 1, sizeof(char));
	for (int i = 0; i < strlen(stroka); i++) {
		new_stroka[i] = toupper(stroka[i]);
	}
	return new_stroka;
}

//------------------------�������� �����������--------------------------------------------------------------
void Look_computer() {
	cout << "����������" << endl;
	for (int i = 0; i <= q_computer; i++) {
		cout << setw(2) << right << i+1 << ". " << computer[i] << endl;
	}
	cout << l << endl;
}

//------------------------�������� ���������----------------------------------------------------------------
void Look_printer() {
	cout << "��������" << endl;
	for (int i = 0; i <= q_printer; i++) {
		cout << setw(2) << right << i + 1 << ". " << printer[i] << endl;
	}
	cout << l << endl;
}

//------------------------�������� ���������----------------------------------------------------------------
void Look_monitor() {
	cout << "��������" << endl;
	for (int i = 0; i <= q_monitor; i++) {
		cout << setw(2) << right << i + 1 << ". " << monitor[i] << endl;
	}
	cout << l << endl;
}

//------------------------�������� ���������----------------------------------------------------------------
void Look_laptop() {
	cout << "��������" << endl;
	for (int i = 0; i <= q_laptop; i++) {
		cout << setw(2) << right << i + 1 << ". " << laptop[i] << endl;
	}
	cout << l << endl;
}

//------------------------�������� �����--------------------------------------------------------------------
void Look_all() {
	system("cls");
	Title();
	Look_computer();
	Look_printer();
	Look_monitor();
	Look_laptop();
	system("pause");
}

//------------------------����������------------------------------------------------------------------------
void Sorting() {
	int choise1 = 0, choise2 = 0;
	while (true) {
		cout << "����� ������ ������� ������ �����������?"
			<< "\n1. ����������"
			<< "\n2. ��������"
			<< "\n3. ��������"
			<< "\n4. ��������"
			<< "\n0. �����" << endl;

		Get_number(choise1);
		if (choise1 == 0) break;
		if (choise1 < 1 || choise1 >4) {
			cout << "��� ������ ��������" << endl;
			continue;
		}
		while (true) {
			cout << ((choise1 == 1) ? "����������" : ((choise1 == 2) ? "��������" : ((choise1 == 3) ?
				"��������" : ((choise1 == 4) ? "��������" : "")))) << "\n";
			cout << "���������� ��:"
				<< "\n1. ������"
				<< "\n2. ����"
				<< "\n0. �����" << endl;
			Get_number(choise2);
			if (choise2 < 0 || choise2 > 2) {
				cout << "��� ������ ��������:" << endl;
				continue;
			}

			if (choise2 == 0) break;
			if (choise1 == 1) Sort(&computer[0], q_computer, choise2);
			else if (choise1 == 2) Sort(&monitor[0], q_monitor, choise2);
			else if (choise1 == 3) Sort(&printer[0], q_printer, choise2);
			else if (choise1 == 4) Sort(&laptop[0], q_laptop, choise2);
		}
	}
}

//------------------------����������------------------------------------------------------------------------
template <typename T>
void Sort(T *massiv, int q, int sort_by) {
	int smallest_index;
	T dop;
	for (int start_index = 0; start_index < q; start_index++) {
		smallest_index = start_index;
		for (int current_index = start_index + 1; current_index <= q; current_index++) {
			if (sort_by == 1 && massiv[current_index].Get_brand() < massiv[smallest_index].Get_brand() ||
				sort_by == 2 && massiv[current_index].Get_price() < massiv[smallest_index].Get_price()) {
				smallest_index = current_index;
			}
		}
		// ������ �������
		dop = massiv[start_index];
		massiv[start_index] = massiv[smallest_index];
		massiv[smallest_index] = dop;
	}
	Title();
	for (int i = 0; i <= q; i++) {
		cout << setw(2) << right << i+1 << ". " << massiv[i] << endl;
	}
}

//------------------------������----------------------------------------------------------------------------
void Filtering() {
	string brand="";
	string model="";
	int choise1, choise2;
	double max_price=0, min_price=0;
	while (true) {
		cout << "�� ����� ������ ������� �� ������ �����������?"
			<< "\n1. �� ���� �������"
			<< "\n2. �� �����������"
			<< "\n3. �� ���������"
			<< "\n4. �� ���������"
			<< "\n5. �� ���������" 
			<< "\n0. �����"  << endl;

		Get_number(choise1);
		if (choise1 == 0) break;
		if (choise1<1 || choise1 >5) {
			cout << "��� ������ ��������." << endl;
			continue;
		}

		while (true) {
			cout << ((choise1 == 1) ? "��� ������" : ((choise1 == 2) ? "����������" : ((choise1 == 3) ? "��������" : ((choise1 == 4) ?
				"��������" : ((choise1 == 5)? "��������" : ""))))) << "\n";
			cout << "�� ����� ����������?"
				<< "\n1. �����"
				<< "\n2. ������"
				<< "\n3. ����" 
				<< "\n0. �����" << endl;
			Get_number(choise2);
			if (choise2 == 0) break;
			switch (choise2) {
			case 1: {
				cout << "������� �������� ������: " << endl;
				cin >> brand;
				break;
			}
			case 2: {
				cout << "������� �������� ������: " << endl;
				cin >> model;
				break;
			}
			case 3: {
				cout << "\n������� ����������� ����: ";
				Get_number(min_price);
				cout << "\n������� ������������ ����: ";
				Get_number(max_price);
				break;
			}
			default: cout << "��� ������ ��������:" << endl;
				continue;
			}
			system("cls");
			cout << "���������� ������: ";
			if (brand != "") { cout << "����� " << brand; } 
			if (model != "") { cout << " ������ " << model;}
			if (max_price + min_price != 0) { cout << " ���� �� " << min_price << " �� " << max_price; }
			cout << endl;
			Title();
			Item::Set_nn(0); // ��������� ��������� (static ����������)
			if (choise1 == 1 || choise1 == 2) {
				for (int i = 0; i <= q_computer; i++) {
					Filter(&computer[i],brand, model, min_price, max_price);
				}
			}
			if (choise1 == 1 || choise1 == 3) {
				for (int i = 0; i <= q_monitor; i++) {
					Filter(&monitor[i],brand, model, min_price, max_price);
				}
			}
			if (choise1 == 1 || choise1 == 4) {
				for (int i = 0; i <= q_printer; i++) {
					Filter(&printer[i],brand, model, min_price, max_price);
				}
			}
			if (choise1 == 1 || choise1 == 5) {
				for (int i = 0; i <= q_laptop; i++) {
					Filter(&laptop[i],brand, model, min_price, max_price);
				}
			}
		}
	}
}

//------------------------���������� ����������-------------------------------------------------------------
void Add(Computer &computer) {
	string brand, model, processor;
	double price;
	int quantity;

	cout << "�����: ";
	brand = Spr_brand.Choise();

	cout << "������: ";
	getline(cin, model);

	cout << "����: ";
	Get_number(price);

	cout << "����������: ";
	Get_number(quantity); 
	computer.Set_Item(brand, model, price, quantity, 0);

	cout << "���������: " ;
	getline(cin, processor);
	computer.Set_processor(processor);
}

//------------------------���������� ��������---------------------------------------------------------------
void Add(Monitor &monitor) {
	string brand, model;
	double price, diagonal;
	int quantity, resolution;

	cout << "�����: ";
	brand = Spr_brand.Choise();

	cout << "������: ";
	getline(cin, model);

	cout << "����: ";
	Get_number(price);

	cout << "����������: ";
	Get_number(quantity); 
	monitor.Set_Item(brand, model, price, quantity, 0);


	cout << "���������: ";
	diagonal = Spr_diagonal.Choise();
	monitor.Set_diagonal(diagonal);

	cout << "����������: ";
	resolution = Spr_resolution.Choise();
	monitor.Set_resolution(resolution);
}

//------------------------���������� ��������---------------------------------------------------------------
void Add(Printer &printer) {
	string brand, model, type;
	double price;
	int quantity, speed;

	cout << "�����: ";
	brand = Spr_brand.Choise();

	cout << "������: ";
	getline(cin, model);

	cout << "����: ";
	Get_number(price);

	cout << "����������: ";
	Get_number(quantity); 
	printer.Set_Item(brand, model, price, quantity, 0);

	cout << "���: ";
	getline(cin, type);
	printer.Set_type(type);

	cout << "��������: ";
	Get_number(speed); 
	printer.Set_speed(speed);
}

//------------------------���������� ��������---------------------------------------------------------------
void Add(Laptop &laptop) {
	string brand, model, processor;
	double price, diagonal, weight;
	int quantity;

	cout << "�����: ";
	brand=Spr_brand.Choise();

	cout << "������: ";
	getline(cin, model);

	cout << "����: ";
	Get_number(price);

	cout << "����������: ";
	Get_number(quantity); 
	laptop.Set_Item(brand, model, price, quantity, 0);

	cout << "���������: ";
	getline(cin, processor);
	laptop.Set_processor(processor);

	cout << "���������: ";
	diagonal = Spr_diagonal.Choise();
	laptop.Set_diagonal(diagonal);

	cout << "���: ";
	Get_number(weight); 
	laptop.Set_weight(weight);
}

//------------------------����������------------------------------------------------------------------------
void Adding() {
	Item *item;
	int choise1 = 0, choise2 = 0, q;

	cout << "����� ���� ���������:\n" << Item::Get_log() << endl;

	while (true) {
		choise1 = Choise_group("\n����� ����� ��������� ������ ��������?");
		if (choise1 == 0) break;
		system("cls");
		switch (choise1) {
		case 1:
			Title();
			Look_computer();
			q_computer++;
			Add(computer[q_computer]);
			Item::Add_log("���������� ");
			Item::Add_log(((computer[q_computer].Get_brand()).append(" ")).append((computer[q_computer].Get_model()).append("\n"))); // ������ �����
			break;
		case 2:
			Title();
			Look_monitor();
			q_monitor++;
			Add(monitor[q_monitor]);
			Item::Add_log("���������� ");
			Item::Add_log(((monitor[q_monitor].Get_brand()).append(" ")).append((monitor[q_monitor].Get_model()).append("\n"))); // ������ �����
			break;
		case 3:
			Title();
			Look_printer();
			q_printer++;
			Add(printer[q_printer]);
			Item::Add_log("���������� ");
			Item::Add_log(((printer[q_printer].Get_brand()).append(" ")).append((printer[q_printer].Get_model()).append("\n"))); // ������ �����
			break;
		case 4:
			Title();
			Look_laptop();
			q_laptop++;
			Add(laptop[q_laptop]);
			Item::Add_log("���������� ");
			Item::Add_log(((laptop[q_laptop].Get_brand()).append(" ")).append((laptop[q_laptop].Get_model()).append("\n"))); // ������ �����
			break;
		default:
			cout << "��� ������ ��������:" << endl;
			system("pause");
			continue;
		}
		cout << "���������" << endl;
		system("pause");
	}
}

//------------------------�������������� ����������---------------------------------------------------------
void Edit(Computer &computer) {
	string brand, model, processor;
	double price;
	int quantity, choise;

	computer.Show();
	cout << "\n�������� ���� ��� ��������������:"
		<< "\n1. ����� � ������"
		<< "\n2. ����"
		<< "\n3. ����������"
		<< "\n4. ���������"
		<< "\n0. �����" << endl;
	while (true) {
		Get_number(choise);

		switch (choise) {
		case 1:
			cout << "�����: ";
			brand = Spr_brand.Choise();
			cout << "������: ";
			getline(cin, model);
			computer.Set_Item(brand, model);
			break;
		case 2: 
			cout << "����: ";
			Get_number(price);
			computer.Set_Item(price);
			break;
		case 3: 
			cout << "����������: ";
			Get_number(quantity);
			computer.Set_Item(quantity);
			break;
		case 4: 
			cout << "���������: ";
			getline(cin, processor);
			computer.Set_processor(processor);
			break;
		case 0:
			break;
		default: cout << "��� ������ ��������!\n";
			system("pause");
			break;
		}
		if (choise >= 0 && choise <=4) break;
	}
}

//------------------------�������������� ��������-----------------------------------------------------------
void Edit(Monitor &monitor) {
	string brand, model, processor;
	double price, diagonal;
	int quantity, resolution, choise;

	monitor.Show();
	cout << "\n�������� ���� ��� ��������������:"
		<< "\n1. ����� � ������"
		<< "\n2. ����"
		<< "\n3. ����������"
		<< "\n4. ���������"
		<< "\n5. ����������"
		<< "\n0. �����" << endl;
	while (true) {
		Get_number(choise);

		switch (choise) {
		case 1:
			cout << "�����: ";
			brand = Spr_brand.Choise();
			cout << "������: ";
			getline(cin, model);
			monitor.Set_Item(brand, model);
			break;
		case 2:
			cout << "����: ";
			Get_number(price);
			monitor.Set_Item(price);
			break;
		case 3:
			cout << "����������: ";
			Get_number(quantity);
			monitor.Set_Item(quantity);
			break;
		case 4:
			cout << "���������: ";
			diagonal = Spr_diagonal.Choise();
			monitor.Set_diagonal(diagonal);
			break;
		case 5:
			cout << "����������: ";
			resolution = Spr_resolution.Choise();
			monitor.Set_resolution(resolution);
			break;
		case 0:
			break;
		default: cout << "��� ������ ��������!\n";
			system("pause");
			break;
		}
		if (choise >= 0 && choise <= 5) break;
	}
}

//------------------------�������������� ��������-----------------------------------------------------------
void Edit(Printer &printer) {
	string brand, model, type;
	double price;
	int quantity, speed, choise;

	printer.Show();
	cout << "\n�������� ���� ��� ��������������:"
		<< "\n1. ����� � ������"
		<< "\n2. ����"
		<< "\n3. ����������"
		<< "\n4. ���"
		<< "\n5. ��������"
		<< "\n0. �����" << endl;
	while (true) {
		Get_number(choise);

		switch (choise) {
		case 1:
			cout << "�����: ";
			brand = Spr_brand.Choise();
			cout << "������: ";
			getline(cin, model);
			printer.Set_Item(brand, model);
			break;
		case 2:
			cout << "����: ";
			Get_number(price);
			printer.Set_Item(price);
			break;
		case 3:
			cout << "����������: ";
			Get_number(quantity);
			printer.Set_Item(quantity);
			break;
		case 4:
			cout << "���: ";
			getline(cin, type);
			printer.Set_type(type);
			break;
		case 5:
			cout << "��������: ";
			Get_number(speed);
			printer.Set_speed(speed);
			break;
		case 0:
			break;
		default: cout << "��� ������ ��������!\n";
			system("pause");
			break;
		}
		if (choise >= 0 && choise <= 5) break;
	}
}

//------------------------�������������� ��������-----------------------------------------------------------
void Edit(Laptop &laptop) {
	string brand, model, processor;
	double price, diagonal, weight;
	int quantity, choise;

	laptop.Show();
	cout << "\n�������� ���� ��� ��������������:"
		<< "\n1. ����� � ������"
		<< "\n2. ����"
		<< "\n3. ����������"
		<< "\n4. ���������"
		<< "\n5. ���������"
		<< "\n6. ���"
		<< "\n0. �����" << endl;
	while (true) {
		Get_number(choise);

		switch (choise) {
		case 1:
			cout << "�����: ";
			brand = Spr_brand.Choise();
			cout << "������: ";
			getline(cin, model);
			laptop.Set_Item(brand, model);
			break;
		case 2:
			cout << "����: ";
			Get_number(price);
			laptop.Set_Item(price);
			break;
		case 3:
			cout << "����������: ";
			Get_number(quantity);
			laptop.Set_Item(quantity);
			break;
		case 4:
			cout << "���������: ";
			getline(cin, processor);
			laptop.Set_processor(processor);
			break;
		case 5:
			cout << "���������: ";
			diagonal = Spr_diagonal.Choise();
			laptop.Set_diagonal(diagonal);
			break;
		case 6:
			cout << "���: ";
			Get_number(weight);
			laptop.Set_weight(weight);
			break;
		case 0:
			break;
		default: cout << "��� ������ ��������!\n";
			system("pause");
			break;
		}
		if (choise >= 0 && choise <= 6) break;
	}
}

//------------------------��������������--------------------------------------------------------------------
void Editing() {
	int choise1 = 0, choise2 = 0, q;
	cout << "����� ���� ���������:\n" << Item::Get_log() << endl;
	while (true) {
		choise1 = Choise_group("����� �� ����� ��������� �� ������ �������������?");
		if (choise1 == 0) break;
		while (true) {
			system("cls");
			switch (choise1) {
			case 1:
				Title();
				Look_computer();
				q = q_computer;
				break;
			case 2:
				Title();
				Look_monitor();
				q = q_monitor;
				break;
			case 3:
				Title();
				Look_printer();
				q = q_printer;
				break;
			case 4:
				Title();
				Look_laptop();
				q = q_laptop;
				break;
			default:
				cout << "��� ������ ��������:" << endl;
				system("pause");
				continue;
			}

			cout << "������� ����� ������ ��� ��������������(0-�����): ";
			Get_number(choise2);

			if (choise2 == 0) break;
			if (choise2 <= 0 || choise2 > q + 1) continue;

			switch (choise1) {
			case 0:
				break;
			case 1:
				Edit(computer[choise2 - 1]);
				Item::Add_log("�������������� ");
				Item::Add_log(((computer[choise2 - 1].Get_brand()).append(" ")).append((computer[choise2 - 1].Get_model()).append("\n")));
				break;
			case 2:
				Edit(monitor[choise2 - 1]);
				Item::Add_log("�������������� ");
				Item::Add_log(((monitor[choise2 - 1].Get_brand()).append(" ")).append((monitor[choise2 - 1].Get_model()).append("\n")));
				break;
			case 3:
				Edit(printer[choise2 - 1]);
				Item::Add_log("�������������� ");
				Item::Add_log(((printer[choise2 - 1].Get_brand()).append(" ")).append((printer[choise2 - 1].Get_model()).append("\n")));
				break;
			case 4:
				Edit(laptop[choise2 - 1]);
				Item::Add_log("�������������� ");
				Item::Add_log(((laptop[choise2 - 1].Get_brand()).append(" ")).append((laptop[choise2 - 1].Get_model()).append("\n")));
				break;
			default:
				cout << "��� ������ ��������:" << endl;
				system("pause");
				continue;
			}

			cout << "\n����� ��������������" << endl;
			system("pause");
		}
	}
}

//------------------------��� ������------------------------------------------------------------------------
void Report_best() {
	double cost_group = 0, cost_all = 0;
	int q_group = 0, q_all = 0;
	system("cls");
	Time();
	cout << "                    ��� �������" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "  ������������        ����    ����������   ���������" << endl;
	cout << "                      (���.)  (��.)        (���.)" << endl;
	cout << "--------------------------------------------------------" << endl;

	cout << "����������" << endl;
	int top_sold, top_i = 0;
	top_sold = computer[0].Get_sold();
	for (int i = 0; i <= q_computer; i++) {
		if (computer[i].Get_sold() > top_sold) {
			top_sold = computer[i].Get_sold();
			top_i = i;
		}
	}
	cout << setw(9) << left << computer[top_i].Get_brand() << setw(13) << left << computer[top_i].Get_model()
		<< setw(8) << left << computer[top_i].Get_price()
		<< setw(13) << left << computer[top_i].Get_sold() << setw(10) << left << computer[top_i].Get_sold()*computer[top_i].Get_price() << endl;

	cout << "��������" << endl;
	top_i = 0;
	top_sold = monitor[0].Get_sold();
	for (int i = 0; i <= q_monitor; i++) {
		if (monitor[i].Get_sold() > top_sold) {
			top_sold = monitor[i].Get_sold();
			top_i = i;
		}
	}
	cout << setw(9) << left << monitor[top_i].Get_brand() << setw(13) << left << monitor[top_i].Get_model()
		<< setw(8) << left << monitor[top_i].Get_price()
		<< setw(13) << left << monitor[top_i].Get_sold() << setw(10) << left << monitor[top_i].Get_sold()*monitor[top_i].Get_price() << endl;

	cout << "��������" << endl;
	top_i = 0;
	top_sold = printer[0].Get_sold();
	for (int i = 0; i <= q_printer; i++) {
		if (printer[i].Get_sold() > top_sold) {
			top_sold = printer[i].Get_sold();
			top_i = i;
		}
	}
	cout << setw(9) << left << printer[top_i].Get_brand() << setw(13) << left << printer[top_i].Get_model()
		<< setw(8) << left << printer[top_i].Get_price()
		<< setw(13) << left << printer[top_i].Get_sold() << setw(10) << left << printer[top_i].Get_sold()*printer[top_i].Get_price() << endl;

	cout << "��������" << endl;
	top_i = 0;
	top_sold = printer[0].Get_sold();
	for (int i = 0; i <= q_laptop; i++) {
		if (laptop[i].Get_sold() > top_sold) {
			top_sold = laptop[i].Get_sold();
			top_i = i;
		}
	}
	cout << setw(9) << left << laptop[top_i].Get_brand() << setw(13) << left << laptop[top_i].Get_model()
		<< setw(8) << left << laptop[top_i].Get_price()
		<< setw(13) << left << laptop[top_i].Get_sold() << setw(10) << left << laptop[top_i].Get_sold()*laptop[top_i].Get_price() << endl;

	system("pause");
}

//------------------------�������� �����--------------------------------------------------------------------
int User::Login() {

	FILE *log_file;
	int i = 0, role;
	char log[20], pass[30], login[20], password[30];

	cout << "������� �����: ";
	cin >> log;
	cout << "������� ������: ";
	cin >> pass;

	if ((log_file = fopen("Login_and_password.txt", "r")) == NULL)
	{
		puts("������� ���� �� �������.\n");
		getchar();
	}
	Crypt(pass);

	while (fscanf(log_file, "%s%s%d", login, password, &role) != EOF) {
		if (strcmp(log, login) == 0 && strcmp(pass, password) == 0) {
			return role;
		}
		i++;
	}

	if (i == 0) {
		puts("���� ����\n");
	}
	return -1;
}

//------------------------����������------------------------------------------------------------------------
void User::Crypt(char *password) {
		for (int i = 0; i < strlen(password); i++)
		{
			password[i] -= 7;
			if (password[i] > 175)
				password[i] += 49;
			if (password[i] > 241)
				password[i] -= 208;
		}
	}

//------------------------���������� ��������������---------------------------------------------------------
void User::Users() {
		int i = 0, kol_users = 0, n_del = 0, no_yes = 0;
		int choise;
		ifstream inf("Login_and_password.txt");

		if (!inf) { // ���� �� �� ����� ������� ���� ���� ��� ������ ��� �����������
			cerr << "������, ���� Login_and_password.txt �� ��������!" << endl;
			exit(1);
		}

		while (inf) {
			inf >> users[i].login;
			inf >> users[i].password;
			inf >> users[i].role;
			i++;
		}
		inf.close();

		kol_users = i - 1;
		while (true) {
			system("cls");
			for (i = 0; i < kol_users; i++) {
				cout << i + 1 << ". " << users[i].login << " " << (users[i].role == 1 ? "�������������" : "������������") << endl;
			}
			cout << "\n1. �������� ������������\n";
			cout << "2. ���������� ������������\n";
			cout << "0. ����� �� ���������� ��������������\n\n";
			cout << "��� �����: ";

			Get_number(choise);
			cout << "\n";

			switch (choise) {
			case 1:
				cout << "\n������� ����� ������, ������� ������ �������: ";
				while (n_del<1 || n_del>kol_users) {
					Get_number(n_del);
					if (n_del<1 || n_del>kol_users) {
						cout << "����� �������� �����. ������� ����� �� 1 �� " << kol_users;
					}
					else {
						cout << "\n� �� ����� ������ �������?(0-���; 1-��) - ";
						Get_number(no_yes);
						if (no_yes == 1) {
							if (n_del < kol_users) {
								for (int i = n_del - 1; i <= kol_users - 2; i++) {
									users[i] = users[i + 1];
								}
							}
							kol_users--;
							break;
						}
					}
				};
				break;

			case 2:
				cout << "������� ������ � ������������:\n";

				kol_users++;

				cout << "�����: ";
				cin >> users[kol_users - 1].login;

				cout << "������: ";
				cin >> users[kol_users - 1].password;
				cin.ignore(32767, '\n');
				Crypt(users[kol_users - 1].password);

				cout << "���� (1-�������������, 2-������������): ";
				Get_number(users[kol_users - 1].role);
				break;

			case 0: {
				ofstream outf("Login_and_password.txt");

				if (!outf) { // ���� �� �� ����� ������� ���� ���� ��� ������ ��� �����������
					cerr << "������, ���� Login_and_password.txt �� �������� ��� ������!" << endl;
					break;
				}

				for (int i = 0; i <= kol_users - 1; i++) {
					outf << users[i].login << " " << users[i].password << " " << users[i].role << endl;
				}
				outf.close();
				break;
			}
			default:
				cout << "��� ������ ��������!\n";
				system("pause");
				break;
			}
			if (choise == 0) break;
		}
	}