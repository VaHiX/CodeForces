// Problem: CF 1006 A - Adjacent Replacements
// https://codeforces.com/contest/1006/problem/A

/*
Algorithm: Mishka's Adjacent Replacements
Techniques: Array traversal, conditional replacement
Time Complexity: O(n)
Space Complexity: O(1)

This code implements Mishka's Adjacent Replacements Algorithm.
For each element in the array:
- If the element is odd and not the largest possible value (10^9), 
  it is replaced with the next even number (element + 1).
- Otherwise, if the element is even and not the smallest possible value (1), 
  it is replaced with the previous odd number (element - 1).
- All other elements remain unchanged.
*/

#include <cstdio>
int k, n;
int main() {
  for (scanf("%d", &n); n--; printf("%d ", k + k % 2 - 1)) // Read next element and print replacement
    scanf("%d", &k); // Read current element into k
}


// https://github.com/VaHiX/codeForces/