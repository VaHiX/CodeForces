// Problem: CF 910 C - Minimum Sum
// https://codeforces.com/contest/910/problem/C

/*
 * Problem: Minimum Sum
 * 
 * Algorithm/Technique: Greedy approach with digit mapping
 * 
 * Time Complexity: O(n * L + 10 * log(10)) where n is number of strings and L is average string length.
 * Space Complexity: O(1) since we use fixed size arrays (10 elements)
 * 
 * Approach:
 * 1. For each input string, we calculate the contribution of each character
 *    to the total value based on its position (units, tens, hundreds, etc.).
 * 2. We store these contributions in a vector of pairs (contribution, character).
 * 3. Sort the characters by their contribution in ascending order.
 * 4. Assign digits greedily, minimizing the total sum:
 *    - Assign 0 to the character with the lowest contribution that is not a leading digit
 *    - Assign 1 to the next lowest, etc.
 * 5. Compute the final sum by multiplying each contribution with its assigned digit.
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  const int N = 10;
  long n;
  std::cin >> n;
  std::vector<std::pair<long, char>> w(N);
  for (int p = 0; p < N; p++) {
    w[p].second = 'a' + p;
  }
  std::vector<bool> nozero(N, 0);
  for (long p = 0; p < n; p++) {
    std::string s;
    std::cin >> s;
    nozero[s[0] - 'a'] = true;  // Mark first character as not allowed to be zero (no leading zero)
    for (long u = s.size() - 1, mult = 1; u >= 0; u--, mult *= 10) {
      w[s[u] - 'a'].first += mult;  // Accumulate multiplier for each digit position
    }
  }
  sort(w.begin(), w.end());  // Sort characters by their accumulated contribution
  bool pendingZero(true);
  std::vector<int> mv(N, 0);
  for (int p = N - 1; p >= 0; p--) {
    if (pendingZero && !nozero[w[p].second - 'a']) {
      mv[p] = 0;
      pendingZero = false;
    } else {
      mv[p] = N - 1 - p + pendingZero;
    }
  }
  long sum(0);
  for (int p = 0; p < N; p++) {
    sum += w[p].first * mv[p];
  }
  std::cout << sum << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/