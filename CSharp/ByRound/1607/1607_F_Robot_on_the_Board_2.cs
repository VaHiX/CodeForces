// Problem: CF 1607 F - Robot on the Board 2
// https://codeforces.com/contest/1607/problem/F

/*
Problem: Robot on the Board 2
Approach:
This problem requires finding the maximum number of steps a robot can take starting from any cell on a grid, where each cell contains a direction command. The robot moves according to these commands, but stops if it goes out of bounds or visits a cell it has already visited.

The solution uses:
1. DFS with a stack to simulate robot movement
2. Dynamic programming to track maximum steps from each cell
3. Cycle detection to handle loops in movement

Time Complexity: O(n * m) where n is number of rows and m is number of columns
Space Complexity: O(n * m) for storing the grid and DP arrays

Algorithms/Techniques:
- Depth First Search with explicit stack (iterative DFS)
- Dynamic Programming with memoization
- Cycle detection in directed graph traversal
- Grid coordinate mapping using row-major order
*/

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace VaHiX
{
    internal class Program
    {
        private static readonly StreamReader reader = new StreamReader(
            Console.OpenStandardInput(1024 * 10),
            Encoding.ASCII,
            false,
            1024 * 10
        );
        private static readonly StreamWriter writer = new StreamWriter(
            Console.OpenStandardOutput(1024 * 10),
            Encoding.ASCII,
            1024 * 10
        );
        private static readonly int[] dx = new[] { 0, -1, 0, 1 }; // Direction deltas for x (L, U, R, D)
        private static int[] dy = new[] { -1, 0, 1, 0 }; // Direction deltas for y (L, U, R, D)
        private static int[] nm; // Direction mapping for each cell (0-3 for U,D,R,L)
        private static int[] dp; // DP array storing maximum steps from each cell
        private static int n; // Number of rows
        private static int m; // Number of columns

        private static void Main(string[] args)
        {
            int t = int.Parse(reader.ReadLine());
            for (int i = 0; i < t; i++)
            {
                Solve();
            }
            writer.Flush();
        }

        private static void Solve()
        {
            reader.ReadLine(); // Read empty line
            string[] ss = reader.ReadLine().Split(' ');
            n = int.Parse(ss[0]);
            m = int.Parse(ss[1]);
            // Reassign dy with grid-specific direction deltas (accounting for row-major order)
            dy = new[] { -m, 0, m, 0 };
            nm = new int[n * m]; // Direction mapping for all cells
            dp = new int[n * m]; // DP array for maximum steps from each cell
            for (int i = 0; i < n; i++)
            {
                string s = reader.ReadLine();
                for (int j = 0; j < m; j++)
                {
                    // Map character directions to numeric values (0-3)
                    if (s[j] == 'U')
                        nm[i * m + j] = 0;
                    if (s[j] == 'D')
                        nm[i * m + j] = 2;
                    if (s[j] == 'R')
                        nm[i * m + j] = 3;
                    if (s[j] == 'L')
                        nm[i * m + j] = 1;
                }
            }
            // Run DFS for all unvisited cells to fill DP array
            for (int i = 0; i < dp.Length; i++)
            {
                if (dp[i] == 0)
                {
                    Dfs(i, -1);
                }
            }
            // Find cell with maximum steps
            int max = dp[0];
            int i1 = 0;
            for (int i = 0; i < dp.Length; i++)
            {
                if (dp[i] > max)
                {
                    max = dp[i];
                    i1 = i;
                }
            }
            // Output the result as 1-indexed row, column and maximum steps
            writer.Write(i1 / m + 1);
            writer.Write(' ');
            writer.Write(i1 % m + 1);
            writer.Write(' ');
            writer.WriteLine(max);
        }

        private static void Dfs(int ii, int dd)
        {
            var st1 = new Stack<int>(); // Stack for cell indices
            var st3 = new Stack<int>(); // Stack for step counts
            st1.Push(ii); // Start with initial cell
            st3.Push(dd); // Start with initial step count
            bool c = false; // Flag for detecting cycle completion
            while (st1.Count > 0)
            {
                int i = st1.Pop(); // Current cell index
                int d = st3.Pop(); // Current step count
                int x = i + dy[nm[i]] + dx[nm[i]]; // Calculate next cell index
                if (d == 0)
                {
                    // Processing a cell that's in the middle of a loop
                    if (c)
                    {
                        // If we're ending a loop, set current cell's steps based on next cell
                        if (dp[i] > 0)
                        {
                            c = false;
                            continue;
                        }
                        dp[i] = dp[x];
                        continue;
                    }
                    // Normal case - increment step count
                    dp[i] = 1 + dp[x];
                    continue;
                }
                // Check if next cell is out of bounds
                if (x < 0 || x >= nm.Length || (dx[nm[i]] != 0 && x / m != i / m))
                {
                    dp[i] = 1; // Can only move one step before falling off
                    c = false;
                    continue;
                }
                // If next cell hasn't been processed yet
                if (dp[x] == 0)
                {
                    dp[i] = d; // Set current cell's steps to d
                    st1.Push(i); // Push current cell again for future processing
                    st3.Push(0); // Set its step count to 0 (for cycle detection)
                    st1.Push(x); // Push next cell to process
                    st3.Push(d - 1); // Decrement remaining steps
                    continue;
                }
                // If next cell is in a cycle (marked with negative value)
                if (dp[x] < 0)
                {
                    int len = dp[x] - d + 1; // Calculate the cycle length
                    dp[x] = len; // Update cycle length
                    dp[i] = len; // Set current cell's steps to cycle length
                    c = true; // Set flag that we're in a cycle
                    continue;
                }
                // Next cell has already been processed and is not in a cycle
                dp[i] = 1 + dp[x]; // Steps = 1 + steps from next cell
                c = false; // Reset cycle flag
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
