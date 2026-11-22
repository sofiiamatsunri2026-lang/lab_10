//////////////////////////////////////////////////////////////////////////////
// Lab_10_2_A.cpp
// головний файл проекту – функція main з меню (рівень A)
// Мацун Софія
#include <iostream>
#include <string>
#include "studentA.h"
#include "studentA.h"
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

    int N = InputInt("Введіть кількість студентів N: ", 1, 1000);

    Student* p = new Student[N];

    bool isData = false;          // чи введено дані
    bool isSorted = false;        // чи масив фізично впорядкований

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента за прізвищем, курсом та спеціальністю" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        menuItem = InputInt("Введіть значення: ", 0, 5);
        cout << endl << endl << endl;

        if (menuItem >= 2 && !isData)
        {
            cout << "Спочатку введіть дані (пункт 1)!" << endl;
            continue;
        }

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            isData = true;
            isSorted = false;
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            isSorted = true;
            cout << "Масив фізично впорядковано." << endl;
            break;
        case 4:
        {
            int* I = IndexSort(p, N);
            PrintIndexSorted(p, I, N);
            delete[] I;
            break;
        }
        case 5:
        {
            if (!isSorted)
            {
                cout << "Бінарний пошук потребує впорядкованого масиву - "
                    "спочатку виконайте пункт 3!" << endl;
                break;
            }
            string prizv = InputPrizv("Введіть прізвище: ");
            int kurs = InputInt("Введіть курс (1-6): ", 1, 6);
            Specialnist specialnist = InputSpecialnist();
            int found = BinSearch(p, N, prizv, kurs, specialnist);
            if (found != -1)
                cout << "Студента знайдено в позиції " << found + 1 << "." << endl;
            else
                cout << "Студента з такими даними не знайдено." << endl;
            break;
        }
        case 0:
            break;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}