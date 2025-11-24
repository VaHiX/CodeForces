// Problem: CF 1980 C - Sofia and the Lost Operations
// https://codeforces.com/contest/1980/problem/C

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Sol() {
    long n = long.Parse(Console.ReadLine()); // Read size of the array
    List<long> v = Console.ReadLine().Split().Select(long.Parse).ToList(); // Read original array
    List<long> b = Console.ReadLine().Split().Select(long.Parse).ToList(); // Read target array
    long m = long.Parse(Console.ReadLine()); // Read number of operations
    List<long> c = Console.ReadLine().Split().Select(long.Parse).ToList(); // Read values to be assigned in operations
    Dictionary<long, long> mp = new Dictionary<long, long>(); // Map to count frequency of operations
    foreach (var val in c) {
      if (mp.ContainsKey(val))
        mp[val]++;
      else
        mp[val] = 1;
    }
    bool flag = false;
    for (int i = 0; i < n; i++) {
      // Check if last operation's value matches current target element
      if (c[(int)m - 1] == b[i]) {
        flag = true;
      }
      // If original and target differ, adjust frequency map
      if (v[i] != b[i]) {
        if (mp.ContainsKey(b[i]))
          mp[b[i]]--;
        else
          mp[b[i]] = -1;
      }
    }
    // Check if any required value has negative count (impossible to fulfill)
    foreach (var kvp in mp) {
      if (kvp.Value < 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      Console.WriteLine("YES");
    } else {
      Console.WriteLine("NO");
    }
  }
  static void Main(string[] args) {
    long test = long.Parse(Console.ReadLine()); // Read number of test cases
    for (long i = 0; i < test; i++) {
      Sol();
    }
  }
}
/*
Algorithm/Techniques: Hash Map, Greedy Approach

Time Complexity: O(n + m)
Space Complexity: O(m)

The algorithm uses a hash map to track frequencies of values in the operations. 
It checks if the required transformations are possible by ensuring that
the frequency of elements in operations can support the differences between
original and target arrays. The last element of the operations is special in that
it should appear in the target array at least once to allow the solution.
*/

// https://github.com/VaHiX/CodeForces/