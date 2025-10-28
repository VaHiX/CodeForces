// Problem: CF 1196 B - Odd Sum Segments
// https://codeforces.com/contest/1196/problem/B

/*
B. Odd Sum Segments
Algorithms/Techniques: Greedy, parity analysis
Time Complexity: O(n) per query
Space Complexity: O(n) per query

The problem requires splitting an array into exactly k non-empty subsegments such that each has an odd sum.
Key observations:
1. For a segment to have an odd sum, it must contain an odd number of odd elements.
2. If we have k segments and want each to be odd-sum, we might need at least k odd numbers in total.
3. If the total sum is even but k is odd, impossible.
4. We greedily find first k-1 odd positions and make cuts there, then put the final cut at the end.
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> a(n);
    ll sum(0);
    for (ll p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read array elements
      sum += a[p];
    }
    std::vector<ll> res;
    for (ll p = 0; p < n; p++) {
      if (res.size() >= k - 1) { // We only need k-1 cuts, so stop once we have them
        break;
      }
      if (a[p] % 2) { // If element is odd, we can consider making a cut before it
        res.push_back(p + 1); // Store 1-based index
      }
    }
    res.push_back(n); // The last segment must go to the end of array
    
    // Check feasibility:
    // 1. Not enough odd numbers if k is even and total sum is even (impossible)
    // 2. Not enough segments in result to make k segments
    if (((k % 2) ^ (sum % 2)) || res.size() < k) {
      puts("NO");
      continue;
    }
    puts("YES");
    for (ll p = 0; p < res.size(); p++) {
      printf("%lld ", res[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/