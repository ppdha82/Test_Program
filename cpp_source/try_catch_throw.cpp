#include <iostream>

using namespace std;

void Devide (int num1, int num2)
{
    if (num2 == 0)
        throw num2;
    cout << "나눗셈의 몫: " << num1 / num2 << "\n";
    cout << "나눗셈의 나머지: " << num1 % num2 << "\n";
}

int main (void)
{
    int n1, n2;
    cout << "두 개의 숫자 입력: ";
    cin >> n1 >> n2;

    try
    {
        Devide(n1, n2);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (int expn)
    {
        cout << "제수는 " << expn << "이 될 수 없습니다" << "\n";
        cout << "프로그램을 종료합니다" << "\n";
    }

    return 0;
}