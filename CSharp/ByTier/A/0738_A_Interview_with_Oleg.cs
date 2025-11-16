// Problem: CF 738 A - Interview with Oleg
// https://codeforces.com/contest/738/problem/A

﻿/*
 * Problem: Replace all maximal filler words "ogo", "ogogo", "ogogogo", etc. with "***"
 * Algorithm: Iterate through string and for each 'o', check if it's the start of a filler.
 *            A filler is a prefix of "ogo" followed by any number of "go" suffixes.
 *            When a filler is found, replace it with "***".
 * 
 * Time Complexity: O(n^2) in worst case due to nested checks (although practically much faster)
 * Space Complexity: O(n) for the result string
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace First {
class Program {
  static void Main(string[] args) {
    int n = int.Parse(Console.ReadLine()); // Read length of string
    string s = Console.ReadLine(); // Read the interview string
    string ans = ""; // Result string to build
    
    for (int i = 0; i < n; i++) {
      if (s[i] == 'o') { // If current character is 'o'
        bool b = false; // Flag to track if we're in a potential filler
        bool br = false; // Flag to track if we've broken out of loop
        
        if (i + 2 >= n) { // If not enough characters left for "ogo"
          ans += s[i]; // Add character as is
        } else {
          while (i + 2 < n) { // While we can check next two characters
            if (s[i + 1] == 'g' && s[i + 2] == 'o') { // If we find "go"
              b = true; // Mark that we found a "go"
              i += 2; // Skip the "go"
            } else if (b) { // If we already found some "go" but current is not "go"
              ans += "***"; // Replace with filler
              br = true; // Mark we're done with this filler
              break; // Exit while loop
            } else { // If we haven't found any "go" yet
              ans += s[i]; // Add current character as is
              br = true; // Mark we're done processing
              break; // Exit while loop
            }
          }
          if (i + 2 >= n && !br && b) { // If we've reached end but still have a filler to handle
            ans += "***"; // Replace with filler
          }
        }
      } else
        ans += s[i]; // Add character as is if not 'o'
    }
    Console.WriteLine(ans); // Print final result
  }
}
}


// https://github.com/VaHiX/CodeForces/