// Problem: CF 2117 B - Shrink
// https://codeforces.com/contest/2117/problem/B

/* 
 * Problem: B. Shrink
 * Purpose: Construct a permutation of length n that maximizes the number of shrink operations.
 * Algorithm: 
 *   - For odd n: Place 1 at start, then alternate between increasing and decreasing sequences (1,3,5...n,n-2,...3,2)
 *   - For even n: Place 2,4,6...n then n-1,n-3,...,3,1
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) extra space (not counting input/output)
 */

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Con970_A {
    internal class Program {
        static void Main(string[] args) { Sol_2(); }

        // Sol_2 solves the shrink problem by constructing a specific permutation
        // based on whether n is even or odd to maximize shrink operations.
        static void Sol_2() {
            int count = Convert.ToInt32(Console.ReadLine());
            for (int i = 0; i < count; i++) {
                int n = Convert.ToInt32(Console.ReadLine());
                if (n % 2 == 1) {
                    // For odd n: build pattern like 1 3 5 ... n n-2 ... 3 2
                    for (int j = 0; j < n / 2; j++) {
                        Console.Write(1 + 2 * j);           // Write increasing odds
                        Console.Write(" ");
                    }
                    Console.Write(n);                       // Write middle element
                    Console.Write(" ");
                    for (int j = 0; j < n / 2; j++) {
                        Console.Write((n - 1) - 2 * j);     // Write decreasing odds
                        Console.Write(" ");
                    }
                } else {
                    // For even n: build pattern like 2 4 6 ... n n-1 n-3 ... 3 1
                    for (int j = 0; j < n / 2; j++) {
                        Console.Write(2 * (j + 1));         // Write increasing evens
                        Console.Write(" ");
                    }
                    for (int j = 0; j < n / 2; j++) {
                        Console.Write((n - 1) - 2 * j);     // Write decreasing odds
                        Console.Write(" ");
                    }
                }
                Console.WriteLine(); // New line after each permutation
            }
        }

        // Sol_1 handles input related to door closing problem, not used in shrink task.
        static void Sol_1() {
            int count = Convert.ToInt32(Console.ReadLine());
            for (int i = 0; i < count; i++) {
                var arr = Console.ReadLine().Split(' ');
                var n = Convert.ToInt32(arr[0]);
                var x = Convert.ToInt32(arr[1]);
                var doors = Console.ReadLine()
                                .Split(' ')
                                .Select(x0 => Convert.ToInt32(x0))
                                .ToList();
                var closedIndex = doors.IndexOf(1);
                var lastClosed = closedIndex;
                while (doors.IndexOf(1, lastClosed + 1) > 0 && lastClosed < n) {
                    lastClosed = doors.IndexOf(1, lastClosed + 1);
                }
                if (lastClosed - closedIndex < x) {
                    Console.WriteLine("YES");
                } else {
                    Console.WriteLine("NO");
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/