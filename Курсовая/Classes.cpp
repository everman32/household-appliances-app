#include <iostream>
#include <string>
#include "Classes.h"
#include <iomanip>

using namespace std;

//Computer---------------------------------------------------------------
ostream& operator<< (ostream &out, const Computer &computer) {
	out << setw(9) << left << computer.Get_brand() 
		<< setw(13) << left << computer.Get_model() 
		<< setw(8) << left << computer.Get_price() 
		<< setw(13) << left << computer.Get_quantity()
		<< "процессор " << computer.m_processor;
	return out;
}

//Printer----------------------------------------------------------------
ostream& operator<< (ostream &out,  const Printer &printer) {
	out << setw(9) << left << printer.Get_brand()
		<< setw(13) << left << printer.Get_model()
		<< setw(8) << left << printer.Get_price()
		<< setw(13) << left << printer.Get_quantity()
		<< "тип " << printer.m_type
		<< "; скорость " << printer.m_speed << " лист/мин";
	return out;
}

//Monitor----------------------------------------------------------------
ostream& operator<< (ostream &out, const Monitor &monitor) {
	out << setw(9) << left << monitor.Get_brand() 
		<< setw(13) << left << monitor.Get_model() 
		<< setw(8) << left << monitor.Get_price() 
		<< setw(13) << left << monitor.Get_quantity()
		<< "диагональ " << monitor.m_diagonal 
		<< "\"; разрешение " <<monitor.m_resolution;
	return out;
}

//Laptop-----------------------------------------------------------------
ostream& operator<< (ostream &out, const Laptop &laptop) {
	out << setw(9) << left << laptop.Get_brand() 
		<< setw(13) << left << laptop.Get_model() 
		<< setw(8) << left << laptop.Get_price() 
		<< setw(13) << left << laptop.Get_quantity() 
		<< "процессор " << laptop.m_processor 
		<< "; диагональ " <<laptop.m_diagonal 
		<< "\" вес " << laptop.m_weight << " кг";
	return out;
}