// Problem: CF 1903 F - Babysitting
// https://codeforces.com/contest/1903/problem/F

/*
Problem: Babysitting - Find maximum minimum difference between indices of chosen nodes in a vertex cover
Algorithms: Binary search on answer + Fenwick tree for efficient range updates and queries
Time Complexity: O(n * log^2(n)) per test case
Space Complexity: O(n) per test case

The solution uses binary search on the answer to find the maximum possible minimum difference.
For each candidate difference, we check if there exists a vertex cover where all chosen vertices
have at least that difference between their indices. This check is done using a greedy approach
with Fenwick trees to track coverage and score efficiently.
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
#define fi first
#define se second
#define vvi vector<vector<int>>
#define vi vector<int>
#ifndef ONLINE_JUDGE
#define debug(x)                                                               \
  cerr << #x << " ";                                                           \
  _print(x);                                                                   \
  cerr << endl;
#else
#define debug(x)
#endif
void _print(ll t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(lld t) { cerr << t; }
void _print(double t) { cerr << t; }
void _print(ull t) { cerr << t; }
template <class T, class V> void _print(pair<T, V> p);
template <class T> void _print(vector<T> v);
template <class T> void _print(set<T> v);
template <class T, class V> void _print(map<T, V> v);
template <class T> void _print(multiset<T> v);
template <class T, class V> void _print(pair<T, V> p) {
  cerr << "{";
  _print(p.fi);
  cerr << ",";
  _print(p.se);
  cerr << "}";
}
template <class T> void _print(vector<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(set<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(multiset<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T, class V> void _print(map<T, V> v) {
  cerr << "[ ";
  for (auto i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
const int mod = 1e9 + 7;
const int inf = 1e9;
const vector<int> mo{(int)1e9 + 9, (int)1e9 + 7};
class fenwick {
public:
  int n;
  vector<ll> tree;
  fenwick() {}
  fenwick(int n) {
    this->n = n;
    tree.assign(n + 1, 0);
  }
  void update(int ind, int ad) {
    for (; ind <= n; ind += ind & -ind) {
      tree[ind] += ad;
    }
  }
  ll get(int ind) {
    ll ans = 0;
    for (; ind > 0; ind -= ind & -ind) {
      ans += tree[ind];
    }
    return ans;
  }
  void clean() { tree.assign(n + 1, 0); }
  void wipe(int ind) { update(ind, get(ind - 1) - get(ind)); }
};
class dsu {
  int n;
  vector<int> parent;
  vector<int> size;

public:
  vector<int> have;
  dsu(int n) {
    this->n = n;
    parent.assign(n + 1, 0);
    size.assign(n + 1, 0);
    have.assign(n + 1, 0);
  }
  void make_set(int v, int val) {
    parent[v] = v;
    size[v] = 1;
    have[v] = val;
  }
  int find_set(int v) {
    if (v == parent[v])
      return v;
    return parent[v] = find_set(parent[v]);
  }
  void unite(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (size[a] < size[b])
        swap(a, b);
      parent[b] = a;
      size[a] += size[b];
    }
  }
};
void F() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  fenwick done(n + 5);
  fenwick score(n + 5);
  int lo = 0, hi = n;
  queue<pair<int, int>> q;
  stack<int> st;
  while (lo < hi) {
    int mid = (lo + hi) >> 1;
    mid++;
    bool flag = false;
    function<bool(int)> work = [&](int nd) -> bool {
      int d = done.get(min(nd + mid - 1, n)) - done.get(max(nd - mid, 0));
      int s = score.get(min(nd + mid - 1, n)) - score.get(max(nd - mid, 0));
      if (d * (-1) + 2 != s)
        return true;
      int i = nd + 1;
      while (i <= min(nd + mid - 1, n) && done.get(i) == done.get(i - 1)) {
        st.push(i);
        q.push(make_pair(i, -1));
        done.update(i, 1);
        score.update(i, -1);
        i++;
      }
      i = nd - 1;
      while (i > max(nd - mid, 0) && done.get(i) == done.get(i - 1)) {
        st.push(i);
        q.push(make_pair(i, -1));
        done.update(i, 1);
        score.update(i, -1);
        i--;
      }
      return false;
    };
    function<bool(int)> work1 = [&](int nd) -> bool {
      for (auto &x : adj[nd]) {
        int vl = score.get(x) - score.get(x - 1);
        if (vl == -1) {
          return true;
        }
        if (vl == 0) {
          st.push(x);
          done.update(x, 1);
          score.update(x, 1);
          q.emplace(x, 1);
        }
      }
      return false;
    };
    function<bool()> check = [&]() -> bool {
      while (q.size()) {
        auto fr = q.front();
        q.pop();
        bool yes = false;
        if (fr.se == 1) {
          yes = work(fr.fi);
          if (yes)
            return false;
        } else {
          yes = work1(fr.fi);
          if (yes)
            return false;
        }
      }
      return true;
    };
    int at = 1;
    while (st.size()) {
      st.pop();
    }
    done.clean();
    score.clean();
    do {
      flag = false;
      while (q.size())
        q.pop();
      q.emplace(at, -1);
      done.update(at, 1);
      score.update(at, -1);
      st.push(at);
      flag |= check();
      if (!flag) {
        while (st.size()) {
          done.wipe(st.top());
          score.wipe(st.top());
          st.pop();
        }
      } else {
        while (st.size()) {
          st.pop();
        }
      }
      if (flag == false) {
        while (q.size())
          q.pop();
        q.emplace(at, 1);
        done.update(at, 1);
        score.update(at, 1);
        st.push(at);
        flag |= check();
      }
      while (at <= n && done.get(at) != done.get(at - 1))
        at++;
    } while (flag && at <= n);
    if (flag) {
      lo = mid;
    } else
      hi = mid - 1;
  }
  cout << lo << '\n';
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("error.txt", "w", stderr);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << fixed << setprecision(17);
  int T = 1;
  cin >> T;
  while (T--)
    F();
  return 0;
}


// https://github.com/VaHiX/CodeForces/