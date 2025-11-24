// Problem: CF 1902 A - Binary Imbalance
// https://codeforces.com/contest/1902/problem/A

/*
 * Problem: Binary Imbalance
 * 
 * Algorithm/Technique: Greedy approach
 * 
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(n) due to the storage of the input string.
 * 
 * The key insight is that we can only insert '1' when two adjacent characters are the same,
 * and we can insert '0' when they are different. 
 * 
 * If there is at least one '0' in the string, we can always make the number of zeros greater than ones
 * by inserting '0' at the correct position. However, if all characters are '1', we can never
 * insert a '0' and thus cannot make zeros greater than ones.
 * 
 * Therefore, the solution is to check if there exists at least one '0' in the string.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace ConsoleApp1 {
internal class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      int gg = int.Parse(Console.ReadLine());
      var s = Console.ReadLine().ToArray();
      int caunt = 0;
      for (int j = 0; j < gg; j++) {
        if (s[j] == '0') {
          Console.WriteLine("YES"); // If we find a '0', we can make the count of '0' greater than '1'
          caunt++;
          break;
        }
      }
      if (caunt == 0) {
        Console.WriteLine("NO"); // If no '0' is found, it's impossible to increase the count of '0'
      }
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/