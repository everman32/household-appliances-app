#include <iostream>
#include <string>
#include "Menu.h"

using namespace std;

//Базовый класс------------------------------------------------------------------------
class Item {
	string m_brand;
	string m_model;
	double m_price;
	int m_quantity;
	int m_sold;
	static string m_log;
	static int m_nn; // статичная переменная номер по порядку

public:
	Item(string brand="", string model="", double price=0, int quantity=0, int sold=0):
		m_brand(brand), m_model(model), m_price(price), m_quantity(quantity), m_sold(sold) {
	}

	void Set_Item(string brand, string model, double price, int quantity, int sold) {
		m_brand = brand;
		m_model = model;
		m_price = price;
		m_quantity = quantity;
		m_sold = sold;
	}
	void Set_Item(string brand, string model) {
		m_brand = brand;
		m_model = model;
	}
	void Set_Item(double price) { m_price = price; }
	void Set_Item(int quantity) { m_quantity = quantity; }
	void Add_sold(int sold) { m_sold += sold; }

	string Get_brand() const { return m_brand; }
	string Get_model() const { return m_model; }
	double Get_price() const { return m_price; }
	int Get_quantity() const { return m_quantity; }
	int Get_sold() const { return m_sold; }

	void Show() {
		cout << "\n" << m_brand << " модель " << m_model << "\nЦена: " << m_price << " р. \nКоличество: " << m_quantity << " шт."<< endl;
	}

	virtual void Print_order(int kol) = 0; // чистая виртуальная функция - абстрактная функция => абстрактный класс

	static void Add_log(string log) {
		m_log.append(log); // добавить текст log к существующему
	}
	static string Get_log() { return m_log; }

	static void Set_nn(int nn) {
		m_nn = nn;
	}
	static int Get_nn_plus() {
		return ++m_nn;
	}
};

//Класс компьютер----------------------------------------------------------------------
class Computer : public Item {
	string m_processor;

public:
	Computer(string brand = "", string model = "", double price = 0, int quantity = 0, string processor = "") :
		Item(brand, model, price, quantity),
		m_processor(processor) {
	}

	void Set(string brand = "", string model = "", double price = 0, int quantity = 0, int sold = 0, string processor = "") {
		Set_Item(brand, model, price, quantity, sold);
		m_processor = processor;
	}
	void Set_processor(string processor) { m_processor = processor; }

	string Write() {
		return Get_brand() + ";" + Get_model() + ";" + to_string(Get_price()) + ";" + to_string(Get_quantity()) + ";" + to_string(Get_sold()) + ";" + m_processor;
	}

	virtual void Print_order(int kol) {
		cout << "Заказ на компьютер " << Get_brand() << " модель "<< Get_model()<< endl;
		cout << "Процессор " << m_processor << endl;
		cout << "Цена " << Get_price() << " руб." << endl;
		cout << "Количество " << kol << " шт." <<endl;
		cout << "Стоимость " << Get_price() * kol << " руб." << endl;
	}

	void Show() {
		Item::Show();
		cout << "Процессор: " << m_processor << endl;
	}

	friend ostream& operator<< (ostream &out, const Computer &computer);
};

//Класс принтер------------------------------------------------------------------------
class Printer : public Item {
	string m_type;
	int m_speed;

public: 
	Printer(string brand = "", string model = "", double price = 0, int quantity = 0, string type = "-", int speed= 0) :
		Item(brand, model, price, quantity),
		m_type(type), m_speed(speed) {
	}

	void Set(string brand = "", string model = "", double price = 0, int quantity = 0, int sold = 0, string type = "", int speed = 0) {
		Set_Item(brand, model, price, quantity, sold);
		m_type = type;
		m_speed = speed;
	}
	void Set_type(string type) { m_type = type; }
	void Set_speed(int speed) { m_speed = speed; }

	string Write() {
		return Get_brand() + ";" + Get_model() + ";" + to_string(Get_price()) + ";" + to_string(Get_quantity()) + ";" + to_string(Get_sold()) + ";" +m_type+";"+to_string(m_speed);
	}

	virtual void Print_order(int kol) {
		cout << "Заказ на принтер " << Get_brand() << " модель " << Get_model() << endl;
		cout << "Тип " << m_type << endl;
		cout << "Скорость " << m_speed << " лист/мин" << endl;
		cout << "Цена " << Get_price() << " руб." << endl;
		cout << "Количество " << kol << " шт." << endl;
		cout << "Стоимость " << Get_price() * kol << " руб." << endl;
	}

	void Show() {
		Item::Show();
		cout << "Тип: " << m_type << "\nСкорость: " << m_speed << " лист/мин" << endl;
	}

