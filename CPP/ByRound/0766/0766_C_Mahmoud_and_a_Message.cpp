// Problem: CF 766 C - Mahmoud and a Message
// https://codeforces.com/contest/766/problem/C

/*
C. Mahmoud and a Message
Algorithm: Dynamic Programming with constraints on substring lengths based on character limits.
Time Complexity: O(n^2)
Space Complexity: O(n)

The problem involves splitting a string into substrings such that each substring's length is within the limit for its constituent characters.
We use dynamic programming:
- ways[p]: number of ways to split first p characters
- minNumber[p]: minimum number of substrings needed for first p characters
- For each position, we look back and check valid splits based on character limits.
*/

#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
int main() {
  const int N = 26;
  const ll MOD = 1000000007;
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<int> a(N);
  for (int p = 0; p < N; p++) {
    std::cin >> a[p];
  }
  std::vector<int> minNumber(n + 1, 0);        // min number of substrings up to index i
  std::vector<ll> ways(n + 1, 0);             // number of ways to split up to index i
  ways[0] = 1;                                // base case: one way to split empty string
  int maxLength(0);                           // maximum length of any valid substring used

  for (int p = 1; p <= n; p++) {
    int allowed(n + 1);                      // max allowed length for current substring ending at p
    minNumber[p] = n + 1;                    // initialize to impossible value
    for (int q = p - 1; q >= 0; q--) {       // iterate over all possible start points
      long length = p - q;
      allowed = (allowed < a[s[q] - 'a']) ? allowed : a[s[q] - 'a'];  // update allowed length based on character
      if (length > allowed) {
        break;                               // if length exceeds allowed, no valid split
      }
      ways[p] += ways[q];                    // accumulate number of ways
      ways[p] %= MOD;
      minNumber[p] = (minNumber[p] < minNumber[q] + 1) ? minNumber[p] : (minNumber[q] + 1);  // update minimum substrings
      maxLength = (maxLength > length) ? maxLength : length;     // track maximum substring length
    }
  }
  std::cout << ways[n] << "\n"
            << maxLength << "\n"
            << minNumber[n] << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/