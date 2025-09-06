

/**
 * ===========================================================================
 * 2130A - Submission is All You Need
 * ===========================================================================
 * 
 * Problem: Calculate the sum of array elements, treating zeros as ones.
 * 
 * Input:  Multiple test cases, each containing an array of integers.
 * Output: For each test case, output the sum of elements (zeros count as ones).
 * 
 * Complexity: O(t * n), where t is number of test cases and n is array size.
 * ===========================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    // Optimize I/O operations for better performance
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int numTestCases;
    cin >> numTestCases;
    
    while (numTestCases--) {
        int arraySize, totalSum = 0;
        cin >> arraySize;
        
        // Process each element in the current test case
        for (int i = 0; i < arraySize; ++i) {
            int currentNumber;
            cin >> currentNumber;
            totalSum += (currentNumber != 0) ? currentNumber : 1;
        }
        
        cout << totalSum << "\n";
    }
    
    return 0;
}
}