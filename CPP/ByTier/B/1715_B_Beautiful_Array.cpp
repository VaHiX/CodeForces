// Problem: CF 1715 B - Beautiful Array
// https://codeforces.com/contest/1715/problem/B

/*
Purpose: This code solves the "Beautiful Array" problem where we need to construct an array of n non-negative integers 
         such that:
         1. The sum of elements equals s.
         2. The "beauty" of the array (sum of floor(a[i]/k)) equals b.

Algorithms/Techniques:
- Greedy approach to build the array.
- First calculate minimum and maximum possible values for b based on constraints.
- Then greedily assign values to elements, maximizing the contribution of each element to the beauty while respecting sum constraint.

Time Complexity: O(n) per test case, as we iterate through array elements once.
Space Complexity: O(1) excluding input/output storage, since we use a fixed number of variables.

*/
#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k, b, s;
    scanf("%lld %lld %lld %lld", &n, &k, &b, &s);
    // Calculate minimum and maximum possible value of b given the constraints
    long mn = (s - (n - 1) * (k - 1)) / k;
    long mx = s / k;
    // If b is not within valid range, impossible to construct array
    if (b < mn || mx < b) {
      puts("-1");
      continue;
    }
    // Start with a large value for first element to contribute enough to reach 'b'
    ll cur = b * k + k - 1;
    // Adjust cur to not exceed total sum s
    cur = (s < cur) ? s : cur;
    printf("%lld ", cur);
    ll rem(s - cur); // Remaining sum to be distributed among other elements
    for (long p = 1; p < n; p++) {
      // Assign maximum possible value (k-1) to remaining elements
      cur = (rem < (k - 1)) ? rem : (k - 1);
      rem -= cur;
      printf("%lld ", cur);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/