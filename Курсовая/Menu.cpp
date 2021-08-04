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

struct about_users {   //данные о пользователях   
	char login[20];      
	char password[30];   
	int role;
};
about_users users[100];

string l = "---------------------------------------------------------------------------------------------------";

//------------------------Выбор группы----------------------------------------------------------------------
int Choise_group(string fraza) {
	int choise = 0;
	while (true) {
		cout << fraza
			<< "\n1. Компьютеры"
			<< "\n2. Мониторы"
			<< "\n3. Принтеры"
			<< "\n4. Ноутбуки"
			<< "\n0. Выход" << endl;

		Get_number(choise);

		if (choise >= 0 && choise <= 4) return choise;
		else  cout << "Нет такого варинта" << endl;
	}
}

//------------------------Ввод числа------------------------------------------------------------------------
template <typename T>
void Get_number(T &chislo) {
	while (true) { // Цикл продолжается до тех пор, пока пользователь не введет корректное значение
		cin >> chislo;
		cin.ignore(32767, '\n');

		if (cin.fail()) { // если предыдущее извлечение оказалось провальным
			cout << "Ошибка при вводе числа. Повторите ввод: ";
			cin.clear(); // возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n');
		}
		else {
			break;
		}
	}
}

//------------------------Вывод текущего времени------------------------------------------------------------
void Time() {
	time_t now = time(0);
	tm *ltm = localtime(&now);

	cout << "Дата  " <<
			setw(2) << setfill('0') << right << ltm->tm_mday << "." <<
			setw(2) << setfill('0') << right << ltm->tm_mon+1 << "." <<
			ltm->tm_year+1900 << " " <<
			"\nВремя " <<
			setw(2) << setfill('0') << right << ltm->tm_hour << ":" <<
			setw(2) << setfill('0') << right << ltm->tm_min << ":" <<
			setw(2) << setfill('0') << right << ltm->tm_sec << endl;
	cout.fill(' ');
}

//------------------------Вывод шапки таблицы---------------------------------------------------------------
void Title() {
	cout << l << endl;
	cout << setw(4) << left << "N/N" << setw(9) << left << "Бренд" << setw(13) << left << "Модель" << setw(8) << left
		<< "Цена р." << setw(13) << left << "Наличие шт." << setw(14) << left << "Характеристики" << endl;
	cout << l << endl;
}

//------------------------Выполнение заказа-----------------------------------------------------------------
void Order() {
	Item *item;
	int choise1 = 0, choise2 = 0, q;
	while (true) {
		choise1 = Choise_group("Товар из какой категории вы хотите продать?");
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
			default: cout << "Нет такого варианта:" << endl;
				system("pause");
				continue;
			}

			cout << "Укажите номер строки для продажи(0-выход): ";
			Get_number(choise2);
			if (choise2 < 0 || choise2 > q+1) {
				cout << "Нет такого варианта:" << endl;
				system("pause");
				continue; 
			}
			if (choise2 == 0) {
				break;
			}

			//Печать чека
			cout << "\n";
			int kol = 0, quantity;
			item = &computer[choise2 - 1]; // для исключения ошибки "потенциально не инециализированная переменная"
			if (choise1 == 1) item = &computer[choise2 - 1];
			else if (choise1 == 2) item = &monitor[choise2 - 1];
			else if (choise1 == 3) item = &printer[choise2 - 1];
			else if (choise1 == 4) item = &laptop[choise2 - 1];
			quantity = item->Get_quantity();

			while (true) {
				kol = 0;
				cout << "Какое количество?" << endl;
				Get_number(kol);
				if (kol<1 || kol > quantity) {
					cout << "Укажите количество от 1 до " << quantity << endl;
				}
				else break;
			}
			
			Time();
			item->Print_order(kol); // вызов виртуальной функции
			item->Set_Item(quantity - kol); // новое количество
			item->Add_sold(kol); // увеличил количество проданного
			system("pause");
			break;
		}
	}
}

