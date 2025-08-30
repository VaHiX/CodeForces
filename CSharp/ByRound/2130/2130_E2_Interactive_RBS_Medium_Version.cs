using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Linq;

namespace CodeForces.Problems.Round2130.E2
{
    /// <summary>
    /// Problem: CF2130E2 - Interactive RBS (Medium Version)
    /// 
    /// This program solves an interactive problem where we need to determine a correct bracket sequence
    /// by making queries about the number of regular bracket sequences in specific substrings.
    /// This is a medium version with potentially larger constraints than the easy version.
    /// 
    /// Approach:
    /// - Use a divide and conquer strategy to find matching brackets
    /// - Process the sequence in chunks to stay within query limits
    /// - Use a binary search-like approach to identify matching brackets
    /// 
    /// Interactive Protocol:
    /// - Queries are made using the format "? k i1 i2 ... ik"
    /// - The judge responds with the number of regular bracket sequences in the specified positions
    /// - The final answer is submitted in the format "! s" where s is the bracket sequence
    /// 
    /// Constraints (Medium Version):
    /// - 1 ≤ t ≤ 100 (number of test cases)
    /// - 1 ≤ n ≤ 4000 (length of the bracket sequence, larger than easy version)
    /// - Maximum 540 queries per test case
    /// </summary>
    public class InteractiveRBSMediumSolver
    {
        private readonly TextReader _input;
        private readonly TextWriter _output;
        private const int BufferSize = 1 << 16;
        private const int MaxQueries = 540;
        private int _queryCount;
        private char[] _answer;
        private static readonly List<int> _chunkSizes = new();
        private static readonly List<int> _chunkWeights = new();

        /// <summary>
        /// Initializes a new instance of the InteractiveRBSMediumSolver class
        /// </summary>
        public InteractiveRBSMediumSolver(TextReader input, TextWriter output)
        {
            _input = input ?? throw new ArgumentNullException(nameof(input));
            _output = output ?? throw new ArgumentNullException(nameof(output));
            _queryCount = 0;
        }

        /// <summary>
        /// Main entry point for the program
        /// </summary>
        public static void Main()
        {
            // Initialize chunk sizes and weights for processing
            InitializeChunkData();

            using var solver = new InteractiveRBSMediumSolver(
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
                _queryCount = 0; // Reset query counter for each test case
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
                throw new ArgumentException("Invalid input: n must be positive", nameof(n));
            }

            // Initialize answer array with 1-based indexing
            _answer = new char[n + 1];
            Array.Fill(_answer, ' ');

            // Process the bracket sequence to find matching pairs
            ProcessBracketSequence(n);

            // Submit the final answer
            SubmitAnswer();
        }

        /// <summary>
        /// Processes the bracket sequence to determine the correct bracket placement
        /// </summary>
        private void ProcessBracketSequence(int n)
        {
            // Step 1: Find matching brackets using divide and conquer
            var currentIndices = Enumerable.Range(2, Math.Min(30, n - 1)).ToList();
            var result = FindMatchingBracket(1, currentIndices);
            var sameBracketIndices = new List<int>();

            // Process all chunks of the sequence
            while (!result.IsFound)
            {
                sameBracketIndices.AddRange(result.SameBrackets);

                // Get next chunk of indices to process
                currentIndices = Enumerable
                    .Range(result.LastProcessedIndex + 1, Math.Min(30, n - result.LastProcessedIndex))
                    .ToList();

                if (currentIndices.Count == 0) break;

                result = FindMatchingBracket(1, currentIndices);
            }

            // Add the indices of brackets that match the first bracket
            sameBracketIndices.AddRange(result.SameBrackets);

            // Determine the bracket type for the sequence
            DetermineBracketTypes(n, result, sameBracketIndices);
        }

        /// <summary>
        /// Determines the bracket types for the sequence
        /// </summary>
        private void DetermineBracketTypes(int n, BracketSearchResult result, List<int> sameBracketIndices)
        {
            // Query to determine the bracket type
            int[] query = { 1, result.MatchIndex, 1, result.MatchIndex };
            long queryResult = MakeQuery(query);

            // Set the bracket types
            int openBracketPos = 1;
            if (queryResult == 1)
            {
                _answer[1] = ')';
                _answer[result.MatchIndex] = '(';
                openBracketPos = result.MatchIndex;
            }
            else
            {
                _answer[1] = '(';
                _answer[result.MatchIndex] = ')';
            }

            // Set all brackets that match the first bracket
            foreach (int index in sameBracketIndices)
            {
                _answer[index] = _answer[1];
            }

            // Process remaining undetermined brackets
            ProcessRemainingBrackets(n, openBracketPos);
        }

        /// <summary>
        /// Processes the remaining brackets that haven't been determined yet
        /// </summary>
        private void ProcessRemainingBrackets(int n, int openBracketPos)
        {
            var undeterminedIndices = new List<int>();
            for (int i = 1; i <= n; i++)
            {
                if (_answer[i] == ' ')
                {
                    undeterminedIndices.Add(i);
                }
            }

            var currentQuery = new List<int>();
            var queryIndices = new List<int>();
            int chunkIndex = 0;

            foreach (int index in undeterminedIndices)
            {
                // Check if we can add more to the current query
                if (currentQuery.Count + 2 * _chunkSizes[chunkIndex] + 1 < 1000)
                {
                    currentQuery.Add(openBracketPos);
                    for (int i = 0; i < _chunkSizes[chunkIndex]; i++)
                    {
                        currentQuery.Add(openBracketPos);
                        currentQuery.Add(index);
                    }
                    queryIndices.Add(index);
                    chunkIndex++;
                }
                else
                {
                    // Process the current batch
                    if (currentQuery.Count > 0)
                    {
                        long queryResult = MakeQuery(currentQuery.ToArray());
                        ProcessQueryResult(queryResult, queryIndices);
                    }

                    // Start a new batch
                    currentQuery.Clear();
                    queryIndices.Clear();

                    currentQuery.Add(openBracketPos);
                    currentQuery.Add(openBracketPos);
                    currentQuery.Add(index);
                    queryIndices.Add(index);
                    chunkIndex = 1;
                }
            }

            // Process any remaining queries
            if (currentQuery.Count > 0)
            {
                long queryResult = MakeQuery(currentQuery.ToArray());
                ProcessQueryResult(queryResult, queryIndices);
            }
        }

