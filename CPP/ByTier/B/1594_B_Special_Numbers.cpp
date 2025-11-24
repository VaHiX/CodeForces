// Problem: CF 1594 B - Special Numbers
// https://codeforces.com/contest/1594/problem/B

/*
B. Special Numbers
The problem asks to find the k-th special number in the sequence of numbers that can be represented as a sum of distinct non-negative powers of n.
This is essentially converting the number k to its binary representation and interpreting it as a sum of powers of n.

Algorithm:
- For each bit set in k (from least significant to most significant):
  - Multiply n by itself 'bit position' times
  - Add this value to result
- This works because each special number corresponds to a unique binary representation of k,
  where the i-th bit being 1 means we include n^i in the sum.

Time Complexity: O(log k) per test case
Space Complexity: O(1)

Input:
The first line contains a single integer t (1 ≤ t ≤ 10^4) — the number of test cases.
Each test case contains two integers n and k (2 ≤ n ≤ 10^9; 1 ≤ k ≤ 10^9).

Output:
For each test case, print one integer — the k-th special number in increasing order modulo 10^9+7.

Example:
Input
3
3 4
2 12
105 564
Output
9
12
3595374
*/

#include <cstdio>
typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll res(0), cur(1); // res stores the result, cur keeps track of current power of n
    while (k) {
      if (k % 2) { // if the least significant bit is 1
        res += cur; // add current power to result
        res %= MOD; // keep result within mod
      }
      cur *= n; // move to next power of n
      cur %= MOD;
      k /= 2; // shift bits right (equivalent to k >>= 1)
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/