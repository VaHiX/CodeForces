using System;
using System.Collections.Generic;
using System.IO;

namespace CodeForces.Problems.Round2132.C1
{
    /// <summary>
    /// Problem: CF2132C1 - The Cunning Seller (Easy Version)
    /// 
    /// This program calculates a special sum based on the ternary (base-3) representation
    /// of a number. The sum is calculated as:
    /// sum(digit * (3 * 3^i + i * 3^(i-1))) for each digit at position i in the ternary representation.
    /// 
    /// Approach:
    /// 1. Convert the number to its ternary (base-3) representation
    /// 2. For each digit in the ternary representation, calculate its contribution to the sum
    /// 3. The contribution is digit * (3 * 3^i + i * 3^(i-1))
    /// 4. Sum up all contributions and return the result
    /// 
    /// Time Complexity: O(log₃N) per test case where N is the input number
    /// Space Complexity: O(log₃N) to store the ternary digits
    /// </summary>
    public static class CunningSellerEasy
    {
        private static readonly StreamReader reader = new StreamReader(Console.OpenStandardInput());
        private static readonly StreamWriter writer = new StreamWriter(Console.OpenStandardOutput());

        /// <summary>
        /// Calculates the special sum based on the ternary representation of the number.
        /// </summary>
        /// <param name="number">The input number to process</param>
        /// <returns>The calculated special sum</returns>
        public static long CalculateSpecialSum(long number)
        {
            // Convert the number to its ternary (base-3) representation
            var ternaryDigits = new List<long>();
            while (number > 0)
            {
                ternaryDigits.Add(number % 3);
                number /= 3;
            }

            long powerOfThree = 1; // 3^0 = 1
            long result = 0;

            // Process each digit in the ternary representation
            for (int position = 0; position < ternaryDigits.Count; position++)
            {
                long digit = ternaryDigits[position];
                // Calculate the contribution of this digit to the result
                // Formula: digit * (3 * 3^position + position * 3^(position-1))
                long term = 3 * powerOfThree + position * (position > 0 ? powerOfThree / 3 : 0);
                result += digit * term;
                
                // Update power of 3 for the next position
                powerOfThree *= 3;
            }

            return result;
        }

        /// <summary>
        /// Reads a long integer from the input stream
        /// </summary>
        private static long ReadLong()
        {
            int c;
            int sign = 1;
            long result = 0;
            
            // Skip non-digit characters
            do
            {
                c = reader.Read();
                if (c == '-') sign = -1;
            } while (c < '0' || c > '9');
            
            // Read the number
            result = c - '0';
            while (true)
            {
                c = reader.Read();
                if (c < '0' || c > '9')
                    return sign * result;
                result = result * 10 + (c - '0');
            }
        }

        public static void Main(string[] args)
        {
            // Read number of test cases
            long testCases = ReadLong();
            
            // Process each test case
            for (int i = 0; i < testCases; i++)
            {
                long number = ReadLong();
                long result = CalculateSpecialSum(number);
                writer.WriteLine(result);
            }
            
            // Ensure all output is written
            writer.Flush();
        }
    }
}