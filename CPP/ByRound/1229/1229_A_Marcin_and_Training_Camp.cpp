// Problem: CF 1229 A - Marcin and Training Camp
// https://codeforces.com/contest/1229/problem/A

#include <cstdio>
#include <vector>
typedef long long ll;

/*
 * Problem: A. Marcin and Training Camp
 *
 * Purpose:
 *   Given n students, each with a skill vector 'a_i' (represented as a bitmask of 60 algorithms)
 *   and a skill level 'b_i', find the maximum sum of skill levels from a group of at least
 *   two students such that no student thinks they are better than all others in the group.
 *   A student x is "better" than student y if x knows some algorithm y does not know.
 *
 * Algorithm:
 *   - Use a greedy approach to iteratively remove "arrogant" students.
 *   - A student is arrogant if they are better than all other active students.
 *   - While there exists an arrogant student, remove them from the team and update the sum.
 *   - Return the final sum if at least two students remain; otherwise return 0.
 *
 * Time Complexity: O(n^2 * log(max(a_i))) where max(a_i) < 2^60 => ~O(n^2 * 60)
 * Space Complexity: O(n)
 */

// Check if student at index 'ind' is arrogant with respect to the current team
bool arrogant(ll ind, std::vector<ll> team) {
  const int B = 60;
  if (team[ind] < 0) {  // Student already removed
    return false;
  }
  for (ll p = 0; p < team.size(); p++) {
    if (team[p] < 0) {  // Skip removed students
      continue;
    }
    if (p == ind) {  // Skip self comparison
      continue;
    }
    ll a(team[ind]), b(team[p]);
    bool better(false);
    // Compare bits from LSB to MSB
    while (a > 0 || b > 0) {
      if ((a & 1) && (b % 2 == 0)) {  // a knows bit, b doesn't
        better = true;
        break;
      }
      a /= 2;
      b /= 2;
    }
    if (!better) {  // If student 'ind' is NOT better than student 'p'
      return false;
    }
  }
  return true;  // Student 'ind' is better than all others
}

int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n), b(n);
  ll sum(0), cnt(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &b[p]);
    sum += b[p];
  }
  bool done(false);
  // Greedily remove arrogant students
  while (!done) {
    done = true;
    for (ll p = 0; p < n; p++) {
      if (a[p] < 0) {  // Skip removed students
        continue;
      }
      if (arrogant(p, a)) {  // Check if student p is arrogant
        done = false;
        --cnt;
        a[p] = -1;  // Mark as removed
        sum -= b[p];  // Update total skill level
      }
    }
  }
  printf("%lld\n", cnt > 1 ? sum : 0);  // Print result if at least two students remain
  return 0;
}


// https://github.com/VaHiX/codeForces/