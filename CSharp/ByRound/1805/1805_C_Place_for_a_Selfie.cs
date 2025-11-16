// Problem: CF 1805 C - Place for a Selfie
// https://codeforces.com/contest/1805/problem/C

﻿/*
 * Problem: C. Place for a Selfie
 *
 * Purpose: Determine if there exists a line y = kx that does not intersect or touch any of the given parabolas.
 *
 * Algorithm:
 * 1. For each parabola y = ax^2 + bx + c, we compute the discriminant of the equation ax^2 + bx + c = kx.
 *    This becomes ax^2 + (b - k)x + c = 0.
 * 2. For a line to not intersect the parabola, the discriminant must be negative: (b - k)^2 - 4ac < 0.
 * 3. Rearranging: (b - k)^2 < 4ac, which gives us an interval for k: b - 2*sqrt(ac) < k < b + 2*sqrt(ac).
 * 4. Since a > 0, we can find the range of k values for which the line intersects the parabola.
 * 5. Then we check if any of the given k values fall outside this interval.
 *
 * Time Complexity: O(n log n + m * log n)
 * Space Complexity: O(n + m)
 *
 * Techniques:
 * - Binary search for efficient lookup of valid k values
 * - Sorting the unique k values to enable binary search
 * - Mathematical analysis of intersection conditions for parabolas and lines
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Compete2
{
    partial class MainClass
    {
        public static void Main(string[] args)
        {
            int fyt = int.Parse(Console.ReadLine());
            List<string> output = new List<string>();
            for (int hz = 0; hz < fyt; hz++)
            {
                var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
                List<string> o = new List<string>();
                bool can = true;
                long n = a[0];
                long m = a[1];
                long[] k = new long[n];
                long[,] p = new long[m, 3];
                for (int i = 0; i < n; i++)
                {
                    var b = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToArray();
                    k[i] = b[0];
                }
                Array.Sort(k);
                k = k.ToList().Distinct().ToArray(); // Remove duplicates and sort
                for (int i = 0; i < m; i++)
                {
                    var b = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToArray();
                    p[i, 0] = b[0];
                    p[i, 1] = b[1];
                    p[i, 2] = b[2];
                    if (p[i, 0] * p[i, 2] > 0)
                    { // Check if a > 0 and c > 0 (since a > 0 is guaranteed)
                        double k1 = 0.0 + p[i, 1] - Math.Sqrt(4.0 * p[i, 0] * p[i, 2]); // Lower bound of k
                        double k2 = 0.0 + p[i, 1] + Math.Sqrt(4.0 * p[i, 0] * p[i, 2]); // Upper bound of k
                        long kl = (long)Math.Floor(k1);
                        int d = Array.BinarySearch(k, kl); // Binary search for closest k
                        if (d < 0)
                            d = ~d; // Get insertion point if not found
                        // Check nearby values in sorted k array to see if any are within the valid interval
                        if (d < k.Length && k[d] > k1 && k[d] < k2)
                        {
                            o.Add("YES");
                            o.Add(k[d].ToString());
                        }
                        else if (d + 1 < k.Length && k[d + 1] > k1 && k[d + 1] < k2)
                        {
                            o.Add("YES");
                            o.Add(k[d + 1].ToString());
                        }
                        else if (d + 2 < k.Length && k[d + 2] > k1 && k[d + 2] < k2)
                        {
                            o.Add("YES");
                            o.Add(k[d + 2].ToString());
                        }
                        else if (d - 1 < k.Length && d > 0 && k[d - 1] > k1 && k[d - 1] < k2)
                        {
                            o.Add("YES");
                            o.Add(k[d - 1].ToString());
                        }
                        else
                            o.Add("NO");
                    }
                    else
                    {
                        o.Add("NO");
                    }
                }
                output.Add(string.Join("\n", o));
            }
            string on = string.Join("\n", output);
            Console.WriteLine(on);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
