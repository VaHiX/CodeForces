// Problem: CF 520 C - DNA Alignment
// https://codeforces.com/contest/520/problem/C

/*
 * Code Purpose:
 * This program calculates the number of DNA strings t of length n such that the Vasya distance
 * ρ(s, t) from a given string s attains its maximum possible value.
 *
 * The Vasya distance ρ(s, t) is defined as the sum of function h(s, t_i) over all cyclic shifts t_i of t,
 * where h(s, t_i) counts the number of matching characters at each position.
 *
 * Algorithm:
 * - For a string s of length n, we count how many times each nucleotide ('A', 'C', 'G', 'T') appears.
 * - We sort these counts in descending order.
 * - We determine how many nucleotides have the maximum count (v[0]).
 * - The maximum number of matching alignments happens when t has all characters equal to the most frequent character in s.
 * - The result is u^n mod (10^9 + 7), where u is the count of characters that can be used to maximize h(s, t_i).
 *
 * Time Complexity: O(n log n) due to sorting of counts, where n is the length of input string.
 * Space Complexity: O(1) since we use a fixed-size vector of size 4 and a few variables.
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
  const int64_t MOD = 1000000007;
  const int N = 4;
  int64_t len(0);
  std::cin >> len;
  std::string s;
  std::cin >> s;
  std::vector<int64_t> v(4);
  for (int64_t p = 0; p < s.size(); p++) {
    if (s[p] == 'A') {
      ++v[0];
    } else if (s[p] == 'C') {
      ++v[1];
    } else if (s[p] == 'G') {
      ++v[2];
    } else if (s[p] == 'T') {
      ++v[3];
    }
  }
  sort(v.rbegin(), v.rend());
  int64_t u = 1;
  for (long p = 1; p < v.size(); p++) {
    u += (v[p] == v[0]); // Count how many characters have the maximum frequency
  }
  int64_t total(1);
  for (int64_t p = 0; p < s.size(); p++) {
    total *= u;
    total %= MOD;
  }
  std::cout << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/