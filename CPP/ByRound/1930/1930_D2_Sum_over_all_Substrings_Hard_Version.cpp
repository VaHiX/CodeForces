// Problem: CF 1930 D2 - Sum over all Substrings (Hard Version)
// https://codeforces.com/contest/1930/problem/D2

/*
Code Purpose:
This program computes the sum of f(p) over all substrings of a binary string s,
where f(p) is defined as the minimum number of 1s in a p-good binary string of the same length as p.
A p-good string q satisfies that for every position i in pattern p, there exists a substring of q
that contains p[i] as a mode (i.e., appears at least ceil(length/2) times).

Algorithms/Techniques:
- Dynamic Programming with reverse iteration
- Preprocessing using a suffix array f[i] to represent the contribution of substrings starting at position i
- Efficient computation of f[p] based on whether the character is '0' or '1'

Time Complexity: O(n) per test case
Space Complexity: O(n) for the arrays f and a

*/

#include <stdio.h>
#include <iosfwd>

#define ll long long
using namespace std;
int t, n;
char a[1000101];
ll f[1000011];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    ll ans = 0;
    scanf("%s", a + 1);
    f[n + 1] = f[n + 2] = f[n + 3] = 0;
    // Reverse iteration to compute f[i] based on values of f[i+1], f[i+2], f[i+3]
    for (int i = n; i; --i) {
      if (a[i] == '1') {
        // If current character is '1', we use the value from f[i+3] and add the remaining length
        f[i] = f[i + 3] + n - i + 1;
      } else {
        // If current character is '0', we carry forward the value of f[i+1]
        f[i] = f[i + 1];
      }
    }
    // Sum up all values of f[i] to get the final answer
    for (int i = 1; i <= n; ++i)
      ans += f[i];
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/