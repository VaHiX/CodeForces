// Problem: CF 2064 A - Brogramming Contest
// https://codeforces.com/contest/2064/problem/A

/*
 * Problem: Brogramming Contest
 * Description: Given a binary string s, we want to transfer characters between s and t such that 
 *              s becomes all 0s and t becomes all 1s using minimum moves. A move consists of 
 *              taking a suffix from s and appending it to t, or vice versa.
 *
 * Algorithm: The key insight is to count the number of transitions from '0' to '1' or from '1' to '0'
 *            in the string. Each transition represents a necessary "cut" point where we must move
 *            a suffix to change the state. This gives us the number of moves needed.
 *
 * Time Complexity: O(n) where n is the length of the input string s.
 * Space Complexity: O(n) for storing the list of unique characters in sequence.
 */

using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of string
      var s = Console.ReadLine().Trim(); // Read binary string
      getAns(n, s); // Process and output result for current test case
    }
  }
  
  static void getAns(int n, string s) {
    var a = new List<char>(); // List to store unique consecutive characters
    
    // If first character is '1', add it to the list (because we start from 1)
    if (s[0] == '1')
      a.Add('1');
    
    // Traverse the string and add characters only when they differ from previous one
    for (int i = 1; i < n; i++) {
      if (s[i] != s[i - 1])
        a.Add(s[i]);
    }
    
    // The count of such transitions gives us the number of moves required
    Console.WriteLine(a.Count);
  }
}


// https://github.com/VaHiX/codeForces/