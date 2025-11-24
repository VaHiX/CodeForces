// Problem: CF 1776 D - Teamwork
// https://codeforces.com/contest/1776/problem/D

/*
Algorithm: Binary search on the number of problems solved, and for each number,
           use a greedy approach to check if it's possible to solve that many.
           The greedy method tries to fit the hardest problems first, using
           the earliest possible start times for each problem to allow more
           problems to be scheduled.

Time Complexity: O(log(n) * l) where n = a + b + c and l is the contest duration.
Space Complexity: O(l) for storing the solution.

Techniques:
- Binary search on the answer to find maximum number of problems.
- Greedy assignment of problems to minimize conflicts.
- Tracking of contestant usage times to avoid overlap.
*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#define mp(a, b) make_pair(a, b)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
typedef long long ll;
typedef long double ld;
mt19937 mrand(random_device{}());
const double pi = acos((double)-1);
const ld eps = 1e-8;
const int inf0 = 1023 * 1024 * 1024;
const ll inf = 4e18;
const ll mod = 998244353;
void solve();
signed main() {
#ifdef DEBUG
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cout << fixed;
  cout.precision(15);
  solve();
  return 0;
}
struct Item {
  int tp;
  int p, q;
};
int pos[3];
int l;
vector<Item> ans;
bool add(Item x) {
  if (x.q > l)
    return false;
  pos[x.tp] = x.q;
  ans.push_back(x);
  return true;
}
int a, b, c;
bool place(int tp, int p, int x) {
  if (x == 0 && a > 0) {
    bool fl = add(Item{tp, p, p + 2});
    if (fl)
      a--;
    return fl;
  } else if (x == 1) {
    if (b > 0) {
      bool fl = add(Item{tp, p, p + 3});
      if (fl)
        b--;
      return fl;
    }
    return place(tp, p + 1, x - 1);
  } else if (x == 2) {
    if (c > 0) {
      bool fl = add(Item{tp, p, p + 4});
      if (fl)
        c--;
      return fl;
    }
    return place(tp, p + 1, x - 1);
  }
  return false;
}
bool check() { return (a >= 1) && (a + b >= 2) && (a + b + c >= 3); }
void smart_solve() {
  ans.clear();
  pos[0] = pos[1] = pos[2] = 0;
  if (l < 2 || (a + b + c) == 0) {
    return;
  } else if (l == 2) {
    if (a >= 1) {
      ans.push_back(Item{0, 0, 2});
    }
    return;
  } else if (a + b + c <= 2) {
    if (a == 2) {
      place(0, 0, 0);
      place(1, 1, 0);
    } else if (b == 2) {
      place(0, 0, 1);
      place(1, 1, 1);
    } else if (c == 2) {
      place(0, 0, 2);
      place(1, 1, 2);
    } else if (a == 1 && b == 1) {
      place(0, 0, 0);
      place(1, 0, 1);
    } else if (a == 1 && c == 1) {
      place(0, 0, 0);
      place(1, 0, 2);
    } else if (b == 1 && c == 1) {
      place(0, 0, 1);
      place(1, 0, 2);
    } else if (a == 1) {
      place(0, 0, 0);
    } else if (b == 1) {
      place(0, 0, 1);
    } else if (c == 1) {
      place(0, 0, 2);
    } else {
      assert(false);
    }
    return;
  }
  for (int i = 0; i <= l; i++) {
    bool bl = false;
    if (c > 0 && i >= 4) {
      int minx = 0;
      for (int x = 0; x < 3; x++) {
        if ((pos[minx] > i - 4 || pos[x] > pos[minx]) && pos[x] <= i - 4)
          minx = x;
      }
      if (pos[minx] <= i - 4) {
        bl = place(minx, i - 4, 2);
        assert(bl);
        continue;
      }
    }
    if (bl)
      continue;
    if (b > 0 && i >= 3) {
      int minx = 0;
      for (int x = 0; x < 3; x++) {
        if ((pos[minx] > i - 3 || pos[x] > pos[minx]) && pos[x] <= i - 3)
          minx = x;
      }
      if (pos[minx] <= i - 3) {
        bl = place(minx, i - 3, 1);
        assert(bl);
        continue;
      }
    }
    if (bl)
      continue;
    if (a > 0 && i >= 2) {
      int minx = 0;
      for (int x = 0; x < 3; x++) {
        if ((pos[minx] > i - 2 || pos[x] > pos[minx]) && pos[x] <= i - 2)
          minx = x;
      }
      if (pos[minx] <= i - 2) {
        bl = place(minx, i - 2, 0);
        assert(bl);
        continue;
      }
    }
  }
}
void solve() {
  int aa, bb, cc;
  cin >> aa >> bb >> cc >> l;
  int tot = aa + bb + cc;
  int lf = 0;
  int rf = tot + 1;
  while (rf - lf > 1) {
    int m = lf + rf >> 1;
    a = min(aa, m);
    b = min(bb, m - a);
    c = min(cc, m - a - b);
    smart_solve();
    if (ans.size() == m)
      lf = m;
    else
      rf = m;
  }
  a = min(aa, lf);
  b = min(bb, lf - a);
  c = min(cc, lf - a - b);
  smart_solve();
  cout << ans.size() << endl;
  for (Item a : ans) {
    cout << a.tp + 1 << " " << a.p << " " << a.q << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/