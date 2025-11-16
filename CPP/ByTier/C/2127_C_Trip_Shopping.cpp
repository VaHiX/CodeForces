// Problem: CF 2127 C - Trip Shopping
// https://codeforces.com/contest/2127/problem/C

/*
C. Trip Shopping

Purpose:
This code solves a game between Ali and Bahamin where they play optimally to either minimize or maximize the sum of absolute differences between arrays a and b after k rounds of rearrangement.

Algorithms/Techniques:
- Greedy approach based on optimal selection and rearrangement
- Sorting to optimize arrangement strategy in each round
- Minimax reasoning for optimal play

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the arrays

*/

#include <stdio.h>
#include <algorithm>
#include <array>
#include <utility>

#define ll long long
using namespace std;
const int N = 2e5 + 10;
int n;
array<int, 2> a[N]; // Stores pairs of (a[i], b[i]) for each index i

void solve() {
  scanf("%d%*d", &n); // Read n and ignore k (not used in algorithm)
  
  // Read elements of array a
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i][0]);
    
  // Read elements of array b
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i][1]);
    
  // Ensure a[i][0] <= a[i][1] to simplify processing
  for (int i = 1; i <= n; i++)
    if (a[i][0] > a[i][1])
      swap(a[i][0], a[i][1]);
      
  // Sort the pairs based on first element
  sort(a + 1, a + n + 1);
  
  // Calculate base sum of differences between pairs (after ensuring order)
  ll s = 0;
  for (int i = 1; i <= n; i++)
    s += a[i][1] - a[i][0];
    
  // Find minimum "overlap" or "gap" that Bahamin can create by rearranging
  int delta = 1e9;
  for (int i = 1; i < n; i++)
    delta = min(delta, max(0, a[i + 1][0] - a[i][1]));
    
  // Add twice the minimal gap to maximize the final value
  s += 2 * delta;
  
  printf("%lld\n", s);
}

int main() {
  int Ncase;
  scanf("%d", &Ncase);
  while (Ncase--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/