// Problem: CF 2009 E - Klee's SUPER DUPER LARGE Array!!!
// https://codeforces.com/contest/2009/problem/E

/*
E. Klee's SUPER DUPER LARGE Array!!!
Algorithms/Techniques: Mathematical analysis, binary search on answer
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves finding an index i in an array a = [k, k+1, ..., k+n-1] such that
the absolute difference between the sum of elements from start to i and the sum
of elements from i+1 to end is minimized.

Key insight:
- Prefix sum: S(i) = k + (k+1) + ... + (k+i-1) = i*k + i*(i-1)/2
- Suffix sum: S'(i) = (k+i) + (k+i+1) + ... + (k+n-1)
  which simplifies to (n-i)*k + (n-i)*(n-i+1)/2 - i*(i+1)/2

We want to minimize |S(i) - S'(i)|.

After algebraic manipulation and optimization:
- We derive that the expression for total sum is: res = (k+n−1)*(k+n)/2 + k*(k−1)/2
- Then, we approximate a value t such that t(t+1)/2 ≈ res.
- Finally, choose between t and t+1 to minimize the difference.

This approach avoids iterating through all possible i values due to constraints (n up to 1e9).
*/

#include <algorithm>
#include <bits/std_abs.h>
#include <cmath>
#include <iostream>
using namespace std;

void solve() {
  long long n, k;
  cin >> n >> k;
  // Compute the total sum of all elements in the array
  long long res = (k + n - 1) * (k + n) / 2 + k * (k - 1) / 2;
  // Estimate square root to find the closest triangular number approximation
  long long t = floor(sqrt(res));
  // Return the minimum absolute difference between res and two consecutive triangular numbers
  cout << min(abs(res - t * (t + 1)), abs(res - (t + 1) * (t + 2))) << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/