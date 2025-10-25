// Problem: CF 2149 A - Be Positive
// https://codeforces.com/contest/2149/problem/A

/*
 * Problem: A. Be Positive
 * Algorithm/Techniques: Greedy approach
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) due to storing the input array.
 * 
 * The goal is to make the product of all elements strictly positive with minimum operations.
 * Each operation increases an element by 1.
 * 
 * Key observations:
 * - If there are any zeros, they must be increased to 1.
 * - If there are negative numbers, their count determines how many need to be flipped.
 *   - An even number of negatives makes the product positive.
 *   - An odd number of negatives requires one extra operation to flip one of them.
 */

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) { // Process each test case
      int n = int.Parse(Console.ReadLine()); // Read array length
      int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray(); // Read array elements
      
      int zeros = a.Count(x => x == 0);          // Count of zeros that need to be turned into 1s
      int negs = a.Count(x => x == -1);          // Count of -1s
      
      // To make product positive:
      // - All zeros contribute 1 operation each (turn to 1)
      // - If odd number of -1s, we need one more operation to turn one -1 into 1
      int operations = zeros + (negs % 2) * 2;
      
      Console.WriteLine(operations); // Output the minimum operations needed
    }
  }
}


// https://github.com/VaHiX/CodeForces/