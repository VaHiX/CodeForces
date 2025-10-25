// Problem: CF 1905 E - One-X
// https://codeforces.com/contest/1905/problem/E

/*
 * Problem: E. One-X
 * Algorithm: Mathematical Analysis + Recursive Tree Traversal
 * 
 * Purpose:
 *   This code computes the sum of least common ancestors (LCAs) for all non-empty subsets of leaves
 *   in a segment tree built for an array of size n. The segment tree is constructed recursively using
 *   the standard build function where each internal node has two children (2v and 2v+1).
 *   
 *   The solution uses a recursive approach based on the binary representation of n to compute
 *   values related to subtree properties and applies mathematical formulas derived from the
 *   structure of the segment tree to achieve O(log n) time complexity per test case.
 *   
 * Time Complexity: O(log n) per test case
 * Space Complexity: O(log n) due to recursion stack depth
 */

#include <cstdio>
#include <iosfwd>

using namespace std;
typedef long long ll;
const int MAXN = 212345;
const ll mod = 998244353;
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, r, l) for (int i = (r); i >= (l); i--)
ll ans;

// Function to calculate result recursively using properties of the segment tree
void cal(ll x, ll cnt0, ll sum0, ll cnt1, ll sum1, ll &leaf0, ll &leaf1) {
  if (x == 1) {
    // Base case: reaching root node
    cnt0 = (cnt0 + 2 * cnt1) % mod;
    sum0 = (sum0 + 4 * sum1 + cnt1) % mod;
    ans = (ans + sum0 + sum1) % mod;
    leaf0 = 1ll << 1, leaf1 = 1ll << 2;
    return;
  }
  ll lf0, lf1;
  if (x & 1) {
    // Odd x: process x >> 1 with modified parameters
    cal(x >> 1, cnt0, (2 * sum0 + cnt0) % mod, (cnt0 + 2 * cnt1) % mod,
        (2 * sum0 + 4 * sum1 + cnt1) % mod, lf0, lf1);
    // Update leaf counts based on current branch
    leaf0 = lf0 * lf1 % mod;
    leaf1 = lf1 * lf1 % mod;
    // Accumulate contribution from current node's subsets
    ans = (ans + sum0 * (lf0 - 1) % mod * (lf1 - 1) % mod +
           sum1 * (lf1 - 1) % mod * (lf1 - 1) % mod) %
          mod;
  } else {
    // Even x: process x >> 1 with different parameter updates
    cal(x >> 1, (2 * cnt0 + cnt1) % mod,
        (4 * sum0 + cnt0 + 2 * sum1 + cnt1) % mod, cnt1, (2 * sum1) % mod, lf0,
        lf1);
    // Update leaf counts accordingly
    leaf0 = lf0 * lf0 % mod;
    leaf1 = lf0 * lf1 % mod;
    // Add the contributions to total answer
    ans = (ans + sum0 * (lf0 - 1) % mod * (lf0 - 1) % mod +
           sum1 * (lf0 - 1) % mod * (lf1 - 1) % mod) %
          mod;
  }
}

int main() {
  int T;
  for (scanf("%d", &T); T; T--) {
    ll N;
    scanf("%lld", &N);
    ans = 0;
    ll lf0, lf1;
    cal(N, 1, 1, 0, 0, lf0, lf1);
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/