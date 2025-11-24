// Problem: CF 509 E - Pretty Song
// https://codeforces.com/contest/509/problem/E

/*
 * Problem: E. Pretty Song
 * 
 * Purpose:
 *   Calculates the "prettiness" of a song title, defined as the sum of
 *   "simple prettiness" over all substrings. Simple prettiness is the
 *   ratio of vowels to total letters in a substring.
 * 
 * Approach:
 *   - Uses prefix sums to efficiently compute the number of vowels in any substring.
 *   - For each substring length l, we calculate how many vowels it contributes to
 *     the total sum using prefix sums.
 *   - The key insight is that for each length l, we can compute the sum of vowel counts
 *     for all substrings of that length using a sliding window technique with prefix sums.
 * 
 * Time Complexity: O(n), where n is the length of the string.
 * Space Complexity: O(n), due to the prefix sum array.
 * 
 * Algorithms/Techniques:
 *   - Prefix Sum
 *   - Sliding Window
 */

#include <stdint.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const string VW = "IEAOUY";
bool is_vw[256];
signed main() {
  // Mark vowels in the is_vw array for O(1) lookup
  for (int i = 0; i < VW.size(); ++i) {
    is_vw[VW[i]] = true;
  }
  ios::sync_with_stdio(false);
  string S;
  cin >> S;
  // Build prefix sum array for vowels
  vector<int> pvw(S.size() + 1);
  for (int i = 0; i < S.size(); ++i) {
    pvw[i + 1] = pvw[i] + is_vw[S[i]];  // Cumulative count of vowels
  }
  double ans = 0;
  int64_t sum = 0;
  // Iterate through all possible substring lengths
  for (int l = 1; l <= S.size(); ++l) {
    // Update sum with new substrings ending at current position
    sum += pvw[S.size() - l + 1] - pvw[l - 1];
    // Add contribution of substrings of length l to final answer
    ans += 1.0 * sum / l;
  }
  cout << fixed << setprecision(9) << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/