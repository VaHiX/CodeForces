// Problem: CF 2147 B - Multiple Construction
// https://codeforces.com/contest/2147/problem/B

/*
B. Multiple Construction
Algorithm: Greedy construction approach
Time Complexity: O(n) amortized over all test cases
Space Complexity: O(n)

The algorithm constructs an array of length 2*n by placing each number x 
from n down to 1 at positions that ensure the distance between its two occurrences 
is a multiple of x. It uses a greedy strategy:
- For each x, find the first available position i.
- Place x at position i and at position i + x.
- This ensures the distance is exactly x (a multiple of x).
The key insight is to process numbers from largest to smallest to avoid conflicts.

*/
using System;
class Program {
  static void Main() {
    if (!int.TryParse(Console.ReadLine(), out int t))
      return;
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()!);
      int m = 2 * n;
      int[] result = new int[m + 1]; // Array to store the result, 1-indexed
      bool[] used = new bool[m + 1]; // Track which positions are already filled
      int cur = 1; // Current position to consider for placing a number
      for (int x = n; x >= 1; x--) { // Process numbers from n down to 1
        while (used[cur]) // Find the first unused position
          cur++;
        int i = cur;
        int j = i + x; // Calculate second position for number x
        while (j <= m && used[j]) { // Find next available j that satisfies condition
          j += x; 
        }
        result[i] = x; // Place x at first position
        result[j] = x; // Place x at second position
        used[i] = true; // Mark positions as used
        used[j] = true;
      }
      for (int i = 1; i <= m; i++) {
        if (i > 1)
          Console.Write(" ");
        Console.Write(result[i]);
      }
      Console.WriteLine();
    }
  }
}


// https://github.com/VaHiX/CodeForces/