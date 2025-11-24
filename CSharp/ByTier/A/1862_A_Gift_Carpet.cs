// Problem: CF 1862 A - Gift Carpet
// https://codeforces.com/contest/1862/problem/A

using System;
using System.Collections.Generic;

/*
 * Problem: Determine if a given carpet (n x m grid of lowercase letters) contains the sequence "vika" 
 * when read column by column from left to right, selecting exactly one letter per column.
 * 
 * Algorithm:
 * - For each column from left to right, scan down the rows to find the next required letter in "vika".
 * - Maintain a pointer k to track which letter of "vika" we are looking for.
 * - If we successfully find all 4 letters in order, output "YES", otherwise "NO".
 * 
 * Time Complexity: O(n * m), where n is number of rows and m is number of columns.
 * Space Complexity: O(n * m), to store the grid of characters.
 */

class Program {
  static void Sol() {
    int n, m;
    string[] input = Console.ReadLine().Split();
    n = int.Parse(input[0]);
    m = int.Parse(input[1]);
    string s = "vika";  // Target name to find
    List<string> v = new List<string>();  // Store the carpet rows
    
    for (int i = 0; i < n; i++) {
      string ll = Console.ReadLine();
      v.Add(ll);
    }
    
    int k = 0;  // Pointer to current letter in "vika" we are looking for
    
    for (int i = 0; i < m; i++) {  // Iterate through columns
      for (int j = 0; j < n; j++) {  // Iterate through rows in current column
        if (v[j][i] == s[k]) {  // If current character matches required letter
          k++;  // Move to next letter in "vika"
          break;  // Move to next column after finding one matching letter
        }
      }
      
      if (k == 4) {  // If all letters of "vika" have been found
        break;
      }
    }
    
    if (k == 4) {
      Console.WriteLine("YES");
    } else {
      Console.WriteLine("NO");
    }
  }
  
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Sol();
    }
  }
}

// https://github.com/VaHiX/CodeForces/