// Problem: CF 2010 A - Alternating Sum of Numbers
// https://codeforces.com/contest/2010/problem/A

/*
 * Problem: Alternating Sum of Numbers
 * 
 * Purpose: This program computes the alternating sum of a sequence of integers,
 *          where signs alternate starting with a positive sign (+a1 -a2 +a3 -a4 ...).
 * 
 * Algorithm:
 *   - For each test case, read the number of elements and the sequence.
 *   - Iterate through the elements, grouping them by odd and even indices.
 *   - Sum elements at odd indices (1-based) and even indices (1-based).
 *   - Return the difference (odd_sum - even_sum).
 * 
 * Time Complexity: O(n) per test case, where n is the length of the sequence.
 * Space Complexity: O(1) excluding input/output storage.
 * 
 * Techniques:
 *   - Single pass through the array
 *   - Index-based even/odd tracking
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ps_2 {
class Program {
  static void Main(string[] args) {
    int GetTestCase = int.Parse(Console.ReadLine()); // Read number of test cases
    int[] Output = new int[GetTestCase]; // Array to store results for each test case
    for (int i = 0; i < GetTestCase; i++) {
      int GetCountOfNumber = int.Parse(Console.ReadLine()); // Read length of sequence
      int[] Numbers = Console.ReadLine().Split(' ').Select(int.Parse).ToArray(); // Read sequence
      int OddSum = 0; // Sum of elements at odd positions (1-based)
      int EvenSum = 0; // Sum of elements at even positions (1-based)
      for (int j = 0; j < Numbers.Length; j++) {
        if (j == 0 || j % 2 == 0) {
          // If index is 0 or even (1-based), it's an odd position (1,3,5...)
          OddSum += Numbers[j];
        } else {
          // If index is odd (1-based), it's an even position (2,4,6...)
          EvenSum += Numbers[j];
        }
      }
      Output[i] = OddSum - EvenSum; // Calculate alternating sum
    }
    for (int i = 0; i < Output.Length; i++) {
      Console.WriteLine(Output[i]); // Print result for each test case
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/