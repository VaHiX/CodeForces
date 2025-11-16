// Problem: CF 1468 E - Four Segments
// https://codeforces.com/contest/1468/problem/E

/*
E. Four Segments
Algorithm: Greedy + Sorting
Time Complexity: O(1) per test case (sorting 4 elements is constant time)
Space Complexity: O(1) (only using a vector of size 4)

Monocarp wants to draw four line segments with given lengths such that they enclose a maximum area rectangle.
The key insight is that for a rectangle, we need two pairs of equal-length sides.
We sort the four lengths and take the product of the smallest and third smallest elements,
which corresponds to choosing the two shorter sides to form the rectangle's width and height.
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<long> a(4);           // Store the four segment lengths
    scanf("%ld %ld %ld %ld", &a[0], &a[1], &a[2], &a[3]);  // Read the lengths
    sort(a.begin(), a.end());         // Sort to easily identify pairs
    printf("%ld\n", a[0] * a[2]);     // Product of smallest and third smallest gives max area
  }
}


// https://github.com/VaHiX/codeForces/