// Problem: CF 1117 B - Emotes
// https://codeforces.com/contest/1117/problem/B

/*
B. Emotes
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the emotes

Algorithms/Techniques:
- Greedy approach with sorting
- Mathematical calculation to determine optimal usage pattern

The strategy is to sort emotes in descending order and then use the highest value emote as much as possible,
but respecting the constraint of using the same emote at most k times in a row. We break the sequence into groups
of (k+1) iterations where we use the highest emote k times followed by the second-highest once.

Key idea:
- Sort emotes in descending order to get the best values first.
- For each group of (k+1) uses: k times highest value + 1 time second highest.
- Handle remainder separately.

Sample Input:
6 9 2
1 3 3 7 4 2

Sample Output:
54
*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  std::vector<ll> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.rbegin(), a.rend()); // Sort in descending order to get highest values first
  ll total = (m / (k + 1)) * (k * a[0] + a[1]) + (m % (k + 1)) * a[0]; // Calculate maximum happiness
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/