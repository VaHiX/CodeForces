// Problem: CF 2003 E1 - Turtle and Inversions (Easy Version)
// https://codeforces.com/contest/2003/problem/E1

/*
Code Purpose:
This code solves the problem of finding the maximum number of inversions in an interesting permutation.
An interesting permutation satisfies certain conditions based on given intervals. The core idea is to 
compute the maximum inversions by subtracting the overlapping interval lengths from the total number of inversions.

Algorithms/Techniques:
- Greedy approach to maximize inversions by placing larger elements before smaller ones.
- Sorting intervals and using two pointers to find optimal overlap reduction.

Time Complexity: O(m * log(m)) due to sorting intervals.
Space Complexity: O(m) for storing the intervals.

*/
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int m, n;
    cin >> n >> m;
    pair<int, int> pr[m];
    for (int i = 0; i < m; i++) {
      cin >> pr[i].first >> pr[i].second;
    }
    // Precompute total number of inversions possible in a permutation of size n
    long long int sum = 1LL * n * (n - 1) / 2;
    
    // Sort intervals by their starting point
    sort(pr, pr + m);
    
    // Two pointers approach to reduce overlaps
    for (int i = 0, j = m - 1; i <= j; i++, j--) {
      // Subtract the length of overlapping intervals from total inversions
      sum = sum - (pr[j].second - pr[i].first);
    }
    cout << sum << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/