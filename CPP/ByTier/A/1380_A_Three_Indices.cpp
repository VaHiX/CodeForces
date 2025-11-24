// Problem: CF 1380 A - Three Indices
// https://codeforces.com/contest/1380/problem/A

/*
Algorithm: Three Indices
Purpose: Given a permutation of integers, find three indices i < j < k such that p[i] < p[j] and p[j] > p[k].
Techniques: Linear scan with sliding window of three elements.

Time Complexity: O(n) - Single pass through the array.
Space Complexity: O(1) - Only using a constant amount of extra space.

Approach: 
- Iterate through the permutation using a sliding window of three consecutive elements.
- For each such window, check if the middle element is greater than both neighbors.
- If found, output the indices of the three elements.

The solution assumes that it's sufficient to look at consecutive triplets.
This works because for any valid peak (j), if it's not part of a valid triplet,
we can still find a valid triplet by moving the window forward.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long pprev;
    scanf("%ld", &pprev);
    long prev;
    scanf("%ld", &prev);
    long idx(0); // Stores the index of the "peak" element (j)
    for (long p = 2; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (pprev < prev && prev > x) {
        idx = p; // Found a valid peak at index p
      }
      pprev = prev;
      prev = x;
    }
    if (idx) {
      printf("YES\n%ld %ld %ld\n", idx - 1, idx, idx + 1); // Output the three indices
    } else {
      puts("NO");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/