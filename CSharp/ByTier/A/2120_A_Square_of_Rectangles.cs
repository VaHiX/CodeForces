// Problem: CF 2120 A - Square of Rectangles
// https://codeforces.com/contest/2120/problem/A

/*
 * Problem: Square of Rectangles
 * 
 * Description:
 * Aryan wants to arrange three rectangles of sizes l1×b1, l2×b2, and l3×b3 such that
 * l3 ≤ l2 ≤ l1 and b3 ≤ b2 ≤ b1 into a square. The rectangles cannot overlap, must be aligned along edges,
 * and cannot be rotated.
 * 
 * Algorithm/Techniques:
 * - Brute force approach checking all valid placements of three rectangles in a square grid.
 * - Since the dimensions are sorted, we can enumerate specific configurations that might form a square.
 * - For each configuration, we verify if sum of lengths and breadths match square requirements.
 * 
 * Time Complexity: O(1) - Constant time as there are only fixed comparisons and checks.
 * Space Complexity: O(1) - Constant space used for variables.
 */

using System;
using System.Linq;
using System.Collections.Generic;
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      int[] nk = Console.ReadLine().Split().Select(int.Parse).ToArray(); // Read and parse input line into array
      int l1 = nk[0];
      int l2 = nk[2];
      int l3 = nk[4];
      int b1 = nk[1];
      int b2 = nk[3];
      int b3 = nk[5];
      if (checkSquare(l1, l2, l3, b1, b2, b3)) {
        Console.WriteLine("Yes");
      } else {
        Console.WriteLine("No");
      }
    }
  }
  static bool checkSquare(int l1, int l2, int l3, int b1, int b2, int b3) {
    // Case 1: All lengths are equal and total breadth equals the common length
    if (l1 == l2 && l2 == l3) {
      if ((b1 + b2 + b3) == l1) {
        return true;
      }
    }
    // Case 2: All breadths are equal and total length equals the common breadth
    if (b1 == b2 && b2 == b3) {
      if ((l1 + l2 + l3) == b1) {
        return true;
      }
    }
    // Case 3: Second and third lengths equal, and their sum matches first length;
    // also check if corresponding breadths add up to first length
    if (b2 == b3 && (l2 + l3) == l1) {
      if ((b1 + b2) == l1) {
        return true;
      }
    }
    // Case 4: Second and third lengths equal, and their contribution in breadth matches first breadth;
    // also check that horizontal dimensions work out
    if (l2 == l3 && (b2 + b3) == b1) {
      if ((l1 + l2) == b1) {
        return true;
      }
    }
    return false; // No valid arrangement found
  }
}


// https://github.com/VaHiX/CodeForces/