// Problem: CF 2034 B - Rakhsh's Revival
// https://codeforces.com/contest/2034/problem/B

using System;
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      string[] inputs = Console.ReadLine().Split();
      int n = int.Parse(inputs[0]);
      int m = int.Parse(inputs[1]);
      int k = int.Parse(inputs[2]);
      string s = Console.ReadLine();
      int operations = 0;
      int consecutiveWeak = 0;
      for (int j = 0; j < n; j++) {
        if (s[j] == '0') {
          consecutiveWeak++; // Increment counter if the spot is weak
        } else {
          consecutiveWeak = 0; // Reset counter if the spot is strong
        }
        if (consecutiveWeak >= m) { // If we have m consecutive weak spots
          operations++; // We must apply Timar (increment operation count)
          consecutiveWeak = 0; // Reset the counter after applying Timar
          j += k - 1; // Skip ahead by k-1 positions since we just strengthened a segment of length k
        }
      }
      Console.WriteLine(operations);
    }
  }
}
/*
Purpose:
This program determines the minimum number of operations required to ensure that no interval of m consecutive spots in a binary string is entirely weak ('0'). It uses a greedy approach where whenever a sequence of m or more consecutive weak spots is detected, it applies the Timar ability (which strengthens a segment of length k) and skips ahead to avoid overlapping operations.

Algorithms/Techniques:
- Greedy Algorithm
- Linear Scan with Early Termination

Time Complexity: O(n)
Space Complexity: O(1)

The algorithm iterates through the string once (O(n)), and each operation involves constant-time checks and updates.
*/

// https://github.com/VaHiX/CodeForces/