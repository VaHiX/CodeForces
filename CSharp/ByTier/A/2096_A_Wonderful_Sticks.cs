// Problem: CF 2096 A - Wonderful Sticks
// https://codeforces.com/contest/2096/problem/A

/*
Problem: Wonderful Sticks
Algorithm: Greedy approach with careful assignment of values based on the direction of the inequality.
Time Complexity: O(n), where n is the number of sticks. Each element is visited once in the loop.
Space Complexity: O(n), for storing the array 'a' of size n.

The algorithm works as follows:
1. Initialize first element of the array to 1.
2. Traverse the string s:
   - If s[i] == '<', increment amax and assign a[i+1] = amax.
   - If s[i] == '>', decrement amin and assign a[i+1] = amin.
3. Adjust all values by adding p = n - amax to ensure all values are in [1,n].
4. Output the resulting array.

This greedy method ensures that we always maintain valid relative orderings according to the string s,
by using increasing/decreasing sequences and then scaling them appropriately.
*/

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      var s = Console.ReadLine().Trim();
      getAns(n, s);
    }
  }
  static void getAns(int n, string s) {
    var a = new int[n];
    a[0] = 1; // First element is initialized to 1
    var amax = 1; // Tracks maximum value used so far
    var amin = 1; // Tracks minimum value used so far
    for (int i = 0; i < n - 1; i++) {
      if (s[i] == '>') { // If next stick must be larger than all before
        amax++; // Increase max to ensure next element is larger
        a[i + 1] = amax;
      } else { // If next stick must be smaller than all before
        amin--; // Decrease min to ensure next element is smaller
        a[i + 1] = amin;
      }
    }
    var p = n - amax; // Offset to scale the values into range [1,n]
    for (int i = 0; i < n; i++)
      a[i] += p; // Adjust all elements to make them valid
    Console.WriteLine(string.Join(" ", a));
  }
}


// https://github.com/VaHiX/codeForces/