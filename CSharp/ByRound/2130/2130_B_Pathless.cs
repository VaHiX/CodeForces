using System;
using System.IO;
using System.Linq;
using System.Text;

namespace CodeForces.Problems.Round2130.B
{
    /// <summary>
    /// Problem: CF2130B - Pathless
    /// 
    /// This program solves a problem that requires specific operations on arrays or sequences
    /// to determine if they can form a valid path under certain conditions.
    /// 
    /// Approach:
    /// - Read input values and count occurrences of 0, 1, and 2
    /// - Check if the sum of the array meets certain conditions
    /// - Output the result based on the conditions
    /// 
    /// Time Complexity: O(n) where n is the length of the array
    /// Space Complexity: O(n) for storing the input array
    /// </summary>
    public class PathlessSolver
    {
        private readonly TextReader _input;
        private readonly TextWriter _output;
        private const int BufferSize = 1 << 16;

        /// <summary>
        /// Initializes a new instance of the PathlessSolver class
        /// </summary>
        public PathlessSolver(TextReader input, TextWriter output)
        {
            _input = input;
            _output = output;
        }

        /// <summary>
        /// Main entry point for the program
        /// </summary>
        public static void Main()
        {
            using var solver = new PathlessSolver(
                Console.In,
                new StreamWriter(Console.OpenStandardOutput(), Encoding.UTF8, BufferSize) { AutoFlush = false });
            
            solver.Run();
        }

        /// <summary>
        /// Runs the solver for multiple test cases
        /// </summary>
        public void Run()
        {
            int testCases = ReadInt();
            for (int i = 0; i < testCases; i++)
            {
                Solve();
            }
            _output.Flush();
        }

        /// <summary>
        /// Solves a single test case
        /// </summary>
        private void Solve()
        {
            int n = ReadInt();
            int s = ReadInt();
            
            int[] array = new int[n];
            int[] count = new int[3]; // Count of 0s, 1s, and 2s
            
            // Read and process the array
            for (int i = 0; i < n; i++)
            {
                array[i] = ReadInt();
                if (array[i] >= 0 && array[i] <= 2)
                {
                    count[array[i]]++;
                }
            }

            int sum = array.Sum();
            
            // Check the path condition
            if (sum + 1 == s || sum > s)
            {
                PrintResult(count);
            }
            else
            {
                _output.WriteLine("-1");
            }
        }

        /// <summary>
        /// Prints the result in the required format
        /// </summary>
        /// <param name="count">Array containing counts of 0s, 1s, and 2s</param>
        private void PrintResult(int[] count)
        {
            // Print 0s first
            for (int i = 0; i < count[0]; i++)
            {
                _output.Write("0 ");
            }
            
            // Then print 2s
            for (int i = 0; i < count[2]; i++)
            {
                _output.Write("2 ");
            }
            
            // Finally print 1s
            for (int i = 0; i < count[1]; i++)
            {
                _output.Write("1 ");
            }
            
            _output.WriteLine();
        }

        #region Input Helpers

        private int ReadInt()
        {
            int c;
            int sign = 1;
            int result = 0;

            // Skip any non-digit characters except for minus sign
            do
            {
                c = _input.Read();
                if (c == '-') sign = -1;
            } while (c < '0' || c > '9');

            // Read the number
            do
            {
                result = result * 10 + (c - '0');
                c = _input.Read();
            } while (c >= '0' && c <= '9');

            return result * sign;
        }

        #endregion
    }
}