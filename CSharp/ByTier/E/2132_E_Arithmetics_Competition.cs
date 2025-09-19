using System;
using System.Text;

namespace CodeForces.Problems.Round2132.E
{
    /// <summary>
    /// Problem: CF2132E - Arithmetics Competition
    /// 
    /// This program solves a problem where we need to select x elements from array A and y elements from array B
    /// such that the sum of selected elements is maximized. The solution uses a greedy approach with prefix sums.
    /// 
    /// Approach:
    /// 1. Sort both arrays in descending order
    /// 2. Create a merged array C that represents the optimal selection between A and B
    /// 3. Precompute prefix sums for efficient range sum queries
    /// 4. For each query (x, y), compute the maximum sum by combining elements from A and B
    /// 
    /// Time Complexity: O((n + m) log (n + m) + q) where n and m are array sizes, q is number of queries
    /// Space Complexity: O(n + m)
    /// </summary>
    public static class ArithmeticsCompetition
    {
        private static readonly StreamReader _reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
        private static readonly StreamWriter _writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);

        /// <summary>
        /// Solves the problem for given arrays A and B and processes the queries
        /// </summary>
        public static void Solve()
        {
            // Read input sizes
            int n = ReadInt();  // Size of array A
            int m = ReadInt();  // Size of array B
            int q = ReadInt();  // Number of queries

            // Read and sort arrays in descending order
            long[] arrayA = ReadAndSortArray(n);
            long[] arrayB = ReadAndSortArray(m);

            // Merge arrays while keeping track of which array each element came from
            var (merged, prefixA, prefixB) = MergeArrays(arrayA, arrayB);
            
            // Precompute prefix sums for array A and B
            ComputePrefixSums(arrayA);
            ComputePrefixSums(arrayB);
            {
                writer.WriteLine(c[z]);
            }
            else if (ca[z] <= x)
            {
                writer.WriteLine((y > 0 ? b[y - 1] : 0) + (z - y >= 0 ? a[z - y] : 0));
            }
            else
            {
                writer.WriteLine((z - x >= 0 ? b[z - x] : 0) + (x > 0 ? a[x - 1] : 0));
            }
        }
    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) Solve();
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
    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}