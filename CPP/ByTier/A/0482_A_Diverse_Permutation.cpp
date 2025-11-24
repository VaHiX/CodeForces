// Problem: CF 482 A - Diverse Permutation
// https://codeforces.com/contest/482/problem/A

/*
Code Purpose:
This code generates a permutation of numbers from 1 to n such that the absolute differences between consecutive elements in the permutation result in exactly k distinct values. 

The algorithm works by:
1. First creating a pattern that generates k distinct differences using alternating high and low values
2. Then filling the rest of the permutation with consecutive values to maintain the required number of distinct differences

Algorithms/Techniques:
- Greedy approach to construct permutation
- Alternating high/low value pattern to generate distinct differences
- Linear time construction

Time Complexity: O(n) - single pass through the permutation array
Space Complexity: O(n) - for storing the permutation vector
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> perm(n);
  // Generate first k elements to create k distinct differences
  for (int p = 0; p < k; p++) {
    if (p % 2) {
      // For odd positions, place high values starting from n
      perm[p] = n - (p - 1) / 2;
    } else {
      // For even positions, place low values starting from 1
      perm[p] = p / 2 + 1;
    }
  }
  // Determine direction for remaining elements (step = 1 or -1)
  int step = (k % 2) ? 1 : -1;
  // Fill remaining elements with consecutive values to preserve distinct differences
  for (int p = k; p < n; p++) {
    perm[p] = perm[p - 1] + step;
  }
  // Print the resulting permutation
  for (int p = 0; p < n; p++) {
    printf("%ld ", perm[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/