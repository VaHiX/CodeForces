// Problem: CF 1106 C - Lunar New Year and Number Division
// https://codeforces.com/contest/1106/problem/C

/*
C. Lunar New Year and Number Division
Problem Description:
Given n positive integers (n is even), divide them into n/2 groups of 2 numbers each, such that the sum of squares of group sums is minimized.

Algorithm:
- Sort the array.
- Pair smallest with largest elements to minimize the sum of squares.
  This is based on the fact that for a fixed total sum, the square of the sum is minimized when the two parts are as close as possible.
  Hence pairing a[i] with a[n-1-i] minimizes the contribution to the final answer.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(1) excluding input storage.

Input:
The first line contains an even integer n (2 ≤ n ≤ 3·10^5).
The second line contains n integers a_1, ..., a_n (1 ≤ a_i ≤ 10^4).

Output:
A single integer denoting the minimum sum of squares of group sums.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]); // Read each number into the vector
  }
  sort(a.begin(), a.end()); // Sort the array to enable optimal pairing
  ll total(0);
  for (ll p = 0; 2 * p < n; p++) {
    ll sum = a[p] + a[n - 1 - p]; // Pair smallest with largest
    total += sum * sum; // Add square of current group sum to result
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/