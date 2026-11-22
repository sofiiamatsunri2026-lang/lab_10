//////////////////////////////////////////////////////////////////////////////
// UnitTest101B.cpp
// unit-тести функцій TretyaOcinka, SerBal, EVidminnyk,
// IndexMaxSerBal, ProcentVidminnykiv (рівень В)
#include "pch.h"
#include "CppUnitTest.h"
#include "../studentB.cpp"     

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101B
{
    TEST_CLASS(UnitTest101B)
    {
    private:

        // заповнює студента; третя оцінка записується в поле об’єднання
        // залежно від спеціальності
        static void Fill(Student& s, const Specialnist spec,
            const int f, const int m, const int third)
        {
            s.prizv = "Test";
            s.kurs = 1;
            s.specialnist = spec;
            s.fizyka = f;
            s.matematyka = m;
            switch (spec)
            {
            case KOMP_NAUKY:  s.prohramuvannya = third;  break;
            case INFORMATYKA: s.chyselni_metody = third; break;
            default:          s.pedahohika = third;      break;
            }
        }

    public:

        // TretyaOcinka: Комп’ютерні науки – програмування
        TEST_METHOD(TestTretyaOcinka_KompNauky)
        {
            Student s;
            Fill(s, KOMP_NAUKY, 5, 5, 3);
            Assert::AreEqual(3, TretyaOcinka(s));
        }

        // TretyaOcinka: Інформатика – чисельні методи
        TEST_METHOD(TestTretyaOcinka_Informatyka)
        {
            Student s;
            Fill(s, INFORMATYKA, 5, 5, 4);
            Assert::AreEqual(4, TretyaOcinka(s));
        }

        // TretyaOcinka: решта спеціальностей – педагогіка
        TEST_METHOD(TestTretyaOcinka_Inshi)
        {
            Student a, b, c;
            Fill(a, MAT_EKONOMIKA, 5, 5, 5);
            Fill(b, FIZ_INFORMATYKA, 5, 5, 4);
            Fill(c, TRUDOVE_NAVCHANNYA, 5, 5, 3);
            Assert::AreEqual(5, TretyaOcinka(a));
            Assert::AreEqual(4, TretyaOcinka(b));
            Assert::AreEqual(3, TretyaOcinka(c));
        }

        // SerBal: (5 + 4 + 3) / 3 = 4
        TEST_METHOD(TestSerBal)
        {
            Student s;
            Fill(s, KOMP_NAUKY, 5, 4, 3);
            Assert::AreEqual(4.0, SerBal(s), 1e-9);
        }

        // EVidminnyk: усі три оцінки «5»
        TEST_METHOD(TestEVidminnyk_True)
        {
            Student s;
            Fill(s, INFORMATYKA, 5, 5, 5);
            Assert::IsTrue(EVidminnyk(s));
        }

        // EVidminnyk: третя оцінка «4»
        TEST_METHOD(TestEVidminnyk_False)
        {
            Student s;
            Fill(s, MAT_EKONOMIKA, 5, 5, 4);
            Assert::IsFalse(EVidminnyk(s));
        }

        // IndexMaxSerBal: єдиний максимум в кінці масиву
        TEST_METHOD(TestIndexMax_Last)
        {
            Student p[3];
            Fill(p[0], KOMP_NAUKY, 4, 4, 3);   // 11
            Fill(p[1], INFORMATYKA, 5, 4, 5);   // 14
            Fill(p[2], MAT_EKONOMIKA, 5, 5, 5);   // 15
            Assert::AreEqual(2, IndexMaxSerBal(p, 3));
        }

        // IndexMaxSerBal: єдиний максимум на початку масиву
        TEST_METHOD(TestIndexMax_First)
        {
            Student p[3];
            Fill(p[0], KOMP_NAUKY, 5, 5, 5);
            Fill(p[1], INFORMATYKA, 4, 4, 3);
            Fill(p[2], MAT_EKONOMIKA, 3, 4, 4);
            Assert::AreEqual(0, IndexMaxSerBal(p, 3));
        }

        // IndexMaxSerBal: однакові найбільші бали – повертається перший
        TEST_METHOD(TestIndexMax_Tie)
        {
            Student p[3];
            Fill(p[0], KOMP_NAUKY, 4, 4, 3);
            Fill(p[1], INFORMATYKA, 5, 5, 5);
            Fill(p[2], MAT_EKONOMIKA, 5, 5, 5);
            Assert::AreEqual(1, IndexMaxSerBal(p, 3));
        }

        // IndexMaxSerBal: один студент
        TEST_METHOD(TestIndexMax_One)
        {
            Student p[1];
            Fill(p[0], KOMP_NAUKY, 3, 3, 3);
            Assert::AreEqual(0, IndexMaxSerBal(p, 1));
        }

        // ProcentVidminnykiv: 2 з 4 – 50%
        TEST_METHOD(TestProcent_Half)
        {
            Student p[4];
            Fill(p[0], KOMP_NAUKY, 5, 5, 5);
            Fill(p[1], INFORMATYKA, 5, 4, 5);
            Fill(p[2], MAT_EKONOMIKA, 4, 4, 3);
            Fill(p[3], FIZ_INFORMATYKA, 5, 5, 5);
            Assert::AreEqual(50.0, ProcentVidminnykiv(p, 4), 1e-9);
        }

        // ProcentVidminnykiv: жодного відмінника – 0%
        TEST_METHOD(TestProcent_None)
        {
            Student p[2];
            Fill(p[0], KOMP_NAUKY, 5, 5, 4);
            Fill(p[1], INFORMATYKA, 4, 4, 4);
            Assert::AreEqual(0.0, ProcentVidminnykiv(p, 2), 1e-9);
        }

        // ProcentVidminnykiv: усі відмінники – 100%
        TEST_METHOD(TestProcent_All)
        {
            Student p[2];
            Fill(p[0], KOMP_NAUKY, 5, 5, 5);
            Fill(p[1], TRUDOVE_NAVCHANNYA, 5, 5, 5);
            Assert::AreEqual(100.0, ProcentVidminnykiv(p, 2), 1e-9);
        }
    };
}