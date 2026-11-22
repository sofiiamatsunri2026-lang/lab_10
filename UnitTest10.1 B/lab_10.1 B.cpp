//////////////////////////////////////////////////////////////////////////////
// Lab_10_1_B.cpp
// головний файл проекту – функція main (рівень В)
// Мацун Софія
#include <iostream>
#include "studentB.h"
#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    int N;
    cout << "Введіть N: "; cin >> N;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    int imax = IndexMaxSerBal(s, N);
    cout << "Студент з найбільшим середнім балом: " << s[imax].prizv << endl;
    cout << "Процент студентів, які вчаться на «відмінно»: "
        << ProcentVidminnykiv(s, N) << "%" << endl;

    delete[] s;
    return 0;
}
