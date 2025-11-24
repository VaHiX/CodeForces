// Problem: CF 2122 C - Manhattan Pairs
// https://codeforces.com/contest/2122/problem/C

/*
C. Manhattan Pairs
Algorithms/Techniques: Sorting, Greedy pairing strategy based on x and y coordinates.
Time Complexity: O(n log n) per test case due to sorting operations.
Space Complexity: O(n) for storing the points and pairs.

Problem Description:
Given n points (xi, yi) on a 2D plane where n is even, select n/2 disjoint pairs 
to maximize the sum of Manhattan distances between paired points.
Manhattan distance between two points (x1,y1) and (x2,y2) is |x1-x2| + |y1-y2|.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

bool paircompare(std::pair<std::pair<long, long>, long> a,
                 std::pair<std::pair<long, long>, long> b) {
  return a.first.second < b.first.second; // Compare y-coordinates for sorting
}

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<std::pair<long, long>, long>> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld %ld", &v[p].first.first, &v[p].first.second); // Read x and y coordinates
      v[p].second = p + 1; // Store original index
    }
    sort(v.begin(), v.end()); // Sort all points by x-coordinate (and then y if x is same)
    sort(v.begin(), v.begin() + n / 2, paircompare); // Sort first half by y-coordinate
    sort(v.begin() + n / 2, v.end(), paircompare); // Sort second half by y-coordinate
    for (long p = 0; p < n / 2; p++) {
      printf("%ld %ld\n", v[p].second, v[n - 1 - p].second); // Pair points from both halves
    }
  }
}


// https://github.com/VaHiX/codeForces/