// Problem: CF 1877 F - Lexichromatography
// https://codeforces.com/contest/1877/problem/F

/*
Code Purpose:
This code solves the problem of counting valid colorings of an array such that:
1. The blue subsequence is lexicographically smaller than the red subsequence.
2. No subarray is imbalanced (the absolute difference between blue and red counts of any value is less than 2).

The solution uses Union-Find (Disjoint Set Union) to identify connected components of values.
It calculates the number of valid colorings using inclusion-exclusion principle and modular arithmetic.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) to group connected values
- Modular exponentiation for fast computation
- Inclusion-exclusion principle to count valid colorings
- Unique value processing and sorting

Time Complexity: O(n log n)
Space Complexity: O(n)
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
typedef long long ll;
const long long MOD = 998244353;
int a[200010], fa[200010], used[200010], color[200010], flag[200010];
ll two[200010];

// Find root with path compression
int get(int x) {
  if (fa[x] == x) {
    return x;
  }
  return fa[x] = get(fa[x]); // Path compression
}

// Modular exponentiation: compute x^k mod MOD
ll calc(ll x, ll k) {
  ll s = 1;
  if (k == 0)
    return 0ll;
  while (k) {
    if (k & 1) {
      s = s * x % MOD; // If k is odd, multiply result by x
    }
    x = x * x % MOD; // Square x
    k >>= 1; // Divide k by 2
  }
  return s % MOD;
}

int main() {
  int n, f = 1, c = 0;
  scanf("%d", &n);
  two[0] = 1;
  for (int i = 1; i <= n; i++) {
    two[i] = two[i - 1] * 2 % MOD; // Precompute powers of 2
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    if (!color[a[i]]) {
      color[a[i]] = 1; // Mark that we've seen this value
      c++; // Count unique values
    }
  }
  for (int i = 1; i <= 200000; i++) {
    fa[i] = i; // Initialize Union-Find
  }
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (used[a[i]] == 1) {
      // If already used, check if it's the front of queue
      if (q.front() == a[i]) {
        q.pop();
        used[a[i]] = 0;
      } else {
        f = 0; // Invalid sequence
        break;
      }
    } else {
      used[a[i]] = 1; // Mark as used
      q.push(a[i]); // Push to queue
      fa[get(a[i])] = get(q.front()); // Union current value with front of queue
    }
  }
  if (!q.empty()) {
    f = 0; // Invalid if queue is not empty at end
  }
  ll s = 0;
  sort(a + 1, a + 1 + n); // Sort array to process unique values
  int len = unique(a + 1, a + 1 + n) - 1 - a; // Get number of unique elements
  for (int i = 1; i <= len; i++) {
    if (fa[a[i]] == a[i]) {
      s++; // Count root nodes (connected components)
    }
  }
  if (f == 0)
    s = 0; // If invalid, set s to 0
  // Compute result using inclusion-exclusion and modular inverse
  cout << (calc(2, c) - calc(2, s) + MOD) % MOD * calc(2, MOD - 2) % MOD
       << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/