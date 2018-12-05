#include <iostream>
#include <cstdio>

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

	return 0;
}
