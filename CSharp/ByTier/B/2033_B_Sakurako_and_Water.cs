// Problem: CF 2033 B - Sakurako and Water
// https://codeforces.com/contest/2033/problem/B

/*
 * Problem: Sakurako and Water
 * 
 * Purpose:
 *   This program solves a problem where we have an n x n matrix representing a valley.
 *   Each cell contains the height of the mountain. If the height is negative, it represents a lake.
 *   Sakurako can use magic to increase the heights of all elements on the main diagonal
 *   of any square submatrix by 1. The goal is to find the minimum number of such operations
 *   needed so that no cells have negative values (i.e., no lakes).
 *
 * Approach:
 *   - For each element in the matrix with a negative value, we determine how many times
 *     we must apply the magic operation centered at that element to neutralize its negativity.
 *   - Each such magic application adds 1 to all elements along the diagonal of a square submatrix.
 *   - The algorithm simulates applying these operations incrementally and tracks total operations.
 *   - Time complexity: O(n^3) per test case due to nested loops over matrix and diagonal updates.
 *   - Space complexity: O(n^2) for storing the input grid.
 *
 * Algorithms/Techniques:
 *   - Diagonal traversal of square submatrices
 *   - Greedy incremental application of operations
 */

using System;

namespace Div3_1 {
  class Program {
    // Adds 'val' to all elements on the main diagonal starting from (x, y) 
    // until end of matrix is reached
    static void addOneToEachElementInMainDiagonal(int[] arr, int n, int ele,
                                                  int val) {
      int eley = ele % n;        // Column index of element 'ele'
      int elex = ele / n;        // Row index of element 'ele'
      int x, y;
      int min = Math.Min(elex, eley);
      x = elex - min;            // Starting row of the diagonal
      y = eley - min;            // Starting column of the diagonal
      while (x < n && y < n) {
        arr[(x * n) + y] += val; // Increment the value at diagonal element
        x++;
        y++;
      }
    }

    static void Qustion() {
      int magicNumber = 0;       // Total number of magic operations performed
      int n = int.Parse(Console.ReadLine());  // Size of matrix
      int s = n * n;
      int[] arr = new int[s];    // Flatten the 2D matrix into a 1D array

      // Reading input matrix row by row and converting to flattened array
      for (int i = 0; i < n; i++) {
        string[] line = Console.ReadLine().Split(' ');
        for (int j = 0; j < n; j++) {
          arr[i * n + j] = int.Parse(line[j]);  // Flattened index calculation
        }
      }

      // Traverse each cell and apply magic if value is negative
      for (int i = 0; i < s; i++) {
        if (arr[i] < 0) {
          int need = -1 * arr[i];   // How much we need to add to make it non-negative
          addOneToEachElementInMainDiagonal(arr, n, i, need); // Apply magic operation
          magicNumber += need;      // Accumulate the number of operations
        }
      }

      Console.WriteLine(magicNumber);
    }

    static void Main(string[] args) {
      int t = int.Parse(Console.ReadLine());  // Number of test cases
      while (t-- > 0) {
        Qustion();  // Process each test case
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/