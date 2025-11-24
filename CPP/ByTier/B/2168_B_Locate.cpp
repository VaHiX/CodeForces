// Problem: CF 2168 B - Locate
// https://codeforces.com/contest/2168/problem/B

/*
 * Problem: Locate
 * Algorithm: Binary search with pre-processing
 * 
 * Approach:
 * - First run (Player A): Determine x based on relative positions of n and 1
 * - Second run (Player B): Use binary search to find position of n based on x value
 * 
 * Time Complexity: O(n log n) for first run (preprocessing) + O(log n) for second run
 * Space Complexity: O(1) - only using a few variables
 *
 * Strategy:
 * - Player A: Check if n occurs before or after position of 1 in permutation
 *   - If n is before 1, send 0
 *   - If n is after 1, send 1
 * - Player B: 
 *   - If x=0: Binary search from left to find position using query range [1, med]
 *   - If x=1: Binary search from right to find position using query range [med, n]
 */

#include <iostream>
#include <string>

using namespace std;
using ll = long long;
const int mod = 998244353;
const int block_size = 7;
string run_id;
string s;
int query(int st, int dr) {
  cout << "? " << st << " " << dr << endl;
  int r;
  cin >> r;
  return r;
}
int target;
int bin_src_dr(int st, int dr) {
  int med, poz = dr;
  while (st <= dr) {
    int med = (st + dr) >> 1;
    if (query(1, med) == target) {  // Check if max-min in range [1, med] equals target
      poz = med;
      dr = med - 1;
    } else
      st = med + 1;
  }
  return poz;
}
int bin_src_st(int st, int dr) {
  int med, poz = 1;
  while (st <= dr) {
    int med = (st + dr) >> 1;
    if (query(med, target + 1) == target) {  // Check if max-min in range [med, target+1] equals target
      poz = med;
      st = med + 1;
    } else
      dr = med - 1;
  }
  return poz;
}
int main() {
  int n, i, t, x, y, k;
  cin >> run_id;
  if (run_id == "first") {
    cin >> t;
    while (t--) {
      cin >> n;
      int p, p1;
      for (i = 1; i <= n; i++) {
        cin >> x;
        if (x == n)
          p = i;   // Store position of n
        if (x == 1)
          p1 = i;  // Store position of 1
      }
      if (p <= p1)
        cout << "0\n";  // If n occurs before or at same position as 1, send 0
      else
        cout << "1\n";  // If n occurs after 1, send 1
    }
  } else {
    cin >> t;
    int f;
    while (t--) {
      cin >> n >> f;
      target = n - 1;  // target represents difference between max and min in range
      if (!f) {
        int rez = bin_src_st(1, n);  // Binary search from left
        cout << "! " << rez << endl;
      } else {
        int rez = bin_src_dr(1, n);  // Binary search from right
        cout << "! " << rez << endl;
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/