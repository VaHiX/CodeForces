// Problem: CF 2153 C - Symmetrical Polygons
// https://codeforces.com/contest/2153/problem/C

/*
C. Symmetrical Polygons
Algorithms/Techniques: Sorting, Greedy, Two Pointers, Set Operations

Time Complexity: O(n log n) per test case due to sorting and linear passes.
Space Complexity: O(n) for storing the input and auxiliary arrays.

Problem Description:
We are given n sticks, and we want to choose a subset to form a symmetrical, strictly convex, and non-degenerate polygon.
The key insights are:
- For a polygon to be symmetrical, it needs at least one axis of symmetry.
- For a polygon to be convex and non-degenerate, the sum of any (n-1) sides must be greater than the largest side.
- We can build symmetrical polygons using pairs of equal-length sticks, and single sticks to balance.
- The approach focuses on grouping equal-length sticks, and then using greedy selection to achieve maximum perimeter under constraints.

Solution Approach:
1. Group sticks by their lengths.
2. Identify pairs (doubles) and singles (unique lengths).
3. For valid symmetrical constructions:
   - If there are no doubles, return 0.
   - Otherwise, consider adding doubles into the perimeter (double each to match symmetry).
   - Balance with singles for maximum perimeter while maintaining convexity.
4. Ensure the constructed polygon satisfies all required properties: non-degenerate, strictly convex, and symmetrical.
*/

#include <math.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define R2D0 ios_base::sync_with_stdio(false), cin.tie(nullptr);
#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define all(vec) vec.begin(), vec.end()
#define prinnt(x) cout << x << '\n'
#define cl(x, v) memset((x), (v), sizeof(x))
#define fo(i, n) for (int i = 0; i < n; ++i)
#define fore(i, k, n) for (int i = k; k < n ? i < n : i >= n; k < n ? ++i : --i)
#define fora(a) for (auto i : a)
#define tr(it, a) for (auto it = a.begin(); it != a.end(); ++it)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
const int N = 1e5 + 5, M = N;
const int MOD = 1e9 + 7, INF = 1e9 + 7;
const ll LINF = 1e18 + 7;
const ld EPS = 1e-9, PI = acos(-1.0);
template <typename T = int> istream &operator>>(istream &in, vector<T> &v) {
  for (auto &x : v)
    in >> x;
  return in;
}
template <typename T = int>
istream &operator>>(istream &in, vector<vector<T>> &v) {
  for (auto &x : v)
    in >> x;
  return in;
}
template <typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
  for (const T &x : v)
    out << x << ' ';
  return out;
}
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
void swap(int &a, int &b) {
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}
vector<string> RETU = {"NO\n", "YES\n", "-1\n"};
void solve() {
  int n, pivo, sinsize;
  ll ans = 0, othersum = 0;
  cin >> n;
  bool flagg = false;
  vi vec(n);
  vi dobles; // store pairs of equal lengths (doubles)
  vi singles; // store unique lengths
  cin >> vec;
  sort(all(vec));
  fo(i, n) {
    // Group equal lengths into pairs
    if (i < n - 1 && vec[i + 1] == vec[i]) {
      dobles.pb(vec[i]);
      i++; // Skip next element as paired with current
    } else {
      singles.pb(vec[i]);
    }
  }
  if (dobles.empty()) { // No pairs available
    cout << "0\n";
    return;
  }
  fora(dobles) { othersum += i; } // Sum of all paired sticks (doubles)
  othersum *= 2; // Each element in dobles contributes twice to total length (due to pairing)
  sort(all(singles));
  sinsize = singles.size();
  if (sinsize == 1 && singles[0] < othersum) { // Single stick smaller than sum of doubles
    ans += singles[0];
  } else if (sinsize > 1) {
    pivo = sinsize - 2; // Start from second-last element to look for optimal fit
    // Decrease pivo until (singles[pivo+1] - singles[pivo]) >= othersum,
    // or it means we can't use more pairs for symmetry
    while (pivo >= 0 && (singles[pivo + 1] - singles[pivo]) >= othersum)
      pivo--;
    if (pivo == (-1) && singles[0] < othersum) {
      ans += singles[0]; // Only first stick fits without violating symmetry
    } else if (pivo >= 0) {
      ans += singles[pivo + 1] + singles[pivo]; // Add two sticks for balance
    }
  }
  // If there are doubles or we have a valid contribution from singles,
  // add the total from doubles into result
  if (dobles.size() > 1 || ans != 0)
    ans += othersum;
  prinnt(ans);
}
int main() {
  R2D0;
  int tc = 1;
  cin >> tc;
  while (tc--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/