// Problem: CF 2134 E - Power Boxes
// https://codeforces.com/contest/2134/problem/E

/*
E. Power Boxes

Algorithm:
This is an interactive problem where we need to determine the power of each box (1 or 2) using at most ⌈3n/2⌉ queries.
We use a greedy approach based on comparing throw results with and without swaps.

Key idea:
- Use swap operations to rearrange boxes in such a way that we can differentiate between
  different configurations caused by power values.
- When throwing, if a ball makes `p` jumps and lands on a coordinate with another box,
  then the ball travels `p` units further. This allows us to determine the power value.

Time Complexity: O(n^2) - Worst case due to nested loops over n elements
Space Complexity: O(n) - For storing arrays of size n for indices, answers and counts

*/
using System.Text;
namespace PowerBoxes;
class Program {
  static int[] ind; // Stores current positions of boxes in terms of original indices
  
  static void Solve() {
    int n = int.Parse(reader.ReadLine());
    int[] ans = new int[n];                // Final answer array
    int[] cnt = new int[n + 2];            // Count of jumps per position
    ind = new int[n];
    for (int i = 0; i < n; i++)
      ind[i] = i;
    for (int i = n - 1; i >= 0;) {
      if (cnt[i + 1] == cnt[i + 2]) {        // If both positions have same jumps count
        if (i - 1 >= 0) {                    // Check if we can perform swap
          int p = Throw(i - 1);              // Throw at previous position
          if (p == cnt[i + 1] + 1) {         // Determine which power it is based on jump count
            ans[i] = 2;
            cnt[i] = cnt[i + 1] + 1;
          } else {
            ans[i] = 1;
            cnt[i] = cnt[i + 1] + 1;
          }
          Swap(i - 1);                       // Do the swap
          i--;
        } else {                             // At beginning, handle special case
          Swap(0);                           // Swap first two positions
          ans[0] = ans[1];                   // Copy value from index 1 to 0
          int p = Throw(1);                  // Throw at index 1 (which may now be different)
          if (p == cnt[2] + 1)               // Based on jump count, decide the correct power
            ans[1] = 1;
          else
            ans[1] = 2;
          break;                             // End loop after handling base case
        }
      } else {                               // Not equal case - just evaluate with throw
        int p = Throw(i);                    // Throw at position i
        if (p == cnt[i + 1] + 1)             // Determine power based on number of jumps
          ans[i] = 1;
        else
          ans[i] = 2;
        cnt[i] = p;                          // Store updated jump count
        i--;                                 // Move backwards
      }
    }
    Ans(ans);                              // Output final answer
  }

  static int Throw(int i) {
    writer.WriteLine($"throw {i + 1}");    // Send throw query to judge
    writer.Flush();
    return int.Parse(reader.ReadLine());   // Read response with jump count
  }

  static void Swap(int i) {
    (ind[i], ind[i + 1]) = (ind[i + 1], ind[i]);   // Update index mapping
    writer.WriteLine($"swap {i + 1}");        // Send swap to judge
    writer.Flush();
  }

  static void Ans(int[] p) {
    writer.Write("!");                      // Start output of final answer
    int[] ans = new int[p.Length];
    for (int i = 0; i < p.Length; i++) {
      ans[ind[i]] = p[i];                   // Map values back to original indices
    }
    foreach (var i in ans) {
      writer.Write(' ');
      writer.Write(i);
    }
    writer.WriteLine();                     // End the line for output
    writer.Flush();
  }

  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();                              // Process each test case
    }
    writer.Flush();
  }

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/