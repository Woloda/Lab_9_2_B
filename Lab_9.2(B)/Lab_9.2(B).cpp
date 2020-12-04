#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Special { КІ, КБ, КН, СА, АЕ };

string s_special[] = { "Комп’ютерна інженерія ",
					   "Кібербезпека",
					   "Комп’ютерні науки",
					   "Системний аналіз",
					   "Атомна енергетика " };

struct student
{
	string prizv;
	int kurs;
	Special specialization;
	int phisuka;
	int matematic;
	union
	{
		int programing;
		int chuslo_metod;
		int pedahohica;
	};
};

void Create(student* s, const int kilkist);
void Print(student* s, const int kilkist);

void Sort(student* s, const int kilkist);
int* IndexSort(student* s, const int kilkist);
void PrintIndexSorted(student* s, int* I, const int kilkist);
int BinSearch(student* s, const int kilkist, const string prizv, const int kurs, const int matematic);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_student;
	cout << "Введіть кількість студентів: "; cin >> kil_student;
	cout << endl;
	student* s = new student[kil_student];

	string prizv;
	int kurs;
	int matematic;
	int found;

	int menuItem;
	do {
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - індексне впорядкування та вивід даних" << endl;
		cout << " [5] - бінарний пошук студента" << endl << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть пункт меню: "; cin >> menuItem;
		switch (menuItem)
		{
		case 1:
			Create(s, kil_student);
			break;
		case 2:
			Print(s, kil_student);
			break;
		case 3:
			Sort(s, kil_student);
			break;
		case 4:
			PrintIndexSorted(s, IndexSort(s, kil_student), kil_student);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cin.get();
			cin.sync();
			cout << " прізвище: ";
			getline(cin, prizv);

			cout << " курс: ";
			cin >> kurs;

			cout << " бал з математики: "; cin >> matematic;
			cout << endl;
			if ((found = BinSearch(s, kil_student, prizv, kurs, matematic)) != -1)
				cout << "Знайдено студента в списку під номером" << found + 1 << endl;
			else
				cout << "Шуканого студента в списку не знайдено" << endl;
			break;

		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
		cout << endl;
	} while (menuItem != 0);

	delete[] s;
}

void Create(student* s, const int kilkist)
{
	int kurs, special;
	for (int i = 0; i < kilkist; i++)
	{
		cout << endl;
		cout << "студент № " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  прізвище: "; getline(cin, s[i].prizv);
		cout << "  курс: "; cin >> s[i].kurs;
		cout << "  спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Метематика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): "; cin >> special;
		s[i].specialization = (Special)special;
		cout << "  оцінка з фізики: "; cin >> s[i].phisuka;
		cout << "  оцінка з математики: "; cin >> s[i].matematic;
		switch (special)
		{
		case 0:
			cout << "  оцінка з програмування: "; cin >> s[i].programing;
			break;
		case 1:
			cout << "  оцінка з чисельних методів: "; cin >> s[i].chuslo_metod;
			break;
		case 2:
		case 3:
		case 4:
			cout << "  оцінка з педагогіки: "; cin >> s[i].pedahohica;
			break;
		default:
			cout << "Ви ввели помилкове значення! " << endl;
		}
		cout << endl;
	}
}

void Print(student* s, const int kilkist)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| №  | Прізвище     | Курс | Спеціальність           | Фізика | Математика  | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < kilkist; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[i].prizv
			<< "| " << setw(3) << right << s[i].kurs << "  "
			<< "| " << setw(23) << left << s_special[s[i].specialization] << " "
			<< "| " << setw(4) << right << s[i].phisuka << "   "
			<< "| " << setw(6) << right << s[i].matematic << "      ";
		switch (s[i].specialization)
		{
		case 0:
			cout << "| " << setw(7) << right << s[i].programing << "       |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 1:
			cout << "| " << setw(15) << "|" << setw(10) << right << s[i].chuslo_metod << "       |" << setw(13) << "|" << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s[i].pedahohica << "     |" << endl;
			break;
		}
	}
	cout << "============================================================================================================================" << endl;
}

void Sort(student* s, const int kilkist)
{
	student tmp;

	for (int i0 = 0; i0 < kilkist - 1; i0++)
		for (int i1 = 0; i1 < kilkist - i0 - 1; i1++)
		{
			if ((s[i1].kurs > s[i1 + 1].kurs)
				|| (s[i1].kurs == s[i1 + 1].kurs && s[i1].matematic > s[i1 + 1].matematic)
				|| (s[i1].kurs == s[i1 + 1].kurs && s[i1].matematic == s[i1 + 1].matematic && s[i1].prizv < s[i1 + 1].prizv)
				)
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}

		}
}

int* IndexSort(student* s, const int kilkist)
{
	int* I = new int[kilkist];

	for (int i = 0; i < kilkist; i++)
		I[i] = i;

	int i, j, value;
	for (i = 1; i < kilkist; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && (
				(s[I[j]].kurs > s[value].kurs)
				||
				(s[I[j]].kurs == s[value].kurs && s[I[j]].matematic > s[value].matematic)
				||
				(s[I[j]].kurs == s[value].kurs && s[I[j]].matematic == s[value].matematic && s[I[j]].prizv > s[value].prizv)
				);
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(student* s, int* I, const int kilkist)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| №  | Прізвище     | Курс | Спеціальність           | Фізика | Математика  | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < kilkist; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[I[i]].prizv
			<< "| " << setw(3) << right << s[I[i]].kurs << "  "
			<< "| " << setw(23) << left << s_special[s[I[i]].specialization] << " "
			<< "| " << setw(4) << right << s[I[i]].phisuka << "   "
			<< "| " << setw(6) << right << s[I[i]].matematic << "      ";
		switch (s[i].specialization)
		{
		case 0:
			cout << "| " << setw(7) << right << s[I[i]].programing << "       |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 1:
			cout << "| " << setw(15) << "|" << setw(10) << right << s[I[i]].chuslo_metod << "       |" << setw(13) << "|" << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s[I[i]].pedahohica << "     |" << endl;
			break;
		}
	}
	cout << "============================================================================================================================";
}

int BinSearch(student* s, const int kilkist, const string prizv, const int kurs, const int matematic)
{
	int L = 0, R = kilkist - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].kurs == kurs && s[m].matematic == matematic && s[m].prizv == prizv)
			return m;
		if (
			(s[m].kurs < kurs)
			|| (s[m].kurs == kurs && s[m].matematic < matematic)
			|| (s[m].kurs == kurs && s[m].matematic == matematic && s[m].prizv < prizv)
			)
		{
			R = m - 1;
		}
		else
		{
			L = m + 1;
		}
	} while (L <= R);
	return -1;
}