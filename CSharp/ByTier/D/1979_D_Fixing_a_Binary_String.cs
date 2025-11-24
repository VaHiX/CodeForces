// Problem: CF 1979 D - Fixing a Binary String
// https://codeforces.com/contest/1979/problem/D

/*
 * Problem: Fixing a Binary String
 *
 * Algorithm: Rolling Hash + Simulation
 *
 * Time Complexity: O(n) per test case, where n is the length of the string
 * Space Complexity: O(n) for storing hash arrays and prefix powers
 *
 * Approach:
 * 1. Precompute rolling hashes for original and reversed strings.
 * 2. For each possible pivot p, simulate the operation:
 *    - Reverse first p characters
 *    - Perform cyclic left shift of p positions
 * 3. Use rolling hash to check whether the resulting string is k-proper.
 * 4. The k-proper condition is checked by comparing against precomputed hash values of valid patterns.
 */

using System;

namespace CF1979_D_Fixing_a_Binary_String
{
    class Program
    {
        const long MOD = 100000007;

        static void Main(string[] args)
        {
            int test = int.Parse(Console.ReadLine());
            while (test-- > 0)
            {
                Solve();
            }
        }

        static void Solve()
        {
            string[] input = Console.ReadLine().Split();
            int n = int.Parse(input[0]);
            int k = int.Parse(input[1]);
            string s = Console.ReadLine().Trim();
            long[] ha = new long[n + 1]; // Hash array for prefix hashes
            long[] rha = new long[n + 2]; // Hash array for suffix hashes
            long[] p = new long[n + 1]; // Powers of 10 modulo MOD
            long h1 = 0,
                h2 = 0; // Precomputed hashes for valid k-proper patterns
            long mod = 100000007;

            // Compute prefix hashes
            for (int i = 1; i <= n; i++)
                ha[i] = (10 * ha[i - 1] + s[i - 1] - '0') % mod;

            // Compute suffix hashes
            for (int i = n; i >= 1; i--)
                rha[i] = (10 * rha[i + 1] + s[i - 1] - '0') % mod;

            // Precompute powers
            p[0] = 1;
            for (int i = 1; i <= n; i++)
                p[i] = (10 * p[i - 1]) % mod;

            // Build hash values for two possible k-proper patterns (000.. or 111.. followed by alternating)
            for (int i = 0; i < n; i++)
                h1 = (h1 * 10 + ((i / k) & 1)) % mod; // Pattern starting with 0
            for (int i = 0; i < n; i++)
                h2 = (h2 * 10 + ((i / k) & 1) ^ 1) % mod; // Pattern starting with 1

            // Lambda functions to compute hash of substring [l,r] in original and reversed
            Func<int, int, long> getha = (l, r) =>
                (ha[r] - (ha[l - 1] * p[r - l + 1] % mod) + mod) % mod;
            Func<int, int, long> getrha = (l, r) =>
                (rha[l] - (rha[r + 1] * p[r - l + 1] % mod) + mod) % mod;

            // Try all possible pivots
            for (int i = 1; i <= n; i++)
            {
                // Compute hash of transformed string using prefix and suffix hashes
                long h = ((getha(i + 1, n) * p[i]) % mod + getrha(1, i)) % mod;

                // Check if the computed hash matches one of the valid k-proper patterns
                if (h == h1 || h == h2)
                {
                    Console.WriteLine(i);
                    return;
                }
            }

            // If no valid pivot found, output -1
            Console.WriteLine(-1);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
