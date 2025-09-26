using System;
using System.IO;
using System.Linq;

namespace CodeForces.Problems.Round2131.C
{
    /// <summary>
    /// Problem: CF2131C - Make it Equal
    /// 
    /// This program determines if two arrays can be made equal by performing the following operations:
    /// 1. For each element in both arrays, replace it with its remainder when divided by k
    /// 2. Then, replace each element with the minimum of itself and (k - itself)
    /// 3. Finally, check if the two arrays can be made equal by sorting
    /// 
    /// Approach:
    /// - Process both arrays using the same transformation
    /// - Sort both arrays
    /// - Check if they are equal
    /// 
    /// Time Complexity: O(n log n) due to sorting
    /// Space Complexity: O(1) additional space
    /// </summary>
    public class ArrayEqualizer
    {
        private readonly TextReader _input;
        private readonly TextWriter _output;
        private const int BufferSize = 1 << 16;

        /// <summary>
        /// Initializes a new instance of the ArrayEqualizer class
        /// </summary>
        public ArrayEqualizer(TextReader input, TextWriter output)
        {
            _input = input;
            _output = output;
        }

        /// <summary>
        /// Main entry point for the program
        /// </summary>
        public static void Main()
        {
            using var equalizer = new ArrayEqualizer(
                Console.In,
                new StreamWriter(Console.OpenStandardOutput(), System.Text.Encoding.UTF8, BufferSize) { AutoFlush = false });
            
            equalizer.Run();
        }

        /// <summary>
        /// Runs the array equalizer for multiple test cases
        /// </summary>
        public void Run()
        {
            int testCases = ReadInt();
            for (int t = 0; t < testCases; t++)
            {
                int[] nk = ReadIntArray();
                if (nk.Length < 2) continue; // Invalid input, skip
                
                int n = nk[0], k = nk[1];
                if (k <= 0) continue; // Invalid k, skip

                int[] array1 = ReadIntArray();
                int[] array2 = ReadIntArray();

                if (array1 == null || array2 == null || array1.Length != n || array2.Length != n)
                {
                    _output.WriteLine("NO");
                    continue;
                }

                ProcessArray(array1, k);
                ProcessArray(array2, k);

                Array.Sort(array1);
                Array.Sort(array2);

                bool areEqual = array1.SequenceEqual(array2);
                _output.WriteLine(areEqual ? "YES" : "NO");
            }
            _output.Flush();
        }

        /// <summary>
        /// Processes the array by applying the modulo and minimum operations
        /// </summary>
        /// <param name="nums">Array to process</param>
        /// <param name="k">The divisor for modulo operation</param>
        private void ProcessArray(int[] nums, int k)
        {
            if (nums == null || k == 0) return;

            for (int i = 0; i < nums.Length; i++)
            {
                // Take modulo k and ensure it's positive
                int mod = nums[i] % k;
                if (mod < 0) mod += k; // Handle negative numbers
                
                // Choose the minimum between mod and (k - mod)
                nums[i] = Math.Min(mod, k - mod);
            }
        }

        private int ReadInt()
        {
            return int.Parse(_input.ReadLine());
        }

        private int[] ReadIntArray()
        {
            return _input.ReadLine().Split().Select(int.Parse).ToArray();
        }
    }
}