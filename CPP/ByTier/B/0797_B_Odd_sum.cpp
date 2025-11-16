// Problem: CF 797 B - Odd sum
// https://codeforces.com/contest/797/problem/B

/*
Code Purpose:
This program finds the maximum sum of a subsequence from a given array such that the sum is odd.
The approach is to include all positive numbers to maximize the sum, and then adjust by removing
the smallest odd positive number or the largest odd negative number, depending on whether the 
initial sum is even or odd.

Algorithms/Techniques:
Greedy approach with careful handling of odd and even numbers to ensure final sum is odd.

Time Complexity: O(n) - Single pass through the array
Space Complexity: O(1) - Only using a few variables regardless of input size
*/

#include <algorithm>
#include <cstdio>
#include <cstdlib>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 100010
#define inf 100000000
#define pi 2 * acos(0.0)
#define pp pair<string, int>
using namespace std;
int main() {
  int i, j, k;
  int n, t;
  scanf("%d", &n);
  int *a = new int[n];
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);
  int sum = 0;
  int mn = -inf, mp = inf;
  for (i = 0; i < n; i++) {
    if (a[i] > 0) {
      sum += a[i];
      if (a[i] % 2)
        mp = min(mp, a[i]);  // Track smallest positive odd number
    } else if (a[i] < 0) {
      if (a[i] % 2)
        mn = max(mn, a[i]);  // Track largest negative odd number
    }
  }
  if (sum % 2 == 0) {
    mn = abs(mn);
    sum -= min(mn, mp);  // Remove the smaller of the two odd numbers to make sum odd
  }
  printf("%d\n", sum);
  return 0;
}


// https://github.com/VaHiX/CodeForces/