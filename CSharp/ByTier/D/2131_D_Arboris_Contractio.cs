using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace CodeForces.Problems.Round2131.D
{
    /// <summary>
    /// Problem: CF2131D - Arboris Contractio
    /// 
    /// This program solves a graph problem where we need to find the minimum number of edges
    /// to remove from a tree so that no node has more than one leaf neighbor.
    /// 
    /// Approach:
    /// 1. Build an adjacency list for the tree
    /// 2. Count the number of leaves in the tree
    /// 3. For each node, count how many leaves are connected to it
    /// 4. The answer is the total number of leaves minus the maximum number of leaves connected to any single node
    /// 
    /// Time Complexity: O(n) where n is the number of nodes
    /// Space Complexity: O(n) for storing the tree and counts
    /// </summary>
    public class ArborisContractioSolver
    {
        private readonly TextReader _input;
        private readonly TextWriter _output;
        private const int BufferSize = 1 << 16;

        /// <summary>
        /// Initializes a new instance of the ArborisContractioSolver class
        /// </summary>
        public ArborisContractioSolver(TextReader input, TextWriter output)
        {
            _input = input;
            _output = output;
            if (c < '0' || c > '9')
                return m * res;
            res *= 10;
            res += c - '0';
        }
    }
    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}