#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

/*
Name: Christopher Bingham
Email: cbingha2@binghamton.edu
Assignment: Week 9 - Rod Cutting Algorithm
*/

#define MAX_RODS 1000

void printdpTable(vector<int> &dp) {
    /*
    Print the dynamic programming table
    Parameters:
        dp <vector<int>>: Dynamic programming table to print
    Returns:
        None
    */
    for (int i = 0; i < 50; i++) {
        cout << "Length " << i << ": " << dp[i] << endl;
    }
}

void initData(ifstream &inputfile, vector<int> &rodLengths, vector<int> &rodPrices, int &numRods) {
    /*
    Read in the input file and store the rod's respective length and price in the respective vectors
    Parameters:
        inputfile <&ifstream>: Input file stream to read rod data from
        rodLengths <vector<int>>: Vector to store the rods' lengths
        rodPrices <vector<int>>: Vector to store the rods' prices
        numRods <int&>: Number of possible rods to cut from
    Returns:
        None
    */
    inputfile >> numRods;
    rodLengths.resize(numRods);
    rodPrices.resize(numRods);
    for(int i = 0; i < numRods; i++) {
        inputfile >> rodLengths[i];
        inputfile >> rodPrices[i];
    }

    return;
}

vector<int> initDPTable(vector<int> &rodLengths, vector<int> &rodPrices) {
    /*
    Initialize the dynamic programming table
    Parameters:
        rodLengths <vector<int>>: Vector of rod lengths
        rodPrices <vector<int>>: Vector of rod prices
    Returns:
        dp <vector<int>>: Dynamic programming table initialized. 
        All profits are unknown (-1) except for Length 0, and all known rod legnths & prices
    */
   vector<int> dp(MAX_RODS, -1);
   dp[0] = 0;

    for (int i = 0; i < rodLengths.size(); i++) {
        dp[rodLengths[i]] = rodPrices[i];
    }

    return dp;
}

int rodCut(int rodToCut, vector<int> &rodLengths, vector<int> &rodPrices, int numRods, vector<int> &dp) {
    /*
    Recursive function to calculate the maximum profit from cutting a rod of length rodToCut.
    Parameters:
        rodToCut <int>: The length of the rod to be cut
        rodLengths <vector<int>>: Vector containing the lengths of available rods
        rodPrices <vector<int>>: Vector containing the prices of available rods
        numRods <int>: The number of available rods
        dp <vector<int>>: Dynamic programming array to store computed values
    Returns:
        The maximum profit that can be obtained from cutting the rod
    */
    if (rodToCut == 0) {
        return 0;
    }
    if (dp[rodToCut] != -1) {
        // cout << "Found| Length: " << rodToCut << " | Cost: " << dp[rodToCut] << endl;
        return dp[rodToCut];
    }

    int maxProfit = 0;
    for (int i = 0; i < numRods; i++) {
        if (rodLengths[i] <= rodToCut) {
            int profit = rodPrices[i] + rodCut(rodToCut - rodLengths[i], rodLengths, rodPrices, numRods, dp);
            maxProfit = max(maxProfit, profit);
        }
    }

    dp[rodToCut] = maxProfit;
    return maxProfit;
}

int main(int argc, char *argv[]) {
    /*
    Main function to execute the Rod Cutting algorithm.
    CommandLine Usage:
        - ./rodCut <input_file>
    Command line arguments:
        - argv[1]: The name of the input file
        - If no command line argument is provided, the user will be prompted to enter the file name.
    Returns:
        - 0: Successful execution
        - 1: Error in opening the input file
    */

    //Read the input file and build the vertices and edges
    ifstream inputFile;
    vector<int> rodLengths;
    vector<int> rodPrices;
    int numRods;
    int rodToCut;

    if (argc != 2) {
        string fileName;
        cout << "Enter File Name: " << endl;
        cin >> fileName;
        inputFile.open(fileName);
    } else {
        inputFile.open(argv[1]);
    }

    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
    inputFile >> rodToCut;

    initData(inputFile, rodLengths, rodPrices, numRods);

    vector<int> dpRod = initDPTable(rodLengths, rodPrices);

    // printdpTable(dpRod);
    
    cout << rodCut(rodToCut, rodLengths, rodPrices, numRods, dpRod) << endl;

    // printdpTable(dpRod);


    return 0;
}