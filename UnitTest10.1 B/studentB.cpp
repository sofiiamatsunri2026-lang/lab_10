/////////////////////////////////////////////////////////////////////////////
// studentB.cpp
// реалізація функцій (рівень В)
#include <iostream>
#include <iomanip>
#include <string>
#include "studentB.h"

using namespace std;

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

void Create(Student* s, const int N)
{
    int specialnist;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.get();
        cin.sync();

        cout << "     прізвище: "; getline(cin, s[i].prizv);
        cout << "     курс: "; cin >> s[i].kurs;
        cout << "     спеціальність (0 - Комп’ютерні науки, 1 - Інформатика," << endl
            << "                    2 - Математика та економіка, 3 - Фізика та інформатика," << endl
            << "                    4 - Трудове навчання): ";
        cin >> specialnist;
        s[i].specialnist = (Specialnist)specialnist;
        cout << "     оцінка з фізики: "; cin >> s[i].fizyka;
        cout << "     оцінка з математики: "; cin >> s[i].matematyka;
        switch (s[i].specialnist)
        {
        case KOMP_NAUKY:
            cout << "     оцінка з програмування: "; cin >> s[i].prohramuvannya;
            break;
        case INFORMATYKA:
            cout << "     оцінка з чисельних методів: "; cin >> s[i].chyselni_metody;
            break;
        default:
            cout << "     оцінка з педагогіки: "; cin >> s[i].pedahohika;
            break;
        }
        cout << endl;
    }
}

void Print(const Student* s, const int N)
{
    cout << "===================================================================================================================="
        << endl;
    cout << "| №  | Прізвище       | Курс | Спеціальність          | Фізика | Математика | Програмув. | Чисел.мет. | Педагогіка |"
        << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------"
        << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(15) << left << s[i].prizv
            << "| " << setw(4) << right << s[i].kurs << " "
            << "| " << setw(23) << left << SpecialnistStr(s[i].specialnist)
            << "| " << setw(6) << right << s[i].fizyka << " "
            << "| " << setw(10) << right << s[i].matematyka << " ";

        if (s[i].specialnist == KOMP_NAUKY)
            cout << "| " << setw(10) << right << s[i].prohramuvannya << " ";
        else
            cout << "| " << setw(10) << "" << " ";

        if (s[i].specialnist == INFORMATYKA)
            cout << "| " << setw(10) << right << s[i].chyselni_metody << " ";
        else
            cout << "| " << setw(10) << "" << " ";

        if (s[i].specialnist != KOMP_NAUKY && s[i].specialnist != INFORMATYKA)
            cout << "| " << setw(10) << right << s[i].pedahohika << " |" << endl;
        else
            cout << "| " << setw(10) << "" << " |" << endl;
    }
    cout << "===================================================================================================================="
        << endl;
    cout << endl;
}

int TretyaOcinka(const Student& s)
{
    switch (s.specialnist)
    {
    case KOMP_NAUKY:   return s.prohramuvannya;
    case INFORMATYKA:  return s.chyselni_metody;
    default:           return s.pedahohika;
    }
}

double SerBal(const Student& s)
{
    return (s.fizyka + s.matematyka + TretyaOcinka(s)) / 3.0;
}

bool EVidminnyk(const Student& s)
{
    return s.fizyka == 5 && s.matematyka == 5 && TretyaOcinka(s) == 5;
}

int IndexMaxSerBal(const Student* s, const int N)
{
    int imax = 0;
    for (int i = 1; i < N; i++)
        if (SerBal(s[i]) > SerBal(s[imax]))
            imax = i;
    return imax;
}

double ProcentVidminnykiv(const Student* s, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (EVidminnyk(s[i]))
            k++;
    return 100.0 * k / N;
}
