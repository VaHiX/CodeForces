// Problem: CF 2077 C - Binary Subsequence Value Sum
// https://codeforces.com/contest/2077/problem/C

/*
C. Binary Subsequence Value Sum
time limit per test3 seconds
memory limit per test256 megabytes
Last | Moment - onoken

This problem computes the sum of scores over all subsequences of a binary string after each flip operation.

The score of a subsequence is defined as max(F(s,1,i) * F(s,i+1,n)) across all i (0 <= i <= n),
where F(s,l,r) = r - l + 1 - 2 * zero(s,l,r).

The algorithm uses an efficient technique:
- Precompute initial sum using a single pass
- Maintain running total of score contributions
- For each update, adjust the running total in O(1)
- Use modular arithmetic for large numbers

Time Complexity: O(n + q) per test case, where n is the string length and q is number of queries.
Space Complexity: O(n), due to storing the binary string.

Algorithms/Techniques:
- Prefix sum technique
- Efficient update tracking with modular arithmetic
- Modular inverse using constant k = 998244353
*/

#include <iostream>
#include <string>

using namespace std;
long long n, m, l, T, ss, su, a1;
const long long k = 998244353, n2 = (k + 1) / 2; // n2 is modular inverse of 2 mod k
string a;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  for (int u = 1; u <= T; u++) {
    cin >> n >> m;
    ss = 1; // ss represents 2^(n-1) mod k
    cin >> a;
    su = 0; // su tracks the cumulative score contribution
    su += a[0] - '0'; // add first char to base sum
    for (int i = 1; i <= n - 1; i++)
      ss = ss * 2 % k, su += a[i] - '0'; // compute powers of 2 and partial sum
    su = su * 2 - n; // adjust final sum to account for difference from formula

    for (int i = 1; i <= m; i++) {
      cin >> a1;
      if (a[a1 - 1] == '0')
        a[a1 - 1] = '1', su += 2; // Flip from 0 to 1, increase su by 2
      else
        a[a1 - 1] = '0', su -= 2; // Flip from 1 to 0, decrease su by 2

      // Formula used for final answer:
      // ss * ((su * su + n - 2 + k) % k) % k * n2 % k * n2 % k * n2 % k
      cout << ss * ((su * su + n - 2 + k) % k) % k * n2 % k * n2 % k * n2 % k
           << '\n';
    }
  }
}


// https://github.com/VaHiX/codeForces/