// Problem: CF 1651 A - Playoff
// https://codeforces.com/contest/1651/problem/A

#include <cstdio>
typedef long long ll;

/*
 * Problem: Playoff Tournament Winner
 * 
 * Description:
 * A tournament is held with 2^n athletes numbered from 1 to 2^n.
 * The tournament proceeds in n stages where athletes are paired up
 * and compete according to specific rules based on the sum of their indices.
 * 
 * Algorithm:
 * For each stage, we simulate the pairing process and determine winners
 * using the given rules. We start with a list of athletes and iteratively
 * eliminate one by one until only one remains.
 * 
 * Key Observations:
 * The tournament structure is like a binary tree where leaves are original athletes,
 * and internal nodes represent matches. Each match result depends on the sum of
 * indices involved (odd -> lower index wins, even -> higher index wins).
 * 
 * Time Complexity: O(2^n) per test case due to the simulation of all matches.
 * Space Complexity: O(1) - only using constant extra space regardless of input size.
 */

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll res(1); // Initialize result as 1
    while (n--) {
      res *= 2; // Double the number of athletes in each stage
    }
    printf("%lld\n", res - 1); // Output the winner index (which is always 2^n - 1)
  }
}

// https://github.com/VaHiX/codeForces/