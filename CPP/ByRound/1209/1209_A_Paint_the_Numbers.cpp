// Problem: CF 1209 A - Paint the Numbers
// https://codeforces.com/contest/1209/problem/A

/*
A. Paint the Numbers
Algorithms/Techniques: Greedy algorithm with sorting and divisibility checking

Time Complexity: O(n^2)
Space Complexity: O(n)

The problem asks to minimize the number of colors needed to paint elements such that:
- Each color group contains elements where all are divisible by the smallest element in that group.
- We aim to find the minimum number of such color groups.

Approach:
1. Sort the array to process elements in ascending order.
2. For each element, check if it is divisible by any previously processed element (smaller ones).
3. If not divisible by any, assign it a new color.
4. Count how many unique colors are needed.

This greedy approach works because:
- Sorting ensures smaller elements are processed before larger ones.
- An element that is not divisible by any previous element must be painted in a new color.
- The first element always starts a new color group.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);  // Read each element into the vector
  }
  sort(a.begin(), a.end());  // Sort the array to process from smallest to largest
  long cnt(0);  // Counter for number of colors used
  for (long p = 0; p < n; p++) {
    bool uniq(true);  // Flag to determine if current element starts new color
    for (long q = 0; q < p; q++) {
      if (a[p] % a[q] == 0) {  // If current element is divisible by any previous one
        uniq = false;
        break;
      }
    }
    cnt += uniq;  // Increment color count if element starts new group
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/