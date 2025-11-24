// Problem: CF 2148 A - Sublime Sequence
// https://codeforces.com/contest/2148/problem/A

/*
Problem: Farmer John creates a sequence of length n by alternating integers x and -x, starting with x.
Task: Find the sum of all integers in the sequence.

Algorithms/Techniques: Pattern recognition, mathematical observation

Time complexity: O(1) - constant time operation for each test case
Space complexity: O(1) - only using a constant amount of extra space

The pattern observed:
- If n is even: sum = 0 (positive and negative pairs cancel out)
- If n is odd: sum = x (odd number of elements, last element is x)
*/

using System;
public class HelloWorld {
  public static void Main(string[] args) {
    int T = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < T; i++) {
      int[] input = Array.ConvertAll(Console.ReadLine().Split(), int.Parse); // Read x and n
      int x = input[0]; // Extract x
      int y = input[1]; // Extract n (renamed to y for consistency with problem)
      int ans = 0; // Initialize result variable
      
      // If n is odd, the last element will be x, otherwise all pairs cancel out
      if (y % 2 == 1) {
        ans = x; // When n is odd, result equals x
      }
      
      Console.WriteLine(ans); // Output the result
    }
  }
}


// https://github.com/VaHiX/codeForces/