        /// <summary>
        /// Processes the query result to determine bracket types
        /// </summary>
        private void ProcessQueryResult(long queryResult, List<int> indices)
        {
            // Process indices in reverse order to handle weights correctly
            for (int i = indices.Count - 1; i >= 0; i--)
            {
                int index = indices[i];
                if (_chunkWeights[i] <= queryResult)
                {
                    queryResult -= _chunkWeights[i];
                    _answer[index] = ')';
                }
                else
                {
                    _answer[index] = '(';
                }
            }
        }

        /// <summary>
        /// Finds the matching bracket for the given position using divide and conquer
        /// </summary>
        private BracketSearchResult FindMatchingBracket(int firstIndex, List<int> otherIndices, bool isSecondHalf = false)
        {
            long queryResult = 1; // Default to non-zero to handle the first call

            // Only make a query if this is the first half of the search
            if (!isSecondHalf)
            {
                // Create a query with the first index and all other indices interleaved
                var query = new int[otherIndices.Count * 2 + 1];
                Array.Fill(query, firstIndex);

                // Fill in the other indices at odd positions
                for (int i = 1, j = 0; i < query.Length; i += 2, j++)
                {
                    query[i] = otherIndices[j];
                }

                queryResult = MakeQuery(query);
            }

            // If no regular bracket sequence found, return the current indices as same brackets
            if (queryResult == 0)
            {
                return new BracketSearchResult
                {
                    IsFound = false,
                    MatchIndex = -1,
                    SameBrackets = otherIndices,
                    LastProcessedIndex = otherIndices.Count > 0 ? otherIndices[^1] : firstIndex
                };
            }

            // Base case: if only one index remains, it's the matching bracket
            if (otherIndices.Count == 1)
            {
                return new BracketSearchResult
                {
                    IsFound = true,
                    MatchIndex = otherIndices[0],
                    SameBrackets = new List<int>(),
                    LastProcessedIndex = otherIndices[0]
                };
            }

            // Split the indices into two halves for divide and conquer
            var firstHalf = new List<int>();
            var secondHalf = new List<int>();

            for (int i = 0; i < otherIndices.Count; i++)
            {
                if (i % 2 == 0)
                    firstHalf.Add(otherIndices[i]);
                else
                    secondHalf.Add(otherIndices[i]);
            }

            // Search in the first half
            var firstResult = FindMatchingBracket(firstIndex, firstHalf);
            if (firstResult.IsFound)
                return firstResult;

            // Search in the second half with the remaining indices
            var secondResult = FindMatchingBracket(firstIndex, secondHalf, true);
            secondResult.SameBrackets.AddRange(firstResult.SameBrackets);
            secondResult.LastProcessedIndex = Math.Max(secondResult.LastProcessedIndex, firstResult.LastProcessedIndex);

            return secondResult;
        }

        /// <summary>
        /// Makes an interactive query to the judge
        /// </summary>
        private long MakeQuery(int[] positions)
        {
            _queryCount++;
            if (_queryCount > MaxQueries)
            {
                throw new InvalidOperationException($"Exceeded maximum number of queries ({MaxQueries})");
            }

            _output.Write($"? {positions.Length}");
            foreach (int pos in positions)
            {
                _output.Write($" {pos}");
            }
            _output.WriteLine();
            _output.Flush();

            string response = _input.ReadLine();
            if (!long.TryParse(response, out long result))
            {
                throw new FormatException($"Invalid response from judge: {response}");
            }

            return result;
        }

        /// <summary>
        /// Submits the final answer to the judge
        /// </summary>
        private void SubmitAnswer()
        {
            _output.Write("! ");
            for (int i = 1; i < _answer.Length; i++)
            {
                _output.Write(_answer[i]);
            }
            _output.WriteLine();
            _output.Flush();
        }

        #region Helper Methods

        /// <summary>
        /// Initializes the chunk data used for processing brackets in batches
        /// </summary>
        private static void InitializeChunkData()
        {
            if (_chunkSizes.Count > 0) return; // Already initialized

            int sum = 0;
            for (int i = 1; i <= 500; i++)
            {
                int weight = i * (i + 1) / 2;
                if (weight > sum)
                {
                    _chunkSizes.Add(i);
                    _chunkWeights.Add(weight);
                    sum += weight;
                }
            }
        }

        /// <summary>
        /// Reads an integer from the input
        /// </summary>
        private int ReadInt()
        {
            string input = _input.ReadLine();
            if (!int.TryParse(input, out int result))
            {
                throw new FormatException($"Expected an integer, got: {input}");
            }
            return result;
        }

        #endregion

        #region Helper Types

        /// <summary>
        /// Represents the result of a bracket search operation
        /// </summary>
        private class BracketSearchResult
        {
            public bool IsFound { get; set; }
            public int MatchIndex { get; set; }
            public List<int> SameBrackets { get; set; } = new List<int>();
            public int LastProcessedIndex { get; set; }
        }

        #endregion
    }
}