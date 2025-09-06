

/**
 * @file 2130_C_Double_Perspective.cpp
 * @brief Solution for Codeforces problem 2130C - Double Perspective
 * 
 * Problem: Given a set of intervals, where each interval has a start and end point,
 * we need to find for each unique start point the interval with the maximum end point,
 * and output their original indices.
 * 
 * Approach:
 * 1. For each test case:
 *    a. Read the number of intervals
 *    b. For each interval, store the maximum end point for each start point
 *    c. Keep track of the original index of the interval with the maximum end point
 *    d. Output the count of unique start points and their corresponding interval indices
 * 
 * Time Complexity: O(n log n) per test case due to map operations
 * Space Complexity: O(n) to store the intervals
 */

#include <iostream>
#include <map>
#include <vector>
using namespace std;

/**
 * @brief Solves a single test case of the problem
 */
void solveTestCase() {
    int numIntervals;
    cin >> numIntervals;
    
    // Maps start point to pair of (max_end_point, original_index)
    map<int, pair<int, int>> startToMaxEnd;
    
    // Read and process each interval
    for (int originalIndex = 1; originalIndex <= numIntervals; ++originalIndex) {
        int start, end;
        cin >> start >> end;
        
        // Update if this is the first occurrence of 'start' or if it has a larger end point
        if (startToMaxEnd[start].first < end) {
            startToMaxEnd[start] = {end, originalIndex};
        }
    }
    
    // Output the number of unique start points
    cout << startToMaxEnd.size() << '\n';
    
    // Output the original indices of the selected intervals
    for (const auto& entry : startToMaxEnd) {
        cout << entry.second.second << ' ';
    }
    cout << '\n';
}

int main() {
    // Improve I/O performance
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        solveTestCase();
    }
    
    return 0;
}
}