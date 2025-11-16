// Problem: CF 1815 B - Sum Graph
// https://codeforces.com/contest/1815/problem/B

/*
Purpose: This code solves the interactive problem "Sum Graph" where we need to determine a hidden permutation p of length n.
The algorithm works by:
1. Making two initial queries with x = n and x = n+1 to build a graph structure
2. Querying distances between consecutive elements to build a sequence of "add" values
3. Using these values to construct two candidate permutations (p1 and p2) 
4. Outputting both permutations as guesses

Algorithms/Techniques:
- Graph construction using type-1 queries (adding edges based on x value)
- Distance queries (type-2) to determine connectivity between nodes
- Mathematical deduction to build candidate permutations
- Union-Find like structure is used to track connected components

Time Complexity: O(n^2) - due to multiple queries and operations on the permutation
Space Complexity: O(n) - for storing vectors and intermediate data structures
*/
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define x first
#define y second
#define ll long long
#define print(x)                                                               \
  {                                                                            \
    cout << (x) << endl;                                                       \
    continue;                                                                  \
  }
#define all(x) x.begin(), x.end()
#define pi pair<int, int>
#define py print("YES");
#define pn print("NO");
ll mod = 1e9 + 7;
int find(int i, vector<int> &par) {
  if (par[i] != i)
    par[i] = find(par[i], par);
  return par[i];
}
bool uni(int a, int b, vector<int> &par, vector<int> &sz) {
  a = find(a, par);
  b = find(b, par);
  if (a == b)
    return 0;
  if (sz[a] > sz[b])
    swap(a, b);
  sz[b] += sz[a];
  par[a] = b;
  return 1;
}
int sq(int n) { return n * (n + 1) / 2; }
int ab(int n) { return n > 0 ? n : -n; }
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tt = 1;
  cin >> tt;
  int n, a, b, c, m = 0, k = 1, q, r, l, x, y;
  string s, s1, s2, s3;
  set<int> st1, st2;
  vector<int> vect, vect1;
  while (tt--) {
    cin >> n;
    cout << "+ " << n << endl;
    cout.flush();
    cin >> a;
    if (a == -2)
      cout << k / m << endl;
    cout << "+ " << n + 1 << endl;
    cout.flush();
    cin >> a;
    if (a == -2)
      cout << k / m << endl;
    vector<int> v;
    v.push_back(n);
    v.push_back(1);
    while (v.size() < n) {
      int u = v.size() - 1;
      if (v[u] + v[u - 1] == n)
        v.push_back(n + 1 - v[u]);
      else
        v.push_back(n - v[u]);
    }
    vector<int> nx(n, -1), nx2(n, -1);
    for (int i = 0; i < n - 1; i++) {
      cout << "? " << i + 1 << ' ' << i + 2 << endl;
      cout.flush();
      cin >> nx[i];
      if (nx[i] == -2)
        cout << k / m << endl;
    }
    for (int i = 0; i < n - 2; i++) {
      cout << "? " << i + 1 << ' ' << i + 3 << endl;
      cout.flush();
      cin >> nx2[i];
      if (nx2[i] == -2)
        cout << k / m << endl;
    }
    vector<int> add(n);
    add[0] = nx[0];
    int sgn = 1;
    for (int i = 1; i < n - 1; i++) {
      if (nx2[i - 1] != nx[i - 1] + nx[i])
        sgn *= -1;
      add[i] = sgn * nx[i];
    }
    vector<int> p1(n), p2(n);
    int c1 = 0, c2 = 0;
    int mx1 = 0, mx2 = 0;
    for (int i = 0; i < n; i++) {
      p1[i] = c1;
      p2[i] = c2;
      c1 += add[i];
      c2 -= add[i];
      mx1 = max(mx1, c1);
      mx2 = max(mx2, c2);
    }
    for (int i = 0; i < n; i++) {
      p1[i] += n - 1 - mx1;
      p2[i] += n - 1 - mx2;
    }
    for (int i = 0; i < n; i++) {
      p1[i] = v[p1[i]];
      p2[i] = v[p2[i]];
    }
    cout << "! ";
    for (int i : p1)
      cout << i << ' ';
    for (int i : p2)
      cout << i << ' ';
    cout << endl;
    cout.flush();
    cin >> a;
    if (a == -2)
      cout << k / m << endl;
  }
}


// https://github.com/VaHiX/CodeForces/