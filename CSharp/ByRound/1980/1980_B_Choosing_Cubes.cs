// Problem: CF 1980 B - Choosing Cubes
// https://codeforces.com/contest/1980/problem/B

﻿/*
 * Problem: Choosing Cubes
 * 
 * Algorithm/Techniques: Sorting, Simulation, Conditional Logic
 * 
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the array of cube values
 * 
 * Approach:
 * 1. Read input values for n, f, k and the array of cube values.
 * 2. Find the value of the favorite cube at index f (1-based).
 * 3. Sort the array in non-increasing order.
 * 4. Compare the k-th largest value with the favorite cube's value:
 *    - If the k-th value is less than favorite value => cube is removed in all cases => YES
 *    - If the k-th value is greater than favorite value => cube is never removed => NO
 *    - Else if k == n or next element after k-th is different from favorite value => YES
 *    - Otherwise => MAYBE
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
                int n = int.Parse(input[0]);
                int f = int.Parse(input[1]);
                int k = int.Parse(input[2]);
                
                input = Console.ReadLine().Split(new char[] { ' ' },
                                                 StringSplitOptions.RemoveEmptyEntries);
                int[] numbers = new int[n];
                for (int i = 0; i < n; i++) {
                    numbers[i] = int.Parse(input[i]);
                }
                
                // Store the value of the favorite cube
                f = numbers[f - 1];
                
                // Sort the cubes in non-increasing order
                Array.Sort(numbers);
                Array.Reverse(numbers);
                
                // Check if the k-th element (after sorting) is less than favorite value
                if (numbers[k - 1] < f) {
                    Console.WriteLine("YES");
                }
                // Check if the k-th element is greater than favorite value
                else if (numbers[k - 1] > f) {
                    Console.WriteLine("NO");
                }
                // When k-th element equals favorite, determine outcome based on next element
                else if ((k == n) || (numbers[k - 1] == f && numbers[k] != f)) {
                    Console.WriteLine("YES");
                }
                // Otherwise, the favorite cube could be removed or not depending on tie breaking
                else {
                    Console.WriteLine("MAYBE");
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/