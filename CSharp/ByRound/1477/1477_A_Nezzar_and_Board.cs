// Problem: CF 1477 A - Nezzar and Board
// https://codeforces.com/contest/1477/problem/A

/*
 * Problem: Nezzar and Board
 * Algorithm: Mathematical Analysis using GCD
 * Time Complexity: O(n log n) per test case due to sorting and GCD computation
 * Space Complexity: O(1) additional space (excluding input storage)
 *
 * Key Insight:
 * The operation 2x - y allows generating new numbers, but all generated values follow a pattern.
 * The set of possible numbers that can be generated is determined by the GCD of differences between initial numbers.
 * Specifically, we can generate any number of the form: x1 + d * t where d = GCD(|x_i - x_j|) for all pairs (i,j).
 * Hence, k is achievable if and only if (k - x1) is divisible by d.
 *
 * Approach:
 * 1. Sort the input array
 * 2. Compute the GCD of all differences between consecutive elements
 * 3. Check if (k - first_element) is divisible by computed GCD
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace NezzarAndBoard {
    class Program {
        static void Main(string[] args) {
            int t = int.Parse(Console.ReadLine());
            for (int i = 0; i < t; i++) {
                var input = Console.ReadLine().Split();
                int n = int.Parse(input[0]);
                long k = long.Parse(input[1]);
                var x = Console.ReadLine().Split().Select(long.Parse).ToArray();

                // Sort the array to easily compute differences
                Array.Sort(x);

                // Compute GCD of all adjacent differences
                long gcd = 0;
                for (int j = 1; j < n; j++) {
                    gcd = GCD(gcd, Math.Abs(x[j] - x[j - 1]));
                }

                // Check if k can be achieved using the formula: k = x[0] + t * gcd
                // This means (k - x[0]) must be divisible by gcd
                if ((k - x[0]) % gcd == 0) {
                    Console.WriteLine("YES");
                } else {
                    Console.WriteLine("NO");
                }
            }
        }

        // Helper method to compute GCD of two numbers
        static long GCD(long a, long b) {
            return b == 0 ? a : GCD(b, a % b);
        }
    }
}


// https://github.com/VaHiX/codeForces/