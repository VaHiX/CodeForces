// Problem: CF 1906 A - Easy As ABC
// https://codeforces.com/contest/1906/problem/A

/*
 * Code Purpose:
 *   This program finds the lexicographically smallest word of length 3 that can be formed
 *   by traversing adjacent cells in a 3x3 grid, where adjacency includes all 8 surrounding cells.
 *   It uses a backtracking-like approach to explore all possible paths of length 3.
 *
 * Algorithm:
 *   - Read the 3x3 grid from input.
 *   - For each starting cell, find the lexicographically smallest adjacent cell to form the first letter.
 *   - From that cell, find the next smallest adjacent cell to form the second letter.
 *   - From the second cell, find the next smallest adjacent cell to form the third letter.
 *   - Keep track of the lexicographically smallest such word found so far.
 *
 * Time Complexity: O(1) - Since the grid is fixed size (3x3), each operation has a constant time.
 * Space Complexity: O(1) - The space used is fixed and does not scale with input size.
 */

using System;
using System.Collections.Generic;

public struct Coord {
  public byte row;
  public byte col;
  public Coord(byte row, byte col) {
    this.row = row;
    this.col = col;
  }
}

public class EasyAsAbc {
  public static void Main() {
    char[,] grid = new char[3, 3];
    for (byte i = 0; i < 3; i++) {
      string row = Console.ReadLine();
      for (byte j = 0; j < 3; j++)
        grid[i, j] = row[j];
    }
    string wordMin = "CCD"; // Initialize with a string larger than any valid 3-letter word (lexicographically)
    char[] chars = new char[3];
    HashSet<Coord> excl = new HashSet<Coord>(); // Set to track already visited cells in current path
    List<Coord> l0 = MinCellsAdj(grid, 1, 1, excl); // Get minimal cell adjacent to center cell (1,1)
    chars[0] = grid[l0[0].row, l0[0].col]; // Assign first character of word
    for (byte i = 0; i < l0.Count; i++) {
      excl.Add(l0[i]); // Mark current cell as visited
      List<Coord> l1 = MinCellsAdj(grid, l0[i].row, l0[i].col, excl); // Find minimal adjacent cell to l0[i]
      chars[1] = grid[l1[0].row, l1[0].col]; // Assign second character of word
      for (byte j = 0; j < l1.Count; j++) {
        excl.Add(l1[j]); // Mark second cell as visited
        List<Coord> l2 = MinCellsAdj(grid, l1[j].row, l1[j].col, excl); // Find minimal adjacent cell to l1[j]
        chars[2] = grid[l2[0].row, l2[0].col]; // Assign third character of word
        string word = string.Join("", chars); // Combine three characters into a word
        if (string.Compare(word, wordMin) < 0) // If current word is lexicographically smaller
          wordMin = word; // Update minimum word
        excl.Remove(l1[j]); // Unmark second cell
      }
      excl.Remove(l0[i]); // Unmark first cell
    }
    Console.WriteLine(wordMin);
  }

  // Function to find the lexicographically smallest adjacent cell to (row, col)
  public static List<Coord> MinCellsAdj(char[,] grid, byte row, byte col,
                                        HashSet<Coord> excl) {
    byte rowMin = Convert.ToByte(Math.Max(0, row - 1)); // Minimum row index with boundaries
    byte rowMax = Convert.ToByte(Math.Min(2, row + 1)); // Maximum row index with boundaries
    byte colMin = Convert.ToByte(Math.Max(0, col - 1)); // Minimum column index with boundaries
    byte colMax = Convert.ToByte(Math.Min(2, col + 1)); // Maximum column index with boundaries
    List<Coord> res = new List<Coord>();
    char cMin = 'D'; // Start with a character larger than 'C' to ensure any valid character will be smaller
    for (byte i = rowMin; i <= rowMax; i++) // Check in 3x3 sub-grid around (row, col)
      for (byte j = colMin; j <= colMax; j++) {
        Coord coord = new Coord(i, j);
        // Skip invalid cells or already visited cells
        if (grid[i, j] > cMin || excl.Contains(coord))
          continue;
        if (grid[i, j] < cMin) { // If a new smaller character is found
          res.Clear(); // Clear result list
          cMin = grid[i, j]; // Update minimum character
        }
        res.Add(coord); // Add coordinate of this character
      }
    return res;
  }
}


// https://github.com/VaHiX/CodeForces/