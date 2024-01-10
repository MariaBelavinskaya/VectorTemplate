#include"../VectorOnTemplates/Vector.h"

int main()
{
	Vector<int> vector1 = { 1, 2, 3 };
	Vector<int> vector2=vector1;
	std::cout << (vector2.toString());

}