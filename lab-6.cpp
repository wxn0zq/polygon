#include <iostream>
#include <vector>

using namespace std;


int findIntegers(int n) {
    int prevBit = 0;  
    int result = 0;  
    int fib[31] = {0}; 
   

    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < 31; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int bitPosition = 30; 

    while (bitPosition >= 0) {
       
        if (n & (1 << bitPosition)) { 
            result += fib[bitPosition];
            if (prevBit == 1) { 
                return result;
            }
            prevBit = 1;
        } else {
            prevBit = 0;
        }
        --bitPosition; 
    }

    return result + 1; 
}

int main() {
    int n = 5;
    cout << findIntegers(n) << endl; // Вывод: 5

    n = 10;
    cout << findIntegers(n) << endl; // Вывод: 8

    n = 20;
    cout << findIntegers(n) << endl; // Вывод: 13

    return 0;
}