//------------------------Наличие товара--------------------------------------------------------------------
void Report_store() {
	double cost_group = 0, cost_all = 0;
	int q_group = 0, q_all = 0;
	system("cls");
	Time();
	cout << "                    Наличие на складе" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "     Наименование         Цена    Количество   Стоимость" << endl;
	cout << "                          (руб.)  (шт.)        (руб.)" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Компьютеры" << endl;
	for (int i = 0; i <= q_computer; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << computer[i].Get_brand() << setw(13) << left << computer[i].Get_model()
			<< setw(8) << left << computer[i].Get_price()
			<< setw(13) << left << computer[i].Get_quantity() << setw(10) << left << computer[i].Get_quantity()*computer[i].Get_price() << endl;
		q_group += computer[i].Get_quantity();
		cost_group += computer[i].Get_quantity()*computer[i].Get_price();
	}
	cout << "Итого по компьютерам: " << q_group << " шт. " << cost_group << " руб." << endl << endl;;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "Мониторы" << endl;
	for (int i = 0; i <= q_monitor; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << monitor[i].Get_brand() << setw(13) << left << monitor[i].Get_model()
			<< setw(8) << left << monitor[i].Get_price()
			<< setw(13) << left << monitor[i].Get_quantity() << setw(10) << left << monitor[i].Get_quantity()*monitor[i].Get_price() << endl;
		q_group += monitor[i].Get_quantity();
		cost_group += monitor[i].Get_quantity()*monitor[i].Get_price();
	}
	cout << "Итого по мониторам: " << q_group << " шт. " << cost_group << " руб." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "Принтеры" << endl;
	for (int i = 0; i <= q_printer; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << printer[i].Get_brand() << setw(13) << left << printer[i].Get_model()
			<< setw(8) << left << printer[i].Get_price()
			<< setw(13) << left << printer[i].Get_quantity() << setw(10) << left << printer[i].Get_quantity()*printer[i].Get_price() << endl;
		q_group += printer[i].Get_quantity();
		cost_group += printer[i].Get_quantity()*printer[i].Get_price();
	}
	cout << "Итого по принтерам: " << q_group << " шт. " << cost_group << " руб." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "Ноутбуки" << endl;
	for (int i = 0; i <= q_laptop; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << laptop[i].Get_brand() << setw(13) << left << laptop[i].Get_model()
			<< setw(8) << left << laptop[i].Get_price()
			<< setw(13) << left << laptop[i].Get_quantity() << setw(10) << left << laptop[i].Get_quantity()*laptop[i].Get_price() << endl;
		q_group += laptop[i].Get_quantity();
		cost_group += laptop[i].Get_quantity()*laptop[i].Get_price();
	}
	cout << "Итого по ноутбукам: " << q_group << " шт. " << cost_group << " руб." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	cout << "Итого: " << q_all << " шт. " << cost_all << " руб." << endl;
	system("pause");
}

//------------------------Проданные товара------------------------------------------------------------------
void Report_sold() {
	double cost_group = 0, cost_all = 0;
	int q_group = 0, q_all = 0;
	system("cls");
	Time();
	cout << "                    Продажа товара" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "     Наименование         Цена    Количество   Стоимость" << endl;
	cout << "                          (руб.)  (шт.)        (руб.)" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Компьютеры" << endl;
	for (int i = 0; i <= q_computer; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << computer[i].Get_brand() << setw(13) << left << computer[i].Get_model()
			<< setw(8) << left << computer[i].Get_price()
			<< setw(13) << left << computer[i].Get_sold() << setw(10) << left << computer[i].Get_sold()*computer[i].Get_price() << endl;
		q_group += computer[i].Get_sold();
		cost_group += computer[i].Get_sold()*computer[i].Get_price();
	}
	cout << "Итого по компьютерам: " << q_group << " шт. " << cost_group << " руб." << endl << endl;;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "Мониторы" << endl;
	for (int i = 0; i <= q_monitor; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << monitor[i].Get_brand() << setw(13) << left << monitor[i].Get_model()
			<< setw(8) << left << monitor[i].Get_price()
			<< setw(13) << left << monitor[i].Get_sold() << setw(10) << left << monitor[i].Get_sold()*monitor[i].Get_price() << endl;
		q_group += monitor[i].Get_sold();
		cost_group += monitor[i].Get_sold()*monitor[i].Get_price();
	}
	cout << "Итого по мониторам: " << q_group << " шт. " << cost_group << " руб." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "Принтеры" << endl;
	for (int i = 0; i <= q_printer; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << printer[i].Get_brand() << setw(13) << left << printer[i].Get_model()
			<< setw(8) << left << printer[i].Get_price()
			<< setw(13) << left << printer[i].Get_sold() << setw(10) << left << printer[i].Get_sold()*printer[i].Get_price() << endl;
		q_group += printer[i].Get_sold();
		cost_group += printer[i].Get_sold()*printer[i].Get_price();
	}
	cout << "Итого по принтерам: " << q_group << " шт. " << cost_group << " руб." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	q_group = 0, cost_group = 0;

	cout << "Ноутбуки" << endl;
	for (int i = 0; i <= q_laptop; i++) {
		cout << setw(2) << right << i + 1 << ". " << setw(9) << left << laptop[i].Get_brand() << setw(13) << left << laptop[i].Get_model()
			<< setw(8) << left << laptop[i].Get_price()
			<< setw(13) << left << laptop[i].Get_sold() << setw(10) << left << laptop[i].Get_sold()*laptop[i].Get_price() << endl;
		q_group += laptop[i].Get_sold();
		cost_group += laptop[i].Get_sold()*laptop[i].Get_price();
	}
	cout << "Итого по ноутбукам: " << q_group << " шт. " << cost_group << " руб." << endl << endl;
	cost_all += cost_group;
	q_all += q_group;
	cout << "Итого: " << q_all << " шт. " << cost_all << " руб." << endl;
	system("pause");
}

