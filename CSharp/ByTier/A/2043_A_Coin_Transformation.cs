// Problem: CF 2043 A - Coin Transformation
// https://codeforces.com/contest/2043/problem/A

/*
 * Problem: Coin Transformation
 * Algorithm: Recursive function with memoization approach
 * Time Complexity: O(log n) per test case due to halving the input in each recursive call
 * Space Complexity: O(log n) for recursion stack depth
 * 
 * Initially, you have a coin with value n. You can transform one coin with value x (x > 3)
 * into two coins with value floor(x/4). The goal is to find the maximum number of coins possible.
 * This is solved using a recursive approach where each coin greater than 3 splits into two coins
 * of value floor(x/4), until all values are <= 3, at which point they contribute 1 coin each.
 */

using System;
public class HelloWorld {
  public static void Main() {
    int a = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < a; i++) {
      long num = long.Parse(Console.ReadLine()); // Read the value of the coin
      Console.WriteLine(nn(num)); // Output result for current test case
    }
  }
  
  public static long nn(long n) { // Recursive helper function to compute max coins
    if (n <= 3) { // Base case: coins with value <= 3 contribute exactly 1 coin
      return 1;
    }
    return 2 * nn(n / 4); // Each coin > 3 splits into 2 coins of value floor(n/4)
  }
}


// https://github.com/VaHiX/codeForces/