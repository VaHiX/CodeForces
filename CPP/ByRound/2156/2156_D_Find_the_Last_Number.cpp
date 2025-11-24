// Problem: CF 2156 D - Find the Last Number
// https://codeforces.com/contest/2156/problem/D

/*
Purpose: This code solves the interactive problem of finding the last element of a hidden permutation of length n.
         It uses bitwise operations and binary search to deduce the value of the last element.

Algorithms/Techniques:
- Binary search on bits of the permutation elements.
- Bitwise AND queries to determine which bits are set in elements.
- Maintaining a list of active indices (indices that could still be valid candidates based on previous queries).

Time Complexity: O(n * log(n)) - For each bit position up to log(n), we query all active elements once.
Space Complexity: O(n) - To store the active indices vector.

*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;
using u64 = unsigned long long;

void solve(void) {
  int n;
  std::cin >> n;
  // Vector to keep track of indices that are still possibly valid
  std::vector<int> active(n - 1);
  // Initialize active with indices 1 to n-1
  std::iota(active.begin(), active.end(), 1);
  // Variable to build up the value of p_n bit by bit
  int pn = 0;
  
  // Lambda function to calculate count of numbers in range [1,n] 
  // that when divided by m and ceiling'd, gives a number >= val
  auto calc = [&](int m, int val) -> int {
    if (val == 0)
      val = m;
    if (val > n)
      return 0;
    return (n - val) / m + 1;
  };
  
  // Iterate through all possible bit positions
  for (int bit = 0; (1 << bit) <= n; bit++) {
    int m = 1 << bit;
    // If there's only one possible value for the current bit combination, we can deduce the result
    if (calc(m, pn) <= 1) {
      int r = pn % m;
      if (r == 0)
        r = m;
      std::cout << "! " << r << std::endl;
      return;
    }
    // Bit to query in this iteration
    int ask = 1 << bit;
    std::vector<int> one, zero;
    // Query the bit 'ask' on each active index
    for (auto i : active) {
      std::cout << "? " << i << ' ' << ask << std::endl;
      int b;
      std::cin >> b;
      if (b)
        one.push_back(i);
      else
        zero.push_back(i);
    }
    // Calculate how many elements should have the bit set based on current pn and ask value
    int high = m << 1;
    int val = pn | ask;
    int cnt = calc(high, val);
    int bits;
    // If 'one' size matches what we expect, then the bit is 0
    if ((int)one.size() == cnt) {
      bits = 0;
      active.swap(zero);
    } else {
      // Otherwise, the bit is 1, and we add it to pn
      bits = 1;
      pn |= ask;
      active.swap(one);
    }
  }
  // Final check for the highest bit that might not have been checked
  int m = 1 << (32 - __builtin_clz(n));
  int r = pn % m;
  if (r == 0)
    r = m;
  std::cout << "! " << r << std::endl;
}

int main(void) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/