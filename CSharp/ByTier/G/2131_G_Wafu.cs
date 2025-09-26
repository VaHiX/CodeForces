using System;
using System.Linq;

namespace CodeForces.Problems.Round2131.G
{
    /// <summary>
    /// Problem: CF2131G - Wafu
    /// 
    /// This program solves a problem where we need to maximize the product of selected numbers
    /// under certain constraints, using a greedy approach with precomputed values.
    /// 
    /// Approach:
    /// 1. Sort the input array in ascending order
    /// 2. Process each number, using precomputed 'turns' and 'score' arrays to determine
    ///    the optimal way to use each number
    /// 3. If we have remaining operations, use the most efficient numbers from the precomputed arrays
    /// 
    /// Time Complexity: O(n log n + k) where n is the number of elements and k is the number of operations
    /// Space Complexity: O(n + m) where m is the maximum value in the 'turns' array
    /// </summary>
    public class WafuSolver
    {
        private const long Mod = 1000000007;
        private static readonly long[] Turns = new long[32]; // Precomputed number of turns for each value
        private static readonly long[] Score = new long[32]; // Precomputed scores for each value

        /// <summary>
        /// Initializes the precomputed arrays for turns and scores
        /// </summary>
        static WafuSolver()
        {
            InitializePrecomputedValues();
        }

        /// <summary>
        /// Solves the Wafu problem for given array and number of operations
        /// </summary>
        public static long CalculateMaxProduct(long[] numbers, long operations)
        {
            Array.Sort(numbers);
            long result = 1;

            // Process each number in the array
            for (int i = 0; operations > 0 && i < numbers.Length; i++)
            {
                long current = numbers[i];
                
                // If the number is larger than our precomputed range
                if (current >= Turns.Length)
                {
                    result = (result * current) % Mod;
                    operations--;
                    break;
                }
                // If using this number would take more operations than we have left
                else if (Turns[current] > operations)
                {
                    result = (result * current) % Mod;
                    operations--;
                    break;
                }
                // Use the precomputed values for this number
                else
                {
                    operations -= Turns[current];
                    result = (result * Score[current]) % Mod;
                }
            }

            // If we still have operations left, use the most efficient numbers
            while (operations > 0)

    const int mod = 1000000007;

    static long[] turns = new long[32];
    static long[] score = new long[32];

    static void Main(string[] args)
    {
        turns[1] = 1;
        score[1] = 1;

        for (int i = 2; i < turns.Length; i++)
        {
            score[i] = i;
            turns[i] = 1;
            for (int j = 1; j < i; j++)
            {
                score[i] = score[i] * score[j] % mod;
                turns[i] += turns[j];
            }
        }

        long p = turns[^1];

        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
        writer.Flush();
    }

    static long Next()
    {
        int c;
        int m = 1;
        long res = 0;
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