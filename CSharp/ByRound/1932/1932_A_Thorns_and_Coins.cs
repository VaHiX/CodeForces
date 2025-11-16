// Problem: CF 1932 A - Thorns and Coins
// https://codeforces.com/contest/1932/problem/A

/*
 * Problem: A. Thorns and Coins
 * 
 * Algorithm/Techniques: Greedy Approach
 * 
 * Time Complexity: O(n) where n is the length of the path string
 * Space Complexity: O(1) - only using a few variables regardless of input size
 * 
 * The solution uses a greedy approach to count coins while traversing the path.
 * It iterates through the path starting from the second cell, counting coins ('@').
 * If it encounters two consecutive thorns ('*'), it breaks the loop as further movement is impossible.
 * The first cell is guaranteed to be empty ('.'), so no special handling is needed for the starting position.
 */

using System;
using System.IO;
class MainClass {
  public static void Main(string[] args) {
    StreamReader reader = new StreamReader(Console.OpenStandardInput());
    int test = int.Parse(reader.ReadLine());
    while (test-- > 0) {
      int lenght = int.Parse(reader.ReadLine());
      string path = reader.ReadLine();
      int coin = 0;
      for (int i = 1; i < lenght; i++) {
        // If current cell contains a coin, increment the coin counter
        if (path[i] == '@')
          coin++;
        // If current cell and previous cell are both thorns, breaking point
        else if (path[i] == '*' && path[i - 1] == '*') {
          break;
        }
      }
      Console.WriteLine(coin);
    }
  }
}


// https://github.com/VaHiX/CodeForces/