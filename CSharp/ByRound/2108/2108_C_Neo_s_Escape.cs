// Problem: CF 2108 C - Neo's Escape
// https://codeforces.com/contest/2108/problem/C

/*
 * Problem: C. Neo's Escape
 * Purpose: Determine the minimum number of clones needed to press all buttons in a non-increasing order.
 * Algorithm:
 *   1. Remove consecutive duplicates from the input array to simplify processing.
 *   2. Find peaks in the simplified array — elements that are greater than their neighbors.
 *   3. The number of such peaks corresponds to the minimum number of clones required.
 * 
 * Time Complexity: O(n), where n is the number of buttons.
 * Space Complexity: O(n), due to storing the simplified list and result count.
 */

using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Linq;

namespace MyApp {
    internal class Program {
        static int Solve(IList<int> nums) {
            // Remove consecutive duplicate elements
            var a = new List<int>(nums.Count);
            foreach (var n in nums) {
                if (a.Count > 0 && a[a.Count - 1] == n) {
                    continue; // Skip duplicates
                }
                a.Add(n);
            }

            // Count number of peaks (local maxima)
            var res = 0;
            for (var i = 0; i < a.Count; i++) {
                // Check if current element is a peak:
                // it should be greater than left neighbor (if exists) and
                // greater than right neighbor (if exists)
                if ((i == 0 || a[i - 1] < a[i]) &&
                    (i == a.Count - 1 || a[i + 1] < a[i])) {
                    res += 1;
                }
            }
            return res;
        }

        static void Main(string[] args) {
            using (Stream inputStream = Console.OpenStandardInput()) 
            using (BufferedStream bufferedStream = new BufferedStream(inputStream)) 
            using (StreamReader reader = new StreamReader(bufferedStream, Encoding.ASCII)) {
                int index = -1;
                string line;
                while ((line = reader.ReadLine()) != null && line != "") {
                    index++;
                    // Skip odd lines (which contain n, not the button weights)
                    if (index == 0 || index % 2 == 1) {
                        continue;
                    }
                    // Parse input line into list of integers representing button weights
                    var nums = line.Split().Select(int.Parse).ToList();
                    Console.WriteLine(Solve(nums));
                }
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/