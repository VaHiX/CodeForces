// Problem: CF 1917 C - Watering an Array
// https://codeforces.com/contest/1917/problem/C

/*
 * Code Purpose:
 * This program solves the "Watering an Array" problem where we have an array of integers and perform operations over 'd' days.
 * Each day we either increment the first b_i elements of the array or count how many elements equal their position and add that to the score,
 * then reset the array to zeros.
 * 
 * Algorithms/Techniques:
 * - Simulation with periodic sequence b
 * - Optimization: Only simulate a limited number of steps (2*n+1) to avoid unnecessary computation
 * - Greedy approach: For each simulation step, compute the score and track maximum
 * 
 * Time Complexity:
 * O(min(2*n + 1, d) * n) where n is the length of array a, and d is the number of days.
 * In worst case, this simplifies to O(n^2) given the constraints.
 * 
 * Space Complexity:
 * O(n + k) where n is the length of array a and k is the length of sequence v.
 * This accounts for the arrays 'entity' and 'bmps' used in the solution.
 */

using System;
using System.Linq;
using System.Collections.Generic;
class Program {
  static void Main() {
    try {
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      int blind = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < blind; testCase++) {
        int soul, gdr, insane;
        soul = gdr = insane = 0;
        string[] input = Console.ReadLine().Split();
        soul = int.Parse(input[0]); // Length of array a
        gdr = int.Parse(input[1]); // Length of sequence v
        insane = int.Parse(input[2]); // Number of days
        int[] entity = new int[soul + 1]; // Array a (1-indexed)
        int[] bmps = new int[gdr + 1]; // Sequence v (1-indexed)
        string[] entityInput = Console.ReadLine().Split();
        for (int i = 1; i <= soul; i++) {
          entity[i] = int.Parse(entityInput[i - 1]); // Read array a values
        }
        string[] bmpsInput = Console.ReadLine().Split();
        for (int i = 1; i <= gdr; i++) {
          bmps[i] = int.Parse(bmpsInput[i - 1]); // Read sequence v values
        }
        int testCnt = Math.Min(2 * soul + 1, insane); // Limit simulation steps to avoid TLE
        int ans = 0, idx = 1; // ans stores max score, idx is pointer to current element in sequence v
        for (int toZero = 1; toZero <= testCnt; toZero++) {
          int cur = 0;
          // Count how many elements equal their position
          for (int i = 1; i <= soul; i++) {
            if (entity[i] == i)
              cur++;
          }
          // Estimate potential future score (optimization heuristic)
          cur += (insane - toZero) / 2;
          ans = Math.Max(ans, cur); // Update maximum score
          // Increment the first bmps[idx] elements
          for (int i = 1; i <= bmps[idx]; i++)
            entity[i]++;
          idx++; // Move to next element in sequence v (wraps around if needed)
          if (idx > gdr)
            idx = 1;
        }
        Console.WriteLine(ans);
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
}


// https://github.com/VaHiX/CodeForces/