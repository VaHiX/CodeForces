// Problem: CF 2139 A - Maple and Multiplication
// https://codeforces.com/contest/2139/problem/A

/*
 * Problem: A. Maple and Multiplication
 * Purpose: Determine the minimum number of operations to make two positive integers a and b equal,
 *          where each operation allows multiplying either a or b by any positive integer.
 *
 * Algorithms/Techniques:
 *   - Mathematical analysis based on divisibility and equality conditions.
 *   - Observation:
 *     1. If a == b, 0 operations needed.
 *     2. If a is divisible by b or b is divisible by a, 1 operation needed (multiply the smaller one by quotient).
 *     3. Otherwise, 2 operations needed (multiply both to reach common value).
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

import java.util.Scanner;
public class ProblemA{
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt(); // Read number of test cases
    while(t-- > 0){ // Process each test case
      int a = sc.nextInt(); // Read first integer
      int b = sc.nextInt(); // Read second integer
      if(a == b){
        System.out.println(0); // Already equal, no operations needed
      } else if(a % b == 0 || b % a == 0){
        System.out.println(1); // One is divisible by the other, one operation suffices
      } else {
        System.out.println(2); // Neither divides the other, two operations required
      }
    }
    sc.close(); // Close scanner to prevent resource leak
  }
}


// https://github.com/VaHiX/codeForces/