//------------------------Фильтр----------------------------------------------------------------------------
template <typename T>
void Filter(T *item, string brand, string model = "", double min_price = 0, double max_price = 0) {
	if (
		(brand == "" || item->Get_brand().find(brand) != string::npos) && // npos=-1
		(model == "" || item->Get_model().find(model) != string::npos) &&
		((min_price == 0 && max_price == 0) || (item->Get_price() >= min_price && item->Get_price() <= max_price))
		) {
		cout << setw(2) << right << Item::Get_nn_plus() << ". " << *item <<  endl; // вывод с нумерацией строк
	}
}

//------------------------Удаление строки-------------------------------------------------------------------
void Deleting() {
	Item *item;
	int choise1 = 0, choise2 = 0, q;

	cout << "Ранее было выполнено:\n" << Item::Get_log() << endl;

	while (true) {
		choise1 = Choise_group("Товар из какой категории вы хотите удалить?");
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
					cout << "Нет такого варианта:" << endl;
					system("pause");
					continue;
			}

			cout << "Укажите номер строки для удаления(0-выход): ";
			Get_number(choise2);

			if (choise2 == 0) break;
			if (choise2 <= 0 || choise2 > q+1) continue;

			switch (choise1) {
				case 0: 
					break;
				case 1: 
					computer[choise2-1].Show();
					Item::Add_log("удаление ");
					Item::Add_log(((computer[choise2 - 1].Get_brand()).append(" ")).append((computer[choise2 - 1].Get_model()).append("\n"))); // журнал работ
					for (int i = choise2 - 1; i < q_computer; i++) {
						computer[i] = computer[i + 1];
					}
					q_computer--;
					break;
				case 2: 
					monitor[choise2-1].Show();
					Item::Add_log("удаление ");
					Item::Add_log(((monitor[choise2 - 1].Get_brand()).append(" ")).append((monitor[choise2 - 1].Get_model()).append("\n"))); // журнал работ

					for (int i = choise2 - 1; i < q_monitor; i++) {
						monitor[i] = monitor[i + 1];
					}
					q_monitor--;
					break;
				case 3: 
					printer[choise2-1].Show();
					Item::Add_log("удаление ");
					Item::Add_log(((printer[choise2 - 1].Get_brand()).append(" ")).append((printer[choise2 - 1].Get_model()).append("\n"))); // журнал работ
					for (int i = choise2 - 1; i < q_printer; i++) {
						printer[i] = printer[i + 1];
					}
					q_printer--;
					break;
				case 4: 
					laptop[choise2-1].Show();
					Item::Add_log("удаление ");
					Item::Add_log(((laptop[choise2 - 1].Get_brand()).append(" ")).append((laptop[choise2 - 1].Get_model()).append("\n"))); // журнал работ
					for (int i = choise2 - 1; i < q_laptop; i++) {
						laptop[i] = laptop[i + 1];
					}
					q_laptop--;
					break;
				default: 
					cout << "Нет такого варианта:" << endl;
					system("pause");
					continue;
			}
			cout << "\nТовар удалён" << endl;
			system("pause");
		}
	}
}

