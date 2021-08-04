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

//������ �� ����� Printer.txt-------------------------------------------------------------------------------------------------
int Read_printer() {
	ifstream inf("Printer.txt");
	
	if (!inf) { // ���� �� �� ����� ������� ���� ���� ��� ������ ��� �����������
		return 1;
	}
	while (inf) { // ���� ���� ������, ������� �� ����� ���������
		getline(inf, strInput); // ������ ������ �����
		if (strInput.length() == 0) { // ��������� ������ - ��� ������
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

//������ � ���� Printer.txt---------------------------------------------------------------------------------------------------
int Write_printer() {
	ofstream outf("Printer.txt");
	if (!outf) {
		cerr << "������, ���� Printer.txt �� ��������!" << endl;
		exit(1);
	}
	for (int i = 0; i <= q_printer; i++) {
		outf << printer[i].Write() <<"\n";
	}
	outf.close();
}

//������ �� ����� Computer.txt------------------------------------------------------------------------------------------------
int Read_computer() {

	ifstream inf("Computer.txt");

	if (!inf)// ���� �� �� ����� ������� ���� ���� ��� ������ ��� �����������
	{
		return 1;
	}

	while (inf)// ���� ���� ������, ������� �� ����� ���������
	{
		getline(inf, strInput); // ������ ������ �����
		if (strInput.length() == 0) { //��������� ����� - ��� ������
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

//������ � ���� Computer.txt--------------------------------------------------------------------------------------------------
int Write_computer() {
	ofstream outf("Computer.txt");
	if (!outf) {
		cerr << "������, ���� Computer.txt �� ��������!" << endl;
		exit(1);
	}
	for (int i = 0; i <= q_computer; i++) {
		outf << computer[i].Write() << "\n";
	}
	outf.close();
}

//������ �� ����� Monitor.txt-------------------------------------------------------------------------------------------------
int Read_monitor() {

	ifstream inf("Monitor.txt");

	if (!inf)// ���� �� �� ����� ������� ���� ���� ��� ������ ��� �����������
	{
		return 1;
	}

	while (inf)// ���� ���� ������, ������� �� ����� ���������
	{
		getline(inf, strInput); // ������ ������ �����
		if (strInput.length() == 0) { //��������� ����� - ��� ������
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

//������ � ���� Moitor.txt----------------------------------------------------------------------------------------------------
int Write_monitor() {
	ofstream outf("Monitor.txt");
	if (!outf) {
		cerr << "������, ���� Monitor.txt �� ��������!" << endl;
		exit(1);
	}
	for (int i = 0; i <= q_monitor; i++) {
		outf << monitor[i].Write() << "\n";
	}
	outf.close();
}

//������ �� ����� Laptop.txt--------------------------------------------------------------------------------------------------
int Read_laptop() {

	ifstream inf("Laptop.txt");

	if (!inf)// ���� �� �� ����� ������� ���� ���� ��� ������ ��� �����������
	{
		return 1;
	}

	while (inf)// ���� ���� ������, ������� �� ����� ���������
	{
		//inf >> strInput;
		getline(inf, strInput); // ������ ������ �����
		if (strInput.length() == 0) { //��������� ����� - ��� ������
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

//������ � ���� Laptop.txt----------------------------------------------------------------------------------------------------
int Write_laptop() {
	ofstream outf("Laptop.txt");
	if (!outf) {
		cerr << "������, ���� Laptop.txt �� ��������!" << endl;
		exit(1);
	}
	for (int i = 0; i <= q_laptop; i++) {
		outf << laptop[i].Write() << "\n";
	}
	outf.close();
	return 1;
}