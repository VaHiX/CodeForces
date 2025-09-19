using System;
using System.IO;
using System.Text;

namespace CodeForces.Problems.Round2130.D
{
    /// <summary>
    /// Problem: CF2130D - Stay or Mirror
    /// 
    /// This program solves a problem that involves processing an array of values and using a segment tree
    /// to efficiently calculate the minimum number of operations needed to make the array non-decreasing.
    /// 
    /// Approach:
    /// - Read the input array and create a sorted version with original indices
    /// - Use a segment tree to efficiently track and update the number of elements
    /// - Calculate the minimum number of operations by comparing left and right segments
    /// 
    /// Time Complexity: O(n log n) due to sorting and segment tree operations
    /// Space Complexity: O(n) for the segment tree and auxiliary arrays
    /// </summary>
    public class StayOrMirrorSolver
    {
        private readonly TextReader _input;
        private readonly TextWriter _output;
        private const int BufferSize = 1 << 16;

        /// <summary>
        /// Initializes a new instance of the StayOrMirrorSolver class
        /// </summary>
        public StayOrMirrorSolver(TextReader input, TextWriter output)
        {
            _input = input ?? throw new ArgumentNullException(nameof(input));
            _output = output ?? throw new ArgumentNullException(nameof(output));
        }

        /// <summary>
        /// Main entry point for the program
        /// </summary>
        public static void Main()
        {
            using var solver = new StayOrMirrorSolver(
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
                long result = Solve();
                _output.WriteLine(result);
            }
            _output.Flush();
        }

        /// <summary>
        /// Solves a single test case
        /// </summary>
        /// <returns>The minimum number of operations needed</returns>
        private long Solve()
        {
            int n = ReadInt();
            if (n <= 0)
            {
                return 0;
            }

            var values = new int[n];
            var positions = new int[n];

            // Read input values and initialize positions
            for (int i = 0; i < n; i++)
            {
                values[i] = ReadInt();
                positions[i] = i;
            }

            // Sort values and track original positions
            Array.Sort(values, positions);

            // Initialize a segment tree to track active elements
            var segmentTree = new SegmentTree<int>(
                new int[n].Fill(1),  // Initialize all elements to 1 (active)
                0,                  // Default value for query
                (x, y) => x + y     // Sum operation
            );

            long totalOperations = 0;

            // Process each element in sorted order
            for (int i = 0; i < n; i++)
            {
                int originalPosition = positions[i];

                // Mark the current position as processed (set to 0)
                segmentTree.Modify(originalPosition, 0);

                // Count active elements to the left and right of the current position
                int leftCount = segmentTree.Query(0, originalPosition);
                int rightCount = segmentTree.Query(originalPosition, n);

                // Add the minimum of left and right active elements to the total
                totalOperations += Math.Min(leftCount, rightCount);
            }

            return totalOperations;
        }

        #region Segment Tree Implementation

        /// <summary>
        /// Generic segment tree implementation with range queries and point updates
        /// </summary>
        /// <typeparam name="T">Type of elements in the segment tree</typeparam>
        private class SegmentTree<T>
        {
            /// <summary>
            /// Delegate type for the binary operation
            /// </summary>
            public delegate T Op(T x, T y);

            private readonly int n;          // Size of the original array
            private readonly T[] tree;       // Segment tree array
            private readonly T defaultValue;  // Default value for out-of-bound queries
            private readonly Op operation;    // Binary operation for combining elements

            /// <summary>
            /// Initializes a new instance of the SegmentTree class
            /// </summary>
            /// <param name="array">The initial array</param>
            /// <param name="defaultValue">Default value for out-of-bound queries</param>
            /// <param name="operation">Binary operation to combine elements</param>
            public SegmentTree(T[] array, T defaultValue, Op operation)
            {
                if (array == null) throw new ArgumentNullException(nameof(array));
                if (operation == null) throw new ArgumentNullException(nameof(operation));

                n = array.Length;
                this.defaultValue = defaultValue;
                this.operation = operation;
                tree = new T[2 * n];

                // Copy the original array to the leaves of the segment tree
                Array.Copy(array, 0, tree, n, n);

                // Build the segment tree
                Build();
            }

            /// <summary>
            /// Builds the segment tree from the initial array
            /// </summary>
            private void Build()
            {
                for (int i = n - 1; i > 0; i--)
                {
                    tree[i] = operation(tree[i << 1], tree[(i << 1) | 1]);
                }
            }

            /// <summary>
            /// Updates the value at the specified position
            /// </summary>
            /// <param name="position">The position to update</param>
            /// <param name="value">The new value</param>
            public void Modify(int position, T value)
            {
                if (position < 0 || position >= n)
                    throw new ArgumentOutOfRangeException(nameof(position));

                // Update the leaf node
                position += n;
                tree[position] = value;

                // Update all affected ancestors
                for (position >>= 1; position > 0; position >>= 1)
                {
                    tree[position] = operation(tree[position << 1], tree[(position << 1) | 1]);
                }
            }

            /// <summary>
            /// Queries the range [left, right) using the segment tree
            /// </summary>
            /// <param name="left">Left boundary (inclusive)</param>
            /// <param name="right">Right boundary (exclusive)</param>
            /// <returns>The result of the range query</returns>
            public T Query(int left, int right)
            {
                if (left < 0) left = 0;
                if (right > n) right = n;
                if (left >= right) return defaultValue;

                T leftResult = defaultValue;
                T rightResult = defaultValue;

                // Convert to 1-based indexing
                left += n;
                right += n;

                while (left < right)
                {
                    // If left is odd, it's the right child of its parent
                    if ((left & 1) == 1)
                    {
                        leftResult = operation(leftResult, tree[left]);
                        left++;
                    }

                    // If right is odd, the left child of the parent needs to be included
                    if ((right & 1) == 1)
                    {
                        right--;
                        rightResult = operation(tree[right], rightResult);
                    }

                    // Move up one level in the tree
                    left >>= 1;
                    right >>= 1;
                }

                return operation(leftResult, rightResult);
            }
        }

        #endregion

        #region Input/Output Helpers

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