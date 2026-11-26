// Лабораторна робота № 10.1, рівень В, варіант 12
// Послідовний пошук в масиві структур з об'єднаннями
// 1. Обчислити кількість кожної з оцінок «5», «4», «3» з фізики.
// 2. Обчислити кількість студентів, які отримали і з фізики і з математики оцінки «4» або «5».

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;

enum Specialnist { KN, INF, ME, FI, TN }; // перелік спеціальностей

struct Student
{
	string      prizv;           // прізвище
	int         kurs = 0;        // курс – ціле число
	Specialnist spec = KN;       // спеціальність – перелік
	int         fizyka = 0;      // оцінка з фізики
	int         matematyka = 0;  // оцінка з математики
	union                        // третя оцінка – залежно від спеціальності
	{
		int programuvannya = 0;  // для спеціальності "Комп'ютерні науки"
		// (в об'єднанні ініціалізується лише одне поле)
		int chyselni_metody;     // для спеціальності "Інформатика"
		int pedahohika;          // для всіх інших спеціальностей
	};
};

string SpecToStr(const Specialnist s);
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void CountFizyka(Student* p, const int N, int& k5, int& k4, int& k3);
int  CountFizMat45(Student* p, const int N);

int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251);       // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N]; // динамічний масив структур з об'єднаннями

	Create(p, N);
	Print(p, N);

	int k5, k4, k3;
	CountFizyka(p, N, k5, k4, k3);
	cout << "Кількість оцінок з фізики:" << endl;
	cout << "  \"5\" : " << k5 << endl;
	cout << "  \"4\" : " << k4 << endl;
	cout << "  \"3\" : " << k3 << endl << endl;

	cout << "Кількість студентів, які отримали і з фізики, і з математики "
		<< "оцінки \"4\" або \"5\": " << CountFizMat45(p, N) << endl;

	delete[] p;
	return 0;
}

// повертає назву спеціальності для виводу в таблицю
string SpecToStr(const Specialnist s)
{
	switch (s)
	{
	case KN:  return "Комп. науки";
	case INF: return "Інформатика";
	case ME:  return "Мат. та екон.";
	case FI:  return "Фіз. та інф.";
	case TN:  return "Труд. навч.";
	default:  return "?";
	}
}

// введення даних про студентів з клавіатури
void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();  // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика," << endl
			<< "   2 - Математика та економіка, 3 - Фізика та інформатика," << endl
			<< "   4 - Трудове навчання): ";
		cin >> spec;
		p[i].spec = (Specialnist)spec;
		cout << " оцінка з фізики     : "; cin >> p[i].fizyka;
		cout << " оцінка з математики : "; cin >> p[i].matematyka;
		switch (p[i].spec)  // третя оцінка залежить від спеціальності
		{
		case KN:
			cout << " оцінка з програмування : "; cin >> p[i].programuvannya;
			break;
		case INF:
			cout << " оцінка з чисельних методів: "; cin >> p[i].chyselni_metody;
			break;
		case ME:
		case FI:
		case TN:
			cout << " оцінка з педагогіки : "; cin >> p[i].pedahohika;
			break;
		}
		cout << endl;
	}
}

// вивід масиву у вигляді таблиці (дев'ять клітинок)
void Print(Student* p, const int N)
{
	cout << "Список студентів" << endl;  // заголовок таблиці
	cout << string(92, '=') << endl;
	cout << "|  № | Прізвище      | Курс | Спеціальність  | Фізика | Матем. "
		<< "| Прогр. | Чис.мет | Педаг. |" << endl;
	cout << string(92, '-') << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(3) << right << i + 1
			<< " | " << setw(13) << left << p[i].prizv
			<< " | " << setw(4) << right << p[i].kurs
			<< " | " << setw(14) << left << SpecToStr(p[i].spec)
			<< " | " << setw(6) << right << p[i].fizyka
			<< " | " << setw(6) << right << p[i].matematyka;
		switch (p[i].spec)  // заповнюємо лише одну з трьох клітинок
		{
		case KN:
			cout << " | " << setw(6) << right << p[i].programuvannya
				<< " | " << setw(7) << ""
				<< " | " << setw(6) << "" << " |" << endl;
			break;
		case INF:
			cout << " | " << setw(6) << ""
				<< " | " << setw(7) << right << p[i].chyselni_metody
				<< " | " << setw(6) << "" << " |" << endl;
			break;
		case ME:
		case FI:
		case TN:
			cout << " | " << setw(6) << ""
				<< " | " << setw(7) << ""
				<< " | " << setw(6) << right << p[i].pedahohika << " |" << endl;
			break;
		}
	}
	cout << string(92, '=') << endl;
	cout << endl;
}

// обчислює кількість оцінок "5", "4", "3" з фізики
// (результат повертається через параметри-посилання k5, k4, k3)
void CountFizyka(Student* p, const int N, int& k5, int& k4, int& k3)
{
	k5 = k4 = k3 = 0;
	for (int i = 0; i < N; i++)
	{
		switch (p[i].fizyka)
		{
		case 5: k5++; break;
		case 4: k4++; break;
		case 3: k3++; break;
		}
	}
}

// повертає кількість студентів, які і з фізики, і з математики
// отримали оцінки "4" або "5"
int CountFizMat45(Student* p, const int N)
{
	int k = 0;
	for (int i = 0; i < N; i++)
		if ((p[i].fizyka == 4 || p[i].fizyka == 5) &&
			(p[i].matematyka == 4 || p[i].matematyka == 5))
			k++;
	return k;
}
