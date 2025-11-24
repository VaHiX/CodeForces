// Problem: CF 1997 C - Even Positions
// https://codeforces.com/contest/1997/problem/C

/*
 * Problem: Even Positions
 * 
 * Purpose: Given a string with brackets on even positions and underscores on odd positions,
 *          restore the string to form a valid bracket sequence with minimum cost.
 *          Cost is defined as the sum of distances between matching bracket pairs.
 * 
 * Algorithms/Techniques:
 * - Stack-based approach to match brackets
 * - Greedy matching to minimize total cost
 * 
 * Time Complexity: O(n) where n is the length of the string. Each character is processed once.
 * Space Complexity: O(n) for the stack in the worst case (all opening brackets).
 * 
 * Approach:
 * - Iterate through the string
 * - When encountering '(' or '_' at an odd position with empty stack, push index to stack
 * - When encountering ')' or '_' at an odd position with non-empty stack, pop from stack
 *   and add the distance (current index - popped index) to the result
 * 
 * Note:
 * - '_' can be either '(' or ')' based on the matching requirement
 * - Matching is done greedily, which ensures minimal cost
 */

using System;
using System.Collections.Generic;
public class EvenPositions {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      Stack<int> stack = new Stack<int>(); // Stack to store indices of unmatched opening brackets
      int ans = 0; // Total cost
      for (int j = 0; j < n; j++) {
        char c = s[j];
        // If current char is '(' or we are at an odd position with no unmatched '(' in stack
        if (c == '(' || (c == '_' && stack.Count == 0)) 
          stack.Push(j); // Push index of opening bracket
        else {
          int k = stack.Pop(); // Pop matching opening bracket index
          ans += j - k; // Add distance between brackets to total cost
        }
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/