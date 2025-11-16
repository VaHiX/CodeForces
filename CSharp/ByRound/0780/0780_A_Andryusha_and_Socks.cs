// Problem: CF 780 A - Andryusha and Socks
// https://codeforces.com/contest/780/problem/A

﻿/*
 * Problem: Andryusha and Socks
 * 
 * Purpose: This code determines the maximum number of socks that were on the table 
 *          at the same time during Andryusha's process of putting socks into the wardrobe.
 * 
 * Algorithm: 
 * - Use a dictionary to track which sock pairs are currently on the table.
 * - For each sock taken from the bag:
 *   - If its pair is already on the table, remove the pair (socks go to wardrobe).
 *   - Otherwise, add the sock to the table.
 * - Track the maximum size of the dictionary (number of socks on table) during the process.
 * 
 * Time Complexity: O(n), where n is the number of pairs. Each operation on the dictionary (add/remove/contains) 
 *                  is O(1) on average, and we process 2n socks.
 * 
 * Space Complexity: O(n), for storing at most n pairs in the dictionary at any point.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Andryusha_and_Socks {
    internal class Program {
        static void Main(string[] args) {
            int input_1 = Convert.ToInt32(Console.ReadLine()), answer = 0;
            string[] split = Console.ReadLine().Split(' ');
            Dictionary<string, int> diction = new Dictionary<string, int>(); // Tracks pairs currently on the table
            
            for (int x = 0; x < split.Length; ++x) {
                if (diction.ContainsKey(split[x])) {
                    // If pair is already on the table, remove it (socks go to wardrobe)
                    diction.Remove(split[x]);
                } else {
                    // If pair is not on the table, add it (sock goes to table)
                    diction.Add(split[x], 1);
                }
                // Update maximum number of socks on the table
                answer = Math.Max(answer, diction.Count);
            }
            Console.WriteLine(answer);
            Console.ReadLine();
        }
    }
}


// https://github.com/VaHiX/CodeForces/