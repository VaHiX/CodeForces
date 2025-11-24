// Problem: CF 1895 C - Torn Lucky Ticket
// https://codeforces.com/contest/1895/problem/C

/*
Purpose: This code solves the problem of counting pairs of ticket strings such that their concatenation forms a "lucky ticket".
A lucky ticket has an even length and equal sums in the first and second halves.
The approach uses pre-processing and a hash-like counting technique to efficiently compute the answer.

Algorithms/Techniques:
- Preprocessing: Store counts of prefix sums for each possible string length and total sum
- Enumeration: Iterate over all possible pairings of lengths and compute valid combinations
- Optimization: Use a 4D array to store counts of (length, total_sum, prefix_length, prefix_sum)

Time Complexity: O(n * L^2 * S^2) where L is max length (5) and S is max sum (5 * 9 = 45)
Space Complexity: O(L^2 * S^2) for the 4D array storage
*/

#include <time.h>
#include <iostream>
#include <string>

using namespace std;
#define fio                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);
using i64 = long long;
const i64 inf = 0x3fffffffffffffff;
i64 book[6][60][6][60]; // 4D array to store counts of (length, total_sum, prefix_len, prefix_sum)
int main() {
  fio;
  i64 n;
  cin >> n;
  string s;
  for (int i = 1; i <= n; i++) {
    cin >> s;
    i64 sum = 0;
    i64 sz = s.size();
    for (i64 j = 0; j < sz; j++) {
      sum += (s[j] - '0'); // Calculate total sum of digits
    }
    i64 prefix_sum = 0;
    for (i64 j = 0; j < sz; j++) {
      prefix_sum += (s[j] - '0'); // Compute prefix sum
      book[sz][sum][j + 1][prefix_sum]++; // Increment count in 4D array
    }
  }
  i64 ans = 0;
  for (i64 l = 1; l <= 5; l++) {
    for (i64 r = 1; r <= 5; r++) {
      if ((l + r) % 2 != 0) {
        continue; // Skip odd total lengths
      }
      if (l < r) {
        // Case where first string is shorter than second
        for (i64 lval = 1; lval <= 50; lval++) {
          for (i64 rval = 1; rval <= 50; rval++) {
            if ((lval + rval) % 2 != 0) {
              continue; // For valid half sums, both must be even or both odd
            }
            ans += book[l][lval][l][lval] *
                   book[r][rval][(r - l) / 2][(rval - lval) / 2];
          }
        }
      } else if (l == r) {
        // Case where both strings have same length
        for (i64 val = 1; val <= 50; val++) {
          ans += book[l][val][l][val] * book[l][val][l][val];
        }
      } else if (l > r) {
        // Case where first string is longer than second
        for (i64 lval = 1; lval <= 50; lval++) {
          for (i64 rval = 1; rval <= 50; rval++) {
            if ((lval + rval) % 2 != 0) {
              continue;
            }
            ans += book[l][lval][l - (l - r) / 2][lval - (lval - rval) / 2] *
                   book[r][rval][r][rval];
          }
        }
      }
    }
  }
  cout << ans << endl;
  cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/