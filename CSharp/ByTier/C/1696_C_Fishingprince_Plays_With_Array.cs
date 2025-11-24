// Problem: CF 1696 C - Fishingprince Plays With Array
// https://codeforces.com/contest/1696/problem/C

﻿/*
 * Problem: Fishingprince Plays With Array
 *
 * Task: Determine if array 'a' can be transformed into array 'b' using two specific operations:
 *       1. Split an element divisible by m into m copies of a_i/m
 *       2. Merge m identical elements into one element with value m * element_value
 *
 * Approach:
 * - Normalize both arrays by decomposing elements into their base form (divided by m until not divisible)
 * - Track the count of how many copies of each base we expect to have
 * - Process elements from both arrays sequentially ensuring that we can form the target array
 *
 * Time Complexity: O(n + k) where n and k are the lengths of arrays a and b.
 * Space Complexity: O(1) - only using a constant amount of extra space.
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
                var q = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
                var n = q[0];
                var m = q[1];
                var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
                Console.ReadLine();
                var b = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
                bool can = true;
                int i = 1; // pointer for array a
                int j = 0; // pointer for array b
                long currentRemainder = a[0]; // base value of current segment in a
                long currentCountLeft = 1; // number of copies of currentRemainder we expect
                // Normalize the first element of a by dividing by m until not divisible
                while (currentRemainder % m == 0)
                {
                    currentRemainder /= m;
                    currentCountLeft *= m;
                }
                // Early check: sums must be equal for transformation to be possible
                if (a.Sum() != b.Sum())
                    can = false;
                if (can)
                {
                    // Process the arrays until all elements are consumed
                    while (i < a.Count || j < b.Count)
                    {
                        long tempRemainder;
                        long tempCountLeft;
                        // Process next element from array a if available
                        if (i < a.Count)
                        {
                            tempRemainder = a[i];
                            tempCountLeft = 1;
                            // Normalize tempRemainder (divide by m until not divisible)
                            while (tempRemainder % m == 0)
                            {
                                tempRemainder /= m;
                                tempCountLeft *= m;
                            }
                            // If we've exhausted previous segment, start a new one
                            if (currentCountLeft == 0)
                            {
                                currentRemainder = tempRemainder;
                            }
                            // If normalized values match, accumulate count
                            if (tempRemainder == currentRemainder)
                            {
                                currentCountLeft += tempCountLeft;
                                i++;
                                continue;
                            }
                        }
                        // Process next element from array b
                        tempRemainder = b[j];
                        tempCountLeft = 1;
                        // Normalize tempRemainder for b
                        while (tempRemainder % m == 0)
                        {
                            tempRemainder /= m;
                            tempCountLeft *= m;
                        }
                        // Verify that we can form this segment from current remainder
                        if (tempRemainder == currentRemainder && currentCountLeft >= tempCountLeft)
                        {
                            currentCountLeft -= tempCountLeft;
                            j++;
                        }
                        else
                        {
                            can = false;
                            break;
                        }
                    }
                }
                // Final validation: check if all elements have been processed correctly
                if (i < a.Count || currentCountLeft > 0)
                    can = false;
                if (can)
                    output.Add("Yes");
                else
                    output.Add("No");
            }
            output.ForEach(d => Console.WriteLine(d));
        }
    }
}


// https://github.com/VaHiX/CodeForces/
