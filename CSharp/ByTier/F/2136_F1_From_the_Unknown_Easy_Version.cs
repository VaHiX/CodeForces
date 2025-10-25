// Problem: CF 2136 F1 - From the Unknown (Easy Version)
// https://codeforces.com/contest/2136/problem/F1

/*
 * Problem: From the Unknown (Easy Version)
 * Algorithm: Binary Search with Interactive Queries
 *
 * The task is to determine an unknown integer W (editor width) using at most 2 queries.
 * Each query sends an article (sequence of word lengths) to the editor,
 * and receives the number of lines needed to display it.
 *
 * Approach:
 * - Use binary search principles to find W within [1, 10^5].
 * - First query: Try a large enough array so that if W is smaller than sum, we get 0.
 * - Based on the result, adjust range and perform second query using carefully crafted inputs.
 *
 * Time Complexity: O(log(10^5)) ≈ O(17) per test case
 * Space Complexity: O(10^5) due to input array size, but only log(10^5) is used for processing
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace FromTheUnknownEasy {
    class Program {
        static void Solve() {
            int[] p = new int[100000];  // Preallocate large array to initialize all elements as 1
            Array.Fill(p, 1);           // Fill with ones to create a small sum for first query

            int q = Ask(p);             // Query the editor with all 1s; get number of lines needed
            if (q == 1) {               // If exactly one line is needed, W must be at least 100000
                Ans(100000);
                return;
            }

            int w = (100000 + q - 1) / q;  // Compute lower bound estimate of W using first query result

            // Validate the computed w
            if ((100000 + w) / (w + 1) != q) {
                Ans(w);
                return;
            }

            // Refine binary search bounds for more precise estimation
            int hi = (100000 + q - 2) / (q - 1);   // Upper bound on possible W
            int lo = w;                             // Lower bound on possible W
            List<int> ints = new() { lo };          // Start building list for second query
            
            int c = 1;                              // Counter to track how many elements added

            // Fill the list with optimized values to minimize number of lines needed
            for (int i = lo + 1; i < hi; i++) {
                ints.Add(lo);               // Add a repeated value to control line breaks
                ints.Add(i - lo);           // Add difference term
                c++;
            }

            int q2 = Ask(ints.ToArray());   // Make a second query based on constructed array
            Ans(lo + c - (q2 - c) - 1);     // Compute final answer using formula derived from response
        }

        static int Ask(int[] p) {
            writer.Write($"? {p.Length}");
            foreach (var i in p) {
                writer.Write(' ');
                writer.Write(i);
            }
            writer.WriteLine();
            writer.Flush();
            return int.Parse(reader.ReadLine());
        }

        static void Ans(int w) {
            writer.WriteLine($"! {w}");
            writer.Flush();
        }

        static void Main(string[] args) {
            int t = int.Parse(reader.ReadLine());
            for (int i = 0; i < t; i++) {
                Solve();
            }
            writer.Flush();
        }

        static readonly StreamReader reader = new(
            Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
        static readonly StreamWriter writer =
            new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
    }
}


// https://github.com/VaHiX/codeForces/