	friend ostream& operator<< (ostream &out,  const Printer &printer);
};

//Класс монитор------------------------------------------------------------------------
class Monitor : public Item {
	double m_diagonal;
	int m_resolution;

public:
	Monitor(string brand = "", string model = "", double price = 0, int quantity = 0, double diagonal = 0.0, int resolution = 0) :
		Item(brand, model, price, quantity),
		m_diagonal(diagonal), m_resolution(resolution) {}

	void Set(string brand = "", string model = "", double price = 0, int quantity = 0, int sold = 0, double diagonal = 0, int resolution = 0) {
		Set_Item(brand, model, price, quantity, sold);
		m_diagonal = diagonal;
		m_resolution = resolution;
	}
	void Set_diagonal(double diagonal) { m_diagonal = diagonal; }
	void Set_resolution(int resolution) { m_resolution = resolution; }

	string Write() {
		return Get_brand() + ";" + Get_model() + ";" + to_string(Get_price()) + ";" + to_string(Get_quantity()) + ";" + to_string(Get_sold()) + ";" + to_string(m_diagonal) + ";" + to_string(m_resolution);
	}

	virtual void Print_order(int kol) {
		cout << "Заказ на монитор " << Get_brand() << " модель " << Get_model() << endl;
		cout << "Диагональ " << m_diagonal << "\"" << endl;
		cout << "Разрешение " << m_resolution << endl;
		cout << "Цена " << Get_price() << " руб." << endl;
		cout << "Количество " << kol << " шт." << endl;
		cout << "Стоимость " << Get_price() * kol << " руб." << endl;
	}

	void Show() {
		Item::Show();
		cout << "Диагональ: " << m_diagonal << "\"\nРазрешение: " << m_resolution << endl;
	}

	friend ostream& operator<< (ostream &out, const Monitor &monitor);
};

//Класс ноутбук------------------------------------------------------------------------
class Laptop : public Item {
	string m_processor;
	double m_diagonal;
	double m_weight;

public:
	Laptop(string brand = "", string model = "", double price = 0, int quantity = 0, string processor = "", double diagonal = 0, double weight = 0) :
		Item(brand, model, price, quantity),
		m_processor(processor), m_diagonal(diagonal), m_weight(weight) {}

	void Set(string brand = "", string model = "", double price = 0, int quantity = 0, int sold = 0, string processor = "", double diagonal = 0, double weight = 0) {
		Set_Item(brand, model, price, quantity, sold);
		m_processor = processor;
		m_diagonal = diagonal;
		m_weight = weight;
	}
	void Set_processor(string processor) { m_processor = processor; }
	void Set_diagonal(double diagonal) { m_diagonal = diagonal; }
	void Set_weight(double weight) { m_weight = weight; }

	string Write() {
		return Get_brand() + ";" + Get_model() + ";" + to_string(Get_price()) + ";" + to_string(Get_quantity()) + ";" + to_string(Get_sold()) + ";" + m_processor + ";" + to_string(m_diagonal) + ";" + to_string(m_weight);
	}

	virtual void Print_order(int kol) {
		cout << "Заказ на ноутбук " << Get_brand() << " модель " << Get_model() << endl;
		cout << "Процессор " << m_processor << endl;
		cout << "Диагональ " << m_diagonal << "''" << endl;
		cout << "Вес " << m_weight << " кг" << endl;
		cout << "Цена " << Get_price() << " руб." << endl;
		cout << "Количество " << kol << " шт." << endl;
		cout << "Стоимость " << Get_price() * kol << " руб." << endl;
	}

	void Show() {
		Item::Show();
		cout << "Процессор: " << m_processor << "\nДиагональ: " << m_diagonal << "\"\nВес: " << m_weight << " кг" << endl;
	}

	friend ostream& operator<< (ostream &out, const Laptop &Laptop);
};

//Класс справочник---------------------------------------------------------------------
template <class T>
class Spravochnik { // множество 
	int m_size;
	T *m_elements;

public:
	Spravochnik(int size) {
		m_elements = new T[size];
		m_size = size;
	}
	~Spravochnik() {
		delete[] m_elements;
	};
	void Add(int i, T s) {
		m_elements[i] = s;
	}
	T Choise() {
		int n = 0;
		cout << endl;
		for (int i = 0; i < m_size; i++) {
			cout << i + 1 << "-" << m_elements[i] << endl;
		}
		cout << "Выберите пункт списка: ";
		
		while (n <= 0 || n > m_size) {
			Get_number(n);
			if (n <= 0 || n > m_size) {
				cout << "Число должно быть в диапозоне от 1 до " << m_size << endl;
			}
		}
		cout << m_elements[n - 1] << endl;
		return m_elements[n - 1];
	}
};

