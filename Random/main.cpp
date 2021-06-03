#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;
const int Options = 20;
int Iterations = 10000000;
float Average = Iterations / Options;
float AveragePercentage = (100 / Options);

float PercentOfTheTime(float value, float denominator){
    return ((float)value / denominator) * 100;
}

int IndexOfLowest(int value[]){
    int index;
    int lowestFoundValue = Iterations;
    for (int i = 0; i < Options; ++i) {
        if(value[i] < lowestFoundValue) {
            lowestFoundValue = value[i];
            index = i;
        }
    }
    return index;
}

int IndexOfHighest(int value[]){
    int index;
    int highestFoundValue = 0;
    for (int i = 0; i < Options; ++i) {
        if(value[i] > highestFoundValue) {
            highestFoundValue = value[i];
            index = i;
        }
    }
    return index;
}

int IndexOfSmallestOffset(int value[]){
    int index;
    float smallest = Iterations;
    for (int i = 0; i < Options; ++i) {
        if(abs(value[i] - Average) < abs(smallest - Average))
        {
            index = i;
            smallest = value[i];
        }
    }
    return index;
}

int IndexOfGreatestOffset(int value[]){
    int index;
    int greatestOffset = 0;
    for (int i = 0; i < Options; ++i) {
        if(abs(value[i] - Average) > greatestOffset) {
            greatestOffset = abs(value[i] - Average);
            index = i;
        }
    }
    return index;
}

float SmallestOffset(int value[]){
    return abs(PercentOfTheTime(value[IndexOfSmallestOffset(value)], Iterations) - AveragePercentage);
}

float AverageOffset(int value[]){
    float avg;
    for (int i = 0; i < Options; ++i) {
        avg += abs(value[i] - Average);
    }
    return (avg / Options);
}

float GreatestOffset(int value[]){
    return abs(value[IndexOfGreatestOffset(value)] - Average);
}

void DisplayStats(int *occurrences) {
    cout <<endl <<"Rolling a " <<Options <<" sided dice " <<Iterations <<" times:" <<endl <<endl;
    cout <<"Average: " <<Average <<endl;
    cout <<"Average Percentage: " <<AveragePercentage <<endl <<endl;
    cout <<IndexOfLowest(occurrences)+1 <<" occurred the least." <<endl;
    cout <<IndexOfHighest(occurrences)+1 <<" occurred the most." <<endl;
    cout <<"Minimum offset: Number " <<IndexOfSmallestOffset(occurrences) + 1 <<" (" <<SmallestOffset(occurrences) <<"%)" <<endl;
    cout <<"Maximum offset: Number " <<IndexOfGreatestOffset(occurrences) + 1 <<" (" <<PercentOfTheTime(GreatestOffset(occurrences), Iterations) <<"%)" <<endl;
    cout <<"Average Offset: " <<(AverageOffset(occurrences) / Average) <<"%" <<endl;
}

void DisplayResults(int value[]){
    for (int i = 0; i < Options; ++i) {
        cout <<"Number " <<i+1 <<": "<< value[i] <<" times ("<< PercentOfTheTime(value[i], Iterations) <<"%)" <<endl;
    }
    DisplayStats(value);
}

int main() {
    int occurrences[Options] {};

    srand(time(0));
    for (int i = 0; i < Iterations; ++i)
        occurrences[rand() % Options]++;

    DisplayResults(occurrences);
    return 0;
}