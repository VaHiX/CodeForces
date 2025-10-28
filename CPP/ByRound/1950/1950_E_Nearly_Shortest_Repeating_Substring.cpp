// Problem: CF 1950 E - Nearly Shortest Repeating Substring
// https://codeforces.com/contest/1950/problem/E

/*
Algorithm: Z-algorithm based approach to find the shortest repeating substring
Purpose: Given a string s, find the minimal length of a substring k such that
         concatenating k multiple times results in a string differing in at most one position from s.

Time Complexity: O(n * sqrt(n)) where n is the length of the string.
Space Complexity: O(n) for storing Z-array and factors.

Techniques:
- Z-algorithm for pattern matching
- Factorization of string length to check possible periods
- Two passes (forward and backward Z arrays) to determine mismatches
*/

#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <vector>

#define vec vector
#define pr pair
#define fr first
#define sc second
#define llu unsigned long long
#define lld long long
#define all(n) begin(n), end(n)
using namespace std;
char bf[200002];
llu z[200003], zz[200003];

// Compute Z-array for the string
void zf(llu n) {
  llu l = 0, r = 0;
  z[0] = 0;
  for (llu i = 1; i < n; i++) {
    z[i] = 0;
    if (i < r)
      z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && bf[z[i]] == bf[i + z[i]])
      z[i]++;
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
}

// Compute reverse Z-array for suffix matching
void zff(llu n) {
  llu l = 0, r = 0;
  zz[0] = 0;
  for (llu i = 1; i < n; i++) {
    zz[i] = 0;
    if (i < r)
      zz[i] = min(r - i, zz[i - l]);
    while (i + zz[i] < n && bf[n - zz[i] - 1] == bf[n - i - zz[i] - 1])
      zz[i]++;
    if (i + zz[i] > r) {
      l = i;
      r = i + zz[i];
    }
  }
}

// Solve function to find the shortest valid repeating substring
llu solv(llu n) {
  vec<llu> f0, f1;
  for (llu i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      f0.push_back(i);
      f1.push_back(n / i);
    }
  }
  reverse(all(f1));
  f1.pop_back(); // Remove the last element to avoid double counting `n`
  zf(n);
  zff(n);
  llu errc;
  // Check divisors from small to large
  for (auto i : f0) {
    errc = 0;
    // Forward direction: check for mismatches
    for (llu k = i; k < n && errc < 2; k += i) {
      if (z[k] >= i)
        continue;
      ++errc;
      for (llu j = z[k] + 1; j < i; ++j)
        errc += bf[j] != bf[k + j];
    }
    if (errc < 2)
      return i;
    errc = 0;
    // Backward direction: check suffix mismatches
    for (llu k = i; k < n && errc < 2; k += i) {
      if (zz[k] >= i)
        continue;
      ++errc;
      for (llu j = zz[k] + 1; j < i; ++j)
        errc += bf[n - 1 - j] != bf[n - 1 - k - j];
    }
    if (errc < 2)
      return i;
  }
  // Check remaining divisors in reverse order
  for (auto i : f1) {
    errc = 0;
    // Forward direction
    for (llu k = i; k < n && errc < 2; k += i) {
      if (z[k] >= i)
        continue;
      ++errc;
      for (llu j = z[k] + 1; j < i; ++j)
        errc += bf[j] != bf[k + j];
    }
    if (errc < 2)
      return i;
    errc = 0;
    // Backward direction
    for (llu k = i; k < n && errc < 2; k += i) {
      if (zz[k] >= i)
        continue;
      ++errc;
      for (llu j = zz[k] + 1; j < i; ++j)
        errc += bf[n - 1 - j] != bf[n - 1 - k - j];
    }
    if (errc < 2)
      return i;
  }
  return n; // No smaller pattern found; return full string
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    llu n;
    scanf("%llu", &n);
    scanf("%s", bf);
    printf("%llu\n", solv(n));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/