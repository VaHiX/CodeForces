using System;
using System.Collections.Generic;

namespace CodeForces.Problems.Round2132.C2
{
    /// <summary>
    /// Problem: CF2132C2 - The Cunning Seller (Hard Version)
    /// 
    /// This program solves an advanced version of the Cunning Seller problem,
    /// where we need to determine if it's possible to represent a number n
    /// as a sum of k terms of a specific form, and find the minimal such representation.
    /// 
    /// Approach:
    /// 1. Precompute the cost values for each digit position in base-3
    /// 2. For each test case, convert n to its base-3 representation
    /// 3. Calculate the minimum number of terms needed (min_k)
    /// 4. If k is less than min_k, output -1 (impossible)
    /// 5. Otherwise, try to use the remaining operations to minimize the result
    /// 6. Output the minimal possible value or -1 if not possible
    /// 
    /// Time Complexity: O(T * log₃N) where T is the number of test cases
    /// Space Complexity: O(log₃N) to store the base-3 digits
    /// </summary>
    public static class CunningSellerHard
    {
        /// <summary>
        /// Precomputes the cost values for each digit position in base-3
        /// </summary>
        /// <returns>Array of precomputed costs</returns>
        private static long[] PrecomputeCosts()
        {
            var costs = new List<long>();
            long currentCost = 3;  // Base cost for the first position
            long positionMultiplier = 1;  // 3^0 = 1
            
            // We only need to compute up to 21 digits since 3^21 is larger than the maximum possible n
            for (int i = 0; i < 21; i++)
            {
                costs.Add(currentCost);
                currentCost = 3 * currentCost + positionMultiplier;
                positionMultiplier *= 3;
            }
            
            return costs.ToArray();
        }

        /// <summary>
        /// Converts a number to its base-3 representation
        /// </summary>
        /// <param name="number">The number to convert</param>
        /// <returns>List of digits in base-3 (least significant digit first)</returns>
        private static (List<long> digits, long minTerms) ConvertToBase3(long number)
        {
            var digits = new List<long>();
            long minTerms = 0;
            
            while (number > 0)
            {
                long digit = number % 3;
                digits.Add(digit);
                minTerms += digit;  // Each digit contributes to the minimum number of terms
                number /= 3;
            }
            
            return (digits, minTerms);
        }

        /// <summary>
        /// Solves a single test case
        /// </summary>
        private static long SolveTestCase(long n, long k, long[] costs)
        {
            // Convert n to base-3 and get minimum terms needed
            var (digits, minTerms) = ConvertToBase3(n);
            
            // If k is less than the minimum terms needed, it's impossible
            if (k < minTerms)
            {
                return -1;
            }
            
            // Calculate remaining operations after using minimum terms
            long remainingOperations = k - minTerms;
            
            // We can combine terms in groups of 3 to reduce the total count
            // Each combination of 3 terms reduces the count by 2 (3 terms become 1)
            // So we can perform at most remainingOperations / 2 such combinations
            remainingOperations /= 2;
            
            // Process digits from most significant to least significant
            for (int i = digits.Count - 1; i >= 1; i--)
            {
                if (digits[i] <= remainingOperations)
                {
                    // Combine this digit's terms into the next higher position
                    digits[i - 1] += 3 * digits[i];
                    remainingOperations -= digits[i];
                    tr[i] = 0;
                }
                else
                {
                    tr[i - 1] += k * 3;
                    tr[i] -= k;
                    break;
                }
            }

            long ans = 0;
            for (int i = tr.Count - 1; i >= 0; --i)
            {
                ans += cost[i] * tr[i];
            }

            Console.WriteLine(ans);
        }
    }
}
