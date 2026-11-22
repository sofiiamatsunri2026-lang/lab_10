//////////////////////////////////////////////////////////////////////////////
// studentA.cpp
// файл реалізації функцій для роботи з масивом студентів (рівень A)

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "studentA.h"

using namespace std;

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
string InputPrizv(const string& prompt)
{
    const unsigned maxLen = 13;
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
Specialnist InputSpecialnist()
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

void Create(Student* p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        p[i].prizv = InputPrizv("    прізвище (до 13 символів): ");
        p[i].kurs = InputInt("    курс (1-6): ", 1, 6);
        p[i].spec = InputSpecialnist();
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

// порівняння студента s з ключем (курс, прізвище, назва спеціальності):
// < 0, якщо s стоїть перед ключем; 0 – збігаються; > 0 – s стоїть після ключа
int CompareKey(const Student& s, const int kurs, const string& prizv,
    const Specialnist spec)
{
    if (s.kurs != kurs)
        return s.kurs < kurs ? -1 : 1;
    if (s.prizv != prizv)
        return s.prizv < prizv ? -1 : 1;
    const string a = SpecStr(s.spec), b = SpecStr(spec);
    if (a != b)
        return a < b ? -1 : 1;
    return 0;
}

// порівняння двох студентів за тими самими ключами
int Compare(const Student& a, const Student& b)
{
    return CompareKey(a, b.kurs, b.prizv, b.spec);
}

// фізичне впорядкування (метод "бульбашки"):
// в першу чергу – за курсом, в другу – за прізвищем, в останню – за назвою спеціальності
void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (Compare(p[i1], p[i1 + 1]) > 0)
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

// перевірка, чи масив фізично впорядкований
bool IsSorted(const Student* p, const int N)
{
    for (int i = 0; i < N - 1; i++)
        if (Compare(p[i], p[i + 1]) > 0)
            return false;
    return true;
}

// бінарний пошук у фізично впорядкованому масиві;
// повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
int BinSearch(const Student* p, const int N, const string& prizv,
    const int kurs, const Specialnist spec)
{
    int L = 0, R = N - 1, m, c;
    while (L <= R)
    {
        m = (L + R) / 2;
        c = CompareKey(p[m], kurs, prizv, spec);
        if (c == 0)
            return m;
        if (c < 0)
            L = m + 1;
        else
            R = m - 1;
    }
    return -1;
}

// індексне впорядкування (метод вставки): будує індексний масив
int* IndexSort(const Student* p, const int N)
{
    int* I = new int[N];    // створили індексний масив

    for (int i = 0; i < N; i++)
        I[i] = i;           // заповнили його початковими даними

    int i, j, value;        // сортуємо масив індексів
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1; j >= 0 && Compare(p[I[j]], p[value]) > 0; j--)
            I[j + 1] = I[j];
        I[j + 1] = value;
    }
    return I;
}

// вивід масиву в порядку, визначеному індексним масивом I
void PrintIndexSorted(const Student* p, const int* I, const int N)
{
    PrintLine('=');
    PrintHeader();
    PrintLine('-');
    for (int i = 0; i < N; i++)
        PrintRow(p[I[i]], i + 1);
    PrintLine('=');
    cout << endl;
}