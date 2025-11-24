// Problem: CF 2119 A - Add or XOR
// https://codeforces.com/contest/2119/problem/A

/*
 * Problem: Make integer 'a' equal to 'b' using two operations:
 *          1. Increment 'a' by 1 (cost = x)
 *          2. XOR 'a' with 1 (cost = y)
 *
 * Algorithm:
 * - If a > b, it's impossible to reach b (since we can only increment or XOR with 1).
 * - If a == b, no operations needed.
 * - If a < b:
 *   - For each step from a to b-1:
 *     - If current value is even: choose cheaper operation between increment and XOR.
 *     - If current value is odd: cost of increment is always x.
 *
 * Time Complexity: O(b - a) per test case, but since b <= 100, it's effectively O(1).
 * Space Complexity: O(1)
 */

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read input line
      var a = int.Parse(line[0]);
      var b = int.Parse(line[1]);
      var x = int.Parse(line[2]);
      var y = int.Parse(line[3]);
      getAns(a, b, x, y); // Call function to compute answer
    }
  }
  static void getAns(int a, int b, int x, int y) {
    var d = b - a; // Difference between a and b
    if (d == -1) { // If a > b, it's impossible to make a equal to b
      Console.WriteLine(a % 2 == 0 ? -1 : y); // If even, can't go back, else return cost of XOR
      return;
    }
    if (d < -1) { // If a > b, definitely impossible
      Console.WriteLine(-1);
      return;
    }
    var cost = 0; // Initialize total cost
    var minab = Min(x, y); // Find cheaper operation between increment and XOR
    while (a < b) { // Traverse from a to b-1
      if (a % 2 == 0) // Even number: choose cheaper option
        cost += minab;
      else // Odd number: must use increment operation
        cost += x;
      a++; // Move forward
    }
    Console.WriteLine(cost); // Print result
  }
}


// https://github.com/VaHiX/CodeForces/