// Problem: CF 1799 C - Double Lexicographically Minimum
// https://codeforces.com/contest/1799/problem/C

/*
Problem: C. Double Lexicographically Minimum
Algorithm: Greedy approach to construct the lexicographically minimum t_max
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) as we use fixed size arrays for character frequencies

The problem asks to find the lexicographically minimum value of t_max over all possible reorderings of a given string s.
t_max is defined as the lexicographically maximum of t and reverse(t).

Approach:
1. Count frequency of each character
2. For each character from 'z' to 'a':
   - If odd frequency, use half of it in the first half and one instance in the middle
   - If even frequency, use half in the first half
3. Construct first part of result
4. Create second part as reverse of first part (excluding middle if exists)
5. Handle special case for odd characters that need to be placed optimally
*/

#include <stdint.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define int long long
#define INF 1000000000000000000
#define MOD 1000000007
#define eps 1e-6
#define pii pair<int, int>
#define tiii pair<pair<int, int>, int>
#define ff first
#define ss second
#define fff first.first
#define sss first.second
#define ttt second
#define mset(a, b) memset(a, b, sizeof(a));
#define readArray(a, n)                                                        \
  for (int i = 0; i < n; i++)                                                  \
    cin >> a[i];
#define printArray(a, n)                                                       \
  for (int i = 0; i < n; i++)                                                  \
    cout << a[i] << " ";                                                       \
  cout << '\n';
#define prefixSum(a, pre, n)                                                   \
  pre[0] = a[0];                                                               \
  for (int i = 1; i < n; i++)                                                  \
    pre[i] = pre[i - 1] + a[i];
#define suffixSum(a, suf, n)                                                   \
  suf[n - 1] = a[n - 1];                                                       \
  for (int i = n - 2; i >= 0; i--)                                             \
    suf[i] = suf[i + 1] + a[i];
#define lbound(a, x) lower_bound(a.begin(), a.end(), x) - a.begin();
#define ubound(a, x) upper_bound(a.begin(), a.end(), x) - a.begin();
#define FastIO                                                                 \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
const int N = 200005;
int f[N], invf[N];
int spf[N];
int power(int a, int b) {
  if (b == 0)
    return 1;
  else {
    int x = power(a, b / 2);
    int y = (x * x) % MOD;
    if (b % 2)
      y = (y * a) % MOD;
    return y;
  }
}
int inverse(int a) { return power(a, MOD - 2); }
int ncr(int n, int r) {
  if (n < 0 || r < 0 || n < r)
    return 0;
  int ans = f[n];
  ans = (ans * invf[r]) % MOD;
  ans = (ans * invf[n - r]) % MOD;
  return ans;
}
void precomputeFactorials() {
  f[0] = 1;
  for (int i = 1; i < N; i++)
    f[i] = (f[i - 1] * i) % MOD;
  for (int i = 0; i < N; i++)
    invf[i] = inverse(f[i]);
}
void precomputeSPF() {
  for (int i = 0; i < N; i++)
    spf[i] = i;
  for (int i = 2; i < N; i++) {
    if (spf[i] == i) {
      for (int j = 2 * i; j < N; j += i) {
        if (spf[j] == j)
          spf[j] = i;
      }
    }
  }
}
void precompute() {}
string rev(string s) {
  string t = s;
  reverse(t.begin(), t.end());
  return t;
}
void solve(int tc) {
  string s;
  cin >> s;
  int n = s.length();
  int f[26];
  memset(f, 0, sizeof(f));
  for (int i = 0; i < n; i++) {
    f[s[i] - 'a']++;
  }
  string t = "", u = "";
  int c[26];
  if (f[25] > 0)
    c[25] = 1;
  else
    c[25] = 0;
  for (int i = 24; i >= 0; i--) {
    if (f[i] > 0)
      c[i] = c[i + 1] + 1;
    else
      c[i] = c[i + 1];
  }
  for (int i = 0; i < 26; i++) {
    if (f[i] % 2 == 1) {
      for (int j = 0; j < f[i] / 2; j++) {
        t += (char)(i + 'a');
        u += (char)(i + 'a');
      }
      if (c[i + 1] > 1) {
        for (int k = i + 1; k < 26; k++) {
          for (int j = 0; j < f[k]; j++)
            t += (char)(k + 'a');
        }
        t += (char)(i + 'a');
        break;
      } else if (c[i + 1] == 1) {
        for (int k = i + 1; k < 26; k++) {
          if (f[k] > 0) {
            for (int j = 0; j < f[k] / 2; j++) {
              t += (char)(k + 'a');
              u += (char)(k + 'a');
            }
            if (f[k] % 2 == 1)
              t += (char)(k + 'a');
            t += (char)(i + 'a');
            break;
          }
        }
        break;
      } else {
        t += (char)(i + 'a');
        break;
      }
    } else {
      for (int j = 0; j < f[i] / 2; j++) {
        t += (char)(i + 'a');
        u += (char)(i + 'a');
      }
    }
  }
  cout << t << rev(u) << '\n';
}
int32_t main() {
  FastIO;
  precompute();
  int tc = 1;
  cin >> tc;
  for (int ttc = 1; ttc <= tc; ttc++)
    solve(ttc);
  return 0;
}


// https://github.com/VaHiX/CodeForces/