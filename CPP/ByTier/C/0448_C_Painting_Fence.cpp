// Problem: CF 448 C - Painting Fence
// https://codeforces.com/contest/448/problem/C

/*
Algorithm: Divide and Conquer with Greedy Strategy
Time Complexity: O(n^2) in the worst case due to nested loops in recursive calls, but often better in practice
Space Complexity: O(n) for the recursion stack depth in worst case

This solution uses a recursive divide and conquer approach to determine the minimum number of strokes.
At each step, we find the minimum height plank in the current segment and decide whether it's cheaper
to paint the entire segment with horizontal strokes (equal to the segment length) or to:
1. Paint the minimum height with horizontal strokes
2. Recursively solve for the left and right parts
3. Add the vertical strokes needed to reach the minimum height from the previous painted height
*/

#include <cstdio>
#include <vector>
long count(const std::vector<long> &v, long left, long right,
           long paintedHeight) {
  if (left >= right) {
    return 0;
  }
  long minPos = left;
  for (long p = left; p < right; p++) {
    minPos = (v[p] < v[minPos]) ? p : minPos;
  }
  // Candidate A: Paint entire segment with horizontal strokes (number of planks)
  long candA = right - left;
  // Candidate B: 
  // 1. Recursively solve for left part
  // 2. Recursively solve for right part  
  // 3. Add vertical strokes needed to raise to min height from paintedHeight
  long candB = count(v, left, minPos, v[minPos]) +
               count(v, minPos + 1, right, v[minPos]) +
               (v[minPos] - paintedHeight);
  return (candA < candB) ? candA : candB;
}
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long total = count(a, 0, n, 0);
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/