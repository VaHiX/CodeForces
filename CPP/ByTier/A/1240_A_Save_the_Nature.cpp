// Problem: CF 1240 A - Save the Nature
// https://codeforces.com/contest/1240/problem/A

/*
Problem: A. Save the Nature
Algorithms/Techniques: Binary search on answer, Greedy sorting, Inclusion-Exclusion principle

Time Complexity: O(n * log(n) + log(max_p * n) * n)
Space Complexity: O(n)

The problem asks to find the minimum number of tickets to sell in order to achieve at least K contribution,
by choosing the optimal order of selling tickets.
We use binary search on the answer (number of tickets to sell).
For a given number of tickets m, we compute the maximum possible contribution
by placing the largest prices in those positions that give higher contribution.
We handle overlapping intervals using inclusion-exclusion principle.
*/

#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;
#define N 200200
int n, p[N], a, x, b, y;
long long K, d;
bool check(int m) {
  int i = m / d, j = m / a - i, k = m / b - i; // i: both programs, j: only x%, k: only y%
  assert(i + j + k <= n);
  long long rlt = 0;
  for (int q = 0; q < i; q++) // contribution from positions covered by both programs
    rlt += p[q] * (x + y); 
  for (int q = 0; q < j; q++) // contribution from positions covered only by x%
    rlt += p[i + q] * x;
  for (int q = 0; q < k; q++) // contribution from positions covered only by y%
    rlt += p[i + j + q] * y;
  return rlt >= K; // Check if we meet the required contribution
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", &p[i]), p[i] /= 100; // Divide by 100 to simplify calculations
    sort(p, p + n, greater<int>()); // Sort in descending order to maximize contribution
    scanf("%d %d %d %d %I64d", &x, &a, &y, &b, &K);
    if (x < y) // Ensure that x >= y for easier logic handling
      swap(x, y), swap(a, b);
    d = 1ll * a * b / __gcd(a, b); // LCM of a and b
    if (!check(n)) // If even all tickets don't meet the contribution, impossible
      puts("-1");
    else {
      int le = 0, ri = n;
      while (le < ri - 1) { // Binary search for minimum valid number of tickets
        int mi = le + ri >> 1; // Midpoint calculation
        if (check(mi))
          ri = mi; // Try smaller value
        else
          le = mi; // Try larger value
      }
      printf("%d\n", ri);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/