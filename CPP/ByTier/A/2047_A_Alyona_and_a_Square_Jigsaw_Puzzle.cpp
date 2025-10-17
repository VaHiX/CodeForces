// Problem: CF 2047 A - Alyona and a Square Jigsaw Puzzle
// https://codeforces.com/contest/2047/problem/A

/*
A. Alyona and a Square Jigsaw Puzzle
Algorithms/Techniques: Prefix sum, set lookup
Time Complexity: O(n * sqrt(max_sum)) where max_sum <= 10^7
Space Complexity: O(sqrt(max_sum)) for the set storing perfect squares

This problem simulates assembling a square jigsaw puzzle where each day
Alyona adds pieces in layers. A layer is complete when the number of pieces
added equals a perfect square (1, 4, 9, 16, ...). The task is to count how many
days result in a complete layer being finished.

We precompute all possible perfect squares up to the maximum possible sum
and store them in a set for fast lookup.
For each test case, we maintain a running prefix sum of pieces added.
Each time we add pieces on a day, if the cumulative sum is a perfect square,
we increment our happiness counter.

Key points:
- The first piece (day 1) always starts the first layer (1 piece)
- Layers are completed in perfect square counts
- A day is happy if the prefix sum becomes a perfect square after that day's pieces
*/

#include <cstdio>
#include <set>
int main() {
  std::set<long> s;
  // Precompute all perfect squares up to 107^2 = 11449
  for (long p = 1; p <= 107; p += 2) {
    s.insert(p * p);  // Insert odd square numbers (1, 9, 25, ...)
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0), cs(0);  // cnt: happiness counter, cs: cumulative sum
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      cs += x;         // Add pieces from current day to cumulative total
      cnt += s.count(cs);  // If cs is a perfect square, increment happiness counter
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/