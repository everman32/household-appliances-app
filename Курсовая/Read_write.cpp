#include <fstream>
#include <iostream>
#include <string>
#include "Classes.h"
#include "Read_write.h"

using namespace std;

extern Computer *computer;
extern Printer *printer;
extern Monitor *monitor;
extern Laptop *laptop;
extern int q_printer;
extern int q_computer;
extern int q_monitor;
extern int q_laptop;

string strInput;
size_t found1;
size_t found2;
size_t found3;
size_t found4;
size_t found5;
size_t found6;
size_t found7;

//Чтение из файла Printer.txt-------------------------------------------------------------------------------------------------
int Read_printer() {
	ifstream inf("Printer.txt");
	
	if (!inf) { // если мы не можем открыть этот файл для чтения его содержимого
		return 1;
	}
	while (inf) { // пока есть данные, которые мы можем прочитать
		getline(inf, strInput); // читаем строку файла
		if (strInput.length() == 0) { // последняя строка - она пустая
			break;
		}
		found1 = strInput.find(";");
		found2 = strInput.find(";", found1 + 1);
		found3 = strInput.find(";", found2 + 1);
		found4 = strInput.find(";", found3 + 1);
		found5 = strInput.find(";", found4 + 1);
		found6 = strInput.find(";", found5 + 1);

		q_printer++;

		printer[q_printer].Set(
			strInput.substr(0, found1),
			strInput.substr(found1 + 1, found2 - found1 - 1),
			stod(strInput.substr(found2 + 1, found3 - found2 - 1)),
			stoi(strInput.substr(found3 + 1, found4 - found3 - 1)),
			stoi(strInput.substr(found4 + 1, found5 - found4 - 1)),
			strInput.substr(found5 + 1, found6 - found5 - 1),
			stoi(strInput.substr(found6 + 1))
		);
	}
	inf.close();
	return 0;
}

//Запись в файл Printer.txt---------------------------------------------------------------------------------------------------
int Write_printer() {
	ofstream outf("Printer.txt");
	if (!outf) {
		cerr << "Ошибка, файл Printer.txt не открылся!" << endl;
		exit(1);
	}
	for (int i = 0; i <= q_printer; i++) {
		outf << printer[i].Write() <<"\n";
	}
	outf.close();
}

//Чтение из файла Computer.txt------------------------------------------------------------------------------------------------
int Read_computer() {

	ifstream inf("Computer.txt");

	if (!inf)// Если мы не можем открыть этот файл для чтения его содержимого
	{
		return 1;
	}

	while (inf)// Пока есть данные, которые мы можем прочитать
	{
		getline(inf, strInput); // Читаем строку файла
		if (strInput.length() == 0) { //последняя срока - она пустая
			break;
		}
		found1 = strInput.find(";");
		found2 = strInput.find(";", found1 + 1);
		found3 = strInput.find(";", found2 + 1);
		found4 = strInput.find(";", found3 + 1);
		found5 = strInput.find(";", found4 + 1);
		
		q_computer++;
		computer[q_computer].Set(
			strInput.substr(0, found1),
			strInput.substr(found1 + 1, found2 - found1 - 1),
			stod(strInput.substr(found2 + 1, found3 - found2 - 1)),
			stoi(strInput.substr(found3 + 1, found4 - found3 - 1)),
			stoi(strInput.substr(found4 + 1, found5 - found4 - 1)),
			strInput.substr(found5 + 1)
		);
	}
	inf.close();
	return 0;
}

//Запись в файл Computer.txt--------------------------------------------------------------------------------------------------
int Write_computer() {
	ofstream outf("Computer.txt");
	if (!outf) {
		cerr << "Ошибка, файл Computer.txt не открылся!" << endl;
		exit(1);
	}
	for (int i = 0; i <= q_computer; i++) {
		outf << computer[i].Write() << "\n";
	}
	outf.close();
}

//Чтение из файла Monitor.txt-------------------------------------------------------------------------------------------------
int Read_monitor() {

	ifstream inf("Monitor.txt");

	if (!inf)// Если мы не можем открыть этот файл для чтения его содержимого
	{
		return 1;
	}

	while (inf)// Пока есть данные, которые мы можем прочитать
	{
		getline(inf, strInput); // Читаем строку файла
		if (strInput.length() == 0) { //последняя срока - она пустая
			break;
		}
		found1 = strInput.find(";");
		found2 = strInput.find(";", found1 + 1);
		found3 = strInput.find(";", found2 + 1);
		found4 = strInput.find(";", found3 + 1);
		found5 = strInput.find(";", found4 + 1);
		found6 = strInput.find(";", found5 + 1);

		q_monitor++;
	    monitor[q_monitor].Set(
			strInput.substr(0, found1),
			strInput.substr(found1 + 1, found2 - found1 - 1),
			stod(strInput.substr(found2 + 1, found3 - found2 - 1)),
			stoi(strInput.substr(found3 + 1, found4 - found3 - 1)),
			stoi(strInput.substr(found4 + 1, found5 - found4 - 1)),
			stod(strInput.substr(found5 + 1, found6 - found5 - 1)),
			stoi(strInput.substr(found6 + 1))
		);
	}
	inf.close();
	return 0;
}

//Запись в файл Moitor.txt----------------------------------------------------------------------------------------------------
int Write_monitor() {
	ofstream outf("Monitor.txt");
	if (!outf) {
		cerr << "Ошибка, файл Monitor.txt не открылся!" << endl;
		exit(1);
	}
	for (int i = 0; i <= q_monitor; i++) {
		outf << monitor[i].Write() << "\n";
	}
	outf.close();
}

//Чтение из файла Laptop.txt--------------------------------------------------------------------------------------------------
int Read_laptop() {

	ifstream inf("Laptop.txt");

	if (!inf)// Если мы не можем открыть этот файл для чтения его содержимого
	{
		return 1;
	}

	while (inf)// Пока есть данные, которые мы можем прочитать
	{
		//inf >> strInput;
		getline(inf, strInput); // Читаем строку файла
		if (strInput.length() == 0) { //последняя срока - она пустая
			break;
		}
		found1 = strInput.find(";");
		found2 = strInput.find(";", found1 + 1);
		found3 = strInput.find(";", found2 + 1);
		found4 = strInput.find(";", found3 + 1);
		found5 = strInput.find(";", found4 + 1);
		found6 = strInput.find(";", found5 + 1);
		found7 = strInput.find(";", found6 + 1);

		q_laptop++;
		laptop[q_laptop].Set(
			strInput.substr(0, found1),
			strInput.substr(found1 + 1, found2 - found1 - 1),
			stod(strInput.substr(found2 + 1, found3 - found2 - 1)),
			stoi(strInput.substr(found3 + 1, found4 - found3 - 1)),
			stoi(strInput.substr(found4 + 1, found5 - found4 - 1)),
			strInput.substr(found5 + 1, found6 - found5 - 1),
			stod(strInput.substr(found6 + 1, found7 - found6 - 1)),
			stod(strInput.substr(found7 + 1))
		);
	}
	inf.close();
	return 0;
}

//Запись в файл Laptop.txt----------------------------------------------------------------------------------------------------
int Write_laptop() {
	ofstream outf("Laptop.txt");
	if (!outf) {
		cerr << "Ошибка, файл Laptop.txt не открылся!" << endl;
		exit(1);
	}
	for (int i = 0; i <= q_laptop; i++) {
		outf << laptop[i].Write() << "\n";
	}
	outf.close();
	return 1;
}