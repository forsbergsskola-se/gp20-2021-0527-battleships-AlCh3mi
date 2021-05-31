#include <iostream>
#include <chrono>  // for high_resolution_clock

using namespace std;

int Fibonacci(int);
int Fib(int num);

int main() {
    cout << "Fibonacci!" << endl;
    cout << "Enter a number to Fibonacci it:";
    int input;
    cin >> input;

    auto start = std::chrono::high_resolution_clock::now();
    cout << "Answer: " << Fibonacci(input) << " solved by Recursion"<< endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    cout << "(completed in " << elapsed.count() << "sec)" << endl;

    cout << endl;

    start = std::chrono::high_resolution_clock::now();
    cout << "Answer: " << Fib(input) << " solved by Iteration" << endl;
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout << "(completed in " << elapsed.count() << "sec)" << endl;
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
