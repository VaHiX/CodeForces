using System;

namespace CodeForces.Problems.Round2131.E
{
    /// <summary>
    /// Problem: CF2131E - Adjacent XOR
    /// 
    /// This program determines if it's possible to transform array 'a' into array 'b' 
    /// using the following operation any number of times:
    /// - Choose an index i (1 ≤ i < n) and set a[i] = a[i] XOR a[i+1]
    /// 
    /// Approach:
    /// 1. The last element of both arrays must be equal since no operation can modify the last element
    /// 2. For each element from second last to first, check if it can be transformed into the target value
    ///    using the XOR operation with its adjacent element
    /// 3. The transformation is possible if either:
    ///    - The current element already matches the target, or
    ///    - The target can be achieved by XORing with either the current or target value of the next element
    /// 
    /// Time Complexity: O(n) per test case
    /// Space Complexity: O(n) for storing the arrays
    /// </summary>
    public class AdjacentXorChecker
    {
        /// <summary>
        /// Determines if array 'a' can be transformed into array 'b' using adjacent XOR operations
        /// </summary>
        public bool CanTransform(int[] a, int[] b, int n)
        {
            // The last element must be the same since it can't be modified
            if (a[n - 1] != b[n - 1])
            {
                return false;
            }

            // Check each element from second last to first
            for (int i = n - 2; i >= 0; i--)
            {
                if (a[i] == b[i])
                {
                    continue;
                }

                // Check if we can transform a[i] to b[i] using XOR with either a[i+1] or b[i+1]
                if (b[i] != (a[i] ^ a[i + 1]) && b[i] != (a[i] ^ b[i + 1]))
                {
                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Reads an array of integers from the console
        /// </summary>
        private static int[] ReadIntArray(int length)
        {
            string[] input = Console.ReadLine()!.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            int[] array = new int[length];
            for (int i = 0; i < length; i++)
            {
                array[i] = int.Parse(input[i]);
            }
            return array;
        }

        /// <summary>
        /// Reads a single integer from the console
        /// </summary>
        private static int ReadInt()
        {
            return int.Parse(Console.ReadLine()!);
        }

        public static void Main()
        {
            var checker = new AdjacentXorChecker();
            int testCases = ReadInt();
            
            while (testCases-- > 0)
            {
                int n = ReadInt();
                int[] a = ReadIntArray(n);
                int[] b = ReadIntArray(n);
                
                if (checker.CanTransform(a, b, n))
                {
                    Console.WriteLine("Yes");
                }
                else
                {
                    Console.WriteLine("No");
                }
            }
        }
    }
}