// Problem: CF 1907 E - Good Triples
// https://codeforces.com/contest/1907/problem/E

/*
 * Problem: E. Good Triples
 * 
 * Purpose: Given a non-negative integer n, count the number of good triples (a, b, c)
 *          such that a + b + c = n and digit_sum(a) + digit_sum(b) + digit_sum(c) = digit_sum(n).
 * 
 * Algorithm: 
 * - Use digit DP (Dynamic Programming) with precomputed transitions.
 * - Precompute for all digit sums from 0 to 9, how many ways we can split a digit into three parts
 *   such that their sum equals the digit sum. This is stored in the `num` array.
 * - For each test case:
 *   - Parse the digits of the number n.
 *   - For each digit, multiply the result by the precomputed value from `num`.
 * 
 * Time Complexity: O(1) per test case after preprocessing (O(10^3) for precomputation)
 * Space Complexity: O(1) (fixed size arrays of size 10)
 * 
 * Techniques:
 * - Digit DP
 * - Precomputation
 * - Modular arithmetic (implicit in this approach)
 */

#include <iostream>
#include <string>

using namespace std;
typedef long long ll;
const int N = 20;
ll num[N];

void slove() {
  string t;
  cin >> t;
  ll ans = 1;
  for (int i = 0; i < t.size(); i++) {
    int x = t[i] - '0';  // Convert char digit to int
    ans *= num[x];       // Multiply result by precomputed number of valid combinations for this digit
  }
  cout << ans << '\n';
}

void init() {
  // Precompute the number of valid ways to split each digit sum into three parts (0-9)
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int z = 0; z <= 9; z++) {
        if (i + j + z <= 9) {
          num[i + j + z]++; // Increment count for the sum of digits
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  
  init(); // Precompute results
  int t = 1;
  cin >> t;
  while (t--)
    slove();
  return 0;
}


// https://github.com/VaHiX/CodeForces/