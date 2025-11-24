// Problem: CF 1401 A - Distance and Axis
// https://codeforces.com/contest/1401/problem/A

/*
Problem: Finding minimum steps to make a point B exist such that |distance(O,B) - distance(A,B)| = k.
Algorithm: Mathematical analysis of distances on a number line.
Time Complexity: O(1) per test case
Space Complexity: O(1)

The key insight is that we want to find an integer point B on the x-axis such that:
| |B| - |n - B| | = k

If we consider different cases for position of B relative to n:
- If B <= 0: distance(O,B) = -B, distance(A,B) = n - B
- If 0 < B < n: distance(O,B) = B, distance(A,B) = n - B  
- If B >= n: distance(O,B) = B, distance(A,B) = B - n

After algebraic manipulation and case analysis, we get the formula:
If k > n: answer is k - n (we need to move A by k - n steps)
Otherwise: 
  result = (2 + (n - k) % 2) % 2
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long res = (k > n) ? (k - n) : ((2 + (n - k) % 2) % 2); // Calculate minimum steps needed
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/