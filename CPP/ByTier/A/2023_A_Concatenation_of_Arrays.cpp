// Problem: CF 2023 A - Concatenation of Arrays
// https://codeforces.com/contest/2023/problem/A

/*
Purpose: 
This code solves the problem of minimizing inversions when concatenating n arrays, each of length 2.
The algorithm sorts the arrays based on the sum of their elements and then concatenates them in that order.
This greedy approach works because placing arrays with smaller sums first minimizes the likelihood of having inversions
between elements from different arrays.

Algorithms/Techniques:
- Greedy sorting based on sum of elements in each array
- Custom comparator for sorting pairs

Time Complexity: O(n log n) per test case due to sorting; overall O(t * n log n) for t test cases
Space Complexity: O(n) for storing the arrays and auxiliary space used by sorting

*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define ll long long
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &[i, j] : a)
      cin >> i >> j;
    // Sort arrays based on the sum of their elements
    sort(a.begin(), a.end(), [](auto x, auto y) {
      return x.first + x.second < y.first + y.second;
    });
    // Output the concatenated result
    for (auto [i, j] : a)
      cout << i << " " << j << " ";
    cout << endl;
  }
}


// https://github.com/VaHiX/CodeForces/