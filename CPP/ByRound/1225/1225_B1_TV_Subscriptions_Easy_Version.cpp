// Problem: CF 1225 B1 - TV Subscriptions (Easy Version)
// https://codeforces.com/contest/1225/problem/B1

/*
==================================================
Problem: B1. TV Subscriptions (Easy Version)
Algorithm: Sliding window with map to track show occurrences
Time Complexity: O(n * d) where n is the number of days, d is the window size
Space Complexity: O(k) where k is the number of shows
==================================================
*/
#include <cstdio>
#include <map>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, d;
    scanf("%ld %ld %ld", &n, &k, &d);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::map<long, long> s; // stores show -> last seen index
    for (long p = 0; p < d; p++) {
      s[a[p]] = p; // populate initial window
    }
    long mn(s.size()); // minimum shows needed in first window
    for (long p = d; p < n; p++) {
      long rem = a[p - d]; // show that's sliding out of window
      long nxt = a[p];     // show that's sliding into window
      if (s[rem] == p - d) { // if this is the last occurrence of 'rem'
        s.erase(rem);        // remove it from map
      }
      s[nxt] = p; // add new element to map
      mn = (mn < s.size()) ? mn : s.size(); // update minimum
    }
    printf("%ld\n", mn);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/