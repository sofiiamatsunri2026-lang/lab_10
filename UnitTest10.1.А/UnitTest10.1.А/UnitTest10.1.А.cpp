#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10.1 A.cpp"      // підключаємо файл з функціями (шлях – за назвою вашого проєкту)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// допоміжна функція: створює студента із заданими даними
Student MakeStudent(string prizv, int kurs, Specialnist spec, int f, int m, int third)
{
    Student s;
    s.prizv = prizv;
    s.kurs = kurs;
    s.spec = spec;
    s.fizyka = f;
    s.matem = m;
    s.inform = third;   // оцінка з інформатики
    return s;
}

namespace UnitTest101
{
    TEST_CLASS(UnitTest1)
    {
    public:

        // сума та середній бал
        TEST_METHOD(TestGrades)
        {
            Student s = MakeStudent("A", 1, KOMP_NAUKY, 5, 4, 3);
            Assert::AreEqual(12, SumGrades(s));
            Assert::AreEqual(4.0, AvgGrade(s), 1e-9);
        }

        // найбільший середній бал – єдиний максимум
        TEST_METHOD(TestMaxAvgIndex_Single)
        {
            Student p[3] = {
                MakeStudent("A", 1, KOMP_NAUKY,  4, 4, 3),   // 11
                MakeStudent("B", 2, INFORMATYKA, 5, 4, 5),   // 14
                MakeStudent("C", 3, MAT_EKON,    5, 5, 5) }; // 15
            Assert::AreEqual(2, MaxAvgIndex(p, 3));
        }

        // однакові найбільші середні бали – повертається перший
        TEST_METHOD(TestMaxAvgIndex_Tie)
        {
            Student p[3] = {
                MakeStudent("A", 1, KOMP_NAUKY,  4, 4, 3),
                MakeStudent("B", 2, INFORMATYKA, 5, 5, 5),
                MakeStudent("C", 3, MAT_EKON,    5, 5, 5) };
            Assert::AreEqual(1, MaxAvgIndex(p, 3));
        }

        // 2 з 4 студентів вчаться на «відмінно» -> 50%
        TEST_METHOD(TestPercentExcellent_Half)
        {
            Student p[4] = {
                MakeStudent("A", 1, KOMP_NAUKY,  5, 5, 5),
                MakeStudent("B", 2, INFORMATYKA, 5, 4, 5),
                MakeStudent("C", 3, MAT_EKON,    4, 4, 3),
                MakeStudent("D", 1, FIZ_INF,     5, 5, 5) };
            Assert::AreEqual(50.0, PercentExcellent(p, 4), 1e-9);
        }

        // жодного відмінника -> 0%
        TEST_METHOD(TestPercentExcellent_None)
        {
            Student p[2] = {
                MakeStudent("A", 1, KOMP_NAUKY,  5, 5, 4),
                MakeStudent("B", 2, INFORMATYKA, 4, 4, 4) };
            Assert::AreEqual(0.0, PercentExcellent(p, 2), 1e-9);
        }

        // всі відмінники -> 100%
        TEST_METHOD(TestPercentExcellent_All)
        {
            Student p[2] = {
                MakeStudent("A", 1, KOMP_NAUKY,  5, 5, 5),
                MakeStudent("B", 2, TRUD_NAVCH,  5, 5, 5) };
            Assert::AreEqual(100.0, PercentExcellent(p, 2), 1e-9);
        }
    };
}