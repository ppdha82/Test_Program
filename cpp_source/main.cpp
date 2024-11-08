#include <iostream>
#include <cstdio>
#include <climits>

int main(void)
{
	int A, B;
	std::cin >> A >> B;
	//std::cout << "A = " << A << " B = " << B << std::endl;
	if (A <= 0 || B <= 0 || A >= 10 || B>= 10)
	{
		std::cout << "You entered excess A or B" << std::endl;
		return -1;
	}
	std::cout << A - B << std::endl;
	std::cout << "INT_MAX[" << INT_MAX << "] INT_MIN[" << INT_MIN << "]\n";

	return 0;
}
