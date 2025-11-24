// Problem: CF 1702 F - Equate Multisets
// https://codeforces.com/contest/1702/problem/F

/*
 * Problem: Equate Multisets
 * 
 * Purpose: Determine if multiset b can be transformed into multiset a using allowed operations:
 *          - Double an element (x -> 2*x)
 *          - Halve an element (x -> floor(x/2))
 * 
 * Algorithm:
 * 1. For each element in array a, repeatedly divide by 2 until it becomes odd.
 *    This gives us the "base" value that the element can reach.
 * 2. Count occurrences of each base value in array a and store in a dictionary.
 * 3. For each element in array b:
 *    - Keep halving it until we find a value that exists in the dictionary with count > 0.
 *    - If no such value is found, return "NO".
 *    - Otherwise, decrease the count of that base value.
 * 4. If all elements in b are matched, return "YES".
 *
 * Time Complexity: O(n * log(max_value)) where n is the size of arrays and max_value is the maximum element.
 *                  The log factor comes from repeatedly dividing elements by 2.
 * Space Complexity: O(n) for storing the dictionary of base values from array a.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace YKCodeForces {
class Program {
  static void Main(string[] args) {
    Solution s = new Solution();
    int t = int.Parse(Console.ReadLine());
    while (t > 0) {
      t--;
      s.Read();
      s.Solve();
    }
    Console.ReadLine();
  }
  class Solution {
    private int n;
    private int[] a, b;
    public Solution() {}
    public void Read() {
      string s = Console.ReadLine();
      n = int.Parse(s);
      a = new int[n];
      b = new int[n];
      string[] inputArr = Console.ReadLine().Split(' ');
      for (int i = 0; i < n; i++) {
        a[i] = int.Parse(inputArr[i]);
      }
      inputArr = Console.ReadLine().Split(' ');
      for (int i = 0; i < n; i++) {
        b[i] = int.Parse(inputArr[i]);
      }
      // Reduce all elements in 'a' to their "base" form by dividing by 2 until odd
      for (int i = 0; i < n; i++) {
        while (a[i] % 2 == 0) {
          a[i] /= 2;
        }
      }
    }
    public void Solve() {
      Dictionary<int, int> map = new Dictionary<int, int>();
      // Count occurrences of base values from array a
      foreach (var num in a) {
        if (!map.ContainsKey(num)) {
          map.Add(num, 0);
        }
        ++map[num];
      }
      bool res = true;
      // For each element in b, find a matching base value from a
      foreach (var num in b) {
        int tmp = num;
        // Keep dividing by 2 to find a base value that exists in the map
        while (tmp != 0) {
          if (map.ContainsKey(tmp) && map[tmp] != 0) {
            break;
          }
          tmp /= 2;
        }
        // If no matching base value found, return "NO"
        if (tmp == 0) {
          res = false;
          break;
        }
        map[tmp]--;
      }
      if (res) {
        Console.WriteLine("YES");
      } else {
        Console.WriteLine("NO");
      }
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/