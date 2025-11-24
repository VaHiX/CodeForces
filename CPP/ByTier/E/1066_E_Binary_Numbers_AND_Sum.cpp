// Problem: CF 1066 E - Binary Numbers AND Sum
// https://codeforces.com/contest/1066/problem/E

/*
E. Binary Numbers AND Sum
Algorithms/Techniques: Bit manipulation, prefix sums, modular arithmetic
Time complexity: O(n + m)
Space complexity: O(n + m)

The problem involves computing the sum of bitwise AND operations between two binary numbers a and b,
as b is repeatedly right-shifted until it becomes zero.
We use the insight that for each bit position k in b, we can calculate how many times the k-th bit
of a contributes to the result by considering the prefix of b's bits up to position k.
The solution uses prefix sums and powers of 2 modulo 998244353 to efficiently compute the answer.

Input:
- n: length of binary number a
- m: length of binary number b
- s1: string representing binary number a (1-indexed)
- s2: string representing binary number b (1-indexed)

Output:
- The sum of a & b for all steps of the process, modulo 998244353.
*/

#include <algorithm>
#include <cstdio>

#define N 200005
using namespace std;
const int p = 998244353;
int n, m, ans, pw[N], s[N];
char s1[N], s2[N];

int main() {
  scanf("%d%d%s%s", &n, &m, s1 + 1, s2 + 1);
  
  // Precompute powers of 2 modulo p
  for (int i = pw[0] = 1; i <= m; i++)
    pw[i] = pw[i - 1] * 2 % p;
  
  // Build prefix sum array of b's bits
  for (int i = 1; i <= m; i++)
    s[i] = s[i - 1] + s2[i] - 48;
  
  // For each step, calculate contribution of a & b in the current iteration
  for (int i = max(1, n - m + 1); i <= n; i++)
    ans = 1ll * (ans + 1ll * pw[n - i] * s[i + m - n] * (s1[i] - 48)) % p;
  
  return printf("%d\n", ans), 0;
}


// https://github.com/VaHiX/codeForces/