/**
 * Problem: CF2131G - Wafu_
 *
 * This program solves a problem involving selecting and processing numbers to
 * maximize a certain value under given constraints. The solution uses dynamic
 * programming and bitmask techniques to efficiently compute the result.
 *
 * Approach:
 * 1. Precompute a DP array where dp[i] represents the product of factorials up
 * to i
 * 2. For each test case, sort the input array and process numbers in ascending
 * order
 * 3. For each number, either include it in the selection (if it fits within the
 * bitmask) or use the remaining bits to maximize the result
 *
 * Time Complexity: O(T * n * 30) where T is the number of test cases and n is
 * the array size Space Complexity: O(n + 30) for the input array and DP table
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int MAX_N = 200500;
const int MOD = 1'000'000'007;
const int MAX_BITS = 30; // Since we're dealing with 2^30

// dp[i] = i! (factorial of i) mod MOD
ll factorial_dp[MAX_BITS + 1];
int numbers[MAX_N];

/**
 * Precompute factorials up to 30 modulo MOD
 */
void precompute_factorials() {
  factorial_dp[0] = 1; // 0! = 1
  for (int i = 1; i <= MAX_BITS; i++) {
    factorial_dp[i] = i * factorial_dp[i - 1] % MOD;
  }
}

/**
 * Solves a single test case
 * @param n: Number of elements in the array
 * @param k: Maximum number of bits that can be set
 * @return: The computed result modulo MOD
 */
ll solve(int n, int k) {
  // Sort the array in ascending order
  sort(numbers + 1, numbers + n + 1);

  ll result = 1;

  for (int i = 1; i <= n; i++) {
    int current = numbers[i];

    // If the current number is too large or requires more bits than available
    if (current > MAX_BITS || (1LL << (current - 1)) > k) {
      if (k > 0) {
        // Use the current number and process remaining bits
        result = result * current % MOD;
        k--;

        // Use remaining bits to multiply by factorials
        for (int bit = 1; bit <= MAX_BITS; bit++) {
          if (k & (1LL << (bit - 1))) {
            result = result * factorial_dp[bit] % MOD;
          }
        }
      }
      break;
    } else {
      // Use the current number's bits
      k -= (1LL << (current - 1));
      result = result * factorial_dp[current] % MOD;
    }
  }

  return result;
}

int main() {
  // Optimize I/O operations
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // Precompute factorials
  precompute_factorials();

  int test_cases;
  cin >> test_cases;

  while (test_cases--) {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
      cin >> numbers[i];
    }

    cout << solve(n, k) << '\n';
  }

  return 0;
}
return 0;
}