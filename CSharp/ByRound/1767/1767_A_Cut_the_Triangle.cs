// Problem: CF 1767 A - Cut the Triangle
// https://codeforces.com/contest/1767/problem/A

﻿/*
 * Problem: Cut the Triangle
 *
 * Purpose: Determine if a given non-degenerate triangle can be cut by a horizontal or vertical line
 *          into two non-degenerate triangles.
 *
 * Algorithm:
 * - For a triangle to be cut into two triangles by a horizontal or vertical line,
 *   the line must intersect two sides of the triangle and must not pass through any vertex.
 * - If all three vertices have at most 2 distinct x-coordinates OR at most 2 distinct y-coordinates,
 *   then it's impossible to cut the triangle into two triangles with a horizontal or vertical line,
 *   because the triangle would either collapse into a line or not be divided properly.
 *
 * Time Complexity: O(1) - We perform a fixed number of operations (3 vertices, 2 distinct checks)
 * Space Complexity: O(1) - We use fixed-size data structures (lists with 3 elements each)
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace Compete3
{
    partial class MainClass
    {
        public static void Main(string[] args)
        {
            int count = int.Parse(Console.ReadLine());
            List<string> output = new List<string>();
            for (int z = 0; z < count; z++)
            {
                var s = Console.ReadLine();
                bool can = true;
                List<long> x = new List<long>();
                List<long> y = new List<long>();
                for (int i = 0; i < 3; i++)
                {
                    s = Console.ReadLine();
                    var a = s.Split(' ').Select(qw => long.Parse(qw)).ToList();
                    x.Add(a[0]);
                    y.Add(a[1]);
                }
                // Check if all x-coordinates or all y-coordinates are unique
                // If there are at most 2 distinct x or y coordinates, the triangle cannot be cut properly
                if (x.Distinct().Count() <= 2 && y.Distinct().Count() <= 2)
                {
                    can = false;
                }
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
