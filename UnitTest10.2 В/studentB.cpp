//////////////////////////////////////////////////////////////////////////////
// student102B.cpp
// реалізація функцій (рівень B)
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "studentB.h"

using namespace std;

int InputInt(const string& prompt, const int minV, const int maxV)
{
    string line;
    size_t pos;
    int value;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
            exit(0);
        try
        {
            value = stoi(line, &pos);
        }
        catch (...)
        {
            cout << "Помилка: потрібно ввести ціле число!" << endl;
            continue;
        }
        while (pos < line.size() && line[pos] == ' ')
            pos++;
        if (pos != line.size())
        {
            cout << "Помилка: потрібно ввести ціле число!" << endl;
            continue;
        }
        if (value < minV || value > maxV)
        {
            cout << "Помилка: число має бути від " << minV << " до " << maxV << "!" << endl;
            continue;
        }
        return value;
    }
}

string InputPrizv(const string& prompt)
{
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
            exit(0);
        if (line.find_first_not_of(' ') != string::npos)
            return line;
        cout << "Помилка: прізвище не може бути порожнім!" << endl;
    }
}

Specialnist InputSpecialnist()
{
    cout << "     спеціальність: 0 - Комп’ютерні науки, 1 - Інформатика," << endl
        << "                    2 - Математика та економіка, 3 - Фізика та інформатика," << endl
        << "                    4 - Трудове навчання" << endl;
    return (Specialnist)InputInt("     введіть номер спеціальності (0-4): ", 0, 4);
}

string SpecialnistStr(const Specialnist specialnist)
{
    switch (specialnist)
    {
    case KOMP_NAUKY:         return "Комп’ютерні науки";
    case INFORMATYKA:        return "Інформатика";
    case MAT_EKONOMIKA:      return "Математика та економіка";
    case FIZ_INFORMATYKA:    return "Фізика та інформатика";
    default:                 return "Трудове навчання";
    }
}

void Create(Student* p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        p[i].prizv = InputPrizv("     прізвище: ");
        p[i].kurs = InputInt("     курс (1-6): ", 1, 6);
        p[i].specialnist = InputSpecialnist();
        p[i].fizyka = InputInt("     оцінка з фізики (1-5): ", 1, 5);
        p[i].matematyka = InputInt("     оцінка з математики (1-5): ", 1, 5);
        switch (p[i].specialnist)
        {
        case KOMP_NAUKY:
            p[i].prohramuvannya = InputInt("     оцінка з програмування (1-5): ", 1, 5);
            break;
        case INFORMATYKA:
            p[i].chyselni_metody = InputInt("     оцінка з чисельних методів (1-5): ", 1, 5);
            break;
        default:
            p[i].pedahohika = InputInt("     оцінка з педагогіки (1-5): ", 1, 5);
            break;
        }
        cout << endl;
    }
}

void PrintHeader()
{
    cout << "====================================================================================================================" << endl;
    cout << "| №  | Прізвище       | Курс | Спеціальність          | Фізика | Математика | Програмув. | Чисел.мет. | Педагогіка |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
}

void PrintRow(const Student& s, const int nomer)
{
    cout << "| " << setw(2) << right << nomer << " "
        << "| " << setw(15) << left << s.prizv
        << "| " << setw(4) << right << s.kurs << " "
        << "| " << setw(23) << left << SpecialnistStr(s.specialnist)
        << "| " << setw(6) << right << s.fizyka << " "
        << "| " << setw(10) << right << s.matematyka << " ";

    if (s.specialnist == KOMP_NAUKY)
        cout << "| " << setw(10) << right << s.prohramuvannya << " ";
    else
        cout << "| " << setw(10) << "" << " ";

    if (s.specialnist == INFORMATYKA)
        cout << "| " << setw(10) << right << s.chyselni_metody << " ";
    else
        cout << "| " << setw(10) << "" << " ";

    if (s.specialnist != KOMP_NAUKY && s.specialnist != INFORMATYKA)
        cout << "| " << setw(10) << right << s.pedahohika << " |" << endl;
    else
        cout << "| " << setw(10) << "" << " |" << endl;
}

void PrintFooter()
{
    cout << "====================================================================================================================" << endl;
    cout << endl;
}

void Print(const Student* p, const int N)
{
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[i], i + 1);
    PrintFooter();
}

void PrintIndexSorted(const Student* p, const int* I, const int N)
{ // як Print(), але доступ до елементів – за допомогою індексного масиву I
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[I[i]], i + 1);
    PrintFooter();
}

bool EMenshe(const Student& a, const Student& b)
{
    if (a.kurs != b.kurs)
        return a.kurs < b.kurs;
    if (a.prizv != b.prizv)
        return a.prizv < b.prizv;
    return SpecialnistStr(a.specialnist) < SpecialnistStr(b.specialnist);
}

void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)          // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (EMenshe(p[i1 + 1], p[i1]))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* IndexSort(const Student* p, const int N)
{ // метод вставки для формування індексного масиву
    int* I = new int[N];

    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1; j >= 0 && EMenshe(p[value], p[I[j]]); j--)
            I[j + 1] = I[j];
        I[j + 1] = value;
    }

    return I;
}

int BinSearch(const Student* p, const int N, const string& prizv,
    const int kurs, const Specialnist specialnist)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
    Student key;
    key.prizv = prizv;
    key.kurs = kurs;
    key.specialnist = specialnist;

    int L = 0, R = N - 1, m;
    while (L <= R)
    {
        m = (L + R) / 2;
        if (EMenshe(p[m], key))
            L = m + 1;
        else if (EMenshe(key, p[m]))
            R = m - 1;
        else
            return m;
    }
    return -1;
}