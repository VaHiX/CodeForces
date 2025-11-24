// Problem: CF 1774 B - Coloring
// https://codeforces.com/contest/1774/problem/B

﻿/*
 * Problem: Coloring
 * Algorithm/Techniques: Greedy, Mathematical Analysis
 *
 * Time Complexity: O(m) per test case, where m is the number of colors.
 * Space Complexity: O(m) for storing color counts.
 *
 * Approach:
 * - The key insight is that in any k consecutive cells, all colors must be distinct.
 * - This implies that the maximum count of any color (m) must not exceed the total number of cells divided by k,
 *   plus a correction term based on how many colors have the maximum count.
 * - We compute the maximum count (m), and count how many colors have this maximum (mc).
 * - Then we check if the total number of cells is sufficient to place all colors under the constraint.
 *   The inequality: n >= (m - 1) * k + mc is used to validate feasibility.
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace Compete2
{
    partial class MainClass
    {
        public static void Main(string[] args)
        {
            int count = int.Parse(Console.ReadLine()); // Read number of test cases
            List<string> output = new List<string>();
            for (int z = 0; z < count; z++)
            {
                var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read n, m, k
                var b = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read color counts
                bool can = true;

                long m = b.Max(); // Find the maximum count of any color
                long mc = b.Where(i => i == m).Count(); // Count how many colors have maximum count

                // Check if it's possible to fit all colors under the k-consecutive constraint
                if (a[0] < (b.Max() - 1) * a[2] + mc)
                    can = false; // If not feasible, mark as impossible

                if (can)
                    output.Add("YES");
                else
                    output.Add("NO");
            }
            string on = string.Join("\n", output);
            Console.WriteLine(on);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
