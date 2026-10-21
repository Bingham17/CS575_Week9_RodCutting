#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

void writeTestFile() {
    /*
    Write various test cases for Rod Cutting
    */
    srand(time(0));
    int randRod = rand() % 900 + 1; // Random number between 1 and 900
    int randNumRods = rand() % 30 + 1; // Random number between 1 and 10
    ofstream testFile;
    string fileName = "testFile" + to_string(randRod) + "_" + to_string(randNumRods) + ".txt";
    testFile.open(fileName);
    testFile << randRod << " ";
    testFile << randNumRods << endl;
    for (int i = 0; i < randNumRods; i++) {
        int randLength = rand() % 30 + 1; // Random length between 1 and 30
        int randPrice = rand() % 100 + 1; // Random price between 1 and 100
        testFile << randLength << " " << randPrice << endl;
    }
    testFile.close();
}

int main(int argc, char *argv[]) {

    writeTestFile();

    return 1;
}