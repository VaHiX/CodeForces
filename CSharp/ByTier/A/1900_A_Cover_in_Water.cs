// Problem: CF 1900 A - Cover in Water
// https://codeforces.com/contest/1900/problem/A

/*
 * Problem: Cover in Water
 * 
 * Algorithm/Technique: Greedy Approach with String Splitting
 * 
 * Time Complexity: O(n), where n is the length of the input string.
 * Space Complexity: O(n), for storing the split parts of the string.
 * 
 * Approach:
 * 1. Split the input string by '#' to get groups of consecutive '.' characters.
 * 2. For each group of '.' characters:
 *    - If the group has less than 3 characters, all need to be filled with water (1 action each).
 *    - If the group has 3 or more characters, we can fill them with just 2 actions of type 1.
 * 3. If there are no groups of 3 or more characters, we sum up all individual '.' characters.
 * 4. If there is at least one group of 3 or more, we output 2.
 * 
 * Key Observations:
 * - A group of 3 or more empty cells can be filled using 2 actions (place water at ends, let the middle fill automatically).
 * - Groups with less than 3 empty cells require action for each cell.
 */

using System;
using System.Collections.Generic;
class sol {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Console.ReadLine(); // Read n (not used in logic)
      string[] str = Console.ReadLine().Split('#'); // Split by blocked cells
      int i = 0;
      bool ok = false;
      foreach (string s in str) {
        if (s.Length < 3) // If group is smaller than 3
          i += s.Length; // Add all cells in this group as they need 1 action each
        else {
          ok = true; // Found at least one group with 3 or more cells
          break;
        }
      }
      if (ok)
        Console.WriteLine(2); // At least one group of size >= 3, so need 2 actions
      else
        Console.WriteLine(i); // All groups < 3, so total count of cells is needed
    }
  }
}


// https://github.com/VaHiX/CodeForces/