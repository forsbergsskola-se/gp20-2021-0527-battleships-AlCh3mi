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
        cout << "Number " << i + 1 << ": " << value[i] << " : " << PercentOfTheTime(value[i]) << " % of the time." << endl;
    }
}

int IndexOfLowest(int value[]){
    int index;
    int lowestFoundValue = iterations;
    for (int i = 0; i < between1and; ++i) {
        if(value[i] < lowestFoundValue) {
            lowestFoundValue = value[i];
            index = i;
        }
    }
    return index;
}

int IndexOfSmallestOffset(int value[]){
    int index;
    float average = iterations/between1and;
    float smallest = iterations;
    for (int i = 0; i < between1and; ++i) {
        if(abs(value[i] - average) < (abs(smallest) - average))
        {
            index = i;
            smallest = value[i];
        }
    }
    return index;
}

int IndexOfHighest(int value[]){
    int index;
    int highestFoundValue = 0;
    for (int i = 0; i < between1and; ++i) {
        if(value[i] > highestFoundValue) {
            highestFoundValue = value[i];
            index = i;
        }
    }
    return index;
}

int IndexOfGreatestOffset(int value[]){
    float lowestOffset = abs(PercentOfTheTime(IndexOfLowest(value)) - (100/between1and));
    float highestOffset = abs(PercentOfTheTime(IndexOfHighest(value)) - (100/between1and));

    if(lowestOffset > highestOffset)
        return IndexOfLowest(value);
    else
        return IndexOfHighest(value);
}

float GreatestOffset(int value[]){
    return abs(PercentOfTheTime(value[IndexOfGreatestOffset(value)]) - (100/between1and));
}

int main() {

    int occurrences[between1and] {};

    srand(time(0));

    for (int i = 0; i < iterations; ++i)
        occurrences[rand() % between1and]++;

    DisplayResults(occurrences);

    cout << IndexOfLowest(occurrences)+1 << " occurred the least." << endl;
    cout << IndexOfHighest(occurrences)+1 << " occurred the most." << endl;


    cout << "Maximum offset: Number " << IndexOfGreatestOffset(occurrences) + 1 << " (" << GreatestOffset(occurrences) << "%)" << endl;
    cout << "Minimum offset: Number " << IndexOfSmallestOffset(occurrences) + 1 << " (" << occurrences[IndexOfSmallestOffset(occurrences)]/iterations << "%)" << endl;
    return 0;
}


