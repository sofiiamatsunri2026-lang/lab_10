//////////////////////////////////////////////////////////////////////////////
// student102B.h
// інтерфейс: типи даних і оголошення функцій (рівень B)
#pragma once
#include <string>

enum Specialnist { KOMP_NAUKY, INFORMATYKA, MAT_EKONOMIKA, FIZ_INFORMATYKA, TRUDOVE_NAVCHANNYA };

struct Student
{
    std::string prizv;
    int         kurs;
    Specialnist specialnist;
    int         fizyka;
    int         matematyka;
    union
    {
        int prohramuvannya;
        int chyselni_metody;
        int pedahohika;
    };
};

// введення з контролем помилок
int         InputInt(const std::string& prompt, const int minV, const int maxV);
std::string InputPrizv(const std::string& prompt);
Specialnist InputSpecialnist();

std::string SpecialnistStr(const Specialnist specialnist);

// формування та вивід
void Create(Student* p, const int N);
void PrintHeader();
void PrintRow(const Student& s, const int nomer);
void PrintFooter();
void Print(const Student* p, const int N);
void PrintIndexSorted(const Student* p, const int* I, const int N);

// порівняння за ключами: курс, прізвище (за зростанням), назва спеціальності
bool EMenshe(const Student& a, const Student& b);

// впорядкування та пошук
void Sort(Student* p, const int N);
int* IndexSort(const Student* p, const int N);
int  BinSearch(const Student* p, const int N, const std::string& prizv,
    const int kurs, const Specialnist specialnist);
#pragma once
