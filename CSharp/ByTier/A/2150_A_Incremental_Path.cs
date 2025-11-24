// Problem: CF 2150 A - Incremental Path
// https://codeforces.com/contest/2150/problem/A

/*
 * Problem: Incremental Path
 * 
 * Task Description:
 * There is a strip with 10^9 cells, initially m cells are black and others are white.
 * For each prefix of commands s[0..i], a person starts from cell 1, executes the commands,
 * and colors the final visited cell black if it wasn't already black. The goal is to output
 * all black cells after processing all prefixes of commands.
 * 
 * Approach:
 * - Use a linked list to maintain current set of black cells for efficient insertions/deletions.
 * - Simulate the process step-by-step: For each command in the string, simulate moving from current position
 *   according to the command (A = next cell, B = next white cell).
 * - Track final position and color that cell black if not already.
 * - Maintain sorted order using LinkedList for fast insertion/removal operations.
 * 
 * Time Complexity: O(n * m + sum of n) where m is number of initially black cells and n is length of commands.
 * Space Complexity: O(m) for storing the black cells in a linked list, which can grow up to the number of operations.
 */

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace IncrementalPath
{
    class Program
    {
        static void Solve()
        {
            int n = Next();
            int m = Next();
            int[] s = new int[n];
            for (int i = 0; i < n; i++)
                s[i] = Next(); // Read command as integer (1 for A, 2 for B)
            LinkedList<int> ll = new LinkedList<int>();
            for (int i = 0; i < m; i++)
                ll.AddLast(Next()); // Add initial black cells to linked list
            ll.AddLast(int.MaxValue); // Sentinel value to simplify boundary checks
            LinkedListNode<int> curr = ll.First;
            if (curr.Value == 1)
                curr = curr.Next; // Skip the first cell if it is black initially
            
            for (int i = 0, pos = 1; i < n; i++) // Iterate through each command in input string
            {
                if (s[i] == 1) // Command A (move to next cell)
                {
                    pos++; // Increment position by one
                    if (curr.Value > pos) // If there's no black cell at this position yet
                    {
                        curr = ll.AddBefore(curr, pos); // Insert new black cell
                    }
                    curr = curr.Next; // Move to next black cell
                }
                else // Command B (jump to next white cell)
                {
                    pos++; // Increment position by one
                    while (curr.Value == pos) // Skip all black cells
                    {
                        curr = curr.Next;
                        pos++;
                    }
                    curr = ll.AddBefore(curr, pos); // Insert the new position as a black cell
                    while (curr.Value == pos) // Again skip if there are duplicates introduced
                    {
                        curr = curr.Next;
                        pos++;
                    }
                }
            }
            
            LinkedListNode<int> ans = ll.First;
            writer.WriteLine(ll.Count - 1); // Output number of black cells (-1 because of sentinel)
            while (ans.Value != int.MaxValue) // Print all black cell positions
            {
                writer.Write(ans.Value);
                writer.Write(' ');
                ans = ans.Next;
            }
            writer.WriteLine();
        }

        static void Main(string[] args)
        {
            long t = Next(); // Read number of test cases
            for (int i = 0; i < t; i++)
                Solve(); // Process each test case
            writer.Flush(); // Flush output buffer
        }

        static int Next() // Utility to parse integers from standard input
        {
            int c;
            int m = 1;
            int res = 0;
            do
            {
                c = reader.Read();
                if (c == 'A')
                    return 1; // Return 1 for command A
                if (c == 'B')
                    return 2; // Return 2 for command B
                if (c == '-')
                    m = -1; // Handle negative sign
            } while (c < '0' || c > '9'); // Skip until digit is found
            res = c - '0';
            while (true)
            {
                c = reader.Read();
                if (c < '0' || c > '9')
                    return m * res; // Return number including sign
                res *= 10;
                res += c - '0'; // Accumulate digit
            }
        }

        static readonly StreamReader reader = new StreamReader(
            Console.OpenStandardInput(1024 * 10),
            Encoding.ASCII,
            false,
            1024 * 10
        );
        static readonly StreamWriter writer = new StreamWriter(
            Console.OpenStandardOutput(1024 * 10),
            Encoding.ASCII,
            1024 * 10
        );
    }
}


// https://github.com/VaHiX/CodeForces/