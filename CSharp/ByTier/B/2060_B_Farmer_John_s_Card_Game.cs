// Problem: CF 2060 B - Farmer John's Card Game
// https://codeforces.com/contest/2060/problem/B

/*
B. Farmer John's Card Game
Algorithm: Greedy + Sorting
Time Complexity: O(n * m * log(m) + n * log(n))
Space Complexity: O(n * m)

The problem involves finding a valid turn order for cows to play cards such that
each cow plays all their cards in increasing order, and each card played must be
greater than the last played card. We approach this by:
1. Ensuring each cow's deck is sorted (greedy: play smallest available card first).
2. Checking if each cow has cards forming an arithmetic sequence with difference n,
    which means they can play sequentially.
3. If valid, assigning cows to turn order based on minimum card value they hold.
4. Final check ensures the turn order results in a valid progression (0 to n*m - 1).

Approach:
- For each cow, sort their cards and verify if it's an arithmetic sequence with diff = n
- Store min card of each cow along with their index
- Sort cows by min card value to assign turn order greedily
- Validate that resulting sequence covers all numbers from 0 to n*m - 1 exactly once.
*/

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      getAns(n, m);
    }
  }
  static bool check(int n, int m, int[] a) {
    // Check if the array forms an arithmetic sequence with common difference equal to n
    for (int i = 0; i < m - 1; i++) {
      if (a[i + 1] - a[i] != n)
        return false;
    }
    return true;
  }
  static void getAns(int n, int m) {
    var c = new(int a0, int id)[n]; // Store min card value and cow id
    var no = false; // Flag to indicate if a cow doesn't form correct sequence
    for (int i = 0; i < n; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      Array.Sort(a); // Sort the cards of each cow in ascending order
      c[i] = (a[0], i + 1); // Store minimum card and cow id
      if (!check(n, m, a)) // If not arithmetic sequence with diff n
        no = true;
    }
    if (no) {
      Console.WriteLine(-1);
      return;
    }
    c = c.OrderBy(x => x.a0).ToArray(); // Sort cows by their minimum card value
    var c2 = Enumerable.Range(0, n).ToArray(); // Expected sequence from 0 to n-1
    var ans = new int[n];
    for (int i = 0; i < n; i++) {
      if (c[i].a0 != c2[i]) { // Check if turn order leads to correct progression
        Console.WriteLine(-1);
        return;
      }
      ans[i] = c[i].id; // Assign cow id to turn position
    }
    Console.WriteLine(string.Join(" ", ans));
  }
}


// https://github.com/VaHiX/codeForces/