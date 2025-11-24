// Problem: CF 2117 C - Cool Partition
// https://codeforces.com/contest/2117/problem/C

/* 
 * Problem: C. Cool Partition
 * 
 * Purpose:
 *   This program finds the maximum number of segments that form a "cool" partition of an array.
 *   A cool partition ensures that for every segment b_j, all elements in b_j also appear in b_{j+1}.
 * 
 * Algorithm:
 *   - For each element in the array, we track its last occurrence.
 *   - As we iterate from right to left, we determine valid cut points where a new segment can begin.
 *   - The key idea is to maintain a set of elements seen so far and decide when it's safe to make a cut
 *     based on whether all previously seen elements are still present in the current segment.
 * 
 * Time Complexity:
 *   O(n) per test case, since we perform a single pass through the array and each operation in the dictionary is O(1) on average.
 * 
 * Space Complexity:
 *   O(n) for storing the array and auxiliary data structures (dictionary to store last positions of elements).
 */

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Con970_A {
internal class Program {
  static void Main(string[] args) { Sol_3(); }
  
  // Dictionary to store the count of occurrences of each element in current window
  static Dictionary<int, int> entries = new Dictionary<int, int>();
  
  static void Sol_3() {
    int count = Convert.ToInt32(Console.ReadLine());
    for (int i = 0; i < count; i++) {
      int n = Convert.ToInt32(Console.ReadLine());
      var arr = Console.ReadLine()
                    .Split(' ')
                    .Select(x0 => Convert.ToInt32(x0))
                    .ToList();
      int total = 0;
      int bound = arr.Count - 1;
      var res = GetBordersCount(arr) + 1; // Add 1 because number of partitions = number of borders + 1
      Console.WriteLine(res);
    }
  }
  
  // Returns left index (number of unique elements in prefix ending at given index)
  static int GetLeftIndex(List<int> arr, int index) {
    for (int i = index; i >= 0; i--) {
      if (entries.ContainsKey(arr[i]))
        entries[arr[i]]++;
      else
        entries[arr[i]] = 1;
    }
    int boundCount = 0;
    for (int i = 0; i < index; i++) {
      if (entries[arr[i]] == 1) {
        boundCount++;
      }
      entries[arr[i]]--;
    }
    return boundCount;
  }
  
  // Calculates number of borders in a cool partition (which determines number of segments)
  static int GetBordersCount(List<int> arr) {
    var borders = new List<int>();
    Dictionary<int, int> sets = new Dictionary<int, int>();
    int currentBorder = arr.Count - 1;
    
    // Traverse from right to left to find valid boundaries
    for (int i = arr.Count - 1; i >= 0; i--) {
      if (sets.ContainsKey(arr[i])) {
        // If this element was seen before
        if (sets[arr[i]] == currentBorder) {
          // A cut can be made here
          currentBorder = i;
          borders.Add(i);
          sets[arr[i]] = currentBorder;
        } else {
          var lastValidBorder = borders.Find(b => b <= sets[arr[i]]);
          sets[arr[i]] = i;
          borders.RemoveAll(b => b < lastValidBorder);
          borders.Add(i);
          currentBorder = i;
        }
      } else {
        // New element encountered
        borders.Clear();
        borders.Add(i);
        currentBorder = i;
        sets[arr[i]] = currentBorder;
      }
    }
    
    borders.Remove(0); // Remove 0 because we must not start with a cut at beginning of array
    
    return borders.Count;
  }
  
  static void Sol_2() {
    int count = Convert.ToInt32(Console.ReadLine());
    for (int i = 0; i < count; i++) {
      int n = Convert.ToInt32(Console.ReadLine());
      if (n % 2 == 1) {
        for (int j = 0; j < n / 2; j++) {
          Console.Write(1 + 2 * j);
          Console.Write(" ");
        }
        Console.Write(n);
        Console.Write(" ");
        for (int j = 0; j < n / 2; j++) {
          Console.Write((n - 1) - 2 * j);
          Console.Write(" ");
        }
      } else {
        for (int j = 0; j < n / 2; j++) {
          Console.Write(2 * (j + 1));
          Console.Write(" ");
        }
        for (int j = 0; j < n / 2; j++) {
          Console.Write((n - 1) - 2 * j);
          Console.Write(" ");
        }
      }
      Console.WriteLine();
    }
  }
  
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