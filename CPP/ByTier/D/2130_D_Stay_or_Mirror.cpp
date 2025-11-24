// Problem: CF 2130 D - Stay or Mirror
// https://codeforces.com/contest/2130/problem/D

/*
D. Stay or Mirror
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

You are given a permutation p_1, p_2, ..., p_n of length n.
You have to build an array a_1, a_2, ..., a_n in the following way:

for each 1 <= i <= n, set either a_i = p_i or a_i = 2n - p_i. 
Find the minimum possible number of inversions in the array a_1, a_2, ..., a_n.
An inversion in the array a_1, a_2, ..., a_n is a pair of indices (i, j) such that 1 <= i < j <= n and a_i > a_j.

Algorithms/Techniques: Brute Force with Optimization
Time Complexity: O(n^2)
Space Complexity: O(n)

The key idea is for each element in the permutation, we can choose to keep it as p[i] or mirror it as 2n - p[i].
For each element p[i], we precompute how many elements after it are greater (greaterAfter),
and then compute an equivalent "mirror" count (mirrorOperations) to determine
the minimal number of inversions contributed by this element.
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

ll solveTestCase(int n, const vector<int> &permutation) {
  ll totalOperations = 0;
  for (int currentIdx = 0; currentIdx < n; ++currentIdx) {
    int greaterAfter = 0;
    // Count how many elements after current index are greater than current element
    for (int nextIdx = currentIdx + 1; nextIdx < n; ++nextIdx) {
      if (permutation[nextIdx] > permutation[currentIdx]) {
        greaterAfter++;
      }
    }
    // Compute the equivalent mirror operations for this element
    int mirrorOperations = (n - permutation[currentIdx]) - greaterAfter;
    // Choose the minimum between staying and mirroring to minimize inversions
    totalOperations += min(greaterAfter, mirrorOperations);
  }
  return totalOperations;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int testCases;
  cin >> testCases;
  while (testCases--) {
    int n;
    cin >> n;
    vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
      cin >> permutation[i];
    }
    ll result = solveTestCase(n, permutation);
    cout << result << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/