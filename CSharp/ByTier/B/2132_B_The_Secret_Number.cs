using System;
using System.Collections.Generic;
using System.Linq;

namespace CodeForces.Problems.Round2132.B
{
    /// <summary>
    /// Problem: CF2132B - The Secret Number
    /// 
    /// This program finds all positive integers x such that n can be expressed as x * (10^d + 1)
    /// for some d >= 1. It outputs the count of such numbers followed by the numbers themselves.
    /// 
    /// Approach:
    /// 1. For each test case, iterate through possible values of d from 1 to 17
    /// 2. For each d, check if n is divisible by (10^d + 1)
    /// 3. If divisible, calculate x = n / (10^d + 1) and add it to the results
    /// 4. Output the count of results followed by the sorted list of results
    /// 
    /// Time Complexity: O(T * 17) where T is the number of test cases
    /// Space Complexity: O(1) - constant space per test case
    /// </summary>
    public static class SecretNumberSolver
    {
        /// <summary>
        /// Finds all valid x values for a given n where n = x * (10^d + 1) for some d >= 1
        /// </summary>
        /// <param name="n">The number to find factors for</param>
        /// <returns>A sorted list of valid x values</returns>
        public static List<long> FindSecretNumbers(long n)
        {
            var result = new HashSet<long>();
            long powerOfTen = 10; // 10^1
            
            // Check for d from 1 to 17 (since 10^18 is larger than the maximum possible n)
            for (int d = 1; d <= 17; d++)
            {
                // Check if n is divisible by (10^d + 1)
                long divisor = powerOfTen + 1;
                if (n >= divisor && n % divisor == 0)
                {
                    long x = n / divisor;
                    if (x > 0) // Only consider positive x
                    {
                        result.Add(x);
                    }
                }
                
                // Calculate next power of 10
                powerOfTen *= 10;
            }
            
            // Return sorted results
            var sortedResult = result.ToList();
            sortedResult.Sort();
            return sortedResult;
        }

        /// <summary>
        /// Solves a single test case and outputs the results
        /// </summary>
        public static void Solve()
        {
            long n = long.Parse(Console.ReadLine());
            var secretNumbers = FindSecretNumbers(n);
            
            // Output the results
            Console.WriteLine(secretNumbers.Count);
            if (secretNumbers.Count > 0)
            {
                Console.WriteLine(string.Join(" ", secretNumbers));
            }
        }

        public static void Main()
        {
            // Read number of test cases
            int testCases = int.Parse(Console.ReadLine());
            
            // Process each test case
            for (int i = 0; i < testCases; i++)
            {
                Solve();
            }
        }
    }
}