#pragma once
/////////////////////////////////////////////////////////////////////////////
// studentB.h
// інтерфейс: типи даних і оголошення функцій (рівень В)
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

std::string SpecialnistStr(const Specialnist specialnist);
void   Create(Student* s, const int N);
void   Print(const Student* s, const int N);
int    TretyaOcinka(const Student& s);
double SerBal(const Student& s);
bool   EVidminnyk(const Student& s);
int    IndexMaxSerBal(const Student* s, const int N);
double ProcentVidminnykiv(const Student* s, const int N);
