// Problem: CF 1380 C - Create The Teams
// https://codeforces.com/contest/1380/problem/C

/*
C. Create The Teams
Algorithm: Greedy approach.
Time Complexity: O(n log n) per test case due to sorting, where n is the number of programmers.
Space Complexity: O(n) for storing the skill array.

The problem asks to form the maximum number of teams such that each team satisfies:
(team_size * min_skill_in_team) >= x.
We use a greedy strategy:
1. Sort the skills in descending order.
2. For each element, try to form a team by including as many programmers as possible 
   such that the minimum skill in the current group multiplied by its size is at least x.
3. Count valid teams formed this way.

This greedy approach works because choosing larger skills first minimizes the chance of 
falling below the required threshold for the number of members needed.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, x;
    scanf("%lld %lld", &n, &x);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    sort(a.rbegin(), a.rend()); // Sort skills in descending order
    ll num(0), cnt(0);
    for (long p = 0; p < a.size(); p++) {
      ++cnt; // Increment count of programmers in current team
      if (cnt * a[p] >= x) { // Check if team satisfies the condition
        ++num; // A valid team is formed
        cnt = 0; // Reset counter for next team
      }
    }
    printf("%lld\n", num);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/