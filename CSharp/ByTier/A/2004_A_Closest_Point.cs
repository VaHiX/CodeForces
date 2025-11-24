// Problem: CF 2004 A - Closest Point
// https://codeforces.com/contest/2004/problem/A

// ======================================================================
// Problem: Closest Point
// Algorithm/Techniques: Greedy approach, array manipulation
// Time Complexity: O(n) per test case, where n is the number of points
// Space Complexity: O(n) for storing the input array
//
// Description:
// Given a set of points on a line, determine whether we can add one more 
// point such that this new point becomes the closest to every existing point.
// The key observation is that only when there's a gap between two adjacent 
// points and we can place a point exactly in the middle, it’s possible to 
// make that new point closest to all others. For two points [a, b], if b - a > 1,
// then placing a point at (a + b) / 2 might work but only if the result is an integer.
//
// ======================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClosestPoint {
    internal class Program {
        static void Main(string[] args) {
            int limit = int.Parse(Console.ReadLine()); // Read number of test cases
            for (int i = 0; i < limit; i++) {
                Solve(); // Process each test case
            }
        }

        static void Solve() {
            int size = int.Parse(Console.ReadLine()); // Read the number of points
            int[] array = Console.ReadLine().Split(' ').Select(int.Parse).ToArray(); // Read and parse the points

            // If there are exactly two points and they are not consecutive,
            // then we can place a point between them so it's closest to both.
            if (array.Length == 2 && array[1] != array[0] + 1) {
                Console.WriteLine("YES");
            } else {
                Console.WriteLine("NO");
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/