// Problem: CF 2130 A - Submission is All You Need
// https://codeforces.com/contest/2130/problem/A

/*
 * Problem: Maximum Score from Multiset Operations
 * 
 * Algorithms/Techniques: Greedy approach
 * 
 * Time Complexity: O(n), where n is the number of elements in the array.
 * Space Complexity: O(1), as we only use a constant amount of extra space.
 * 
 * Description:
 * Given a multiset S of non-negative integers, we can perform two operations:
 * 1. Select a subset S', add sum(S') to the score, then remove S' from S.
 * 2. Select a subset S', add mex(S') to the score, then remove S' from S.
 * 
 * Strategy:
 * For each element in the array:
 * - If the element is 0, we can always take it and add 1 to our score (because 0 is present).
 * - Otherwise, we sum up all elements and add them to the score.
 * 
 * This greedy approach works because we are trying to maximize the sum,
 * and we can always greedily select the elements that give us maximum benefit.
 * Since mex of a set containing 0 can be at least 1, we should consider how many 0s there are
 * and add them appropriately in our final score calculation.
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert string array to int array
      getAns(n, a); // Compute and print result
    }
  }
  static void getAns(int n, int[] a) {
    var c0 = a.Count(x => x == 0); // Count number of zeros in the array
    Console.WriteLine(a.Sum() + c0); // Output sum of all elements plus count of zeros
  }
}


// https://github.com/VaHiX/codeForces/