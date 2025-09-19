using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace CodeForces.Problems.Round2131.F
{
    /// <summary>
    /// Problem: CF2131F - Unjust Binary Life
    /// 
    /// This program solves a problem involving binary strings and calculates metrics
    /// related to the difference between counts of '1's and '0's in prefixes of the input strings.
    /// 
    /// Approach:
    /// 1. Calculate prefix sums of '0's and '1's for the input strings
    /// 2. Compute the difference between counts of '1's and '0's for each position
    /// 3. Process these differences to calculate various metrics
    /// 
    /// Time Complexity: O(n log n) due to sorting
    /// Space Complexity: O(n)
    /// </summary>
    public class UnjustBinaryLifeSolver
    {
        private static readonly StreamReader _reader = new(Console.OpenStandardInput());
        private static readonly StreamWriter _writer = new(Console.OpenStandardOutput());

        /// <summary>
        /// Solves the Unjust Binary Life problem
        /// </summary>
        public static long CalculateUnfairness(int n, string a, string b)
        {
            // Prefix sums for '0's and '1's
            var prefixCounts = new int[n, 2];
            
            // Calculate prefix sums
            for (int i = 0; i < n; i++)
            {
                prefixCounts[i, a[i] - '0']++;
                if (i > 0)
                st_plus.Push(1 + st_plus.Pop());
            }
        }
        for (int i = 0; i < n; i++) if (d[i] == 0) zero++;


        long ans = 0;
        long s = 1L * n * (n + 1) / 2;
        for (int i = 0; i < n; i++)
        {
            s += n;
            if (b[i] == '1')
            {
                st_plus.Push(zero);
                count_plus += zero;
                sum_plus += count_plus;

                if (st_minus.Count > 0)
                {
                    zero = st_minus.Pop();
                    sum_minus -= count_minus;
                    count_minus -= zero;
                }
                else
                {
                    zero = 0;
                }
            }
            else
            {
                st_minus.Push(zero);
                count_minus += zero;
                sum_minus += count_minus;
                if (st_plus.Count > 0)
                {
                    zero = st_plus.Pop();
                    sum_plus -= count_plus;
                    count_plus -= zero;
                }
                else
                {
                    zero = 0;
                }
            }
            ans += (s - sum_plus - sum_minus) / 2;
        }
        return ans;
    }

    static void Main(string[] args)
    {
        int t = int.Parse(reader.ReadLine());
        for (int i = 0; i < t; i++)
        {
            writer.WriteLine(Solve());
        }
        writer.Flush();
    }

    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}