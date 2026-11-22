//////////////////////////////////////////////////////////////////////////////
// studentA.h
// заголовний файл – оголошення типів та функцій (рівень A)
#pragma once

#include <string>

enum Specialnist { KOMP_NAUKY, INFORMATYKA, MAT_EKON, FIZ_INF, TRUD_NAVCH };

struct Student
{
    std::string prizv;
    int         kurs;
    Specialnist spec;
    int         fizyka;
    int         matem;
    int         inform;
};

int         InputInt(const std::string& prompt, const int minV, const int maxV);
std::string InputPrizv(const std::string& prompt);
Specialnist InputSpecialnist();
std::string SpecStr(const Specialnist spec);
void        Create(Student* p, const int N);
void        PrintLine(const char ch);
void        PrintHeader();
void        PrintRow(const Student& s, const int num);
void        Print(const Student* p, const int N);
int         CompareKey(const Student& s, const int kurs, const std::string& prizv,
    const Specialnist spec);
int         Compare(const Student& a, const Student& b);
void        Sort(Student* p, const int N);
bool        IsSorted(const Student* p, const int N);
int         BinSearch(const Student* p, const int N, const std::string& prizv,
    const int kurs, const Specialnist spec);
int* IndexSort(const Student* p, const int N);
void        PrintIndexSorted(const Student* p, const int* I, const int N);