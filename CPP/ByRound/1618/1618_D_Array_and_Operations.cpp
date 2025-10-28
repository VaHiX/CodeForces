// Problem: CF 1618 D - Array and Operations
// https://codeforces.com/contest/1618/problem/D

/*
D. Array and Operations
Algorithm: Greedy with sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the vector storage

You are given an array a of n integers, and another integer k such that 2k <= n.
You have to perform exactly k operations with this array. In one operation, you have to choose two elements of the array (let them be ai and aj; they can be equal or different, but their positions in the array must not be the same), remove them from the array, and add floor(ai/aj) to your score.
Initially, your score is 0. After you perform exactly k operations, you add all the remaining elements of the array to the score.
Calculate the minimum possible score you can get.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end()); // Sort the array to facilitate greedy choice
    long long res(0);
    // Add the smallest (n - 2*k) elements directly to the result
    for (long p = 0; p < n - 2 * k; p++) {
      res += a[p];
    }
    // For the remaining k pairs, we want to minimize the contribution from floor division
    // So we pair larger elements with smaller ones to reduce floor values
    for (long p = 0; p < k; p++) {
      res += a[n - k - 1 - p] / a[n - 1 - p]; // Take largest available element and divide by the smallest of remaining
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/