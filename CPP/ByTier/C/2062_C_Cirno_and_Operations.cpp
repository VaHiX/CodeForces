// Problem: CF 2062 C - Cirno and Operations
// https://codeforces.com/contest/2062/problem/C

/*
C. Cirno and Operations
Problem Description:
Given a sequence of integers, we can perform two operations any number of times (until length becomes 1):
1. Reverse the sequence.
2. Replace the sequence with its difference sequence (each element becomes difference of consecutive elements).

Goal: Find the maximum possible sum of all elements in the sequence after all operations.

Algorithm:
- For each test case, repeatedly compute the difference sequence and track the maximum sum encountered.
- The process continues until there's only one element left.
- At each step, we compute the difference sequence by subtracting adjacent elements,
  then we take the absolute value of total sum (for tracking), and keep updating max sum.

Time Complexity: O(n^2) per test case
Space Complexity: O(n)

Note: The algorithm simulates all possible operations for a given sequence to find the maximum sum.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n);
    ll mx(0);  // Initialize max sum as 0
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
      mx += v[p];  // Initially, sum of all elements
    }
    while (v.size() > 1) {
      ll total(0);  // Total absolute sum at current step
      for (ll p = 1; p < v.size(); p++) {
        v[p - 1] = v[p] - v[p - 1];  // Compute difference sequence
        total += v[p - 1];  // Accumulate the sum of differences
      }
      total = (total > 0 ? total : -total);  // Make it positive (absolute value)
      mx = (mx > total ? mx : total);  // Update maximum
      v.pop_back();  // Remove last element to reduce size
    }
    printf("%lld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/