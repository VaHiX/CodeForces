// Problem: CF 2037 B - Intercepted Inputs
// https://codeforces.com/contest/2037/problem/B

/*
 * Problem: Intercepted Inputs
 * 
 * Purpose: Given a shuffled list of integers that were originally meant to form an n x m grid,
 *          determine possible values of n and m such that the total number of elements equals k.
 *          The grid dimensions n and m must satisfy n * m = k, and the values of n and m must be
 *          such that both n and m appear in the input data (at least once for distinct, twice for equal).
 *
 * Algorithms/Techniques:
 * - Factorization: Loop through all possible factors up to sqrt(k) to try and find valid n, m pairs
 * - Frequency counting: Count occurrences of each input value to determine which ones are n and m
 *
 * Time Complexity: O(sqrt(k) + k) per test case
 * Space Complexity: O(k) for storing the frequency array
 */
using System;
public class InterceptedInputs {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      int k = int.Parse(Console.ReadLine()); // Read total number of integers
      string[] parts = Console.ReadLine().Split(); // Split the input line into parts
      int[] c = new int[k]; // Frequency array to count occurrences of each number (1-indexed)
      for (int j = 0; j < k; j++) {
        int aj = int.Parse(parts[j]); // Parse each integer
        c[aj - 1]++; // Increment frequency of aj (since array is 0-indexed)
      }
      int n = 0;
      int m = 0;
      k -= 2; // Adjust k since we know n and m are among the k values
      bool solved = false;
      // Loop through possible factors of k to find valid n and m
      for (int j = 1; j * j <= k && !solved; j++)
        if (k % j == 0) { // If j divides k
          n = j;
          m = k / j;
          // Check if n and m are valid dimensions
          solved =
              n != m && c[n - 1] > 0 && c[m - 1] > 0 || n == m && c[n - 1] > 1;
        }
      Console.WriteLine("{0} {1}", n, m); // Output the found n and m
    }
  }
}


// https://github.com/VaHiX/CodeForces/