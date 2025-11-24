// Problem: CF 677 A - Vanya and Fence
// https://codeforces.com/contest/677/problem/A

/*
Code Purpose:
This program calculates the minimum width of the road required for a group of friends to walk in a single row without being noticed by a guard. Each friend's height is compared to the fence height 'h'. If a friend's height exceeds 'h', they must bend, which increases their width contribution to the road by 1 (from 1 to 2). The total width is the sum of all individual widths.

Algorithms/Techniques:
- Simple iteration through the list of friends
- Conditional check for each friend's height
- Accumulation of width based on bending requirement

Time Complexity: O(n), where n is the number of friends
Space Complexity: O(1), constant space used regardless of input size

*/
#include <cstdio>
int main() {
  int n, h;
  scanf("%d %d", &n, &h);
  int width(n);  // Initialize width with number of friends (each contributes at least 1)
  while (n--) {
    int x;
    scanf("%d ", &x);
    width += (x > h);  // Add 1 if the person has to bend (height > fence height)
  }
  printf("%d\n", width);
  return 0;
}


// https://github.com/VaHiX/CodeForces/