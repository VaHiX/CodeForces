// Problem: CF 578 A - A Problem about Polyline
// https://codeforces.com/contest/578/problem/A

/*
 * Problem: A. A Problem about Polyline
 * 
 * Algorithm/Technique: Mathematical analysis and solving linear equations.
 * 
 * Time Complexity: O(1) - Constant time operations.
 * Space Complexity: O(1) - Only using a fixed amount of variables.
 * 
 * The polyline alternates between points at (k*x, 0) and (k*x + x, x) where k is even and odd respectively.
 * The height of the polyline at point (a, b) must satisfy the pattern:
 * - If a < b, it's impossible because the maximum height at any x-coordinate is b = x.
 * - Otherwise, we solve for x such that the given point (a,b) fits the pattern.
 * 
 * The formula derived from the pattern is:
 * x = (a + b) / (2 * (a + b) / (2 * b)) which simplifies to x = b.
 * But the code implements a more direct computation to get x = (a + b) / (2 * (a + b) / (2 * b))
 * which simplifies as x = (a + b) / ((a + b) / b) = b.
 * 
 * However, the code in fact computes:
 * x = (a + b) / ((a + b) / (2 * b)) = (2 * b * (a + b)) / (a + b) = 2 * b
 * This seems an error; however, the expression:
 * 1.0 * (a + b) / (2.0 * ((a + b) / (2 * b)))  = (a + b) / ( (a + b) / b ) = b
 * So the result is b, but this is not correct based on the problem.
 * 
 * A correct approach would check that for a point (a,b):
 * - If a < b then return -1;
 * - Otherwise, the x value needs to be such that a point with x-coordinate 'a' and y-coordinate 'b' 
 *   lies on the polyline.  
 * 
 * Let's analyze: if we are at kx, k is even (y=0), then next is at (kx + x) and y = x.
 * If point is (a,b), then b must be the height at that x-coordinate.
 * If a = k*x, then k even and y=0, so b cannot be non-zero.
 * If a = k*x + x, then k odd and y = x, so a = (k+1)*x and b = x.
 * 
 * So, if b = x, and we have a = (k+1)*x => x = a / (k+1) => b = a / (k+1) => k = (a/b) - 1.
 * Therefore, we can compute x = a / (k + 1) = a / ((a/b) - 1 + 1) = a / (a/b) = b.
 * Hence, x = b is one possibility if there exists a k such that k is odd and a = (k+1)*x.
 * And when k is odd, there should be k = (a - x) / x = (a/x) - 1.
 * 
 * From the structure, if we are at x = a, and b = x, then a should be of the form (2k + 1)*x.
 * So x = a / (2k + 1) and b = x -> a = (2k + 1)*b -> (a/b) = 2k + 1 -> k = (a/b - 1)/2.
 * For this to be integer, (a/b - 1) must be even and non-negative, also a >= b.
 * 
 * So, the expression is trying to compute:
 * x = (a + b) / (2 * (a + b) / (2 * b)) = (2 * b * (a + b)) / (a + b) = 2 * b ?
 * But that's incorrect.
 * Correct approach:
 * - If a < b, return -1.
 * - Try to find x such that (a, b) lies on the polyline.
 * - Since b = x for odd steps, x = b.
 * - Then check if a = (2k + 1) * b for some k >= 0.
 * - Rearrange: a = 2kb + b => a = b(2k + 1) => 2k + 1 = a/b => k = (a/b - 1)/2.
 * - k must be a non-negative integer.
 * - If a/b is an integer and (a/b - 1) is even, then solution is possible.
 * 
 * But we can simply calculate directly:
 * If a % b == 0 and (a / b) is odd, and a >= b, then x = b. 
 * This matches with the output format and expected answers.
 * 
 * Note: The solution is implemented with mathematical expression that attempts to directly compute x.
 * This may not be fully intuitive but works for provided test cases.
 */

#include <cstdio>
int main() {
  long a, b;
  scanf("%ld %ld\n", &a, &b);
  if (a < b) {
    puts("-1");
  } else {
    // The formula seems to be derived to directly solve for x from the pattern
    // This works for the provided test cases but is mathematically complex
    printf("%.10lf\n", 1.0 * (a + b) / (2.0 * ((a + b) / (2 * b))));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/