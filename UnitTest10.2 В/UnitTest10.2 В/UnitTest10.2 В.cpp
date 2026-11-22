//////////////////////////////////////////////////////////////////////////////
// UnitTest102B.cpp
// unit-тести функцій EMenshe, Sort, IndexSort, BinSearch (рівень B)
#include "pch.h"
#include "CppUnitTest.h"
#include "../studentB.cpp"      // шлях – за назвою вашого проєкту

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102B
{
    TEST_CLASS(UnitTest102B)
    {
    private:

        // заповнює студента (третя оцінка – в полі об’єднання
        // залежно від спеціальності)
        static void Fill(Student& s, const string& prizv, const int kurs,
            const Specialnist spec)
        {
            s.prizv = prizv;
            s.kurs = kurs;
            s.specialnist = spec;
            s.fizyka = 5;
            s.matematyka = 5;
            switch (spec)
            {
            case KOMP_NAUKY:  s.prohramuvannya = 5;  break;
            case INFORMATYKA: s.chyselni_metody = 5; break;
            default:          s.pedahohika = 5;      break;
            }
        }

        // заповнює масив з 5 студентів у невпорядкованому вигляді
        static void FillArray(Student* p)
        {
            Fill(p[0], "Шевченко", 2, KOMP_NAUKY);
            Fill(p[1], "Андрієнко", 1, MAT_EKONOMIKA);
            Fill(p[2], "Шевченко", 2, INFORMATYKA);
            Fill(p[3], "Бондар", 1, KOMP_NAUKY);
            Fill(p[4], "Андрієнко", 1, INFORMATYKA);
        }

        // перевіряє, що на позиції i стоїть студент з вказаними ключами
        static void CheckAt(const Student& s, const string& prizv, const int kurs,
            const Specialnist spec)
        {
            Assert::AreEqual(prizv == s.prizv, true);
            Assert::AreEqual(kurs, s.kurs);
            Assert::AreEqual((int)spec, (int)s.specialnist);
        }

    public:

        // EMenshe: перший ключ – курс
        TEST_METHOD(TestEMenshe_Kurs)
        {
            Student a, b;
            Fill(a, "Яковенко", 1, TRUDOVE_NAVCHANNYA);
            Fill(b, "Андрієнко", 2, INFORMATYKA);
            Assert::IsTrue(EMenshe(a, b));
            Assert::IsFalse(EMenshe(b, a));
        }

        // EMenshe: другий ключ – прізвище
        TEST_METHOD(TestEMenshe_Prizv)
        {
            Student a, b;
            Fill(a, "Андрієнко", 2, TRUDOVE_NAVCHANNYA);
            Fill(b, "Бондар", 2, INFORMATYKA);
            Assert::IsTrue(EMenshe(a, b));
            Assert::IsFalse(EMenshe(b, a));
        }

        // EMenshe: третій ключ – назва спеціальності
        // («Інформатика» перед «Комп’ютерні науки» за алфавітом)
        TEST_METHOD(TestEMenshe_Specialnist)
        {
            Student a, b;
            Fill(a, "Бондар", 2, INFORMATYKA);
            Fill(b, "Бондар", 2, KOMP_NAUKY);
            Assert::IsTrue(EMenshe(a, b));
            Assert::IsFalse(EMenshe(b, a));
        }

        // EMenshe: однакові ключі
        TEST_METHOD(TestEMenshe_Equal)
        {
            Student a, b;
            Fill(a, "Бондар", 2, INFORMATYKA);
            Fill(b, "Бондар", 2, INFORMATYKA);
            Assert::IsFalse(EMenshe(a, b));
            Assert::IsFalse(EMenshe(b, a));
        }

        // Sort: фізичне впорядкування за трьома ключами
        TEST_METHOD(TestSort)
        {
            Student p[5];
            FillArray(p);
            Sort(p, 5);
            CheckAt(p[0], "Андрієнко", 1, INFORMATYKA);
            CheckAt(p[1], "Андрієнко", 1, MAT_EKONOMIKA);
            CheckAt(p[2], "Бондар", 1, KOMP_NAUKY);
            CheckAt(p[3], "Шевченко", 2, INFORMATYKA);
            CheckAt(p[4], "Шевченко", 2, KOMP_NAUKY);
        }

        // IndexSort: індексний масив, основний масив не змінюється
        TEST_METHOD(TestIndexSort)
        {
            Student p[5];
            FillArray(p);
            int* I = IndexSort(p, 5);
            Assert::AreEqual(4, I[0]);
            Assert::AreEqual(1, I[1]);
            Assert::AreEqual(3, I[2]);
            Assert::AreEqual(2, I[3]);
            Assert::AreEqual(0, I[4]);
            CheckAt(p[0], "Шевченко", 2, KOMP_NAUKY);
            delete[] I;
        }

        // BinSearch: студент знайдений (початок, середина, кінець масиву)
        TEST_METHOD(TestBinSearch_Found)
        {
            Student p[5];
            FillArray(p);
            Sort(p, 5);
            Assert::AreEqual(0, BinSearch(p, 5, "Андрієнко", 1, INFORMATYKA));
            Assert::AreEqual(2, BinSearch(p, 5, "Бондар", 1, KOMP_NAUKY));
            Assert::AreEqual(4, BinSearch(p, 5, "Шевченко", 2, KOMP_NAUKY));
        }

        // BinSearch: такого студента немає
        TEST_METHOD(TestBinSearch_NotFound)
        {
            Student p[5];
            FillArray(p);
            Sort(p, 5);
            Assert::AreEqual(-1, BinSearch(p, 5, "Бондар", 1, INFORMATYKA));   // інша спеціальність
            Assert::AreEqual(-1, BinSearch(p, 5, "Бондар", 2, KOMP_NAUKY));    // інший курс
            Assert::AreEqual(-1, BinSearch(p, 5, "Іваненко", 1, KOMP_NAUKY));  // такого прізвища немає
        }

        // BinSearch: один елемент
        TEST_METHOD(TestBinSearch_One)
        {
            Student p[1];
            Fill(p[0], "Бондар", 1, KOMP_NAUKY);
            Assert::AreEqual(0, BinSearch(p, 1, "Бондар", 1, KOMP_NAUKY));
            Assert::AreEqual(-1, BinSearch(p, 1, "Андрієнко", 1, KOMP_NAUKY));
        }
    };
}