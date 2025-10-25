// Problem: CF 1602 B - Divine Array
// https://codeforces.com/contest/1602/problem/B

#include <cstdio>
#include <map>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1); // Initialize array with 1-based indexing
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<std::vector<long>> v; // Store all transformations up to convergence
    v.push_back(a); // Add initial array to list of transformations
    bool done(false);
    while (!done) {
      std::map<long, long> m; // Count occurrences of each element in current array
      for (long p = 1; p <= n; p++) {
        ++m[a[p]];
      }
      std::vector<long> b(n + 1); // New array after one transformation step
      bool chg(false); // Flag to track whether any change occurred
      for (long p = 1; p <= n; p++) {
        b[p] = m[a[p]]; // Set each element to its count in current array
        if (b[p] != a[p]) { // If value changed, set flag
          chg = true;
        }
      }
      if (!chg) { // No change means we've reached a stable state
        done = true;
      }
      v.push_back(b); // Add the new array to the list of transformations
      a = b; // Update a for next iteration
    }
    long q;
    scanf("%ld", &q);
    while (q--) {
      long x, k;
      scanf("%ld %ld", &x, &k);
      if (k >= v.size()) { // If k is beyond the computed transformations, use last one
        k = v.size() - 1;
      }
      printf("%ld\n", v[k][x]); // Print value at xth index after k steps
    }
  }
}

// https://github.com/VaHiX/codeForces/