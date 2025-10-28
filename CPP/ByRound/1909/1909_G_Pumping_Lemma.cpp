// Problem: CF 1909 G - Pumping Lemma
// https://codeforces.com/contest/1909/problem/G

/*
Algorithm: Pumping Lemma Application with KMP-like Matching
Purpose:
    Given two strings s and t, count the number of triples (x, y, z) such that:
    1. s = x + y + z
    2. t = x + y^k + z for some integer k >= 1 (where y^k is y repeated k times)
    
This implementation uses:
- Prefix/suffix matching to identify common parts of s and t
- KMP-like algorithm to find periodicity in the middle part of t
- Mathematical counting based on periodic length to avoid brute-force

Time Complexity: O(n + m)
Space Complexity: O(n)

The algorithm is based on the observation that if s = x + y + z and t = x + y^k + z,
then the middle part y must repeat in t between the prefix and suffix that match s.

Steps:
1. Match prefix and suffix of s and t
2. Identify period of repeating pattern in the middle using KMP-like logic
3. Enumerate valid periods and count valid (x,y,z) combinations

*/

#include <time.h>
#include <algorithm>
#include <iostream>

typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int N = 1e7 + 5;
int n, m, pre, suf, nxt[N];
char s[N], t[N];
int main() {
#ifdef ddxrS
  freopen("sample.in", "r", stdin);
  freopen("sample.out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> (s + 1) >> (t + 1);
  // Match prefix of s and t to find common begin
  while (s[pre + 1] == t[pre + 1] && pre < n)
    pre++;
  // Match suffix of s and t to find common end
  while (s[n - suf] == t[m - suf] && suf < n)
    suf++;
  // If prefix and suffix don't cover full s, no solution exists
  if (pre + suf < n)
    return cout << 0 << '\n', 0;
  // Length of repeated middle part
  int len = m - n, l = pre + 1, r = pre + len;
  // Initialize KMP failure function for pattern matching
  nxt[l] = l - 1;
  for (int i = l + 1, j = l - 1; i <= r; i++) {
    // Adjust failure function
    while (j >= l && t[j + 1] != t[i])
      j = nxt[j];
    // Update j if match
    j += (t[j + 1] == t[i]);
    nxt[i] = j;
  }
  // Compute minimum period of repeating pattern in t
  int p = r - nxt[r];
  // If not divisible, we consider full length
  if (len % p)
    p = len;
  // Start index of matching middle section in t
  l = m - suf - len + 1;
  // Upper bound for valid period lengths
  int lim = min(m - n, pre - l + 1);
  ll ans = 0;
  // Enumerate all possible valid periods
  for (int i = p; i <= lim; i += p)
    if (len % i == 0)
      ans += (pre - l + 1) - i + 1;
  cout << ans << '\n';
  cerr << clock() * 1.0 / CLOCKS_PER_SEC << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/