// Problem: CF 1744 D - Divisibility by 2^n
// https://codeforces.com/contest/1744/problem/D

/*
D. Divisibility by 2^n
Problem Description:
Given an array of positive integers, make the product of all elements divisible by 2^n using the minimum number of operations. Each operation allows replacing a[i] with a[i] * i.

Algorithms/Techniques:
- Count total powers of 2 in the initial product
- For each element, calculate how many times we can multiply it by its index to gain powers of 2
- Greedily select the indices that give maximum power of 2 per operation
- Sort and use greedy approach to cover required number of powers

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing array v
*/

#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int x, sum = 0, ss = 0, v[n];
    for (int i = 1; i <= n; i++) {
      cin >> x;
      v[i] = 0;
      // Count powers of 2 in current element and add to total
      while (x % 2 == 0) {
        x = x / 2;
        sum++;
      }
      int j = i;
      // Count how many times we can multiply by index i to gain powers of 2
      while (j % 2 == 0) {
        j = j / 2;
        v[i]++;
      }
    }
    sort(v + 1, v + n + 1); // Sort the gains in ascending order
    // Greedily select operations from highest gain to lowest until we have enough powers
    for (int i = n; i >= 1 && sum < n; i--) {
      sum += v[i];
      ss++;
    }
    if (sum < n)
      cout << -1 << endl; // Not possible to achieve required divisibility
    else
      cout << ss << endl; // Minimum operations needed
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/