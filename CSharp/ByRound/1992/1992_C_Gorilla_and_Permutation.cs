// Problem: CF 1992 C - Gorilla and Permutation
// https://codeforces.com/contest/1992/problem/C

/*
 * Problem: Gorilla and Permutation
 *
 * Purpose:
 *   Given integers n, m, k (where m < k), construct a permutation of length n
 *   such that the difference between the sum of f(i) and the sum of g(i) over all prefixes is maximized.
 *
 *   Where:
 *     - f(i) = sum of elements in prefix i that are >= k
 *     - g(i) = sum of elements in prefix i that are <= m
 *
 * Algorithm:
 *   The strategy is to place large numbers (>= k) early in the array to maximize f(i) values,
 *   and small numbers (<= m) towards the end to minimize g(i) contributions.
 *   Specifically:
 *     1. Place numbers from n down to m+1 (all > m) at the beginning.
 *     2. Then place numbers from 1 to m (all <= m) at the end.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the result list
 *
 * Techniques:
 *   Greedy construction based on value ranges to maximize prefix function differences.
 */

using System;
using System.Collections.Generic;

public class Program
{
    public static void Main()
    {
        int T = int.Parse(Console.ReadLine()); // Read number of test cases
        for (int t = 0; t < T; t++)
        {
            string[] token = Console.ReadLine().Split();
            int n = int.Parse(token[0]);
            int m = int.Parse(token[1]);
            int k = int.Parse(token[2]);
            List<int> ans = new List<int>(); // Initialize result list

            // Add numbers from n down to m+1 (these are > m, so they contribute to f(i) but not g(i))
            for (int i = n; i >= m + 1; i--)
                ans.Add(i);

            // Add numbers from 1 to m (these are <= m, so they contribute to g(i) but not f(i))
            for (int i = 1; i <= m; i++)
                ans.Add(i);

            Console.WriteLine(string.Join(" ", ans)); // Output the constructed permutation
        }
    }
}


// https://github.com/VaHiX/CodeForces/
