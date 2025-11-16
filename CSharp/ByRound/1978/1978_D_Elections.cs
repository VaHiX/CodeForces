// Problem: CF 1978 D - Elections
// https://codeforces.com/contest/1978/problem/D

using System;
using System.Text;

public class Program {
  // Purpose: Determine the minimum number of candidates to exclude so that each candidate can win.
  // Algorithm: 
  // 1. Initially, all undecided voters (c) are assigned to the first candidate.
  // 2. Find the candidate with the maximum votes (with lowest index as tiebreaker).
  // 3. Iterate through each candidate and calculate how many candidates need to be excluded for this candidate to win:
  //    a. If candidate is the current maximum, they win (0 excludes).
  //    b. Otherwise, if cumulative votes including this candidate >= max votes, then exclude up to this candidate.
  //    c. Else, exclude up to the next candidate.
  // Time Complexity: O(n) per test case
  // Space Complexity: O(n) for storing votes and output
  private static StringBuilder output = new StringBuilder();
  
  public static void Main() {
    int test = int.Parse(Console.ReadLine().Trim());
    while (test-- > 0) {
      Sol();
    }
    Console.Write(output.ToString());
  }
  
  public static void Sol() {
    string[] firstLine = Console.ReadLine().Trim().Split();
    int n = int.Parse(firstLine[0]);
    long e = long.Parse(firstLine[1]);
    long[] v = new long[n];
    string[] secondLine = Console.ReadLine().Trim().Split();
    for (int i = 0; i < n; i++) {
      v[i] = long.Parse(secondLine[i]);
    }
    // Assign all undecided voters to the first candidate
    v[0] += e;
    
    int ind = 0;
    long m = v[0];
    // Find the maximum votes and the index of the candidate with that (lowest number in case of tie)
    for (int i = 0; i < v.Length; i++) {
      if (m < v[i]) {
        m = v[i];
        ind = i;
      }
    }
    
    long pre = 0;
    StringBuilder ans = new StringBuilder();
    for (int i = 0; i < v.Length; i++) {
      long val = v[i];
      pre += val;
      if (i == ind) {
        // If this candidate is the one with max votes, they win without excluding anyone
        ans.Append("0 ");
      } else {
        // Check if cumulative sum of votes including current candidate
        // can make them win.
        if (pre >= m) {
          // Exclude up to current candidate
          ans.Append(i + " ");
        } else {
          // Exclude one more candidate (i+1) to ensure they are the one winning
          ans.Append((i + 1) + " ");
        }
      }
    }
    output.AppendLine(ans.ToString());
  }
}

// https://github.com/VaHiX/CodeForces/