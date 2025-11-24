// Problem: CF 2067 A - Adjacent Digit Sums
// https://codeforces.com/contest/2067/problem/A

/*
 * Problem: Adjacent Digit Sums
 * Task: Determine if there exists an integer n such that S(n) = x and S(n+1) = y,
 *       where S(a) denotes the sum of digits of a.
 * 
 * Algorithm:
 * - When we increment a number by 1, the digit sum typically decreases by 9
 *   when a carry occurs (e.g., 999 -> 1000). Otherwise, it increases by 1.
 * - Thus S(n+1) = S(n) + 1, unless there's a carry involving trailing 9s.
 * - If n ends in k trailing 9s, then S(n+1) = S(n) - 9*k + 1.
 * 
 * Key Observations:
 * - If we want S(n+1) = y and S(n) = x, we can write the condition as:
 *   y = x - 9*k + 1 (for some k >= 0). Solving for k gives:
 *   k = (x - y + 1) / 9, which must be a non-negative integer.
 * 
 * However, in this implementation:
 * - It checks if (n + 1) % 9 == m % 9 AND m <= n + 1,
 *   assuming there's a direct solution approach based on digit sum properties.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using System;
using System.Collections.Generic;
using System.Numerics;

namespace program {
    class Program {
        public static void Main(string[] args) {
            int t = Convert.ToInt32(Console.ReadLine());
            while (t-- > 0) {
                string[] x = Console.ReadLine().Split(' ');
                int n = int.Parse(x[0]); // x in the problem - target sum of digits for n
                int m = int.Parse(x[1]); // y in the problem - target sum of digits for n+1

                // Check if valid conditions are met:
                // (n + 1) % 9 == m % 9 ensures that the digit sums are compatible with increment behavior.
                // m - 1 <= n ensures basic feasibility (i.e., n is large enough)
                string ans = (n + 1) % 9 == m % 9 && m - 1 <= n ? "YES" : "NO";
                Console.WriteLine(ans);
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/