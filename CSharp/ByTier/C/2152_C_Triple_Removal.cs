// Problem: CF 2152 C - Triple Removal
// https://codeforces.com/contest/2152/problem/C

/*
 * Problem: C. Triple Removal
 * Algorithm: Dynamic Programming with Prefix Sums
 * Time Complexity: O(n + q) per test case
 * Space Complexity: O(n) per test case
 *
 * For each query, we need to determine the minimum cost to remove all elements 
 * from a subarray such that each removal operation involves three identical 
 * elements and costs min(k-j, j-i). We use prefix sums to quickly compute:
 * - Total count of 0s and 1s in any range
 * - Count of 1s at odd indices (for determining patterns)
 *
 * Key observations:
 * - If a subarray length is not divisible by 3, impossible
 * - If total sum is not divisible by 3, impossible 
 * - If sum equals number of elements or zero, the cost can be adjusted based on parity checks
 */

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace TripleRemoval
{
    class Program
    {
        static void Solve()
        {
            int n = Next();
            int q = Next();
            int[] a = new int[n];
            for (int i = 0; i < n; i++)
                a[i] = Next(); // Read array elements
            int[] s = new int[n + 1]; // Prefix sum of all elements
            int[] s2 = new int[n + 1]; // Prefix sum of 1s at odd indices (1-based indexing)
            for (int i = 0; i < n; i++)
            {
                s[i + 1] = s[i] + a[i]; // Accumulate total values
                if ((i & 1) == 1)       // If index is odd (1-based)
                    s2[i + 1] = s2[i] + a[i]; 
                else
                    s2[i + 1] = s2[i];      // Otherwise no increment
            }
            while (q-- > 0)
            {
                int l = Next() - 1;     // Convert from 1-based to 0-based
                int r = Next();
                if ((r - l) % 3 != 0)   // If length not divisible by three, impossible
                {
                    writer.WriteLine("-1");
                    continue;
                }
                int all = s[r] - s[l]; // Total sum in subarray - equivalent to count of 1s
                if (all % 3 != 0)       // If count of 1s not divisible by three, impossible
                {
                    writer.WriteLine("-1");
                    continue;
                }
                int half = s2[r] - s2[l]; // Count of 1s at odd positions in subarray
                
                // Special case logic to determine optimal cost
                if (all != 0 && all != (r - l) && all == (r - l) / 2 && (half == 0 || half == all))
                {
                    writer.WriteLine(1 + (r - l) / 3);  // Adjust for pattern matching condition
                }
                else
                {
                    writer.WriteLine((r - l) / 3); // Direct calculation of operations needed
                }
            }
        }

        static void Main(string[] args)
        {
            long t = Next(); // Read number of test cases
            for (int i = 0; i < t; i++)
                Solve();
            writer.Flush();
        }

        static int Next()
        {
            int c;
            int m = 1;
            int res = 0;
            do
            {
                c = reader.Read();
                if (c == '-')
                    m = -1;
            } while (c < '0' || c > '9');
            res = c - '0';
            while (true)
            {
                c = reader.Read();
                if (c < '0' || c > '9')
                    return m * res;
                res *= 10;
                res += c - '0';
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