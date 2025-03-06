#include <stdexcept>
#include "biginteger.h"

void main()
{
	std::string str = "1";
	BigInteger a(str), b(-1);// , b(str2);
	a += b;
	std::cout << "a = " << a << " , b = " << b << std::endl;
	system("pause");
}



