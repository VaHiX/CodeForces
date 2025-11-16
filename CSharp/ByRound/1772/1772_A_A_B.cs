// Problem: CF 1772 A - A+B?
// https://codeforces.com/contest/1772/problem/A

/*
Purpose: This code evaluates simple addition expressions of the form "a+b" where a and b are single digit integers (0-9).
Algorithm: Parse input string, split by '+', convert parts to integers, add them, and output the result.
Time Complexity: O(t) where t is the number of test cases, as each operation within the loop is O(1).
Space Complexity: O(1) as we use a constant amount of extra space (fixed size arrays and variables regardless of input size).

Algorithms/Techniques: String parsing, arithmetic operations, iterative processing
*/

using System;
public class Test {
  public static void Main() {
    int input;
    input = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < input; i++) {
      string val = Console.ReadLine(); // Read the expression string
      string[] parts = val.Split('+'); // Split the string by '+' character
      int num1 = int.Parse(parts[0]); // Convert first part to integer
      int num2 = int.Parse(parts[1]); // Convert second part to integer
      int sum = num1 + num2; // Calculate the sum
      Console.WriteLine(sum); // Output the result
    }
  }
}


// https://github.com/VaHiX/CodeForces/