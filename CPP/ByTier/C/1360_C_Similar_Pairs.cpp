// Problem: CF 1360 C - Similar Pairs
// https://codeforces.com/contest/1360/problem/C

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());
    bool odds(true), nxt(false);
    // 'odds' tracks if we have odd count of odd numbers so far, 
    // 'nxt' checks for consecutive elements (which are similar)
    for (long p = 0; p < n; p++) {
      if (a[p] & 1) {     // if current number is odd
        odds = !odds;     // toggle the odds flag
      }
      if (p > 0 && a[p] == a[p - 1] + 1) {   // if current element is consecutive to previous
        nxt = true;    // set flag indicating consecutive pair exists
      }
    }
    puts((odds || nxt) ? "YES" : "NO"); // if odd count of odds OR consecutive elements exist, YES
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/