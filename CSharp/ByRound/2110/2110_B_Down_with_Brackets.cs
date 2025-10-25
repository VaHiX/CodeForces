// Problem: CF 2110 B - Down with Brackets
// https://codeforces.com/contest/2110/problem/B

/*
B. Down with Brackets
Purpose: Determine if removing exactly one opening and one closing bracket from a balanced bracket string makes it unbalanced.

Algorithm:
- For each test case, we process the string to find valid positions where we can remove a pair of brackets.
- We track the balance (sum) of brackets as we iterate through the string.
- When balance reaches zero, it means we have a valid subsequence ending at that position.
- If there is exactly one such valid subsequence, removing any pair of brackets from that subsequence will leave the string balanced.
- Otherwise, there are multiple such subsequences and removals can break balance.

Time Complexity: O(n) where n is the length of the input string
Space Complexity: O(n) for storing the indices of valid closing brackets

Techniques:
- Bracket matching using a running balance counter
- Identifying valid balanced subsequences
- Greedy selection to determine if removal can make sequence unbalanced

*/
using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var s = Console.ReadLine().Trim();
      getAns(s);
    }
  }
  static void getAns(string s) {
    var n = s.Length;
    var z = new List<int>(); // Store indices of closing brackets that complete a balanced subsequence
    var sum = 0; // Running balance counter for brackets
    for (int i = 0; i < n; i++) {
      if (s[i] == '(')
        sum++; // Increment when encountering an opening bracket
      else {
        sum--; // Decrement when encountering a closing bracket
        if (sum == 0) // If balance becomes zero, a complete balanced subsequence ends here
          z.Add(i); // Record the index of this closing bracket
      }
    }
    // If there's only one such subsequence, removing one pair from it won't break the sequence
    Console.WriteLine(z.Count == 1 ? "NO" : "YES");
  }
}


// https://github.com/VaHiX/codeForces/