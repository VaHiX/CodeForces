// Problem: CF 1324 A - Yet Another Tetris Problem
// https://codeforces.com/contest/1324/problem/A

/*
A. Yet Another Tetris Problem
Algorithms/Techniques: Greedy, parity analysis
Time complexity: O(n) per test case
Space complexity: O(1)

The problem involves determining if we can clear a Tetris field by placing 2x1 figures.
Each figure adds 2 units of height to one column.
After each placement, all columns are reduced by 1 unit (if possible).
The key insight is that when we place a figure in a column of height h,
after the decrement step, it becomes h+2-1 = h+1.

So placing a figure in a column of even height increases it to odd,
and vice versa. To clear all columns, we must be able to balance
the parity of all heights after the placement of figures.

If there exists at least one column with an even height and at least one
with an odd height, then we cannot always clear the field (since some
combinations would produce conflicting parities). However, if either all
columns are even or all columns are odd, then it's possible to clear them.

This solution counts how many even and odd numbers there are and checks 
if both exist; if both exist, return "NO".

*/

#include <stdio.h>
int m, n, a, cnt[2];  // cnt[0] = count of even heights, cnt[1] = count of odd heights
int main() {
  for (scanf("%d", &m); m--; cnt[0] = cnt[1] = 0) {  // read number of test cases and reset counters
    scanf("%d", &n);  // read number of columns
    for (int i = 0; i < n; i++)  // process each column
      scanf("%d", &a), cnt[a & 1]++;  // count parity: a&1 gives 0 if even, 1 if odd
    puts(!cnt[0] || !cnt[1] ? "YES" : "NO");  // if all are even or all are odd, YES; else NO
  }
}


// https://github.com/VaHiX/codeForces/