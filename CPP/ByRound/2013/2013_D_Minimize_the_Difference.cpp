// Problem: CF 2013 D - Minimize the Difference
// https://codeforces.com/contest/2013/problem/D

/*
D. Minimize the Difference
Problem Description:
Given an array of integers, we can perform operations where we decrease an element at index i and increase the next element at index i+1. The goal is to minimize the difference between the maximum and minimum elements in the array after any number of such operations.

Algorithms/Techniques:
- Prefix and suffix sum computations with binary search logic
- Greedy approach using prefix and suffix averages

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array

*/

#include <iostream>
#include <algorithm>

#define N 200005
using namespace std;
long long a[N];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  
  long long s = 0, minn = 1e18, maxn = -1e18;
  
  // Compute prefix averages to find the minimum possible maximum value
  for (int i = 1; i <= n; ++i)
    s += a[i], minn = min(minn, s / i);  // s/i gives average of first i elements rounded down
  
  s = 0;
  
  // Compute suffix averages to find the maximum possible minimum value
  for (int i = 1; i <= n; ++i)
    s += a[n - i + 1], maxn = max(maxn, (s + i - 1) / i);  // (s+i-1)/i gives average rounded up
  
  cout << maxn - minn << "\n";
}

int main() {
  ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/