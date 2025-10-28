// Problem: CF 1907 F - Shift and Reverse
// https://codeforces.com/contest/1907/problem/F

/*
 * Problem: F. Shift and Reverse
 * Algorithms: Greedy, Simulation, Array Manipulation
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array and auxiliary structures
 *
 * The problem involves sorting an array using two operations:
 * 1. Shift: move last element to front
 * 2. Reverse: reverse the entire array
 *
 * The approach:
 * - Identify the minimum element and its positions
 * - Check if the array can be sorted using these operations
 * - Try possible rotations that lead to sorted arrays
 * - Compute minimum operations needed
 *
 * Key insight:
 * - If all elements are same, it's already sorted (0 operations)
 * - If there's a segment of minimum elements that spans the whole array,
 *   then it might be possible to sort it
 * - Try to simulate the sorted array by shifting and then reversing
 * - Count the operations required for each valid configuration
 */

#include <algorithm>
#include <iostream>
#include <vector>

#define ld long double
#define ll long long int
#define st first
#define nd second
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
using namespace std;
const int N = 1e5 + 5;
int a[N];
int n;
bool is[N];

// Check if array is sorted in non-decreasing order
bool sorted(vector<int> x) {
  for (int i = 1; i < (int)x.size(); i++) {
    if (x[i] < x[i - 1])
      return false;
  }
  return true;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  int mn = a[1];
  for (int i = 2; i <= n; i++)
    mn = min(mn, a[i]);
  int cnt = 0;
  for (int i = 1; i <= n; i++)
    cnt += (a[i] == mn);
  for (int i = 1; i <= n; i++)
    is[i] = (a[i] == mn);
  bool ok = true;
  int fi = -1;
  int la = -1;
  if (is[1]) {
    int got = 0;
    int ptr = 1;
    while (ptr <= n && a[ptr] == mn) {
      ptr += 1;
      got += 1;
    }
    la = ptr - 1;
    if (ptr < n) {
      ptr = n;
      while (ptr >= 1 && a[ptr] == mn) {
        ptr -= 1;
        got += 1;
      }
    }
    if (got != cnt) {
      cout << -1 << "\n";
      return;
    }
    fi = ptr + 1;
  } else {
    int ptr = 1;
    while (a[ptr] != mn)
      ptr += 1;
    fi = ptr;
    int got = 0;
    while (ptr <= n && a[ptr] == mn) {
      ptr += 1;
      got += 1;
    }
    la = ptr - 1;
    if (got != cnt) {
      cout << -1 << "\n";
      return;
    }
  }
  if (cnt == n) {
    cout << 0 << "\n";
    return;
  }
  if (fi == n + 1)
    fi = 1;
  if (la == 0)
    la = n;
  vector<int> ord1, ord2;
  int c1 = min(n + 1 - fi, fi - 1 + 2);
  if (fi == 1)
    c1 = 0;
  int c2 = 1 + min(n - la, n - n + la);
  if (la == n)
    c2 = 1;
  const int inf = 1e9;
  int ans = inf;
  int pos = fi;
  if (pos == n + 1)
    pos = 1;
  for (int i = 0; i < n; i++) {
    ord1.pb(a[pos]);
    pos += 1;
    if (pos == n + 1)
      pos = 1;
  }
  pos = la;
  for (int i = 0; i < n; i++) {
    ord2.pb(a[pos]);
    pos -= 1;
    if (pos == 0)
      pos = n;
  }
  if (sorted(ord1))
    ans = min(ans, c1);
  if (sorted(ord2))
    ans = min(ans, c2);
  if (ans == inf)
    ans = -1;
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tests = 1;
  cin >> tests;
  while (tests--)
    solve();
}


// https://github.com/VaHiX/CodeForces/