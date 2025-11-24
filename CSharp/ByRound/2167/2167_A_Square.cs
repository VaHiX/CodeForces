// Problem: CF 2167 A - Square?
// https://codeforces.com/contest/2167/problem/A

using System;
public class Program {
  // Purpose: Determine if four given stick lengths can form a square.
  // Algorithm: A square requires all four sides to be equal in length.
  // Time Complexity: O(t), where t is the number of test cases.
  // Space Complexity: O(1), constant space usage.
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] input = Console.ReadLine().Split(' '); // Read the four stick lengths
      int a = int.Parse(input[0]); // First stick length
      int b = int.Parse(input[1]); // Second stick length
      int c = int.Parse(input[2]); // Third stick length
      int d = int.Parse(input[3]); // Fourth stick length
      if (a == b && b == c && c == d) // Check if all sides are equal
        Console.WriteLine("YES");
      else
        Console.WriteLine("NO");
    }
  }
}

// https://github.com/VaHiX/CodeForces/