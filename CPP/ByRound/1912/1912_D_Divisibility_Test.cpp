// Problem: CF 1912 D - Divisibility Test
// https://codeforces.com/contest/1912/problem/D

/*
Purpose:
This program finds the smallest group size k for which a divisibility test exists 
for a given base b and modulo n. It checks three types of divisibility rules:
- Kind 1: Take the last k digits (based on b^k ≡ 0 (mod n))
- Kind 2: Take a sum of groups of k digits (based on b^k ≡ 1 (mod n))
- Kind 3: Take an alternating sum of groups of k digits (based on b^k ≡ -1 (mod n))

The problem reduces to finding the smallest k such that b^k ≡ 0, 1, or -1 (mod n).
We iterate through powers of b modulo n until we find a match or detect a cycle.

Time Complexity: O(n), where n is the modulo value. In worst case, we need to compute up to n different powers.
Space Complexity: O(n), due to the boolean vector dp used to detect cycles.
*/
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
  int TC;
  cin >> TC;
  while (TC--) {
    ll b, n;
    scanf("%lld%lld", &b, &n);
    ll p = b % n; // Start with b^1 mod n
    int k = 1;
    vector<bool> dp(n); // Track visited remainders to detect cycles
    bool isYes = false;
    
    while (!dp[p]) { // Continue until we see a repeated remainder
      if (p == 0) {
        // b^k ≡ 0 (mod n), so we can test by taking last k digits
        isYes = true;
        printf("1 %d\n", k);
        break;
      }
      if (p == 1) {
        // b^k ≡ 1 (mod n), so we can test by summing groups of k digits
        isYes = true;
        printf("2 %d\n", k);
        break;
      }
      if (p == n - 1) {
        // b^k ≡ -1 (mod n), so we can test by alternating sum of groups of k digits
        isYes = true;
        printf("3 %d\n", k);
        break;
      }
      k++;
      dp[p] = true; // Mark current remainder as visited
      p = (p * b) % n; // Compute next power
    }
    if (!isYes)
      printf("0\n"); // No valid test found
  }
}


// https://github.com/VaHiX/CodeForces/