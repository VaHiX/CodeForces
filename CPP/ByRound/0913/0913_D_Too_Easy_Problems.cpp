// Problem: CF 913 D - Too Easy Problems
// https://codeforces.com/contest/913/problem/D

/*
Problem: D. Too Easy Problems
Purpose: Maximize the final score in a scheduling problem with time and difficulty constraints.
Algorithm: Binary search on the answer combined with greedy selection of problems.
Time Complexity: O(n * log(n) + n * log(n)) due to sorting and binary search over the number of solved problems.
Space Complexity: O(n) for storing problem information and result.

The idea is to determine the maximum number of points we can achieve by:
1. Sorting problems by time needed (ascending).
2. Using binary search on the number of points (number of problems to solve).
3. For each candidate number of points, we greedily select problems that:
   - Allow us to get at least that many points (a_i >= number of points).
   - Fit within the time limit.
   - Are selected in ascending order of time to maximize the chance of fitting more in the same time.

This greedy selection ensures maximum possible score for a given number of problems to solve.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

struct prob {
  ll a, t, r; // a: maximum number of problems allowed to be solved to get point, t: time needed, r: problem index
};

// Compare function to sort by time needed
bool cmp(prob A, prob B) { return A.t < B.t; }

// Function to check if we can solve at least 's' problems with 's' points under time 'T'
std::vector<prob> check(const std::vector<prob> v, const ll T, const ll s) {
  ll rt(T), cnt(0);
  std::vector<prob> res;
  for (long p = 0; p < v.size(); p++) {
    if (v[p].a < s) {
      continue; // Skip problems that cannot contribute to the current score (s points)
    }
    if (v[p].t > rt) {
      break; // No more problems can fit within time limit
    }
    ++cnt;
    rt -= v[p].t;
    res.push_back(v[p]);
    if (cnt >= s) {
      break; // We've collected enough problems for this score target
    }
  }
  return res;
}

int main() {
  ll n, T;
  scanf("%lld %lld", &n, &T);
  std::vector<prob> v(n);
  for (long p = 0; p < n; p++) {
    scanf("%lld %lld", &v[p].a, &v[p].t);
    v[p].r = p + 1; // Store the index (1-based)
  }
  sort(v.begin(), v.end(), cmp); // Sort by time needed (ascending)

  ll left(0), right(n);
  std::vector<prob> solve;

  // Binary search on the possible number of points we can get
  while (left <= right) {
    ll mid = (left + right) / 2;
    std::vector<prob> cand = check(v, T, mid);
    if (cand.size() >= mid) {
      solve = cand;
      left = mid + 1; // Try for higher points
    } else {
      right = mid - 1; // Try for fewer points
    }
  }

  // Output result
  printf("%ld\n%ld\n", solve.size(), solve.size());
  for (long p = 0; p < solve.size(); p++) {
    printf("%lld ", solve[p].r);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/