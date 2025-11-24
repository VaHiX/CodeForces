// Problem: CF 2029 B - Replacement
// https://codeforces.com/contest/2029/problem/B

using System;
public class Replacement {
  // Purpose: Determine if a binary string s can be reduced to a single character
  //          using a sequence of operations defined by string r.
  //          Each operation selects a position k where s[k] != s[k+1] and replaces
  //          s[k]s[k+1] with r[i]. 
  //          The key insight is that we must ensure we always have a valid k to operate on.
  //          Time Complexity: O(n) per test case
  //          Space Complexity: O(1) - only using a few variables
  
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      string r = Console.ReadLine();
      int count0 = 0;
      int count1 = 0;
      // Count total number of 0s and 1s in s
      for (int j = 0; j < n; j++) {
        if (s[j] == '0')
          count0++;
        else
          count1++;
      }
      int idxLast = n - 1;
      bool ans = true;
      // Process each operation in r
      for (int j = 0; j < idxLast && ans; j++) {
        // If no more 0s or 1s, we can't make a move
        if (count0 == 0 || count1 == 0)
          ans = false;
        else if (r[j] == '0')
          count1--; // We are replacing a pair with a '0', so decrement 1s
        else
          count0--; // We are replacing a pair with a '1', so decrement 0s
      }
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
}

// https://github.com/VaHiX/CodeForces/