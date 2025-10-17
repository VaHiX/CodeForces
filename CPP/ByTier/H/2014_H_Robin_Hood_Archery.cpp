// Problem: CF 2014 H - Robin Hood Archery
// https://codeforces.com/contest/2014/problem/H

/*
 * Problem: H. Robin Hood Archery
 * Algorithm: XOR-based prefix sum with optimal game strategy simulation
 * Time Complexity: O(n + q) per test case, where n is the number of targets and q is number of queries
 * Space Complexity: O(n + 10^6) due to prefix sums array s and lookup table v
 *
 * This solution uses a technique similar to the "game theory" approach with XOR operations,
 * leveraging that in optimal play, if the XOR of all elements in the subarray is zero,
 * then the first player cannot win (i.e., the second player can force a tie or win).
 * For each query [l,r], we compute prefix XORs and compare s[r] with s[l-1].
 *
 * Key idea:
 * - If XOR of elements from l to r equals 0, it means that either:
 *   1) The first player cannot force a win (Sheriff can avoid losing),
 *   2) Or the game will end in a tie.
 *   We are asked whether Sheriff "does not lose", so even a tie counts as "YES".
 * - This problem is modeled such that if the XOR of any segment is 0,
 *   it implies fair play scenario where second player can mirror moves to tie or win,
 *   making Sheriff's loss impossible.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>

using namespace std;
const int N = 2e5 + 5;
int T, n, m;
unsigned long long s[N], v[1000005]; // v[] stores random values for hashing
signed main() {
  ios::sync_with_stdio(0); // Speed up I/O operations
  cin.tie(0);
  mt19937 rnd(time(0)); // Initialize random number generator
  srand(time(0));       // Seed for rand()
  cin >> T;             // Read number of test cases
  for (int i = 0; i <= 1000000; i++)
    v[i] = rnd();       // Fill v[] with random values to prevent collisions in hashing

  while (T--) {
    cin >> n >> m;      // Read number of targets and queries
    for (int i = 1, x; i <= n; i++) {
      cin >> x;
      s[i] = s[i - 1] ^ v[x]; // Build prefix XOR using v[x]
    }
    for (int l, r, i = 1; i <= m; i++) {
      cin >> l >> r;
      if (s[r] == s[l - 1]) // If the XOR of the range is zero
        puts("YES");        // Then Sheriff does not lose (can avoid losing)
      else
        puts("NO");         // Otherwise, he might lose
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/