//------------------------Перевод в строчные буквы----------------------------------------------------------
char* Upper(char *stroka) {
	char *new_stroka;
	new_stroka = (char*)calloc(strlen(stroka) + 1, sizeof(char));
	for (int i = 0; i < strlen(stroka); i++) {
		new_stroka[i] = toupper(stroka[i]);
	}
	return new_stroka;
}

//------------------------Просмотр компьютеров--------------------------------------------------------------
void Look_computer() {
	cout << "Компьютеры" << endl;
	for (int i = 0; i <= q_computer; i++) {
		cout << setw(2) << right << i+1 << ". " << computer[i] << endl;
	}
	cout << l << endl;
}

//------------------------Просмотр принтеров----------------------------------------------------------------
void Look_printer() {
	cout << "Принтеры" << endl;
	for (int i = 0; i <= q_printer; i++) {
		cout << setw(2) << right << i + 1 << ". " << printer[i] << endl;
	}
	cout << l << endl;
}

//------------------------Просмотр мониторов----------------------------------------------------------------
void Look_monitor() {
	cout << "Мониторы" << endl;
	for (int i = 0; i <= q_monitor; i++) {
		cout << setw(2) << right << i + 1 << ". " << monitor[i] << endl;
	}
	cout << l << endl;
}

//------------------------Просмотр ноутбуков----------------------------------------------------------------
void Look_laptop() {
	cout << "Ноутбуки" << endl;
	for (int i = 0; i <= q_laptop; i++) {
		cout << setw(2) << right << i + 1 << ". " << laptop[i] << endl;
	}
	cout << l << endl;
}

//------------------------Просмотр всего--------------------------------------------------------------------
void Look_all() {
	system("cls");
	Title();
	Look_computer();
	Look_printer();
	Look_monitor();
	Look_laptop();
	system("pause");
}

