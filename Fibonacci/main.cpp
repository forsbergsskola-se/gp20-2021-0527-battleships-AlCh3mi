#include <iostream>

using namespace std;

int Fibonacci(int);
int Fib(int num);

int main() {
    cout << "Fibonacci!" << endl;
    cout << "Enter a number to Fibonacci it:";
    int input;
    cin >> input;
    cout << "Answer: " << Fibonacci(input) << " solved by Recursion"<<endl;
    cout << "Answer: " << Fib(input) << " solved by Iteration" << endl;
    return 0;
}

int Fibonacci(int value) {
    if(value < 2) return value;
    return Fibonacci(value - 1) + Fibonacci(value - 2);
}

int Fib(int value) {
    int current = 0, next = 1;
    int tmp = 0;

    for (int i = 0; i < value; i++) {
        tmp = current + next;
        current = next;
        next = tmp;
    }
    return current;
}
