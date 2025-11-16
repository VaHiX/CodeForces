// Problem: CF 2150 B - Grid Counting
// https://codeforces.com/contest/2150/problem/B

/*
B. Grid Counting
Algorithm: Dynamic Programming + Combinatorics
Time Complexity: O(n) per test case
Space Complexity: O(n)

The problem counts the number of ways to place black cells in an n×n grid such that:
1. Row k has exactly a[k] black cells.
2. There is exactly one cell with max(x_i, y_i) = k for each k.
3. There is exactly one cell with max(x_i, n+1-y_i) = k for each k.

This problem uses the structure of the constraints to build an efficient solution based on:
- A "pyramidal" arrangement constraint that helps reduce the number of valid configurations
- Precomputed factorials and inverse factorials to compute combinations efficiently
- Dynamic programming approach from center outward to assign valid cell positions
*/

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace GridCounting
{
    class Program
    {
        static long Solve()
        {
            int n = Next(); // Read grid size
            int[] a = new int[n]; // Array of black cell counts per row
            long s = 0; // Total number of black cells
            for (int i = 0; i < n; i++)
                s += a[i] = Next(); // Populate array with input data and compute sum
            if (s != n) // Check if total black cells equals n (necessary condition)
                return 0;
            long ans = 1; // Initialize result to 1
            
            // Process the second half of the grid (from middle to end)
            for (int i = (n + 1) / 2; i < n; i++)
                if (a[i] > 0)
                    return 0; // If any row in second half has black cells, invalid configuration
                    
            // Process first half backwards
            for (int i = (n + 1) / 2 - 1, c = 1 + (n + 1) % 2; i >= 0; i--, c += 2)
            {
                if (a[i] > c)
                    return 0; // If more black cells assigned than allowed in current layer
                ans = ans * GetCFact(c, a[i]) % mod; // Multiply result by C(c, a[i])
                c -= a[i]; // Update available positions
            }
            return ans;
        }

        private const int mod = 998244353;
        private static long[] fact; // Stores factorials modulo mod
        private static long[] fact1; // Stores inverse factorials modulo mod

        private static void InitFact(int n)
        {
            fact = new long[n];
            fact1 = new long[n];
            fact[0] = 1; // Base case for factorial calculation
            for (int i = 1; i < fact.Length; i++)
            {
                fact[i] = (fact[i - 1] * i) % mod; // Compute factorials iteratively
            }
            fact1[n - 1] = Pow(fact[n - 1], mod - 2); // Compute inverse of last factorial
            for (int i = fact1.Length - 2; i >= 0; i--)
            {
                fact1[i] = (fact1[i + 1] * (i + 1)) % mod; // Compute inverse factorials iteratively
            }
        }

        private static long GetCFact(int n, int k)
        {
            return (((fact[n] * fact1[k]) % mod) * fact1[n - k]) % mod; // C(n,k) = n! / (k! * (n-k)!)
        }

        private static long Pow(long a, int k)
        {
            long r = 1; // Result initialized to 1
            while (k > 0)
            {
                if ((k & 1) == 1) // If k is odd
                {
                    r = (r * a) % mod; // Multiply result by a
                }
                a = (a * a) % mod; // Square base
                k >>= 1; // Divide exponent by 2
            }
            return r;
        }

        static void Main(string[] args)
        {
            InitFact(200001); // Initialize precomputed factorials up to 200001
            long t = Next(); // Read number of test cases
            for (int i = 0; i < t; i++)
                writer.WriteLine(Solve()); // Process each test case
            writer.Flush(); // Flush output buffer
        }

        static int Next()
        {
            int c;
            int m = 1; // Sign multiplier
            int res = 0;
            do
            {
                c = reader.Read();
                if (c == '-')
                    m = -1; // Mark negative number
            } while (c < '0' || c > '9');
            res = c - '0'; // Start building the number
            while (true)
            {
                c = reader.Read();
                if (c < '0' || c > '9')
                    return m * res; // Return final signed integer
                res *= 10;
                res += c - '0'; // Continue building number
            }
        }

        static readonly StreamReader reader = new StreamReader(
            Console.OpenStandardInput(1024 * 10),
            Encoding.ASCII,
            false,
            1024 * 10
        );
        static readonly StreamWriter writer = new StreamWriter(
            Console.OpenStandardOutput(1024 * 10),
            Encoding.ASCII,
            1024 * 10
        );
    }
}


// https://github.com/VaHiX/CodeForces/