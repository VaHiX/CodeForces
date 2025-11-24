// Problem: CF 2125 B - Left and Down
// https://codeforces.com/contest/2125/problem/B

/*
 * Problem: B. Left and Down
 * 
 * Purpose: Given a robot at position (a, b) on an infinite grid, determine the minimum cost
 *          to move it to (0, 0) using operations that move dx left and dy down, where 
 *          0 <= dx, dy <= k. Each unique (dx, dy) pair has a cost of 1 if used for the first time,
 *          otherwise 0.
 * 
 * Algorithm:
 * - Key insight: The minimum number of operations needed is determined by 
 *   the smallest number of steps required to reduce both coordinates to zero.
 * - If we can move (a/g, b/g) in one step, then the cost is 1. Otherwise, it takes 2 steps.
 * - This is based on the idea that if the GCD(a, b) is such that a/g and b/g are each <= k,
 *   then one operation suffices; otherwise, two operations are required.
 * 
 * Time Complexity: O(log(min(a, b))) per test case due to GCD calculation
 * Space Complexity: O(log(min(a, b))) for recursive GCD calls (stack space)
 */

import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    for (int tc = 0; tc < t; ++tc) {
      long a = sc.nextLong(); // x-coordinate of initial position
      long b = sc.nextLong(); // y-coordinate of initial position
      long k = sc.nextLong(); // maximum allowed dx and dy
      System.out.println(solve(a, b, k));
    }
    sc.close();
  }

  static int solve(long a, long b, long k) {
    long g = gcd(a, b); // Compute GCD of a and b
    
    // Check if the reduced coordinates (a/g, b/g) are within bounds [0, k]
    // If so, one operation suffices (cost = 1)
    // Otherwise, two operations are needed (cost = 2)
    return (Math.max(a / g, b / g) <= k) ? 1 : 2;
  }

  static long gcd(long x, long y) {
    // Euclidean algorithm to compute GCD
    return (y == 0) ? x : gcd(y, x % y);
  }
}


// https://github.com/VaHiX/CodeForces/