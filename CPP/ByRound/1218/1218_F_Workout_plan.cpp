// Problem: CF 1218 F - Workout plan
// https://codeforces.com/contest/1218/problem/F

#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;
/*
F. Workout plan

Algorithm: Greedy with Multiset
- For each day, we check if Alan can lift the required weight.
- If not, we must buy a drink from the cheapest available gym (using multiset).
- We always greedily buy the cheapest drink that allows us to proceed.
- Time Complexity: O(N log N) due to multiset operations.
- Space Complexity: O(N) for storing daily costs.

Input format:
- N days, initial lifting capacity K
- Required weights X[i] for each day
- Permanent gain A from each drink
- Cost C[i] of drink at each gym

Output:
- Minimum total cost to complete plan, or -1 if impossible
*/
int main() {
  ll n, cur;
  scanf("%lld %lld", &n, &cur);
  std::vector<ll> w(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &w[p]);
  }
  ll a;
  scanf("%lld", &a);
  std::vector<ll> d(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &d[p]);
  }
  ll cost(0);
  bool possible(true);
  std::multiset<ll> s;
  for (ll p = 0; p < n; p++) {
    s.insert(d[p]); // Insert current gym's drink cost into multiset
    while ((!s.empty()) && (cur < w[p])) { // While we can't lift required weight
      cur += a; // Buy the cheapest available drink
      cost += *(s.begin()); // Add its cost to total
      s.erase(s.begin()); // Remove it from available options
    }
    if (cur < w[p]) { // If still unable to lift
      possible = false;
      break;
    }
  }
  printf("%lld\n", possible ? cost : -1);
  return 0;
}

// https://github.com/VaHiX/codeForces/