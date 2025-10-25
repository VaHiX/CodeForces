// Problem: CF 1825 B - LuoTianyi and the Table
// https://codeforces.com/contest/1825/problem/B

/*
Problem: Maximize the sum of differences between max and min in all subtables
Algorithm: Greedy approach using sorting and strategic placement
Time Complexity: O(n*m*log(n*m)) due to sorting
Space Complexity: O(1) excluding input storage

The idea is to place elements strategically so that for each subtable,
we maximize the difference between maximum and minimum elements.
We sort all values, then assign the largest elements to positions where they 
can contribute most to the sum. A greedy method is used involving:
- Finding max and second max (for top-left corner)
- Finding min and second min (for bottom-right corner)  
- Calculating contribution of differences based on optimal placement

*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll mxf(-1e5 - 7), mxs(-1e5 - 7), mnf(1e5 + 7), mns(1e5 + 7);
    for (ll p = 0; p < m * n; p++) {
      ll a;
      scanf("%lld", &a);
      if (a >= mxf) {           // Update maximum and second maximum
        mxs = mxf;
        mxf = a;
      } else if (a > mxs) {
        mxs = a;
      }
      if (a <= mnf) {           // Update minimum and second minimum
        mns = mnf;
        mnf = a;
      } else if (a < mns) {
        mns = a;
      }
    }
    ll df(mxf - mnf), ds(mxf - mns);  // df: max difference, ds: another possible difference
    if (mxs - mnf > ds) {             // Update ds if needed
      ds = mxs - mnf;
    }
    // Compute final result based on strategic arrangement
    ll res = (m * n - 1) * df - (((m < n) ? m : n) - 1) * (df - ds);
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/