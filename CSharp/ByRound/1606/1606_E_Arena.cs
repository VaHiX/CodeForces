// Problem: CF 1606 E - Arena
// https://codeforces.com/contest/1606/problem/E

/*
 * Problem: E. Arena
 * Algorithm: Dynamic Programming with Inclusion-Exclusion Principle
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 *
 * The problem asks to count the number of ways to assign health points to heroes
 * such that no hero wins (i.e., there's no hero who survives all rounds).
 *
 * Approach:
 * - Use dynamic programming where mas[i, j] represents the number of ways to assign
 *   health points such that exactly i heroes survive and the minimum health is j.
 * - Precompute factorials and binomial coefficients for combinatorial calculations.
 * - Apply inclusion-exclusion principle and dynamic programming to count valid assignments.
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace VaHiX
{
    class Program
    {
        static long mod = 998244353L;

        static void Main(string[] args)
        {
            var input = Console.ReadLine().Split(' ').Select(int.Parse).ToList();
            int n = input[0],
                x = input[1];

            // Precompute powers of integers up to n
            var xar = new long[n + 1, n + 1];
            for (int i = 1; i <= n; i++)
            {
                xar[i, 0] = 1;
                for (int j = 1; j <= n; j++)
                    xar[i, j] = (xar[i, j - 1] * i) % mod;
            }

            // Precompute binomial coefficients
            var c = new long[n + 1, n + 1];
            c[0, 0] = 1;
            for (int i = 1; i <= n; i++)
            {
                c[i, 0] = 1;
                for (int k = 1; k <= i; k++)
                    c[i, k] = (c[i - 1, k - 1] + c[i - 1, k]) % mod;
            }

            // Dynamic programming calculation
            var mas = new long[n + 1, x + 1];
            for (int i = 1; i <= n; i++)
            {
                for (int j = i; j <= x; j++)
                {
                    if (i == 1)
                    {
                        mas[i, j] = j;
                        continue;
                    }
                    for (int k = 0; k < i; k++)
                        mas[i, j] =
                            (
                                mas[i, j]
                                + (((xar[i - 1, k] * c[i, k]) % mod) * mas[i - k, j - i + 1]) % mod
                            ) % mod;
                }
            }

            // Total number of ways to assign health points (x^n)
            long xn = 1;
            for (int i = 1; i <= n; i++)
                xn = (xn * x) % mod;

            // Result = Total - Ways where at least one hero wins
            var res = (xn - mas[n, x] + mod) % mod;
            Console.Write(res);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
