// Problem: CF 1856 D - More Wrong
// https://codeforces.com/contest/1856/problem/D

/*
Algorithm: Binary search with inversion counting
Approach:
- Use a recursive divide and conquer strategy to find the maximum element.
- At each step, we split the array into two halves and recursively find the maximum in the left half.
- Then we query the number of inversions in subarrays involving the current maximum candidate.
- The key insight is that if we have the maximum element at position pos_max, 
  then the number of inversions in the subarray [pos_max, r] will be exactly (r - pos_max), 
  because all elements to the right of pos_max are greater than it and contribute 1 inversion each.
Time Complexity: O(n log n) - for each of the log n levels, we do O(n) work in queries
Space Complexity: O(log n) - recursion stack depth
*/

#include <iostream>
#include <random>

using namespace std;
template <class T> bool minimum(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T> bool maximum(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}
#define bit(mask, i) ((mask >> i) & 1)
#define cntbit(mask) __builtin_popcountll(mask)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define uniquev(v) sort(all(v)), (v).resize(unique(all(v)) - (v).begin())
#define sz(s) (int)s.size()
#define __lcm(a, b) ((int64_t)a / __gcd(a, b) * b)
const int MAXN = 1e6 + 10;
const int MAXM = 1e6 + 10;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int DX[] = {};
const int DY[] = {};
int ask(int l, int r) {
  if (l == r)
    return 0;
  cout << "? " << l << " " << r << endl;
  int p;
  cin >> p;
  return p;
}
int dp(int l, int r) {
  if (l == r)
    return l;
  int m = l + r >> 1; // Midpoint of current segment
  int pos_max = dp(l, m); // Recursively find max in left half
  if (ask(pos_max, r) - ask(pos_max + 1, r) == r - pos_max)
    // If inversion count difference equals number of elements from pos_max to r,
    // it means pos_max is indeed the maximum in this segment
    return pos_max;
  return dp(m + 1, r); // Otherwise, max is in right half
}
void etohari() {
}
signed main() {
  int test = 1;
  int n;
  int ans;
  
  cin >> test;
  for (int i_test = 1; i_test <= test; i_test++) {
    cin >> n;
    ans = dp(1, n);
    cout << "! " << ans << endl;
  }
  return (0 ^ 0);
}


// https://github.com/VaHiX/CodeForces/