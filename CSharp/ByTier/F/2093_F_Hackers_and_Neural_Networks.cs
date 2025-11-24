// Problem: CF 2093 F - Hackers and Neural Networks
// https://codeforces.com/contest/2093/problem/F

// Purpose: This code solves the problem of finding the minimum number of operations to transform an array of blanks into a target array using neural networks.
//          Each neural network provides a version of the target array, and each operation replaces a blank in the current array with a specific string from one of the networks.
//          The solution involves determining the minimum number of operations needed by analyzing how many times each network can contribute to building the target,
//          and then computing the optimal sequence based on that.

// Algorithms/Techniques:
// 1. Greedy approach: For each position in the target array, we check which networks can provide the correct string.
// 2. Counting: We count how many times each network contributes to constructing the target array.
// 3. Optimization: The minimum operations are calculated based on the network that contributes most and the remaining positions.

// Time Complexity: O(n * m), where n is the length of the target array and m is the number of neural networks.
// Space Complexity: O(n * m), for storing the input arrays and intermediate results.

using System;
using System.Linq;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var parts = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int n = parts[0], m = parts[1];
      string[] target = Console.ReadLine().Split();
      string[][] nets = new string[m][];
      for (int i = 0; i < m; i++) {
        nets[i] = Console.ReadLine().Split();
      }
      int[] cnt = new int[m];
      bool ok = true;
      for (int j = 0; j < n; j++) {
        bool found = false;
        for (int i = 0; i < m; i++) {
          if (nets[i][j] == target[j]) {
            cnt[i]++; // Count how many times each network contributes
            found = true;
          }
        }
        if (!found) {
          ok = false; // If no network can provide the needed value, it's impossible
          break;
        }
      }
      if (!ok) {
        Console.WriteLine(-1);
        continue;
      }
      int best = cnt.Max(); // Find the network that contributes the most
      Console.WriteLine(n + 2 * (n - best)); // Calculate the minimum number of operations
    }
  }
}


// https://github.com/VaHiX/CodeForces/