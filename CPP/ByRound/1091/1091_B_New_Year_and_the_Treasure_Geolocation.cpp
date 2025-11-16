// Problem: CF 1091 B - New Year and the Treasure Geolocation
// https://codeforces.com/contest/1091/problem/B

// Problem: New Year and the Treasure Geolocation
// Purpose: Given n obelisks and n clues, find the unique treasure location T such that
//          each clue (a_j, b_j) points from some obelisk (x_i, y_i) to T.
//          That is, T = (x_i + a_j, y_i + b_j) for some permutation of obelisks/clues.
// Algorithm: For all combinations of obelisk i and clue j, compute candidate treasure position
//            as (x_i + a_j, y_i + b_j). Count how many times each candidate appears.
//            The treasure location is the one that appears most frequently.
// Time Complexity: O(n^2)
// Space Complexity: O(n^2)

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::pair<long, long>> s(n); // obelisks
  for (long p = 0; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    s[p] = std::make_pair(x, y);
  }
  std::vector<std::pair<long, long>> t(n); // clues
  for (long p = 0; p < n; p++) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    t[p] = std::make_pair(a, b);
  }
  std::map<std::pair<long, long>, long> cnt; // count of each candidate treasure location
  long maxcnt(0); // maximum count so far
  std::pair<long, long> ans; // answer (treasure location)
  for (long p = 0; p < n; p++) {
    for (long q = 0; q < n; q++) {
      long u = s[p].first + t[q].first;   // compute x-coordinate of candidate
      long v = s[p].second + t[q].second; // compute y-coordinate of candidate
      std::pair<long, long> cand = std::make_pair(u, v); // candidate treasure position
      if (!cnt.count(cand)) {
        cnt[cand] = 0;
      }
      ++cnt[cand]; // increment count for this candidate
      if (cnt[cand] > maxcnt) { // update maximum if needed
        maxcnt = cnt[cand];
        ans = cand;
      }
    }
  }
  printf("%ld %ld\n", ans.first, ans.second);
  return 0;
}


// https://github.com/VaHiX/codeForces/