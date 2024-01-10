#include "pch.h"
#include "CppUnitTest.h"
#include"../VectorOnTemplates/Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestVector
{
	TEST_CLASS(TestVector)
	{
	public:
		
		TEST_METHOD(OperatorForCompareTest_ValitData_Success)
		{
			Vector<int> vector1 {1, 4, 2, 6};
			Vector<int> vector2 {1, 4, 2, 6};
			bool are_equal = (vector1 == vector2);
			Assert::IsTrue(are_equal);
		}

		TEST_METHOD(ToString_ValitData_Success)
		{
			Vector<int> vector{1, 2, 3, 4};
			bool are_equal = (vector.toString() == "1 2 3 4 ");
			Assert::IsTrue(are_equal);
		}

		TEST_METHOD(OperatorForNotCompareTest_ValitData_Success)
		{
			Vector<int> vector1 {1, 4, 2, 6};
			Vector<int> vector2 {2, 4, 5, 6};
			bool arequal = (vector1 != vector2);
			Assert::IsTrue(arequal);
		}

		TEST_METHOD(GetSize_ValitData_Success)
		{
			Vector<int> vector1 {1, 4, 2, 6};
			bool arequal = (vector1.getSize()==4);
			Assert::IsTrue(arequal);
		}

		TEST_METHOD(DeletI_ValitData_Success)
		{
			Vector<int> vector1 {1, 4, 2 };
			vector1.deleteI(1);
			bool arequal = (vector1.toString()=="1 2 ");
			Assert::IsTrue(arequal);
		}
	};
}
