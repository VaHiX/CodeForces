using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace CodeForces.Problems.Round2130.C
{
    /// <summary>
    /// Problem: CF2130C - Double Perspective
    /// 
    /// This program solves a problem that involves finding a maximum set of intervals
    /// with specific properties, likely related to interval covering or scheduling.
    /// 
    /// Approach:
    /// - Read input values representing intervals with start and end points
    /// - Sort the intervals based on start points (and end points as tiebreaker)
    /// - Use a greedy algorithm to select the maximum number of non-overlapping intervals
    ///   or similar selection criteria
    /// - Output the selected intervals' indices
    /// 
    /// Time Complexity: O(n log n) due to sorting
    /// Space Complexity: O(n) for storing intervals and results
    /// </summary>
    public class DoublePerspectiveSolver
    {
        private readonly TextReader _input;
        private readonly TextWriter _output;
        private const int BufferSize = 1 << 16;

        /// <summary>
        /// Represents an interval with start, end, and original index
        /// </summary>
        private record Interval(int Start, int End, int Index);

        /// <summary>
        /// Initializes a new instance of the DoublePerspectiveSolver class
        /// </summary>
        public DoublePerspectiveSolver(TextReader input, TextWriter output)
        {
            _input = input ?? throw new ArgumentNullException(nameof(input));
            _output = output ?? throw new ArgumentNullException(nameof(output));
        }

        /// <summary>
        /// Main entry point for the program
        /// </summary>
        public static void Main()
        {
            using var solver = new DoublePerspectiveSolver(
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
            if (n <= 0)
            {
                _output.WriteLine("0\n");
                return;
            }

            // Read intervals with their original indices (1-based)
            var intervals = new Interval[n];
            for (int i = 0; i < n; i++)
            {
                int a = ReadInt();
                int b = ReadInt();
                intervals[i] = new Interval(a, b, i + 1);
            }

            // Sort intervals by start time, then by end time in descending order
            Array.Sort(intervals, (x, y) =>
            {
                int compareStart = x.Start.CompareTo(y.Start);
                return compareStart != 0 ? compareStart : y.End.CompareTo(x.End);
            });

            var selectedIndices = new List<int> { intervals[0].Index };
            int currentMaxEnd = intervals[0].End;
            int nextBestIndex = -1;

            // Greedily select intervals
            for (int i = 1; i < n; nextBestIndex = -1)
            {
                // Find the next interval that starts before currentMaxEnd with maximum end
                while (i < n && intervals[i].Start <= currentMaxEnd)
                {
                    if (nextBestIndex == -1 || intervals[nextBestIndex].End < intervals[i].End)
                    {
                        nextBestIndex = i;
                    }
                    i++;
                }

                if (nextBestIndex == -1)
                {
                    // No overlapping interval found, take the next one
                    if (i < n)
                    {
                        selectedIndices.Add(intervals[i].Index);
                        currentMaxEnd = intervals[i].End;
                        i++;
                    }
                }
                else if (intervals[nextBestIndex].End > currentMaxEnd)
                {
                    // Found a better interval that extends our coverage
                    selectedIndices.Add(intervals[nextBestIndex].Index);
                    currentMaxEnd = intervals[nextBestIndex].End;
                }
            }

            // Output the result
            _output.WriteLine(selectedIndices.Count);
            foreach (var index in selectedIndices)
            {
                _output.Write($"{index} ");
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