// Problem: CF 2046 A - Swap Columns and Find a Path
// https://codeforces.com/contest/2046/problem/A

﻿/*
 * Problem: Swap Columns and Find a Path
 * 
 * Algorithm/Technique: Greedy approach with optimal column swapping.
 * 
 * Time Complexity: O(n) per test case, where n is the number of columns.
 * Space Complexity: O(1) additional space (excluding input storage).
 * 
 * Approach:
 * - For each column, decide whether to take the value from row 1 or row 2.
 * - The key idea is that we can freely swap columns, so we want to maximize
 *   the sum of values in the path from (1,1) to (2,n).
 * - Path can only go down or right, so the optimal choice at each step is
 *   to pick the maximum of the two values in a column.
 * - However, we must ensure that the last column contributes an optimal
 *   value by taking the maximum of the two values, but also possibly
 *   allowing one column to contribute the smaller value to maintain
 *   a valid path from start to end.
 * - This is handled by keeping track of the best possible minimum value
 *   that we've seen so far, ensuring the last element contributes optimally.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NewContest {
    internal class Program {
        static void Main(string[] args) {
            int t = int.Parse(Console.ReadLine());
            for (int o = 0; o < t; o++) {
                string[] input = Console.ReadLine().Split(
                    new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                int m = int.Parse(input[0]);
                int[,] matrix = new int[2, m];
                for (int i = 0; i < 2; i++) {
                    input = Console.ReadLine().Split(new char[] { ' ' },
                                                     StringSplitOptions.RemoveEmptyEntries);
                    for (int j = 0; j < m; j++) {
                        matrix[i, j] = int.Parse(input[j]);
                    }
                }
                int maxCost = 0;
                int maxmin = -10000000; // Initialize to a very small value
                for (int j = 0; j < m; j++) {
                    if (matrix[0, j] > matrix[1, j]) {
                        maxCost += matrix[0, j]; // Choose the larger value from row 1
                        if (matrix[1, j] > maxmin) { // Update maxmin with the smaller value
                            maxmin = matrix[1, j];
                        }
                    } else {
                        maxCost += matrix[1, j]; // Choose the larger value from row 2
                        if (matrix[0, j] > maxmin) { // Update maxmin with the smaller value
                            maxmin = matrix[0, j];
                        }
                    }
                }
                maxCost += maxmin; // Add the best minimum value to make sure path is valid
                Console.WriteLine(maxCost);
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/