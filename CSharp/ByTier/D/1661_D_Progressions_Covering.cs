// Problem: CF 1661 D - Progressions Covering
// https://codeforces.com/contest/1661/problem/D

/*
 * Problem: D. Progressions Covering
 *
 * Algorithm: Difference Array + Greedy
 *
 * Time Complexity: O(n), where n is the length of array b
 * Space Complexity: O(k), where k is the subsegment length
 *
 * Approach:
 * - Use a greedy method from right to left.
 * - Maintain a "difference array" concept using a sliding window of size k.
 * - For each position i, calculate how many operations are needed to make a[i] >= b[i].
 * - Use a running sum (cs) to track the cumulative effect of operations in the window.
 * - Update the operation counts in the window and propagate the effect.
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
            int count = 1;
            List<string> output = new List<string>();
            Dictionary<string, int> dp = new Dictionary<string, int>();
            for (int z = 0; z < count; z++)
            {
                var a = Console.ReadLine().Split(' ').Select(s => long.Parse(s)).ToList();
                var b = Console.ReadLine().Split(' ').Select(s => long.Parse(s)).ToList();
                int n = (int)a[0];
                int k = (int)a[1];
                long o = 0; // Total operations count
                long[] op2 = new long[k]; // Sliding window to track operations
                long cs = 0; // Cumulative sum of operations in the window
                long mu = 0; // Current operation count at the start of window
                int id0 = 0; // Index to track the sliding window
                for (int i = n - 1; i >= 0; i--)
                {
                    // Remove the effect of the element that is now out of the window
                    cs -= mu;
                    // Update mu to reflect the removal of the oldest element in the window
                    mu -= op2[id0];
                    id0++;
                    id0 = id0 % k; // Move window index
                    // Calculate how many more operations are needed at position i
                    long lo = (long)
                        Math.Ceiling((0.0 + Math.Max(b[i] - cs, 0)) / Math.Min(i + 1, k));
                    o += lo; // Add operations to total
                    mu += lo; // Add to current window state
                    if (k <= i + 1)
                    {
                        // If the window is full (size k), update last element
                        op2[(k - 1 + id0) % k] = lo;
                        cs += lo * k; // Add to cumulative sum
                    }
                    else
                    {
                        // If the window is not full, update partial window
                        op2[(i + id0) % k] = lo;
                        op2[(k - 1 + id0) % k] = 0; // Clear the last element
                        cs += lo * (i + 1); // Add to cumulative sum based on actual window size
                    }
                }
                output.Add(o.ToString());
            }
            output.ForEach(d => Console.WriteLine(d));
        }
    }
}


// https://github.com/VaHiX/CodeForces/
