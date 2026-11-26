
#include "pch.h"
#include "CppUnitTest.h"
#include "../PR_10.1 B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1001B
{
    TEST_CLASS(UnitTest1001B)
    {
    public:

        TEST_METHOD(TestCountFizyka)
        {
            Student p[6];

            p[0].fizyka = 5;
            p[1].fizyka = 4;
            p[2].fizyka = 3;
            p[3].fizyka = 5;
            p[4].fizyka = 4;
            p[5].fizyka = 2;

            int k5, k4, k3;

            CountFizyka(p, 6, k5, k4, k3);

            Assert::AreEqual(2, k5);
            Assert::AreEqual(2, k4);
            Assert::AreEqual(1, k3);
        }

        TEST_METHOD(TestCountFizMat45)
        {
            Student p[6];

            p[0].fizyka = 5;
            p[0].matematyka = 4;

            p[1].fizyka = 4;
            p[1].matematyka = 5;

            p[2].fizyka = 3;
            p[2].matematyka = 3;

            p[3].fizyka = 5;
            p[3].matematyka = 5;

            p[4].fizyka = 4;
            p[4].matematyka = 3;

            p[5].fizyka = 2;
            p[5].matematyka = 4;

            int result = CountFizMat45(p, 6);

            Assert::AreEqual(3, result);
        }
    };
}
