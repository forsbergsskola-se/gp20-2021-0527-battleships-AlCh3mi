#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

int iterations = 1000000;
const int between1and = 20;


float PercentOfTheTime(int value){
    return ((float)value / iterations) * 100;
}

void DisplayResults(int value[]){
    for (int i = 0; i < between1and; ++i) {
        cout << "Number " << i+1 << ": " << value[i] << " : " << PercentOfTheTime(value[i]) << "% of the time." << endl;
    }
}

int main() {

    int occurrences[between1and] {};

    srand(time(0));

    for (int i = 0; i < iterations; ++i)
        occurrences[rand() % between1and]++;

    DisplayResults(occurrences);


    return 0;
}


