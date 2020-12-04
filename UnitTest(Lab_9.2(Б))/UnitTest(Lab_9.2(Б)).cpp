#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_9.2(B)/Lab_9.2(B).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab92Б
{
	TEST_CLASS(UnitTestLab92Б)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int kil_student = 2;
			student* s = new student[kil_student];
			s[0].prizv = "gre";                  s[1].prizv = "wasf";
			s[0].kurs = 6;                        s[1].kurs = 3;
			s[0].specialization = (Special)2;     s[1].specialization = (Special)0;
			s[0].phisuka = 4;                     s[1].phisuka = 2;
			s[0].matematic = 4;                   s[1].matematic = 3;
			s[0].pedahohica = 5;                  s[1].programing = 5;

			Sort(s, kil_student);

			Assert::AreEqual(s[0].kurs, 3);
		}
	};
}
