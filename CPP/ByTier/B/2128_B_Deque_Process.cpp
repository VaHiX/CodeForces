// Problem: CF 2128 B - Deque Process
// https://codeforces.com/contest/2128/problem/B

/*
B. Deque Process
time limit per test1.5 seconds
memory limit per test256 megabytes

Algorithm/Techniques:
- Greedy approach with careful selection of left or right element to remove at each step.
- For each pair of elements from both ends (left and right), decide whether to take from left or right based on comparison
  to avoid creating a bad subsequence of 5 consecutive increasing or decreasing elements.
- Time Complexity: O(n)
- Space Complexity: O(n)

The idea is to process elements from both ends using a greedy strategy:
1. For each position p from 0 to n/2 - 1, compare v[p] and v[n-1-p].
2. If they are in the same "direction" (both less than or greater than), remove from left; 
   otherwise remove from right.
3. Handle middle element separately if n is odd.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    // Process pairs from both ends
    for (long p = 0; p < n / 2; p++) {
      if ((p % 2 == 0) == (v[p] < v[n - 1 - p])) {
        printf("LR"); // Left then Right to ensure we don't create a bad subsequence
      } else {
        printf("RL"); // Right then Left based on same logic
      }
    }
    // Handle odd-length case: middle element
    puts(n % 2 ? "L" : "");
  }
}


// https://github.com/VaHiX/codeForces/