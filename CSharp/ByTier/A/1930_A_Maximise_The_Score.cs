// Problem: CF 1930 A - Maximise The Score
// https://codeforces.com/contest/1930/problem/A

﻿/*
 * Problem: Maximize The Score
 * 
 * Algorithm/Technique: Greedy approach with sorting
 * 
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the array of numbers
 * 
 * Approach:
 * - Sort the array of 2n integers in ascending order.
 * - To maximize the score, we should always pair the smallest available numbers.
 * - By pairing the smallest elements together, we ensure that the minimum of each pair is as large as possible.
 * - The optimal strategy is to take the first element (smallest) in each pair and add it to the score.
 * - Since we are pairing adjacent elements after sorting, we only need to sum every other element starting from index 0.
 * 
 * Example walkthrough:
 *   For input [1, 1, 2, 1], sorted becomes [1, 1, 1, 2].
 *   Pairs: (1,1) and (1,2)
 *   Score: min(1,1) + min(1,2) = 1 + 1 = 2
 * 
 * This greedy strategy ensures that we always pick the smallest available value,
 * which is optimal because pairing smaller values together maximizes the total score.
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
                input = Console.ReadLine().Split(new char[] { ' ' },
                                                 StringSplitOptions.RemoveEmptyEntries);
                int[] numbers = new int[2 * n];
                for (int i = 0; i < 2 * n; i++) {
                    numbers[i] = int.Parse(input[i]);
                }
                Array.Sort(numbers); // Sort the array in ascending order
                int sum = 0;
                int j = 0;
                while (j < 2 * n) {
                    sum += numbers[j]; // Add the smaller element of each pair to score
                    j += 2; // Move to next unpaired element
                }
                Console.WriteLine(sum);
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/