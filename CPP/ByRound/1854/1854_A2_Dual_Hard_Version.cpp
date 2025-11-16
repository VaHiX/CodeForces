// Problem: CF 1854 A2 - Dual (Hard Version)
// https://codeforces.com/contest/1854/problem/A2

/*
Purpose: 
This code solves the "Dual (Hard Version)" problem where we need to make an array non-decreasing using at most 31 operations. 
Each operation allows adding the value of one element to another element.

Algorithms/Techniques:
- Classification of array elements into positive and negative groups.
- Strategy based on the magnitude of minimum and maximum elements to decide how to balance the array:
  * If absolute value of minimum element is less than or equal to maximum, we try to make all negative elements positive using the largest positive element.
  * Otherwise, we try to make all positive elements negative using the smallest negative element.
- Greedy approach to perform necessary operations in a fixed sequence.

Time Complexity: O(n^2) per test case due to nested loops for finding max/min in lists and operations.
Space Complexity: O(n) for storing the array and auxiliary vectors for indices of positive and negative elements.

*/
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n), b, c; // b stores indices of negative elements, c stores indices of positive elements
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      if (a[i] < 0)
        b.push_back(i);
      if (a[i] > 0)
        c.push_back(i);
      x = min(x, a[i]); // Track minimum value
      y = max(y, a[i]); // Track maximum value
    }
    vector<pair<int, int>> ans; // Stores operations as pair of (from_index, to_index)
    if (b.size() == 0 && c.size() == 0) {
      cout << 0 << "\n";
      continue;
    }
    if (abs(x) <= abs(y)) { // If abs(minimum) <= abs(maximum)
      if (b.size() <= 12) { // If number of negative elements is small
        int mx = c[0]; // Find the index of maximum positive element
        for (int i = 0; i < c.size(); i++) {
          if (a[mx] < a[c[i]])
            mx = c[i];
        }
        for (int i = 0; i < b.size(); i++) {
          ans.push_back({b[i], mx}); // Add each negative element to the max positive
        }
        for (int i = 0; i + 1 < n; i++) {
          ans.push_back({i + 1, i}); // Make array non-decreasing from left to right
        }
      } else { // If there are too many negative elements
        for (int i = 0; i < 5; i++) {
          ans.push_back({b[0], b[0]}); // Duplicate the first negative element 5 times to build up its value
        }
        for (int i = 0; i < c.size(); i++) {
          ans.push_back({c[i], b[0]}); // Add all positives to the first negative to make it large
        }
        for (int i = n - 1; i >= 1; i--) {
          ans.push_back({i - 1, i}); // Build non-decreasing from right to left
        }
      }
    } else { // If abs(maximum) < abs(minimum)
      if (c.size() <= 12) { // If number of positive elements is small
        int mi = b[0]; // Find index of minimum negative element
        for (int i = 0; i < b.size(); i++) {
          if (a[mi] > a[b[i]])
            mi = b[i];
        }
        for (int i = 0; i < c.size(); i++) {
          ans.push_back({c[i], mi}); // Add all positives to the smallest negative to make it negative
        }
        for (int i = n - 1; i >= 1; i--) {
          ans.push_back({i - 1, i}); // Make array non-decreasing from right to left
        }
      } else { // If there are too many positive elements
        for (int i = 0; i < 5; i++) {
          ans.push_back({c[0], c[0]}); // Duplicate the first positive element 5 times to build up its value
        }
        for (int i = 0; i < b.size(); i++) {
          ans.push_back({b[i], c[0]}); // Add all negatives to the first positive to make it large
        }
        for (int i = 0; i + 1 < n; i++) {
          ans.push_back({i + 1, i}); // Build non-decreasing from left to right
        }
      }
    }
    cout << ans.size() << "\n";
    for (auto i : ans) {
      cout << i.first + 1 << " " << i.second + 1 << "\n"; // Convert indices to 1-based
    }
  }
}


// https://github.com/VaHiX/CodeForces/