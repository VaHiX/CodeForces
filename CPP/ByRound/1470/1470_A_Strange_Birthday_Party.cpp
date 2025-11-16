// Problem: CF 1470 A - Strange Birthday Party
// https://codeforces.com/contest/1470/problem/A

/*
Algorithm/Technique: Greedy approach with sorting
Time Complexity: O(n log n + m)
Space Complexity: O(n + m)

The problem can be solved using a greedy strategy:
1. For each friend, we have two options:
   - Give them a present with cost c[k_i] (if k_i is valid index)
   - Give them k_i dollars directly (which is c[k_i] if k_i is a valid index)

2. To minimize cost:
   - We sort the k values in descending order to process the friends with the highest requirements first.
   - For each friend, we choose between giving a present or giving k_i dollars.
   - Since prices are sorted in ascending order, the best option is to use the minimum among:
     - Present cost: c[k_i]
     - Direct money: c[k_i]

3. Optimization: 
   - We can optimize by noting that we always want to buy the cheapest available present for each friend.
   - The choice is to buy or not, but since k_i represents an upper limit for how many presents we can access,
     we can think of choosing c[k_i] as a valid present or c[k_i] dollars.
   - We sort the k values in descending order so we process large ones first.
   - The key insight is that to get minimum cost for each, we should compare the direct cost
     (i.e., c[kv[p]]) to the cost of the present (i.e., c[idx]).
     And we can do this in such a way that index idx = min(p, kv[p]) works.

Note: The actual logic is to assign the cheapest possible valid present to a friend,
      but due to sorting, the indices are carefully used.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<ll> kv(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &kv[p]);
      --kv[p]; // Convert to 0-based indexing
    }
    sort(kv.rbegin(), kv.rend()); // Sort in descending order
    std::vector<ll> c(m);
    for (ll p = 0; p < m; p++) {
      scanf("%lld", &c[p]);
    }
    ll res(0);
    for (ll p = 0; p < n; p++) {
      ll idx = (p < kv[p]) ? p : kv[p]; 
      // idx represents the cheapest valid present we can offer to friend p
      res += c[idx];
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/CodeForces/