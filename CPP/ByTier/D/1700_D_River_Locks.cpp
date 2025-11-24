// Problem: CF 1700 D - River Locks
// https://codeforces.com/contest/1700/problem/D

/*
Code Purpose:
This program solves the river locks problem where locks fill up with water from pipes,
and water overflows to the next lock. The goal is to find the minimum number of pipes
to open such that all locks are filled within a given time.

Algorithms/Techniques:
- Prefix sum and greedy approach
- Binary search or direct calculation for minimum pipes needed

Time Complexity:
O(n + q) where n is the number of locks and q is the number of queries.

Space Complexity:
O(1) - only using a few variables regardless of input size.

*/

#include <stdint.h>
#include <algorithm>
#include <iostream>

using namespace std;
int64_t n, q, mx, sm, in;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    sm += x; // Accumulate total volume of all locks
    mx = max(mx, (sm + i - 1) / i); // Compute maximum required time if all pipes opened at once
  }
  cin >> q;
  while (q--) {
    cin >> in;
    // If given time is less than the max time needed, impossible to fill all locks
    // Otherwise, compute minimum pipes needed using ceiling division
    cout << ((in < mx) ? -1 : (sm + in - 1) / in) << endl;
  }
}


// https://github.com/VaHiX/CodeForces/