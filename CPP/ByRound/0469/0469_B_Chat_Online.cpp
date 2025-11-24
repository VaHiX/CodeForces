// Problem: CF 469 B - Chat Online
// https://codeforces.com/contest/469/problem/B

/*
Algorithm: Brute Force with Interval Overlap Checking
Approach:
- For each possible time k from l to r (inclusive), check if there exists at least one overlapping interval
  between Little Z's fixed schedule and Little X's schedule shifted by k.
- Little Z's schedule is fixed: [a1, b1], [a2, b2], ..., [ap, bp]
- Little X's schedule is dynamic: [c1+k, d1+k], [c2+k, d2+k], ..., [cq+k, dq+k]
- Two intervals [x1, x2] and [y1, y2] overlap if not (x2 < y1 or y2 < x1)

Time Complexity: O((r - l + 1) * p * q)
Space Complexity: O(p + q)

The algorithm checks for every possible wake-up time k in [l, r], and for each such k,
it computes the shifted intervals of Little X and compares them against all fixed intervals
of Little Z to see if any pair overlaps.

*/

#include <cstdio>
#include <vector>
#include <utility>

int main() {
  int p, q, l, r;
  scanf("%d %d %d %d", &p, &q, &l, &r);
  std::vector<std::pair<int, int>> fixed;
  std::vector<std::pair<int, int>> changing;
  for (int k = 0; k < p; k++) {
    int a, b;
    scanf("%d %d", &a, &b);
    fixed.push_back(std::pair<int, int>(a, b));
  }
  for (int k = 0; k < q; k++) {
    int a, b;
    scanf("%d %d", &a, &b);
    changing.push_back(std::pair<int, int>(a, b));
  }
  bool done;
  int output(0);
  for (int k = l; k <= r; k++) {
    done = 0;
    for (int x = 0; x < fixed.size(); x++) {
      if (done) {
        continue;
      }
      for (int y = 0; y < changing.size(); y++) {
        // Check if intervals [fixed[x].first, fixed[x].second] and 
        // [k + changing[y].first, k + changing[y].second] overlap
        if ((fixed[x].second < k + changing[y].first) ||
            (k + changing[y].second < fixed[x].first)) {
          continue;
        } else {
          done = 1;
          ++output;
          break;
        }
      }
    }
  }
  printf("%d\n", output);
  return 0;
}


// https://github.com/VaHiX/CodeForces/