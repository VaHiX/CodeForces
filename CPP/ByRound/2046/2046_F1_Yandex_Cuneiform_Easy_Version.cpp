// Problem: CF 2046 F1 - Yandex Cuneiform (Easy Version)
// https://codeforces.com/contest/2046/problem/F1

/*
Algorithm/Techniques: 
- This problem involves checking if a given string of 'Y', 'D', 'X' characters can be generated 
  through a specific insertion process that maintains no adjacent equal characters.
- The approach uses a greedy strategy:
  1. First check if the string has valid counts of each character (equal distribution).
  2. Check that there are no adjacent duplicate characters.
  3. For the insertion process, use a segment tree to efficiently track and update positions.
  4. At each step, select the next character to insert based on which character's count will be reduced and the constraint of no adjacent equal characters.
- Uses a set to maintain valid positions for insertion, ensuring constraints are met.

Time Complexity: O(n log n) where n is the length of the string. This accounts for:
  - Initial checks: O(n)
  - Segment tree operations: O(log n) per operation, total O(n log n)
Space Complexity: O(n) for the segment tree, arrays, and auxiliary data structures.

*/
#include <assert.h>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define sz(a) int(a.size())
#define all(a) a.begin(), a.end()
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;
template <class A, class B>
ostream &operator<<(ostream &out, const pair<A, B> &a) {
  return out << "(" << a.x << ", " << a.y << ")";
}
template <class A> ostream &operator<<(ostream &out, const vector<A> &v) {
  out << "[";
  forn(i, sz(v)) {
    if (i)
      out << ", ";
    out << v[i];
  }
  return out << "]";
}
mt19937 rnd(time(NULL));
const int INF = int(1e9);
const li INF64 = li(1e18);
const int MOD = int(1e9) + 7;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);
int n;
string s;
bool read() {
  if (!(cin >> s))
    return false;
  n = sz(s);
  return true;
}
const string al = "YDX";
vector<int> f;
void upd(int x) {
  for (int i = x; i < sz(f); i |= i + 1)
    ++f[i];
}
int get(int x) {
  int res = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
    res += f[i];
  return res;
}
void solve() {
  cerr << s << endl;
  forn(i, 3) forn(j, i) if (count(all(s), al[i]) != n / 3) {
    cout << "NO" << '\n';
    return;
  }
  forn(i, n - 1) if (s[i] == s[i + 1]) {
    cout << "NO" << '\n';
    return;
  }
  f.assign(n, 0);
  vector<int> a(n);
  forn(i, n) a[i] = al.find(s[i]);
  set<int> alive;
  forn(i, n) alive.insert(i);
  vector<set<int>> ok(3);
  forn(i, n - 2) if (a[i] != a[i + 2]) ok[a[i]].insert(i);
  vector<array<pair<char, int>, 3>> ans;
  auto op = [&](array<int, 3> rem) {
    ans.pb({});
    for (int i = 2; i >= 0; --i) {
      ans.back()[i] = {s[rem[i]], rem[i] - get(rem[i])};
      upd(rem[i]);
    }
    for (int x : rem) {
      auto it = alive.erase(alive.find(x));
      ok[a[x]].erase(x);
      for (int iter = 0; iter < 2 && it != alive.begin(); ++iter) {
        auto jt = it;
        it = prev(it);
        if (jt != alive.end() && next(jt) != alive.end() &&
            a[*next(jt)] != a[*it])
          ok[a[*it]].insert(*it);
        else
          ok[a[*it]].erase(*it);
      }
    }
  };
  forn(_, n / 3) {
    int fst = *alive.begin();
    assert(!ok[a[fst]].empty());
    int pos = *ok[a[fst]].begin();
    auto it = next(next(alive.find(pos)));
    pos = *it;
    if (next(it) == alive.end() || a[*next(it)] != a[fst])
      op({fst, pos, *prev(it)});
    else
      op({*prev(it), pos, *next(it)});
  }
  cout << "YES" << '\n';
  cout << s << '\n';
  reverse(all(ans));
  for (auto it : ans) {
    forn(i, 3) { cout << it[i].x << " " << it[i].y << " "; }
    cout << '\n';
  }
  cout.flush();
}
bool gen() {
  n = (rnd() % 2 + 1) * 3;
  s = "";
  forn(i, 3) forn(_, n / 3) s += al[i];
  shuffle(all(s), rnd);
  return true;
}
int main() {
  cerr.precision(15);
  cout.precision(15);
  cerr << fixed;
  cout << fixed;
  cin.tie(0);
  ios::sync_with_stdio(false);
  int tc;
  cin >> tc;
  while (tc--) {
    read();
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/