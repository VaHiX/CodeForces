// Problem: CF 995 B - Suit and Tie
// https://codeforces.com/contest/995/problem/B

/*
Code Purpose:
This program finds the minimum number of adjacent swaps needed to make each couple adjacent in a line. 
It uses a greedy approach where for each person at position p, it finds their couple and performs swaps 
to bring the couple together, counting the swaps required.
Algorithms/Techniques: Greedy algorithm with adjacent swaps
Time Complexity: O(n^2) where n is the number of pairs
Space Complexity: O(n) for storing the array of people
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(2 * n);
  for (long p = 0; p < 2 * n; p++) {
    scanf("%ld", &a[p]);
  }
  long cnt(0);
  for (long p = 0; p < 2 * n; p++) {
    if (!a[p]) {
      continue;
    }
    long q;
    // Find the matching partner for person at position p
    for (q = p + 1; q < 2 * n && a[q] != a[p]; q++) {
      // Count how many people need to be swapped to get to the partner
      cnt += (a[q] > 0);
    }
    a[q] = 0; // Mark the partner as processed
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/