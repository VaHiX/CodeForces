// Problem: CF 1608 D - Dominoes
// https://codeforces.com/contest/1608/problem/D

// Purpose: This code solves the problem of counting valid colorings of dominoes such that
//          a valid arrangement exists where adjacent dominoes have different colors on
//          their meeting cells. The solution uses combinatorics and modular arithmetic.
//
// Algorithms/Techniques:
//   - Modular exponentiation with Fermat's little theorem for inverse computation
//   - Preprocessing factorials for combination calculation
//   - Counting valid and invalid domino types
//   - Combinatorial counting with inclusion-exclusion principle
//
// Time Complexity: O(n)
// Space Complexity: O(1) (excluding input storage)
#include <iostream>
#include <string>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
string s;
ll ans1, ans2, jie[N];
const int p = 998244353;
ll qmod(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}
void init() {
  jie[0] = 1;
  for (int i = 1; i <= 200000; i++)
    jie[i] = jie[i - 1] * i % p;
}
ll C(ll a, ll b) {
  if (b < 0 || a < b)
    return 0;
  return jie[a] * qmod(jie[b], p - 2) % p * qmod(jie[a - b], p - 2) % p;
}
ll BW, WB, __;
int main() {
  int n;
  cin >> n;
  bool flag = true;
  ans2 = 1;
  ll sum = 0, sumA = 0;
  init();
  for (int i = 1; i <= n; i++) {
    cin >> s;
    if (s == "WB" || s == "?B" || s == "W?")
      WB++;
    else if (s == "BW" || s == "?W" || s == "B?")
      BW++;
    else if (s == "WW" || s == "BB")
      ans2 = 0;
    else if (s == "??")
      ans2 = ans2 * 2 % p;
    for (int j = 0; j < 2; j++) {
      if (s[j] == '?')
        sum++;
      if (s[j] == 'W')
        sumA++;
    }
  }
  if (n == 1)
    ans2 = 0;
  if (BW == 0 && ans2 != 0)
    ans1++;
  if (WB == 0 && ans2 != 0)
    ans1++;
  ans1 = (ans1 + C(sum, n - sumA) + p - ans2) % p;
  cout << ans1 << endl;
}


// https://github.com/VaHiX/CodeForces/