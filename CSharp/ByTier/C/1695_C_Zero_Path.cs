// Problem: CF 1695 C - Zero Path
// https://codeforces.com/contest/1695/problem/C

﻿/*
 * Problem: Zero Path
 *
 * Purpose: Determine if there exists a path from the top-left to bottom-right corner of a grid,
 *          moving only right or down, such that the sum of all visited cell values equals zero.
 *
 * Algorithm: Dynamic Programming with min/max tracking.
 *   - For each cell (i,j), track the minimum and maximum possible sums achievable to reach that cell.
 *   - At each step, update the min/max values based on the previous row or column.
 *   - A valid path exists if there's a way to get sum = 0, which means:
 *     1. The final sum is even (since all values are ±1, total must be even to be 0)
 *     2. The minimum sum is ≤ 0 and maximum sum is ≥ 0
 *
 * Time Complexity: O(n*m) where n and m are grid dimensions
 * Space Complexity: O(m) for storing min and max values for each column
 *
 * Techniques:
 *   - Dynamic Programming with prefix tracking
 *   - Min/max value propagation
 *   - Path sum feasibility checking
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace VaHiX
{
    partial class MainClass
    {
        public static void Main(string[] args)
        {
            int count = int.Parse(Console.ReadLine());
            List<string> output = new List<string>();
            for (int z = 0; z < count; z++)
            {
                var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
                bool can = true;
                int[,] d = new int[a[0], a[1]];
                for (int i = 0; i < a[0]; i++)
                {
                    var b = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
                    for (int j = 0; j < a[1]; j++)
                        d[i, j] = b[j];
                }
                // Arrays to store minimum and maximum possible sums to reach each column
                int[] mi = new int[a[1]];
                int[] ma = new int[a[1]];

                // Initialize first cell
                mi[0] = d[0, 0];
                ma[0] = d[0, 0];

                // Fill first row with cumulative sums (only right moves possible)
                for (int j = 1; j < a[1]; j++)
                {
                    mi[j] = mi[j - 1] + d[0, j];
                    ma[j] = ma[j - 1] + d[0, j];
                }

                // Fill the rest of the grid row by row
                for (int i = 1; i < a[0]; i++)
                {
                    // Update first column (only down moves from previous row)
                    mi[0] = mi[0] + d[i, 0];
                    ma[0] = ma[0] + d[i, 0];

                    // Update other columns (choose between coming from left or above)
                    for (int j = 1; j < a[1]; j++)
                    {
                        mi[j] = Math.Min(mi[j - 1], mi[j]) + d[i, j]; // Take minimum of possible paths
                        ma[j] = Math.Max(ma[j - 1], ma[j]) + d[i, j]; // Take maximum of possible paths
                    }
                }

                // Check if zero sum is achievable:
                // 1. Final sum should be even (path sum of ±1 values must be even to be 0)
                // 2. Minimum value should be <= 0 and maximum should be >= 0
                if (mi[a[1] - 1] % 2 != 0)
                    can = false;
                if (mi[a[1] - 1] > 0 || ma[a[1] - 1] < 0)
                    can = false;

                if (can)
                    output.Add("YES");
                else
                    output.Add("NO");
            }
            output.ForEach(d => Console.WriteLine(d));
        }
    }
}


// https://github.com/VaHiX/CodeForces/
