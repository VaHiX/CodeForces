// Problem: CF 2000 D - Right Left Wrong
// https://codeforces.com/contest/2000/problem/D

/* 
 * Problem: D. Right Left Wrong
 * Purpose: Maximize points by selecting pairs of 'L' and 'R' segments,
 *          where each selected segment contributes the sum of values between indices.
 * Algorithm:
 *   - Use prefix sums to quickly calculate subarray sums.
 *   - Greedily select non-overlapping L-R pairs from left to right.
 *   - Two pointers approach: move left pointer forward until 'L', 
 *     and right pointer backward until 'R'.
 * Time Complexity: O(n) amortized per test case.
 * Space Complexity: O(n) for the prefix sum array.
 */
#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<ll> a(n + 2, 0); // Prefix sum array, padded with 0s at both ends
    for (long p = 1; p <= n; p++) {
      std::cin >> a[p];
      a[p] += a[p - 1]; // Build prefix sum
    }
    std::string s;
    std::cin >> s;
    s = 'R' + s + 'L'; // Add sentinel characters to simplify edge case handling
    long left(0), right(n + 1); // Pointers to track current L and R positions
    ll total(0);
    do {
      ++left;
      while (s[left] != 'L') { // Move left pointer to next 'L'
        ++left;
      }
      --right;
      while (s[right] != 'R') { // Move right pointer to next 'R'
        --right;
      }
      if (left < right) {
        total += a[right] - a[left - 1]; // Add sum of subarray [left, right]
      } else {
        break;
      }
    } while (left < right);
    std::cout << total << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/