// Problem: CF 1914 D - Three Activities
// https://codeforces.com/contest/1914/problem/D

/*
D. Three Activities

Purpose:
This program finds the maximum total number of friends that can join Monocarp for three different activities (skiing, movie, board games) over three distinct days.

Algorithm:
- For each activity (skiing, movie, board games), we select the top 3 days with maximum attendance.
- We then try all permutations of assigning these 3 activities to 3 distinct days.
- For each permutation, we greedily assign the best available day for each activity such that no day is reused.
- The maximum sum across all permutations is returned.

Time Complexity:
O(n log n + D! * D * n) where D=3, so effectively O(n log n + 6 * 3 * n) = O(n log n).

Space Complexity:
O(D * n) = O(3 * n) = O(n), for storing the vectors and permutations.

Techniques:
- Sorting with reverse iterator to get top elements.
- Permutations via std::next_permutation.
- Greedy assignment with a set to track used days.
*/

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
#include <utility>

int main() {
  const int D = 3; // Number of activities
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::vector<std::pair<long, long>>> w(
        D, std::vector<std::pair<long, long>>(D));
    // For each activity, store pairs of (attendance, day_index)
    for (long d = 0; d < D; d++) {
      std::vector<std::pair<long, long>> v(n);
      for (long p = 0; p < n; p++) {
        scanf("%ld", &v[p].first);
        v[p].second = p;
      }
      sort(v.rbegin(), v.rend()); // Sort in descending order of attendance
      for (int p = 0; p < D; p++) {
        w[d][p] = v[p]; // Store top D days for each activity
      }
    }
    std::vector<int> m(3);
    m[0] = 0;
    m[1] = 1;
    m[2] = 2;
    long mx(0);
    do {
      std::set<long> taken; // Track which days have been assigned
      long total(0);
      for (long q = 0; q < D; q++) {
        long idx = m[q]; // idx is the activity index
        for (long r = 0; r < D; r++) {
          if (taken.count(w[idx][r].second)) {
            continue; // Skip if day already taken
          }
          taken.insert(w[idx][r].second); // Mark day as used
          total += w[idx][r].first; // Add the attendance count
          break;
        }
      }
      mx = (mx > total) ? mx : total; // Keep track of maximum total
    } while (next_permutation(m.begin(), m.end())); // Try all permutations of activity assignments
    printf("%ld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/