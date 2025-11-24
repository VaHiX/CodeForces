// Problem: CF 2106 C - Cherry Bomb
// https://codeforces.com/contest/2106/problem/C

/*
C. Cherry Bomb
Algorithms/Techniques: Two-pointer technique, math
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to count the number of ways to replace -1s in array b such that arrays a and b are complementary.
That is, for all i, a[i] + b[i] = x for some constant x. 

We can compute the minimum and maximum possible values for x based on constraints:
- For each element where b[i] != -1, we know a[i] + b[i] = x, so x = a[i] + b[i].
- For elements where b[i] == -1, we must determine valid ranges for b[i] such that a[i] + b[i] still equals x.

We precompute bounds on x:
- left: the minimum possible value of x across all valid configurations.
- right: the maximum possible value of x across all valid configurations.

We then calculate how many valid values of x satisfy all constraints, which gives us 1 + (right - left) number of valid arrays b.

This solution uses two pointers to efficiently compute min and max x values by processing each index once.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long left(0), right(2 * k); // Initialize bounds for valid x
    for (long p = 0; p < n; p++) {
      long curleft = a[p] + (b[p] < 0 ? 0 : b[p]); // Minimum possible x when we fix current a[p] and set b[p]=0 if missing
      left = (left > curleft ? left : curleft);     // Update left bound
      long curright = a[p] + (b[p] < 0 ? k : b[p]); // Maximum possible x when we fix a[p] and set b[p]=k if missing
      right = (right < curright ? right : curright); // Update right bound
    }
    long ans(left <= right ? (right - left + 1) : 0); // If valid range exists, count valid values; otherwise zero
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/