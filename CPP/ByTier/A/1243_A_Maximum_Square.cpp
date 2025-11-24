// Problem: CF 1243 A - Maximum Square
// https://codeforces.com/contest/1243/problem/A

/*
Problem: Maximum Square
Algorithms/Techniques: Sorting, Greedy
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the planks

Given n planks of heights a_i, we want to find the maximum side length of a square
that can be cut from a rectangle formed by placing some planks side-by-side.
The key insight is that if we sort the planks in descending order and pick the first k planks,
the maximum square we can form has side length min(a_1, a_2, ..., a_k) where k is chosen optimally.

We can iterate through the sorted array and for each position p, check if a square of size (p+1) can be formed 
by taking the first (p+1) planks. Since planks are sorted in decreasing order, we simply check if a[p] >= p+1.
If so, we update the maximum side length. The answer is the largest such valid p+1.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read the height of each plank
    }
    sort(a.rbegin(), a.rend()); // Sort planks in descending order
    long side(0);
    for (long p = 0; p < n; p++) {
      if (a[p] >= p + 1) { // If current plank is tall enough to form square of size (p+1)
        side = p + 1;      // Update maximum square side
      } else {
        break;             // No point checking further since planks are sorted in descending order
      }
    }
    printf("%ld\n", side);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/