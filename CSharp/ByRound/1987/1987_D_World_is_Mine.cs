// Problem: CF 1987 D - World is Mine
// https://codeforces.com/contest/1987/problem/D

// Purpose: This code solves the "World is Mine" game problem where Alice and Bob play optimally to maximize and minimize the number of cakes Alice eats respectively.
// Algorithm: Dynamic Programming (DP) with state transition based on the maximum tastiness value and count of cakes.
// Time Complexity: O(n^2), where n is the number of cakes. The nested loops iterate through all possible states.
// Space Complexity: O(n^2), for storing the DP table of size (n+5) x ((n+5)/2 + 1).

using System;
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Solve();
    }
  }
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    long[] a = new long[n + 5]; // Array to store cake tastiness values
    long[] k = new long[n + 5]; // Array to count occurrences of each tastiness value
    string[] input = Console.ReadLine().Split();
    for (int i = 1; i <= n; i++) {
      a[i] = long.Parse(input[i - 1]); // Read and store each cake's tastiness
      k[a[i]]++; // Count how many cakes have the same tastiness
    }
    long[,] dp = new long[n + 5, (n + 5) / 2 + 1]; // DP table: dp[i][j] represents max gain/loss for first i cakes with j turns
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= (n + 1) / 2; j++) {
        dp[i, j] = -1000000000; // Initialize dp values to a very small number
      }
    }
    dp[0, 0] = 0; // Base case: no cakes, no turns -> zero gain
    
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= (n + 1) / 2; j++) {
        // Alice's turn: if she can take a cake with higher tastiness than previous, she gains 1
        if (j > 0)
          dp[i, j] = Math.Max(dp[i, j], dp[i - 1, j - 1] + 1);
        // Bob's turn: if he can eat k[i] number of cakes (with same tastiness), he loses k[i] 
        if (dp[i - 1, j] >= k[i])
          dp[i, j] = Math.Max(dp[i, j], dp[i - 1, j] - k[i]);
      }
    }
    
    // Find maximum number of turns Alice can take (j) where dp[n,j] >= 0
    for (int j = 0; j <= n; j++) {
      if (dp[n, j] >= 0) {
        Console.WriteLine(j);
        return;
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/