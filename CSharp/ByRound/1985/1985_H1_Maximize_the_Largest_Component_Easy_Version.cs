// Problem: CF 1985 H1 - Maximize the Largest Component (Easy Version)
// https://codeforces.com/contest/1985/problem/H1

/*
 * Algorithm: Connected Components and Grid Operations
 * 
 * Purpose: Find the maximum size of a connected component of '#' cells after performing at most one operation of setting an entire row or column to '#'.
 * 
 * Approach:
 * 1. First, identify all connected components of '#' cells using BFS and label them.
 * 2. For each row, simulate setting all cells in that row to '#' and calculate the potential maximum component size:
 *    - Count how many distinct components are adjacent to the '.' cells in that row.
 *    - Sum the sizes of these components with the area of '.' cells in the row.
 * 3. Do the same for each column.
 * 4. Return the maximum among all possibilities.
 * 
 * Time Complexity: O(n * m) per test case, where n is rows and m is columns.
 * Space Complexity: O(n * m) for storing grid, components labels, and component sizes.
 */

using System;
using System.Collections.Generic;
using System.IO;
class Program {
  static (int, int)[] Directions = { (-1, 0), (0, 1), (1, 0), (0, -1) };
  static bool IsInBounds((int, int)point, int rowCount, int columnCount) {
    return point.Item1 >= 0 && point.Item1 < rowCount && point.Item2 >= 0 &&
           point.Item2 < columnCount;
  }
  static void FillGrid(List<string> grid, int rowCount, StreamReader reader) {
    for (int i = 0; i < rowCount; i++) {
      grid.Add(reader.ReadLine());
    }
  }
  static void SolveTestCase(int testCaseIndex, StreamReader reader,
                            StreamWriter writer) {
    int rowCount, columnCount;
    string[] dimensions = reader.ReadLine().Split();
    rowCount = int.Parse(dimensions[0]);
    columnCount = int.Parse(dimensions[1]);
    List<string> grid = new List<string>();
    FillGrid(grid, rowCount, reader);
    long[,] components = new long[rowCount, columnCount];
    Dictionary<long, long> componentSizes = new Dictionary<long, long>();
    long maxComponentSize = 0, componentLabel = 1;
    // First pass: Label all connected components of '#' cells
    for (int i = 0; i < rowCount; i++) {
      for (int j = 0; j < columnCount; j++) {
        if (grid[i][j] == '#' && components[i, j] == 0) {
          Queue<(int, int)> queue = new Queue<(int, int)>();
          queue.Enqueue((i, j));
          while (queue.Count > 0) {
            var currentPoint = queue.Dequeue();
            if (!IsInBounds(currentPoint, rowCount, columnCount)) {
              continue;
            }
            if (grid[currentPoint.Item1][currentPoint.Item2] == '.' ||
                components[currentPoint.Item1, currentPoint.Item2] != 0) {
              continue;
            }
            components[currentPoint.Item1, currentPoint.Item2] = componentLabel;
            if (!componentSizes.ContainsKey(componentLabel))
              componentSizes[componentLabel] = 1;
            else
              componentSizes[componentLabel]++;
            foreach (var direction in Directions) {
              queue.Enqueue((currentPoint.Item1 + direction.Item1,
                             currentPoint.Item2 + direction.Item2));
            }
          }
          maxComponentSize =
              Math.Max(maxComponentSize, componentSizes[componentLabel]);
          componentLabel++;
        }
      }
    }
    // Second pass: Evaluate maximum component size if we fill a row
    for (int i = 0; i < rowCount; i++) {
      long totalArea = 0;
      HashSet<long> componentLabels = new HashSet<long>();
      for (int j = 0; j < columnCount; j++) {
        if (grid[i][j] == '#') {
          componentLabels.Add(components[i, j]);
        } else {
          totalArea++; // Count the '.' cell in the row
          // Check adjacent '#' cells (up and down)
          if (i > 0 && grid[i - 1][j] == '#') {
            componentLabels.Add(components[i - 1, j]);
          }
          if (i + 1 < rowCount && grid[i + 1][j] == '#') {
            componentLabels.Add(components[i + 1, j]);
          }
        }
      }
      foreach (long label in componentLabels) {
        totalArea += componentSizes[label];
      }
      maxComponentSize = Math.Max(maxComponentSize, totalArea);
    }
    // Third pass: Evaluate maximum component size if we fill a column
    for (int j = 0; j < columnCount; j++) {
      long totalArea = 0;
      HashSet<long> componentLabels = new HashSet<long>();
      for (int i = 0; i < rowCount; i++) {
        if (grid[i][j] == '#') {
          componentLabels.Add(components[i, j]);
        } else {
          totalArea++; // Count the '.' cell in the column
          // Check adjacent '#' cells (left and right)
          if (j > 0 && grid[i][j - 1] == '#') {
            componentLabels.Add(components[i, j - 1]);
          }
          if (j + 1 < columnCount && grid[i][j + 1] == '#') {
            componentLabels.Add(components[i, j + 1]);
          }
        }
      }
      foreach (long label in componentLabels) {
        totalArea += componentSizes[label];
      }
      maxComponentSize = Math.Max(maxComponentSize, totalArea);
    }
    writer.WriteLine(maxComponentSize);
  }
  static void Main(string[] args) {
    using (
        StreamReader reader = new StreamReader(
            Console
                .OpenStandardInput())) using (StreamWriter writer =
                                                  new StreamWriter(
                                                      Console
                                                          .OpenStandardOutput())) {
      int testCaseCount = int.Parse(reader.ReadLine());
      for (int i = 0; i < testCaseCount; i++) {
        SolveTestCase(i, reader, writer);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/