// Problem: CF 1466 B - Last minute enhancements
// https://codeforces.com/contest/1466/problem/B

#include <cstdio>
#include <vector>
// Problem: Maximize diversity of a musical note sequence by increasing notes by at most 1.
// Algorithm: Greedy approach - process from right to left, incrementing a note if it can be increased without conflict.
// Time Complexity: O(n) per test case, where n is the length of the song.
// Space Complexity: O(n) for storing the sequence.
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long cnt(1); // Start with count of 1 since at least one element exists
    ++a[n - 1]; // Increment the last element to potentially increase diversity
    for (long p = n - 2; p >= 0; p--) {
      // If current note + 1 is less than next note, we can increment it to maintain uniqueness
      if (a[p] + 1 < a[p + 1]) {
        ++a[p];
        ++cnt;
      } else if (a[p] < a[p + 1]) {
        // If current note is less but not enough to increment, still count as unique
        ++cnt;
      }
    }
    printf("%ld\n", cnt);
  }
}

// https://github.com/VaHiX/codeForces/