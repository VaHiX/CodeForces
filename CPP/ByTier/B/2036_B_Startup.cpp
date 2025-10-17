// Problem: CF 2036 B - Startup
// https://codeforces.com/contest/2036/problem/B

/*
B. Startup
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: Greedy + Map + Sorting
- For each brand, sum up the costs of all bottles of that brand (using a map).
- Sort the total costs of brands in descending order.
- Take the top 'n' brands and sum their costs to maximize profit.

Time Complexity: O(k log k) per test case, where k is the number of bottles.
Space Complexity: O(k) for storing bottle data and brand totals.

Input:
The first line contains one integer t (1≤t≤10^4) — the number of test cases.
The first line of each test case contains two integers n and k (1≤n,k≤2⋅10^5), where n is the number of shelves in the machine, and k is the number of bottles available to Arseniy.
The next k lines contain two integers b_i and c_i (1≤b_i≤k, 1≤c_i≤1000) — the brand and cost of the i-th bottle.

Output:
For each test case, output one integer — the maximum amount that Arseniy can earn.
*/

#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::map<ll, ll> m;  // Map to store total cost per brand
    for (ll p = 0; p < k; p++) {
      ll b, c;
      scanf("%lld %lld", &b, &c);
      m[b] += c;  // Accumulate cost for each brand
    }
    std::vector<ll> v;
    for (std::map<ll, ll>::iterator it = m.begin(); it != m.end(); it++) {
      v.push_back(it->second);  // Extract total costs of brands
    }
    sort(v.rbegin(), v.rend());  // Sort in descending order to get highest values first
    ll total(0);
    for (ll p = 0; p < v.size() && p < n; p++) {
      total += v[p];  // Add top 'n' brand totals to maximize profit
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/