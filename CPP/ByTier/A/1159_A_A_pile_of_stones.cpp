// Problem: CF 1159 A - A pile of stones
// https://codeforces.com/contest/1159/problem/A

/*
 * Problem: A pile of stones
 * Algorithm: Prefix sum with minimum tracking
 * Time Complexity: O(n), where n is the length of string s
 * Space Complexity: O(1), only using a few variables
 *
 * The problem simulates operations on a pile of stones.
 * We track the cumulative effect of operations (+'s increase, -'s decrease).
 * The minimum value reached during these operations determines how many
 * stones we must start with to never go below zero.
 * The result is total change minus the minimum prefix sum.
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;              // Read number of operations
  std::string s;
  std::cin >> s;              // Read the sequence of operations
  long cnt(0), mn(0);         // cnt: current count, mn: minimum prefix sum
  for (long p = 0; p < s.size(); p++) {
    cnt += (s[p] == '+') - (s[p] == '-');  // Update count: +1 for '+', -1 for '-'
    mn = (mn < cnt) ? mn : cnt;            // Track minimum prefix sum
  }
  printf("%ld\n", cnt - mn);  // Minimum stones needed = final count - min prefix
  return 0;
}


// https://github.com/VaHiX/codeForces/