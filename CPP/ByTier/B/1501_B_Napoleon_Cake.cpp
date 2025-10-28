// Problem: CF 1501 B - Napoleon Cake
// https://codeforces.com/contest/1501/problem/B

#include <cstdio>
#include <vector>
// Problem: B. Napoleon Cake
// Time Complexity: O(n) per test case
// Space Complexity: O(n) for the vector storage
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
    long rem(0), cnt(0);
    // Traverse from the top (last layer) to bottom
    for (long p = n - 1; p >= 0; p--) {
      // Update remaining cream that will drench future layers
      rem = (rem > a[p]) ? rem : a[p];
      // Set current layer as drenched if there's still cream to apply
      a[p] = (rem > 0);
      // Decrease the amount of cream available for next layer
      --rem;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/