//------------------------Сортировка------------------------------------------------------------------------
void Sorting() {
	int choise1 = 0, choise2 = 0;
	while (true) {
		cout << "Какую группу товаров хотите сортировать?"
			<< "\n1. Компьютеры"
			<< "\n2. Мониторы"
			<< "\n3. Принтеры"
			<< "\n4. Ноутбуки"
			<< "\n0. Выход" << endl;

		Get_number(choise1);
		if (choise1 == 0) break;
		if (choise1 < 1 || choise1 >4) {
			cout << "Нет такого варианта" << endl;
			continue;
		}
		while (true) {
			cout << ((choise1 == 1) ? "Компьютеры" : ((choise1 == 2) ? "Мониторы" : ((choise1 == 3) ?
				"Принтеры" : ((choise1 == 4) ? "Ноутбуки" : "")))) << "\n";
			cout << "Сортировка по:"
				<< "\n1. Бренду"
				<< "\n2. Цене"
				<< "\n0. Выход" << endl;
			Get_number(choise2);
			if (choise2 < 0 || choise2 > 2) {
				cout << "Нет такого варианта:" << endl;
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

//------------------------Сортировка------------------------------------------------------------------------
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
		// меняем местами
		dop = massiv[start_index];
		massiv[start_index] = massiv[smallest_index];
		massiv[smallest_index] = dop;
	}
	Title();
	for (int i = 0; i <= q; i++) {
		cout << setw(2) << right << i+1 << ". " << massiv[i] << endl;
	}
}

//------------------------Фильтр----------------------------------------------------------------------------
void Filtering() {
	string brand="";
	string model="";
	int choise1, choise2;
	double max_price=0, min_price=0;
	while (true) {
		cout << "По какой группе товаров вы хотите фильтровать?"
			<< "\n1. По всем товарам"
			<< "\n2. По компьютерам"
			<< "\n3. По мониторам"
			<< "\n4. По принтерам"
			<< "\n5. По ноутбукам" 
			<< "\n0. Выход"  << endl;

		Get_number(choise1);
		if (choise1 == 0) break;
		if (choise1<1 || choise1 >5) {
			cout << "Нет такого варианта." << endl;
			continue;
		}

		while (true) {
			cout << ((choise1 == 1) ? "Все товары" : ((choise1 == 2) ? "Компьютеры" : ((choise1 == 3) ? "Мониторы" : ((choise1 == 4) ?
				"Принтеры" : ((choise1 == 5)? "Ноутбуки" : ""))))) << "\n";
			cout << "По каким параметрам?"
				<< "\n1. Бренд"
				<< "\n2. Модель"
				<< "\n3. Цена" 
				<< "\n0. Выход" << endl;
			Get_number(choise2);
			if (choise2 == 0) break;
			switch (choise2) {
			case 1: {
				cout << "Введите название бренда: " << endl;
				cin >> brand;
				break;
			}
			case 2: {
				cout << "Введите название модели: " << endl;
				cin >> model;
				break;
			}
			case 3: {
				cout << "\nВведите минимальную цену: ";
				Get_number(min_price);
				cout << "\nВведите максимальную цену: ";
				Get_number(max_price);
				break;
			}
			default: cout << "Нет такого варианта:" << endl;
				continue;
			}
			system("cls");
			cout << "Установлен фильтр: ";
			if (brand != "") { cout << "бренд " << brand; } 
			if (model != "") { cout << " модель " << model;}
			if (max_price + min_price != 0) { cout << " цена от " << min_price << " до " << max_price; }
			cout << endl;
			Title();
			Item::Set_nn(0); // обнуление нумерации (static переменная)
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

//------------------------Добавление компьютера-------------------------------------------------------------
void Add(Computer &computer) {
	string brand, model, processor;
	double price;
	int quantity;

	cout << "Бренд: ";
	brand = Spr_brand.Choise();

	cout << "Модель: ";
	getline(cin, model);

	cout << "Цена: ";
	Get_number(price);

	cout << "Количество: ";
	Get_number(quantity); 
	computer.Set_Item(brand, model, price, quantity, 0);

	cout << "Процессор: " ;
	getline(cin, processor);
	computer.Set_processor(processor);
}

//------------------------Добавление монитора---------------------------------------------------------------
void Add(Monitor &monitor) {
	string brand, model;
	double price, diagonal;
	int quantity, resolution;

	cout << "Бренд: ";
	brand = Spr_brand.Choise();

	cout << "Модель: ";
	getline(cin, model);

	cout << "Цена: ";
	Get_number(price);

	cout << "Количество: ";
	Get_number(quantity); 
	monitor.Set_Item(brand, model, price, quantity, 0);


	cout << "Диагональ: ";
	diagonal = Spr_diagonal.Choise();
	monitor.Set_diagonal(diagonal);

	cout << "Разрешение: ";
	resolution = Spr_resolution.Choise();
	monitor.Set_resolution(resolution);
}

//------------------------Добавление принтера---------------------------------------------------------------
void Add(Printer &printer) {
	string brand, model, type;
	double price;
	int quantity, speed;

	cout << "Бренд: ";
	brand = Spr_brand.Choise();

	cout << "Модель: ";
	getline(cin, model);

	cout << "Цена: ";
	Get_number(price);

	cout << "Количество: ";
	Get_number(quantity); 
	printer.Set_Item(brand, model, price, quantity, 0);

	cout << "Тип: ";
	getline(cin, type);
	printer.Set_type(type);

	cout << "Скорость: ";
	Get_number(speed); 
	printer.Set_speed(speed);
}

//------------------------Добавление ноутбука---------------------------------------------------------------
void Add(Laptop &laptop) {
	string brand, model, processor;
	double price, diagonal, weight;
	int quantity;

	cout << "Бренд: ";
	brand=Spr_brand.Choise();

	cout << "Модель: ";
	getline(cin, model);

	cout << "Цена: ";
	Get_number(price);

	cout << "Количество: ";
	Get_number(quantity); 
	laptop.Set_Item(brand, model, price, quantity, 0);

	cout << "Процессор: ";
	getline(cin, processor);
	laptop.Set_processor(processor);

	cout << "Диагональ: ";
	diagonal = Spr_diagonal.Choise();
	laptop.Set_diagonal(diagonal);

	cout << "Вес: ";
	Get_number(weight); 
	laptop.Set_weight(weight);
}

//------------------------Добавление------------------------------------------------------------------------
void Adding() {
	Item *item;
	int choise1 = 0, choise2 = 0, q;

	cout << "Ранее было выполнено:\n" << Item::Get_log() << endl;

	while (true) {
		choise1 = Choise_group("\nТовар какой категории хотите добавить?");
		if (choise1 == 0) break;
		system("cls");
		switch (choise1) {
		case 1:
			Title();
			Look_computer();
			q_computer++;
			Add(computer[q_computer]);
			Item::Add_log("добавление ");
			Item::Add_log(((computer[q_computer].Get_brand()).append(" ")).append((computer[q_computer].Get_model()).append("\n"))); // журнал работ
			break;
		case 2:
			Title();
			Look_monitor();
			q_monitor++;
			Add(monitor[q_monitor]);
			Item::Add_log("добавление ");
			Item::Add_log(((monitor[q_monitor].Get_brand()).append(" ")).append((monitor[q_monitor].Get_model()).append("\n"))); // журнал работ
			break;
		case 3:
			Title();
			Look_printer();
			q_printer++;
			Add(printer[q_printer]);
			Item::Add_log("добавление ");
			Item::Add_log(((printer[q_printer].Get_brand()).append(" ")).append((printer[q_printer].Get_model()).append("\n"))); // журнал работ
			break;
		case 4:
			Title();
			Look_laptop();
			q_laptop++;
			Add(laptop[q_laptop]);
			Item::Add_log("добавление ");
			Item::Add_log(((laptop[q_laptop].Get_brand()).append(" ")).append((laptop[q_laptop].Get_model()).append("\n"))); // журнал работ
			break;
		default:
			cout << "Нет такого варианта:" << endl;
			system("pause");
			continue;
		}
		cout << "Добавлено" << endl;
		system("pause");
	}
}

//------------------------Редактирование компьютера---------------------------------------------------------
void Edit(Computer &computer) {
	string brand, model, processor;
	double price;
	int quantity, choise;

	computer.Show();
	cout << "\nВыберите поле для редактирования:"
		<< "\n1. Бренд и модель"
		<< "\n2. Цена"
		<< "\n3. Количество"
		<< "\n4. Процессор"
		<< "\n0. Выход" << endl;
	while (true) {
		Get_number(choise);

		switch (choise) {
		case 1:
			cout << "Бренд: ";
			brand = Spr_brand.Choise();
			cout << "Модель: ";
			getline(cin, model);
			computer.Set_Item(brand, model);
			break;
		case 2: 
			cout << "Цена: ";
			Get_number(price);
			computer.Set_Item(price);
			break;
		case 3: 
			cout << "Количество: ";
			Get_number(quantity);
			computer.Set_Item(quantity);
			break;
		case 4: 
			cout << "Процессор: ";
			getline(cin, processor);
			computer.Set_processor(processor);
			break;
		case 0:
			break;
		default: cout << "Нет такого варианта!\n";
			system("pause");
			break;
		}
		if (choise >= 0 && choise <=4) break;
	}
}

//------------------------Редактирование монитора-----------------------------------------------------------
void Edit(Monitor &monitor) {
	string brand, model, processor;
	double price, diagonal;
	int quantity, resolution, choise;

	monitor.Show();
	cout << "\nВыберите поле для редактирования:"
		<< "\n1. Бренд и модель"
		<< "\n2. Цена"
		<< "\n3. Количество"
		<< "\n4. Диагональ"
		<< "\n5. Разрешение"
		<< "\n0. Выход" << endl;
	while (true) {
		Get_number(choise);

		switch (choise) {
		case 1:
			cout << "Бренд: ";
			brand = Spr_brand.Choise();
			cout << "Модель: ";
			getline(cin, model);
			monitor.Set_Item(brand, model);
			break;
		case 2:
			cout << "Цена: ";
			Get_number(price);
			monitor.Set_Item(price);
			break;
		case 3:
			cout << "Количество: ";
			Get_number(quantity);
			monitor.Set_Item(quantity);
			break;
		case 4:
			cout << "Диагональ: ";
			diagonal = Spr_diagonal.Choise();
			monitor.Set_diagonal(diagonal);
			break;
		case 5:
			cout << "Разрешение: ";
			resolution = Spr_resolution.Choise();
			monitor.Set_resolution(resolution);
			break;
		case 0:
			break;
		default: cout << "Нет такого варианта!\n";
			system("pause");
			break;
		}
		if (choise >= 0 && choise <= 5) break;
	}
}

//------------------------Редактирование принтера-----------------------------------------------------------
void Edit(Printer &printer) {
	string brand, model, type;
	double price;
	int quantity, speed, choise;

	printer.Show();
	cout << "\nВыберите поле для редактирования:"
		<< "\n1. Бренд и модель"
		<< "\n2. Цена"
		<< "\n3. Количество"
		<< "\n4. Тип"
		<< "\n5. Скорость"
		<< "\n0. Выход" << endl;
	while (true) {
		Get_number(choise);

		switch (choise) {
		case 1:
			cout << "Бренд: ";
			brand = Spr_brand.Choise();
			cout << "Модель: ";
			getline(cin, model);
			printer.Set_Item(brand, model);
			break;
		case 2:
			cout << "Цена: ";
			Get_number(price);
			printer.Set_Item(price);
			break;
		case 3:
			cout << "Количество: ";
			Get_number(quantity);
			printer.Set_Item(quantity);
			break;
		case 4:
			cout << "Тип: ";
			getline(cin, type);
			printer.Set_type(type);
			break;
		case 5:
			cout << "Скорость: ";
			Get_number(speed);
			printer.Set_speed(speed);
			break;
		case 0:
			break;
		default: cout << "Нет такого варианта!\n";
			system("pause");
			break;
		}
		if (choise >= 0 && choise <= 5) break;
	}
}

//------------------------Редактирование ноутбука-----------------------------------------------------------
void Edit(Laptop &laptop) {
	string brand, model, processor;
	double price, diagonal, weight;
	int quantity, choise;

	laptop.Show();
	cout << "\nВыберите поле для редактирования:"
		<< "\n1. Бренд и модель"
		<< "\n2. Цена"
		<< "\n3. Количество"
		<< "\n4. Процессор"
		<< "\n5. Диагональ"
		<< "\n6. Вес"
		<< "\n0. Выход" << endl;
	while (true) {
		Get_number(choise);

		switch (choise) {
		case 1:
			cout << "Бренд: ";
			brand = Spr_brand.Choise();
			cout << "Модель: ";
			getline(cin, model);
			laptop.Set_Item(brand, model);
			break;
		case 2:
			cout << "Цена: ";
			Get_number(price);
			laptop.Set_Item(price);
			break;
		case 3:
			cout << "Количество: ";
			Get_number(quantity);
			laptop.Set_Item(quantity);
			break;
		case 4:
			cout << "Процессор: ";
			getline(cin, processor);
			laptop.Set_processor(processor);
			break;
		case 5:
			cout << "Диагональ: ";
			diagonal = Spr_diagonal.Choise();
			laptop.Set_diagonal(diagonal);
			break;
		case 6:
			cout << "Вес: ";
			Get_number(weight);
			laptop.Set_weight(weight);
			break;
		case 0:
			break;
		default: cout << "Нет такого варианта!\n";
			system("pause");
			break;
		}
		if (choise >= 0 && choise <= 6) break;
	}
}

//------------------------Редактирование--------------------------------------------------------------------
void Editing() {
	int choise1 = 0, choise2 = 0, q;
	cout << "Ранее было выполнено:\n" << Item::Get_log() << endl;
	while (true) {
		choise1 = Choise_group("Товар из какой категории вы хотите редактировать?");
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
				cout << "Нет такого варианта:" << endl;
				system("pause");
				continue;
			}

			cout << "Укажите номер строки для редактирования(0-выход): ";
			Get_number(choise2);

			if (choise2 == 0) break;
			if (choise2 <= 0 || choise2 > q + 1) continue;

			switch (choise1) {
			case 0:
				break;
			case 1:
				Edit(computer[choise2 - 1]);
				Item::Add_log("редактирование ");
				Item::Add_log(((computer[choise2 - 1].Get_brand()).append(" ")).append((computer[choise2 - 1].Get_model()).append("\n")));
				break;
			case 2:
				Edit(monitor[choise2 - 1]);
				Item::Add_log("редактирование ");
				Item::Add_log(((monitor[choise2 - 1].Get_brand()).append(" ")).append((monitor[choise2 - 1].Get_model()).append("\n")));
				break;
			case 3:
				Edit(printer[choise2 - 1]);
				Item::Add_log("редактирование ");
				Item::Add_log(((printer[choise2 - 1].Get_brand()).append(" ")).append((printer[choise2 - 1].Get_model()).append("\n")));
				break;
			case 4:
				Edit(laptop[choise2 - 1]);
				Item::Add_log("редактирование ");
				Item::Add_log(((laptop[choise2 - 1].Get_brand()).append(" ")).append((laptop[choise2 - 1].Get_model()).append("\n")));
				break;
			default:
				cout << "Нет такого варианта:" << endl;
				system("pause");
				continue;
			}

			cout << "\nТовар отредактирован" << endl;
			system("pause");
		}
	}
}

//------------------------Топ продаж------------------------------------------------------------------------
void Report_best() {
	double cost_group = 0, cost_all = 0;
	int q_group = 0, q_all = 0;
	system("cls");
	Time();
	cout << "                    Топ товаров" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "  Наименование        Цена    Количество   Стоимость" << endl;
	cout << "                      (руб.)  (шт.)        (руб.)" << endl;
	cout << "--------------------------------------------------------" << endl;

	cout << "Компьютеры" << endl;
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

	cout << "Мониторы" << endl;
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

	cout << "Принтеры" << endl;
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

	cout << "Ноутбуки" << endl;
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

//------------------------Открытие файла--------------------------------------------------------------------
int User::Login() {

	FILE *log_file;
	int i = 0, role;
	char log[20], pass[30], login[20], password[30];

	cout << "Введите логин: ";
	cin >> log;
	cout << "Введите пароль: ";
	cin >> pass;

	if ((log_file = fopen("Login_and_password.txt", "r")) == NULL)
	{
		puts("Открыть файл не удалось.\n");
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
		puts("Файл пуст\n");
	}
	return -1;
}

//------------------------Шифрование------------------------------------------------------------------------
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

//------------------------Управление пользователями---------------------------------------------------------
void User::Users() {
		int i = 0, kol_users = 0, n_del = 0, no_yes = 0;
		int choise;
		ifstream inf("Login_and_password.txt");

		if (!inf) { // если мы не можем открыть этот файл для чтения его содержимого
			cerr << "Ошибка, файл Login_and_password.txt не открылся!" << endl;
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
				cout << i + 1 << ". " << users[i].login << " " << (users[i].role == 1 ? "Администратор" : "Пользователь") << endl;
			}
			cout << "\n1. Удаление пользователя\n";
			cout << "2. Добавление пользователя\n";
			cout << "0. Выход из управления пользователями\n\n";
			cout << "Ваш выбор: ";

			Get_number(choise);
			cout << "\n";

			switch (choise) {
			case 1:
				cout << "\nВведите номер записи, которую хотите удалить: ";
				while (n_del<1 || n_del>kol_users) {
					Get_number(n_del);
					if (n_del<1 || n_del>kol_users) {
						cout << "Введён неверный номер. Введите номер от 1 до " << kol_users;
					}
					else {
						cout << "\nА Вы точно хотите удалить?(0-нет; 1-да) - ";
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
				cout << "Введите данные о пользователе:\n";

				kol_users++;

				cout << "Логин: ";
				cin >> users[kol_users - 1].login;

				cout << "Пароль: ";
				cin >> users[kol_users - 1].password;
				cin.ignore(32767, '\n');
				Crypt(users[kol_users - 1].password);

				cout << "Роль (1-Администратор, 2-Пользователь): ";
				Get_number(users[kol_users - 1].role);
				break;

			case 0: {
				ofstream outf("Login_and_password.txt");

				if (!outf) { // если мы не можем открыть этот файл для записи его содержимого
					cerr << "Ошибка, файл Login_and_password.txt не открылся для записи!" << endl;
					break;
				}

				for (int i = 0; i <= kol_users - 1; i++) {
					outf << users[i].login << " " << users[i].password << " " << users[i].role << endl;
				}
				outf.close();
				break;
			}
			default:
				cout << "Нет такого варианта!\n";
				system("pause");
				break;
			}
			if (choise == 0) break;
		}
	}