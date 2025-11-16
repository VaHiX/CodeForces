// Problem: CF 1343 C - Alternating Subsequence
// https://codeforces.com/contest/1343/problem/C

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll sum(0); // Initialize sum to accumulate the maximum alternating subsequence sum
    ll cur; // Current element in the sequence being processed
    scanf("%lld", &cur); // Read first element
    for (ll p = 1; p < n; p++) { // Loop through remaining elements
      ll x;
      scanf("%lld", &x); // Read next element
      if (cur * x > 0) { // If current and next have same sign
        cur = (cur > x) ? cur : x; // Keep the larger (in absolute value) to maximize sum
      } else { // If signs differ (alternating)
        sum += cur; // Add previous element to sum
        cur = x; // Start new segment with current element
      }
    }
    sum += cur; // Add last element to total sum
    printf("%lld\n", sum);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/