using System;
using System.IO;
using System.Text;

namespace CodeForces.Problems.Round2131.B
{
    /// <summary>
    /// Problem: CF2131B - Alternating Series
    /// 
    /// This program generates an alternating series of numbers where:
    /// - Even indices (0-based) contain -1
    /// - Odd indices contain 3, except for the last element which is 2
    /// 
    /// Approach:
    /// - Iterate through each position in the sequence
    /// - For even indices, output -1
    /// - For odd indices, output 3 unless it's the last element, then output 2
    /// 
    /// Time Complexity: O(n) where n is the length of the sequence
    /// Space Complexity: O(1) additional space
    /// </summary>
    public class AlternatingSeriesGenerator
    {
        private const int BufferSize = 1 << 16;
        private readonly TextWriter _output;
        private readonly TextReader _input;

        /// <summary>
        /// Initializes a new instance of the AlternatingSeriesGenerator class
        /// </summary>
        public AlternatingSeriesGenerator(TextReader input, TextWriter output)
        {
            _input = input;
            _output = output;
        }

        /// <summary>
        /// Main entry point for the program
        /// </summary>
        public static void Main()
        {
            using var generator = new AlternatingSeriesGenerator(
                Console.In,
                new StreamWriter(Console.OpenStandardOutput(), Encoding.UTF8, BufferSize) { AutoFlush = false });
            
            generator.Run();
        }

        /// <summary>
        /// Runs the generator for multiple test cases
        /// </summary>
        public void Run()
        {
            int testCases = ReadInt();
            for (int i = 0; i < testCases; i++)
            {
                GenerateSequence(ReadLong());
            }
            _output.Flush();
        }

        /// <summary>
        /// Generates and outputs the alternating series of length n
        /// </summary>
        /// <param name="n">Length of the sequence to generate</param>
        private void GenerateSequence(long n)
        {
            if (n <= 0)
            {
                _output.WriteLine();
                return;
            }

            var result = new StringBuilder();
            for (int i = 0; i < n; i++)
            {
                if (i % 2 == 0)
                {
                    result.Append("-1 ");
                }
                else
                {
                    result.Append(i == n - 1 ? "2 " : "3 ");
                }
            }

            // Remove trailing space and write the result
            if (result.Length > 0)
            {
                result.Length--; // Remove last space
            }
            _output.WriteLine(result);
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

        private long ReadLong()
        {
            int c;
            int sign = 1;
            long result = 0;

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