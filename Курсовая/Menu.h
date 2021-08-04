#pragma once
void Title();
void Look_computer();
void Look_monitor();
void Look_printer();
void Look_laptop();
void Look_all();
void Filtering();
void Sorting();
void Order();
void Time();
template <typename T>
void Get_number(T &chislo);
template <typename T>
void Sort(T *massiv, int q, int sort_by);
void Deleting();
void Adding();
void Editing();
double Get_number_double();
void Report_store();
void Report_sold();
void Report_best();
namespace User {
	int Login();
	void Crypt(char *password);
	void Users();
}