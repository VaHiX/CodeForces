// Problem: CF 1970 A1 - Balanced Shuffle (Easy)
// https://codeforces.com/contest/1970/problem/A1

/*
 * Balanced Shuffle Algorithm
 * 
 * Purpose:
 *   This program computes the "balanced shuffle" of a given balanced parentheses sequence.
 *   The balanced shuffle operation sorts the characters of the input sequence based on
 *   the prefix balance and position, such that the result is also a balanced parentheses sequence.
 * 
 * Algorithm:
 *   1. For each character in the input string, compute the prefix balance (running sum of '(' and ')').
 *   2. Store characters in a sorted dictionary grouped by their prefix balance.
 *   3. For each balance level (in ascending order), pop characters from the stack and append to result.
 * 
 * Time Complexity: O(n log n)
 *   - O(n) for scanning the input to build the dictionary.
 *   - O(n log n) for sorting due to the use of SortedDictionary.
 * 
 * Space Complexity: O(n)
 *   - The dictionary and stacks store all characters of the input string.
 * 
 * Techniques:
 *   - Prefix balance tracking.
 *   - Use of SortedDictionary for sorting by balance.
 *   - Stack-based reverse appending to maintain correct order.
 */

using System;
using System.Collections.Generic;
using System.Text;
public class BalancedShuffleEasy {
  public static void Main() {
    string s = Console.ReadLine();
    // SortedDictionary to store characters grouped by prefix balance
    SortedDictionary<int, Stack<char>> sort =
        new SortedDictionary<int, Stack<char>>();
    int balance = 0;
    // Traverse the string and calculate prefix balance for each character
    for (int i = 0; i < s.Length; i++) {
      // If no stack exists for current balance, create one
      if (!sort.ContainsKey(balance))
        sort.Add(balance, new Stack<char>());
      // Push the character to the stack corresponding to its balance
      sort[balance].Push(s[i]);
      // Update balance: +1 for '(', -1 for ')'
      balance += (s[i] == '(' ? 1 : -1);
    }
    StringBuilder ans = new StringBuilder();
    // Process each balance level in ascending order
    foreach (KeyValuePair<int, Stack<char>> kvp in sort)
      // Pop all characters from the stack and append to result
      while (kvp.Value.Count > 0)
        ans.Append(kvp.Value.Pop());
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/CodeForces/