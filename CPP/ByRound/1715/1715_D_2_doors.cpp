// Problem: CF 1715 D - 2+ doors
// https://codeforces.com/contest/1715/problem/D

/*
Purpose: 
  This code finds the lexicographically smallest array 'a' that satisfies all given bitwise OR constraints between pairs of elements.
  Each constraint is of the form a[i] | a[j] = x.

Algorithms/Techniques:
  - Graph representation of constraints
  - Bitwise operations to determine values
  - Greedy assignment to minimize lexicographical value
  - Iterative refinement using adjacency list

Time Complexity: O(n + q * 30) where 30 is the number of bits (up to 30 bits for integers)
Space Complexity: O(n + q) for storing adjacency list and array elements

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int main() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n, -1); // Initialize array with -1, which will later be set properly
  vector<vector<pair<int, int>>> g(n); // Graph to store constraints: adjacency list of pairs (neighbor, xor_value)
  for (int i = 0; i < q; i++) {
    int j, k, x;
    scanf("%d%d%d", &j, &k, &x);
    j--;
    k--;
    a[j] &= x; // Set bits that must be 0 in a[j] based on the constraint
    a[k] &= x; // Set bits that must be 0 in a[k] based on the constraint
    g[j].push_back({k, x}); // Add constraint to graph
    g[k].push_back({j, x}); // Add constraint to graph
  }
  for (int i = 0; i < n; i++) {
    int x = a[i]; // Start with current value of a[i]
    for (auto [j, k] : g[i])
      x &= i == j ? 0 : a[j]; // Compute intersection of all adjacent bits that are known
    printf("%d ", a[i] ^= a[i] & x); // Apply correction to minimize lexicographically
  }
}


// https://github.com/VaHiX/CodeForces/