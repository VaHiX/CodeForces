// Problem: CF 1955 D - Inaccurate Subsequence Search
// https://codeforces.com/contest/1955/problem/D

/*
Purpose: 
This code solves the "Inaccurate Subsequence Search" problem. Given two arrays a and b, 
and a parameter k, the goal is to count how many subsegments of array a of length m 
can be rearranged so that at least k elements match elements in array b.

Algorithm:
- Sliding window technique with frequency counting.
- For each subsegment of length m in array a, we check if at least k elements 
  can be matched with elements in array b by using frequency maps.
- A window of size m slides over array a, and we maintain the frequency of elements 
  in the current window. We compare this frequency with that of array b to determine 
  if k or more matches are possible.

Time Complexity: O(n + m)
Space Complexity: O(max_element in a and b)

The sliding window maintains the count of elements in the current segment and 
compares it with the count in array b to determine how many elements can be matched.
*/
#include <stdint.h>
#include <iostream>
#include <utility>

using namespace std;
#ifdef MIKU
string dbmc = "\033[1;38;2;57;197;187m", dbrs = "\033[0m";
#define debug(x...) cout << dbmc << "[" << #x << "]: ", dout(x)
void dout() { cout << dbrs << endl; }
template <typename T, typename... U> void dout(T t, U... u) {
  cout << t << (sizeof...(u) ? ", " : "");
  dout(u...);
}
#else
#define debug(...) 39
#endif
#define fs first
#define sc second
#define mp make_pair
#define FOR(i, j, k) for (int i = j, Z = k; i < Z; i++)
using ll = long long;
typedef pair<int, int> pii;
const int MXN = 200005;
int n, m, k, a[MXN], b[MXN];
int c[MXN * 5], d[MXN * 5]; // c stores frequency of b, d stores frequency of current window in a
int acc; // tracks how many elements in current window match the required count from b
void ADD(int x) {
  if (++d[x] <= c[x]) // if adding this element doesn't exceed b's count for x
    acc++;
}
void REM(int x) {
  if (--d[x] < c[x]) // if removing this element makes count less than b's
    acc--;
}
int calc() { return (acc >= k); } // check if at least k elements match
void miku() {
  cin >> n >> m >> k;
  FOR(i, 0, n) cin >> a[i];
  FOR(i, 0, m) cin >> b[i];
  FOR(i, 0, m) c[b[i]]++; // build frequency map for b
  FOR(i, 0, m) { ADD(a[i]); } // initialize the first window
  int ans = calc(); // check if first window is good
  FOR(i, 0, n - m) {
    REM(a[i]); // remove leftmost element from window
    ADD(a[i + m]); // add new rightmost element to window
    ans += calc(); // increment answer if window is good
  }
  cout << ans << '\n';
}
void RESET() {
  FOR(i, 0, n) {
    c[a[i]] = 0; // reset the frequency array for a
    d[a[i]] = 0;
    c[b[i]] = 0; // reset the frequency array for b
    d[b[i]] = 0;
  }
  acc = 0;
}
int32_t main() {
  cin.tie(0)->sync_with_stdio(false);
  cin.exceptions(cin.failbit);
  int t;
  cin >> t;
  while (t--) {
    miku();
    RESET();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/