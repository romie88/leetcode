#include "166.Fraction.to.Recurring.Decimal.cpp"

int main() {
    
    int i1, i2;
    std::cout << "please enter two integers: " << std::endl;
    std::cin >> i1 >> i2;

    Solution s;
    std::cout << s.fractionToDecimal( i1, i2 ) << std::endl;

    return 0;
}
