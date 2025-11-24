// Problem: CF 1678 B2 - Tokitsukaze and Good 01-String (hard version)
// https://codeforces.com/contest/1678/problem/B2

/*
Algorithm: Greedy
Purpose: To find the minimum number of operations to make a binary string "good" (each contiguous segment has even length),
         and also find the minimum number of segments in such a solution.
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables for counting

The approach:
1. For each pair of adjacent characters, we check if they differ.
   - If they differ, we need to change one of them to make the segment even (hence incrementing operation count).
2. We also track the number of segments where consecutive pairs are equal but differ from previous segment.
   - This is used to determine the minimum number of segments needed in the final solution.
3. If the number of such segments is 0, we set it to 1 (minimum number of segments needed when string is already good).
*/

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      Console.ReadLine(); // Read n, but we don't use it directly
      var s = Console.ReadLine();
      long o = 0; // Number of operations needed
      long m = 0; // Minimum number of segments
      char la = '2'; // Last character seen to detect transitions
      for (int i = 0; i < s.Length / 2; i++) {
        // Compare characters at positions 2*i and 2*i+1 (pairs)
        if (s[i * 2] != s[i * 2 + 1])
          o++; // If different, one operation is needed to make them same
        else if (la != s[i * 2]) {
          m++; // If same as previous pair but different from last segment, increment segment count
          la = s[i * 2]; // Update last character
        }
      }
      if (m == 0)
        m = 1; // If no transitions, at least one segment is required
      output.Add(o.ToString() + " " + m.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/