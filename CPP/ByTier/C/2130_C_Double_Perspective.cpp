// Problem: CF 2130 C - Double Perspective
// https://codeforces.com/contest/2130/problem/C

/*
C. Double Perspective

Purpose:
This code solves a problem where given a set of intervals (pairs), we need to select a subset such that the difference between the "union length" (f(S)) and the "number of nodes in cycles" (g(S)) is maximized. 
It selects intervals optimally by keeping only those with the maximum end value for each start point, which helps in maximizing f(S) while minimizing g(S).

Algorithms/Techniques:
- Greedy approach with map to avoid overlapping intervals with same start.
- Use of map<int, pair<int, int>> to store start -> {max_end, original_index}.

Time Complexity: O(n log n)
Space Complexity: O(n)

Input:
- Number of test cases t
- For each test case:
  - Number of intervals n
  - n pairs of integers (start, end)

Output:
- Size of selected subset k
- Indices of selected intervals (1-based)
*/

#include <iostream>
#include <map>
#include <utility>

using namespace std;

void solveTestCase() {
  int numIntervals;
  cin >> numIntervals;
  // Map to store start -> {max_end, original_index}
  map<int, pair<int, int>> startToMaxEnd;
  for (int originalIndex = 1; originalIndex <= numIntervals; ++originalIndex) {
    int start, end;
    cin >> start >> end;
    // If current interval has a larger end value, update the map
    if (startToMaxEnd[start].first < end) {
      startToMaxEnd[start] = {end, originalIndex};
    }
  }
  // Print number of intervals in selected subset
  cout << startToMaxEnd.size() << '\n';
  // Print indices of selected intervals
  for (const auto &entry : startToMaxEnd) {
    cout << entry.second.second << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int testCases;
  cin >> testCases;
  while (testCases--) {
    solveTestCase();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/