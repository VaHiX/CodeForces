// Problem: CF 1860 F - Evaluate RBS
// https://codeforces.com/contest/1860/problem/F

/*
Algorithm: This solution attempts to determine if there exist positive x and y such that sorting the brackets
by a·x + b·y results in a valid bracket sequence. The key insight is that for a valid bracket sequence,
the prefix sum of bracket values must not go negative at any point, and must end at zero.

Approach:
1. Process input data to build arrays of bracket data.
2. Preprocess the bracket sequence to compute prefix sums and track minimum prefix sum.
3. Generate candidate swaps based on differences in (a,b) values and bracket types.
4. Sort these candidates by a custom comparator that uses cross products to avoid floating point arithmetic.
5. Iterate through sorted candidates and attempt to make swaps that reduce or maintain the prefix sum.
6. Check if we can make the total prefix sum become zero, making the sequence valid.

Time Complexity: O(n^4) in worst case due to nested loops in preprocessing and swap attempts.
Space Complexity: O(n^2) for storing candidate swaps and intermediate arrays.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int c = 3005;
long long n, l[c], r[c], ert[c]; // l: 'a' values, r: 'b' values, ert: bracket values (-1 for '(' , 1 for ')')
int t[c], inv[c], pref[c], sum, jo; // t: sorting permutation, inv: inverse permutation, pref: prefix sums
vector<pair<pair<int, int>, int>> sz; // sz: list of candidates for swaps
bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
  // Custom comparator to avoid floating point arithmetic using cross product
  int A = a.first.first, B = a.first.second, C = b.first.first,
      D = b.first.second;
  long long x = (l[A] - l[B]) * (r[D] - r[C]), // Cross product to compare slopes
            y = (l[C] - l[D]) * (r[B] - r[A]);
  return (x < y || (x == y && a.second < b.second)); // Return true if a should come before b
}
void solve() {
  cin >> n;
  n *= 2; // Total number of brackets (n open, n close)
  for (int i = 1; i <= n; i++) {
    cin >> l[i] >> r[i];
    char c;
    cin >> c;
    ert[i] = (c == '(' ? -1 : 1); // Assign bracket value
  }
  // Sort tuples by a,b values (in this case, simple sorting for simplicity)
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (l[j] < l[i] || (l[j] == l[i] &&
                          (r[j] < r[i] || (r[j] == r[i] && ert[j] < ert[i])))) {
        swap(l[i], l[j]);
        swap(r[i], r[j]);
        swap(ert[i], ert[j]);
      }
    }
  }
  // Set up initial prefix sums and inverse permutation arrays
  for (int i = 1; i <= n; i++) {
    t[i] = i, inv[i] = i;
    pref[i] = pref[i - 1] + ert[i];
    sum += max(0, pref[i]); // Sum of positive prefix values
  }
  jo = (sum == 0); // Check if initial total is valid
  // Generate candidate swaps based on bracket values and positions
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (r[j] < r[i]) { // If right value of bracket j is less than bracket i
        sz.push_back({{i, j}, ert[j] - ert[i]}); // Add candidate swap with bracket difference
      }
    }
  }
  sort(sz.begin(), sz.end(), cmp); // Sort candidates using custom comparator
  for (auto x : sz) {
    int A = x.first.first, B = x.first.second, val = x.second;
    if (inv[A] < inv[B]) { // If bracket A is before B in current order
      swap(t[inv[A]], t[inv[B]]); // Swap their positions in the sort order
      for (int i = inv[A]; i < inv[B]; i++) {
        sum -= max(0, pref[i]);
        pref[i] += val;
        sum += max(0, pref[i]); // Update prefix sum changes
      }
      swap(inv[A], inv[B]); // Update inverse permutation
    }
    if (sum == 0) {
      jo = 1; // If valid, set solution flag
    }
  }
  cout << (jo ? "YES" : "NO") << "\n";
  // Reset arrays for next test case
  for (int i = 0; i < c; i++) {
    l[i] = 0, r[i] = 0, ert[i] = 0, t[i] = 0, inv[i] = 0, pref[i] = 0;
  }
  jo = 0, sum = 0;
  sz.clear();
}
int main() {
  ios_base::sync_with_stdio(false);
  int w;
  cin >> w;
  while (w--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/