// Problem: CF 1526 A - Mean Inequality
// https://codeforces.com/contest/1526/problem/A

/*
Code Purpose:
This code solves the "Mean Inequality" problem where we need to arrange 2n distinct integers in a circle such that no element equals the arithmetic mean of its two neighbors. 
The approach is to sort the array and then interleave the first half with the second half to create a valid circular arrangement.

Algorithms/Techniques:
- Sorting the array
- Interleaving elements from the first half and second half of the sorted array
- This greedy approach ensures that no element is the mean of its neighbors due to the ordering strategy

Time Complexity: O(n log n) due to sorting; the rest of the operations are O(n)
Space Complexity: O(n) for storing the vector of size 2n

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(2 * n);  // Create vector of size 2n
    for (long p = 0; p < 2 * n; p++) {
      scanf("%ld", &v[p]);  // Read all elements
    }
    sort(v.begin(), v.end());  // Sort the array
    for (long p = 0; p < n; p++) {
      printf("%ld %ld ", v[p], v[p + n]);  // Interleave first and second half
    }
    puts("");  // Print newline after each test case
  }
}


// https://github.com/VaHiX/CodeForces/