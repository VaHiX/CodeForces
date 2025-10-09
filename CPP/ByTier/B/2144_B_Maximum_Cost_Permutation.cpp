// Problem: CF 2144 B - Maximum Cost Permutation
// https://codeforces.com/contest/2144/problem/B

/*
B. Maximum Cost Permutation
Algorithms/Techniques: Greedy, Simulation, Sorting
Time Complexity: O(n log n) per test case due to sorting and linear scans
Space Complexity: O(n) for the vector storage

Recall that a permutation of length n is a sequence of length n such that each integer from 1 to n appears in it exactly once.
Let's define the cost of a permutation as the minimum length of its contiguous subsegment (possibly empty) that needs to be sorted so that the entire permutation becomes sorted in ascending order.
You are given an integer array p consisting of integers from 0 to n, where no positive (strictly greater than zero) integer appears more than once. You should replace zeros with integers so that the array p becomes a permutation. 
Your task is to calculate the maximum possible cost of the resulting permutation.
*/
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> p(n);
  int zer = 0, idx = -1;
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    if (!p[i])
      zer++, idx = i;
  }
  // If there's exactly one zero, replace it with the value that makes the total sum correct
  if (zer == 1)
    p[idx] = (n + 1ll) * n / 2 - accumulate(p.begin(), p.end(), 0ll);
  
  // Find the leftmost and rightmost position where element doesn't equal its expected value (i+1)
  int l = -1, r = -2;
  for (int i = 0; i < n; i++) {
    if (p[i] == i + 1)
      continue;
    r = i;
    if (!~l)   // if l is still -1
      l = i;
  }
  cout << r - l + 1 << '\n';
}

int main() {
  cin.tie(NULL)->sync_with_stdio(false);
  int tt = 1;
  cin >> tt;
  while (tt--)
    solve();
}


// https://github.com/VaHiX/codeForces/