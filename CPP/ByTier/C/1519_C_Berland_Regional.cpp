// Problem: CF 1519 C - Berland Regional
// https://codeforces.com/contest/1519/problem/C

/*
C. Berland Regional
Algorithms/Techniques: Sorting, Prefix sums, Greedy approach

Time Complexity: O(n^2) in the worst case per test case due to nested loops,
but with optimizations and constraints, it is efficient enough for n <= 2*10^5.
Space Complexity: O(n^2) in the worst case for storing teams per university.

Polycarp is an organizer of a Berland ICPC regional event. There are n universities
in Berland numbered from 1 to n. Polycarp knows all competitive programmers in the region.
There are n students: the i-th student is enrolled at a university u_i and has a programming skill s_i.

Polycarp needs to decide on the rules of team formation:
- If the team size is k, each university will send their k strongest students
  in batches until there aren't enough students.
- The strength of the region is total skill of all members of present teams.

Approach:
1. Group students by university.
2. For each university, sort students' skills in descending order.
3. Use prefix sums for efficient calculation of team strengths.
4. For each possible team size k from 1 to n, calculate how many full teams can be formed
   and compute their total strength using prefix sums.
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
    std::vector<std::pair<ll, ll>> w(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &w[p].first);   // University number
    }
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &w[p].second);  // Skill value
    }
    std::vector<std::vector<ll>> s(n + 1); // s[u] stores skills of students from university u
    for (ll p = 0; p < n; p++) {
      s[w[p].first].push_back(w[p].second);
    }
    for (ll p = 1; p <= n; p++) {
      sort(s[p].begin(), s[p].end());  // Sort in ascending order
    }
    std::vector<ll> res(n + 1, 0);       // result array for team sizes from 1 to n

    // Process each university's list of students
    for (ll u = 1; u <= n; u++) {
      if (s[u].size() <= 0) {
        continue;
      }
      // Compute prefix sums
      for (ll p = 1; p < s[u].size(); p++) {
        s[u][p] += s[u][p - 1];
      }

      ll sum = s[u].back();                   // Total sum of skills for this university
      for (ll p = 1; p <= s[u].size(); p++) { // For each team size
        ll leftout = s[u].size() % p;         // Number of students left over after forming full teams
        res[p] += (sum - (leftout > 0 ? s[u][leftout - 1] : 0));
      }
    }

    for (ll p = 1; p <= n; p++) {
      printf("%lld ", res[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/