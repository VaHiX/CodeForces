// Problem: CF 1822 E - Making Anti-Palindromes
// https://codeforces.com/contest/1822/problem/E

/*
Algorithm: Making Anti-Palindromes
Approach:
1. First check if it's possible to make an anti-palindrome:
   - If n is odd, impossible (since middle character cannot be paired).
   - Count frequencies of characters; if any character appears more than n/2 times, impossible.
2. For even-length strings:
   - Identify pairs of characters that are equal at symmetric positions (s[i] == s[n-1-i]).
   - Count such pairs for each character.
   - Try to resolve pairs by swapping to make all symmetric pairs different.
   - Use a greedy approach with max heap (priority queue) to minimize operations.
   - Handle remaining characters that are still in conflict.

Time Complexity: O(n log n) due to sorting and operations on priority queue.
Space Complexity: O(1) as we use fixed size arrays (26 characters).
*/

#include <string.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;
#define F first
#define S second
#define R cin >>
#define ln cout << '\n'
#define ll long long
#define in(a) insert(a)
#define pb(a) push_back(a)
#define pd(a) printf("%.12f\n", a)
#define mem(a) memset(a, 0, sizeof(a))
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define rrep(i, n) for (ll i = (ll)(n) - 1; i >= 0; i--)
#define REP(i, m, n) for (ll i = (ll)(m); i < (ll)(n); i++)
#define rep(i, n) REP(i, 0, n)
#define tr(it, c) for (iter(c) it = (c).begin(); it != (c).end(); it++)
ll check(ll n, ll m, ll x, ll y) { return x >= 0 && x < n && y >= 0 && y < m; }
void pr() { ln; }
template <class A, class... B> void pr(const A &a, const B &...b) {
  cout << a << (sizeof...(b) ? " " : "");
  pr(b...);
}
template <class A> void PR(A a, ll n) {
  rep(i, n) cout << (i ? " " : "") << a[i];
  ln;
}
const ll MAX = 1e9 + 7, MAXL = 1LL << 61, dx[8] = {-1, 0, 1, 0, -1, -1, 1, 1},
         dy[8] = {0, 1, 0, -1, -1, 1, 1, -1};
typedef pair<ll, ll> P;
void Main() {
  ll T;
  R T;
  while (T--) {
    ll n;
    string s;
    cin >> n >> s;
    if (n % 2) {
      pr(-1);
      continue;
    }
    {
      ll c[26];
      mem(c);
      rep(i, n) c[s[i] - 'a']++;
      sort(c, c + 26, greater<ll>());
      if (c[0] > n / 2) {
        pr(-1);
        continue;
      }
    }
    ll c[26], d[26];
    mem(c);
    mem(d);
    rep(i, n / 2) {
      if (s[i] == s[n - 1 - i])
        c[s[i] - 'a']++;
      else
        d[s[i] - 'a']++, d[s[n - i - 1] - 'a']++;
    }
    priority_queue<P> que;
    rep(i, 26) que.push(P(c[i], i));
    ll ans = 0;
    while (1) {
      P p = que.top();
      que.pop();
      P q = que.top();
      que.pop();
      if (p.F && q.F) {
        ans++;
        c[p.S]--;
        c[q.S]--;
        d[p.S] += 2;
        d[q.S] += 2;
        p.F--;
        q.F--;
        que.push(p);
        que.push(q);
      } else
        break;
    }
    rep(i, 26) {
      ll k = 0;
      while (c[i]) {
        while (k < 26 && (!d[k] || k == i))
          k++;
        if (k >= 26)
          break;
        c[i]--;
        d[k]--;
        ans++;
      }
    }
    rep(i, 26) {
      if (c[i])
        ans = -1;
    }
    pr(ans);
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  Main();
  return 0;
}


// https://github.com/VaHiX/CodeForces/