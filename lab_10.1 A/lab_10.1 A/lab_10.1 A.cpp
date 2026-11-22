//////////////////////////////////////////////////////////////////////////////
// Lab_10_1.cpp
// Лабораторна робота № 10.1. Послідовний пошук в масиві структур
// Варіант 19, рівень А
//   1. Вивести прізвище студента, у якого найбільший середній бал.
//   2. Обчислити процент студентів, які вчаться на «відмінно».

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <Windows.h>               // забезпечення відображення кирилиці
using namespace std;

enum Specialnist { KOMP_NAUKY, INFORMATYKA, MAT_EKON, FIZ_INF, TRUD_NAVCH };

struct Student
{
    string      prizv;
    int         kurs;
    Specialnist spec;
    int         fizyka;
    int         matem;
    int         inform;
};

int         InputInt(const string& prompt, const int minV, const int maxV);
string      InputString(const string& prompt, const unsigned maxLen);
Specialnist InputSpec();
string      SpecStr(const Specialnist spec);
int         SumGrades(const Student& s);
double      AvgGrade(const Student& s);
void        Create(Student* p, const int N);
void        PrintLine(const char ch);
void        PrintHeader();
void        PrintRow(const Student& s, const int num);
void        Print(const Student* p, const int N);
int         MaxAvgIndex(const Student* p, const int N);
double      PercentExcellent(const Student* p, const int N);

int main()
{                             // забезпечення відображення кирилиці:
    SetConsoleCP(1251);       // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

    int N = InputInt("Введіть кількість студентів N: ", 1, 1000);

    Student* p = new Student[N];

    Create(p, N);
    Print(p, N);

    int imax = MaxAvgIndex(p, N);
    cout << "Найбільший середній бал (" << fixed << setprecision(2)
        << AvgGrade(p[imax]) << ") має студент: " << p[imax].prizv << endl;

    cout << "Процент студентів, які вчаться на \"відмінно\": "
        << fixed << setprecision(2) << PercentExcellent(p, N) << "%" << endl;

    delete[] p;
    return 0;
}

// введення цілого числа з перевіркою діапазону [minV; maxV]
int InputInt(const string& prompt, const int minV, const int maxV)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && value >= minV && value <= maxV)
        {
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // залишок рядка
            return value;
        }
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cout << "Помилка! Введіть ціле число від " << minV
            << " до " << maxV << "." << endl;
    }
}

// введення непорожнього рядка довжиною не більше maxLen
string InputString(const string& prompt, const unsigned maxLen)
{
    string s;
    while (true)
    {
        cout << prompt;
        getline(cin, s);
        if (!s.empty() && s.size() <= maxLen)
            return s;
        cin.clear();
        cout << "Помилка! Рядок має бути непорожнім і не довшим за "
            << maxLen << " символів." << endl;
    }
}

// вибір спеціальності зі списку
Specialnist InputSpec()
{
    cout << "    спеціальність:" << endl;
    for (int k = 0; k <= TRUD_NAVCH; k++)
        cout << "        " << k << " - " << SpecStr((Specialnist)k) << endl;
    return (Specialnist)InputInt("    виберіть номер спеціальності: ", 0, TRUD_NAVCH);
}

// назва спеціальності
string SpecStr(const Specialnist spec)
{
    static const string names[] = { "Комп'ютерні науки", "Інформатика",
                                    "Математика та економіка",
                                    "Фізика та інформатика", "Трудове навчання" };
    return names[spec];
}

// сума трьох оцінок студента
int SumGrades(const Student& s)
{
    return s.fizyka + s.matem + s.inform;
}

// середній бал студента
double AvgGrade(const Student& s)
{
    return SumGrades(s) / 3.0;
}

void Create(Student* p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        p[i].prizv = InputString("    прізвище (до 13 символів): ", 13);
        p[i].kurs = InputInt("    курс (1-6): ", 1, 6);
        p[i].spec = InputSpec();
        p[i].fizyka = InputInt("    оцінка з фізики (2-5): ", 2, 5);
        p[i].matem = InputInt("    оцінка з математики (2-5): ", 2, 5);
        p[i].inform = InputInt("    оцінка з інформатики (2-5): ", 2, 5);

        cout << endl;
    }
}

void PrintLine(const char ch)
{
    cout << string(93, ch) << endl;
}

void PrintHeader()
{
    cout << "| " << setw(3) << left << "№" << " "
        << "| " << setw(13) << left << "Прізвище" << " "
        << "| " << setw(4) << left << "Курс" << " "
        << "| " << setw(23) << left << "Спеціальність" << " "
        << "| " << setw(6) << left << "Фізика" << " "
        << "| " << setw(10) << left << "Математика" << " "
        << "| " << setw(12) << left << "Інформатика" << " |" << endl;
}

void PrintRow(const Student& s, const int num)
{
    cout << "| " << setw(3) << right << num << " "
        << "| " << setw(13) << left << s.prizv << " "
        << "| " << setw(4) << right << s.kurs << " "
        << "| " << setw(23) << left << SpecStr(s.spec) << " "
        << "| " << setw(6) << right << s.fizyka << " "
        << "| " << setw(10) << right << s.matem << " "
        << "| " << setw(12) << right << s.inform << " |" << endl;
}

void Print(const Student* p, const int N)
{
    PrintLine('=');
    PrintHeader();
    PrintLine('-');
    for (int i = 0; i < N; i++)
        PrintRow(p[i], i + 1);
    PrintLine('=');
    cout << endl;
}

// послідовний пошук: індекс студента з найбільшим середнім балом
// (якщо таких кілька – перший з них)
int MaxAvgIndex(const Student* p, const int N)
{
    int imax = 0;
    for (int i = 1; i < N; i++)
        if (SumGrades(p[i]) > SumGrades(p[imax]))
            imax = i;
    return imax;
}

// послідовний пошук: процент студентів, які вчаться на «відмінно»
// (всі три оцінки дорівнюють 5)
double PercentExcellent(const Student* p, const int N)
{
    if (N <= 0)
        return 0;
    int k = 0;
    for (int i = 0; i < N; i++)
        if (p[i].fizyka == 5 && p[i].matem == 5 && p[i].inform == 5)
            k++;
    return 100.0 * k / N;
}