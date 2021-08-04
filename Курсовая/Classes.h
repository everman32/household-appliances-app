#include <iostream>
#include <string>
#include "Menu.h"

using namespace std;

//������� �����------------------------------------------------------------------------
class Item {
	string m_brand;
	string m_model;
	double m_price;
	int m_quantity;
	int m_sold;
	static string m_log;
	static int m_nn; // ��������� ���������� ����� �� �������

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
		cout << "\n" << m_brand << " ������ " << m_model << "\n����: " << m_price << " �. \n����������: " << m_quantity << " ��."<< endl;
	}

	virtual void Print_order(int kol) = 0; // ������ ����������� ������� - ����������� ������� => ����������� �����

	static void Add_log(string log) {
		m_log.append(log); // �������� ����� log � �������������
	}
	static string Get_log() { return m_log; }

	static void Set_nn(int nn) {
		m_nn = nn;
	}
	static int Get_nn_plus() {
		return ++m_nn;
	}
};

//����� ���������----------------------------------------------------------------------
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
		cout << "����� �� ��������� " << Get_brand() << " ������ "<< Get_model()<< endl;
		cout << "��������� " << m_processor << endl;
		cout << "���� " << Get_price() << " ���." << endl;
		cout << "���������� " << kol << " ��." <<endl;
		cout << "��������� " << Get_price() * kol << " ���." << endl;
	}

	void Show() {
		Item::Show();
		cout << "���������: " << m_processor << endl;
	}

	friend ostream& operator<< (ostream &out, const Computer &computer);
};

//����� �������------------------------------------------------------------------------
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
		cout << "����� �� ������� " << Get_brand() << " ������ " << Get_model() << endl;
		cout << "��� " << m_type << endl;
		cout << "�������� " << m_speed << " ����/���" << endl;
		cout << "���� " << Get_price() << " ���." << endl;
		cout << "���������� " << kol << " ��." << endl;
		cout << "��������� " << Get_price() * kol << " ���." << endl;
	}

	void Show() {
		Item::Show();
		cout << "���: " << m_type << "\n��������: " << m_speed << " ����/���" << endl;
	}

	friend ostream& operator<< (ostream &out,  const Printer &printer);
};

//����� �������------------------------------------------------------------------------
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
		cout << "����� �� ������� " << Get_brand() << " ������ " << Get_model() << endl;
		cout << "��������� " << m_diagonal << "\"" << endl;
		cout << "���������� " << m_resolution << endl;
		cout << "���� " << Get_price() << " ���." << endl;
		cout << "���������� " << kol << " ��." << endl;
		cout << "��������� " << Get_price() * kol << " ���." << endl;
	}

	void Show() {
		Item::Show();
		cout << "���������: " << m_diagonal << "\"\n����������: " << m_resolution << endl;
	}

	friend ostream& operator<< (ostream &out, const Monitor &monitor);
};

//����� �������------------------------------------------------------------------------
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
		cout << "����� �� ������� " << Get_brand() << " ������ " << Get_model() << endl;
		cout << "��������� " << m_processor << endl;
		cout << "��������� " << m_diagonal << "''" << endl;
		cout << "��� " << m_weight << " ��" << endl;
		cout << "���� " << Get_price() << " ���." << endl;
		cout << "���������� " << kol << " ��." << endl;
		cout << "��������� " << Get_price() * kol << " ���." << endl;
	}

	void Show() {
		Item::Show();
		cout << "���������: " << m_processor << "\n���������: " << m_diagonal << "\"\n���: " << m_weight << " ��" << endl;
	}

	friend ostream& operator<< (ostream &out, const Laptop &Laptop);
};

//����� ����������---------------------------------------------------------------------
template <class T>
class Spravochnik { // ��������� 
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
		cout << "�������� ����� ������: ";
		
		while (n <= 0 || n > m_size) {
			Get_number(n);
			if (n <= 0 || n > m_size) {
				cout << "����� ������ ���� � ��������� �� 1 �� " << m_size << endl;
			}
		}
		cout << m_elements[n - 1] << endl;
		return m_elements[n - 1];
	}
};

