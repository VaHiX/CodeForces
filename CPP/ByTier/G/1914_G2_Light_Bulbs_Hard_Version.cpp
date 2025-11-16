// Problem: CF 1914 G2 - Light Bulbs (Hard Version)
// https://codeforces.com/contest/1914/problem/G2

/*
 * Problem: G2. Light Bulbs (Hard Version)
 * 
 * Algorithm/Techniques:
 * - Union-Find (Disjoint Set Union) with path compression and union by size
 * - Segment merging and processing ranges to determine minimum initial bulbs to turn on
 * - Modular arithmetic for counting valid sets
 * 
 * Time Complexity: O(n * α(n)) where α is the inverse Ackermann function, practically constant
 * Space Complexity: O(n)
 */

#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define pb push_back
#define endl '\n'
#define ll long long
#define ld long double
#define mset multiset
#define all(x) x.begin(), x.end()
#define count_bits(mask) __builtin_popcountll(mask)
const int N = 4e5 + 5;
int rep[N], sz[N], sz1[N]; // rep: parent in DSU, sz: size of component, sz1: count of bulbs in component

// Find root of component with path compression
int root(int r) {
  if (rep[r] == r)
    return r;
  return rep[r] = root(rep[r]); // Path compression
}

// Merge two components
void merge(int a, int b) {
  int ra = root(a), rb = root(b);
  if (ra == rb)
    return;
  rep[ra] = rb;
  sz[rb] += sz[ra];
  sz1[rb] += sz1[ra];
}

int mod = 998244353;

// Return size of component containing r
int Size(int r) {
  r = root(r);
  return sz[r];
}

void solve() {
  int n;
  cin >> n;
  int c[2 * n];
  for (int i = 0; i < 2 * n; i++) {
    cin >> c[i];
    c[i]--; // Convert to 0-based indexing
  }
  
  int sec[n], fir[n]; // fir[i]: first occurrence of color i, sec[i]: second occurrence of color i
  for (int i = 0; i < n; i++)
    fir[i] = -1;
  for (int i = 0; i < 2 * n; i++) {
    rep[i] = i, sz[i] = 2, sz1[i] = 1; // Initialize DSU
    if (fir[c[i]] == -1)
      fir[c[i]] = i;
    else
      sec[c[i]] = i;
  }
  
  vector<pair<int, int>> ranges; // To store ranges of bulbs
  int s = 0, e = sec[c[0]];
  while (e < 2 * n) {
    for (int i = s; i <= e && e < 2 * n; i++)
      e = max(e, sec[c[i]]); // Extend range to cover all bulbs of same color in current group
    ranges.push_back({s, e});
    s = e = e + 1; // Move to next segment
  }
  
  int ways = 1;
  for (auto r : ranges) {
    int s = r.first, e = r.second;
    vector<int> v; // Stack to store indices
    for (int i = s; i <= e; i++) {
      if (i == sec[c[i]]) { // If it's the last bulb of its color
        // Merge with previous components
        while (v.size() && v.back() >= fir[c[i]]) {
          merge(c[v.back()], c[i]);
          v.pop_back();
        }
        int r = root(c[i]);
        sz1[r]++; // Increment count of bulbs in component
        if (sz[r] != (sz1[r])) { // If not all bulbs in component are yet used up
          v.push_back(i);
        }
      } else
        v.push_back(i); // Add to stack
    }
    ways = 1ll * ways * Size(c[s]) % mod; // Multiply by number of bulbs at start of range
  }
  cout << ranges.size() << ' ' << ways << endl; // Output minimum size and number of ways
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  srand(time(0));
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/