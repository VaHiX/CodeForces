// Problem: CF 1814 C - Search in Parallel
// https://codeforces.com/contest/1814/problem/C

/*
Algorithm/Technique: Greedy
Time Complexity: O(n log n) due to sorting; O(n) for assignment, so overall O(n log n)
Space Complexity: O(n) for storing input and temporary structures

This code solves the problem of assigning boxes to two robots to minimize the total search time
for a series of ball requests. The strategy is to assign boxes greedily to the robot that would
be faster at processing the next box in the sorted list of requests by number of requests.
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n, s1, s2;
    cin >> n >> s1 >> s2;
    vector<int> a, b;
    vector<pair<int, int>> c(n);
    for (int i = 0; i < n; ++i) {
      cin >> c[i].second;   // Read the number of requests for color i+1
      c[i].first = i + 1;   // Store the color index
    }
    sort(c.begin(), c.end(), [&](pair<int, int> x, pair<int, int> y) {
      return x.second > y.second;  // Sort by number of requests in descending order
    });
    for (int i = 0; i < n; ++i) {
      int cur = c[i].first;   // Current color to assign
      // Compare the estimated total time to process all boxes assigned to each robot
      // (size + 1) * s1 represents time for robot 1 to process its boxes
      // (size + 1) * s2 represents time for robot 2 to process its boxes
      if ((a.size() + 1) * s1 <= (b.size() + 1) * s2) {
        a.push_back(cur);   // Assign to robot 1
      } else
        b.push_back(cur);   // Assign to robot 2
    }
    cout << a.size() << " ";
    for (int c : a)
      cout << c << " ";
    cout << "\n";
    cout << b.size() << " ";
    for (int c : b)
      cout << c << " ";
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/