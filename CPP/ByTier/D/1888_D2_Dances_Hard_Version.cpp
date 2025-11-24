// Problem: CF 1888 D2 - Dances (Hard Version)
// https://codeforces.com/contest/1888/problem/D2

/*
Purpose: This code solves a problem where we have two arrays a and b, and we need to find the minimum number of operations to make a[i] < b[i] for all valid i, after reordering elements in each array optimally. The problem is extended to compute the sum over m pairs of arrays where the first element of the first array varies from 1 to m.

Algorithms/Techniques: 
- Binary search on the answer to determine maximum number of pairs (a[i], b[i]) that can be made valid.
- Sorting both arrays to allow greedy matching.
- Mathematical calculation to compute total operations for all m pairs.

Time Complexity: O(n * log n) per test case due to sorting and binary search.
Space Complexity: O(n) for storing arrays a and b.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
#define M 200200
int n;
int m;
int a[M];
int b[M];
int c[M];

// Function to check if 'x' pairs can be made valid
bool okay(int x) {
  for (int i = 2; i <= x + 1; i++) {
    if (a[i] >= b[n - x - 1 + i])
      return 0;
  }
  return 1;
}

void solve() {
  scanf("%d", &n);
  scanf("%d", &m);
  a[1] = 1; // First element of array 'c' is always 1
  for (int i = 2; i <= n; i++)
    scanf("%d", a + i);
  sort(a + 1, a + n + 1); // Sort array 'a'
  for (int i = 1; i <= n; i++)
    scanf("%d", b + i);
  sort(b + 1, b + n + 1); // Sort array 'b'
  
  int mn = 0, mx = n; // Binary search boundaries
  while (mn < mx - 1) {
    int md = (mn + mx) / 2;
    if (okay(md)) {
      mn = md; // If valid, try higher
    } else {
      mx = md; // If invalid, try lower
    }
  }
  
  int i;
  // Find how many elements satisfy the condition from the sorted arrays
  for (i = 2; i <= mn + 1; i++) {
    if (a[i] < b[n - mn + i - 2])
      continue;
    break;
  }
  
  int j = b[n - mn + i - 2] - 1; // Calculate the value of j
  j = min(j, m); // Clamp j to m
  ll answer = 1ll * n * m - 1ll * m * mn - j; // Final computation
  printf("%I64d\n", answer);
}

int main() {
  int T;
  for (scanf("%d", &T); T--;) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/