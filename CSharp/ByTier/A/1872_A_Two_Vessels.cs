// Problem: CF 1872 A - Two Vessels
// https://codeforces.com/contest/1872/problem/A

/*
 * Problem: Two Vessels
 * 
 * Algorithm/Technique: Mathematical approach to find minimum moves
 * 
 * Time Complexity: O(1) - Constant time for each test case
 * Space Complexity: O(1) - Constant space used
 * 
 * Approach:
 * 1. Calculate the difference between the two vessel amounts.
 * 2. Determine how many transfers of capacity 'c' are needed to balance the vessels.
 * 3. Since we can transfer at most 'c' grams in one move, and each move affects both vessels,
 *    we need to determine the minimal number of moves by calculating how many times we need to
 *    transfer half of the difference (rounded up).
 * 
 * Example walkthrough:
 * If a=3, b=7, c=2:
 *   - mx = 7, mn = 3
 *   - diff = 4
 *   - moves = ceil(4 / 2) / 2 = ceil(2) = 2? No, it's just ceil(diff / (2 * c))
 *   Wait, let's recheck:
 *   We must make both vessels have (a + b) / 2 grams.
 *   The imbalance is |a - b| / 2.
 *   To balance, we need ceil(imbalance / c) moves.
 *   But wait, in each move we transfer at most c, and it reduces the imbalance by at most 2*c.
 *   So minimum moves = ceil(|a - b| / (2 * c))
 * 
 * However, looking at the code more carefully, it computes:
 *   r = ceil((mx - mn) / el) / 2
 * This implies:
 *   r = ceil((mx - mn) / (2 * el))
 * Which means it computes (difference) / (2 * c) and rounds up.
 * If difference is 4, c=2, then ceil(4 / (2*2)) = ceil(1) = 1 ✔️
 * 
 * Note: The exact mathematical derivation was not explained clearly in the original code,
 * but based on the expected outputs, the code logic holds for valid input.
 */

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Runtime.Remoting.Metadata.W3cXsd2001;
using System.Text;
using System.Threading.Tasks;

namespace Practi__selling_1 {
    internal class Codeforces {
        static void Main(string[] args) {
            int t = Convert.ToInt32(Console.ReadLine()); // Read number of test cases
            double mx;  // Maximum amount of water in vessels
            double mn;  // Minimum amount of water in vessels
            double el;  // Capacity of the cup (c)
            double r;   // Result - minimum number of moves
            int c = 0;  // Unused variable, likely left-over from previous versions

            while (t > 0) {
                string[] str = Console.ReadLine().Split(); // Read a, b, c from input
                double[] a = new double[3]; // Array to store a, b, c
                for (int i = 0; i < str.Length; i++) {
                    a[i] = Convert.ToInt32(str[i]); // Convert string inputs to integers
                }

                mx = Math.Max(a[0], a[1]);  // Find maximum amount of water
                mn = Math.Min(a[0], a[1]);  // Find minimum amount of water
                el = a[2];  // Cup capacity

                // Compute minimum moves needed using formula:
                // ceil((max - min) / (2 * c)) 
                r = Math.Ceiling(((mx - mn) / el) / 2);

                Console.WriteLine(r);  // Output result
                t--;  // Decrement test case counter
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/