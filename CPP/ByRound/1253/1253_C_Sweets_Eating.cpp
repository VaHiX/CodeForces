// Problem: CF 1253 C - Sweets Eating
// https://codeforces.com/contest/1253/problem/C

/*
C. Sweets Eating
Algorithms/Techniques: Greedy algorithm with prefix sums
Time Complexity: O(n log n)
Space Complexity: O(n)

The problem involves minimizing the total sugar penalty when eating k sweets over days,
where each sweet eaten on day d contributes d * a_i to the penalty. To minimize this,
we need to carefully assign sweets to days so that higher sugar sweets are eaten earlier.

Approach:
- Sort the array of sweets by their sugar concentration in ascending order.
- Use dynamic programming with prefix sums: 
  For each number of sweets k, we try assigning the first k sweets to minimize cost.
  We use a rolling window over m days, where at most m sweets can be eaten per day.
  The recurrence relation uses previous results to build up optimal costs for larger k.

The key insight is that we sort the array because eating higher sugar sweets later (in terms of day number)
reduces overall penalty — but we must respect the "at most m sweets per day" constraint.
We compute prefix sums and apply a sliding window over days to ensure we respect the m-sweets-per-day limit.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<ll> a(n);
  for (ll p = 0; p <= n; p++) { // Read all sweets' sugar concentrations
    scanf("%lld", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort by sugar concentration to apply greedy strategy
  ll cs(0);
  std::vector<ll> v(n);
  for (long p = 0; p < n; p++) { // Iterate through each number of sweets to eat
    cs += a[p]; // Running sum of sugar concentrations
    // v[p] = prefix sum + (if we have enough days, add cost from m days ago)
    v[p] = cs + ((p >= m) ? v[p - m] : 0); 
    printf("%lld ", v[p]);
  }
  puts("");
}


// https://github.com/VaHiX/codeForces/