// Problem: CF 1541 B - Pleasant Pairs
// https://codeforces.com/contest/1541/problem/B

/*
B. Pleasant Pairs

Algorithm: For each test case, we process an array of distinct integers and count pairs (i,j) such that i < j and a[i] * a[j] = i + j.
Approach:
1. For each element, store its value and original index.
2. Sort the array by value.
3. For each pair (p,q) with p < q in sorted order:
   - If a[p].first * a[q].first > 2*n, break (since further elements will only be larger).
   - Otherwise, check if a[p].first * a[q].first == a[p].second + a[q].second.
Time Complexity: O(n^2) per test case in worst case; however, due to constraints and sorting, it's efficient enough for given limits.
Space Complexity: O(n) for storing the pairs.

Input:
- t (number of test cases)
- For each test case:
  - n (length of array)
  - n integers a_1, ..., a_n

Output:
- Number of pairs (i,j) such that i < j and a[i] * a[j] = i + j
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::pair<ll, ll>> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p].first);   // Read the value
      a[p].second = p + 1;          // Store the original index (1-based)
    }
    sort(a.begin(), a.end());       // Sort by values
    ll cnt(0);
    for (ll p = 0; p < n; p++) {
      for (ll q = p + 1; q < n; q++) {
        if (a[p].first * a[q].first > 2 * n) {  // Early termination: product exceeds possible sum
          break;
        }
        cnt += (a[p].first * a[q].first == a[p].second + a[q].second);  // Check condition
      }
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/