using System;
using System.Text;

namespace CodeForces.Problems.Round2132.A
{
    /// <summary>
    /// Problem: CF2132A - Homework
    /// 
    /// This program processes a series of test cases where each case involves
    /// constructing a string by appending or prepending characters based on
    /// a direction string.
    /// 
    /// Approach:
    /// 1. For each test case, read the initial string and a series of characters with directions
    /// 2. For each character, prepend it if direction is 'V', append if direction is 'D'
    /// 3. Print the final constructed string
    /// 
    /// Time Complexity: O(T * n) where T is the number of test cases and n is the length of operations
    /// Space Complexity: O(n) where n is the length of the final string
    /// </summary>
    public static class HomeworkSolver
    {
        /// <summary>
        /// Processes a single test case and returns the result string.
        /// </summary>
        /// <param name="initialString">The initial string to process</param>
        /// <param name="characters">Characters to add to the string</param>
        /// <param name="directions">Directions for each character ('V' for prepend, 'D' for append)</param>
        /// <returns>The processed string after all operations</returns>
        public static string ProcessTestCase(string initialString, string characters, string directions)
        {
            var result = new StringBuilder(initialString);
            
            for (int i = 0; i < directions.Length; i++)
            {
                if (directions[i] == 'V')
                {
                    // Prepend the character
                    result.Insert(0, characters[i]);
                }
                else if (directions[i] == 'D')
                {
                    // Append the character
                    result.Append(characters[i]);
                }
            }
            
            return result.ToString();
        }

        public static void Main(string[] args)
        {
            // Read number of test cases
            int testCases = int.Parse(Console.ReadLine());
            var results = new string[testCases];
            
            for (int i = 0; i < testCases; i++)
            {
                // Read input values (lengths are read but not used in this implementation)
                _ = int.Parse(Console.ReadLine()); // originalLength
                string initialString = Console.ReadLine();
                _ = int.Parse(Console.ReadLine()); // operationsCount
                string characters = Console.ReadLine();
                string directions = Console.ReadLine();
                
                // Process the test case
                results[i] = ProcessTestCase(initialString, characters, directions);
            }
            
            // Output all results
            foreach (var result in results)
            {
                Console.WriteLine(result);
            }
        }
    }
}