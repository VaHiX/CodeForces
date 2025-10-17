// Problem: CF 2092 B - Lady Bug
// https://codeforces.com/contest/2092/problem/B

/*
B. Lady Bug

Algorithm:
The problem involves determining whether two binary strings a and b can be made such that string a consists only of zeros using specific swap operations. The key insight is to analyze the positions where elements are swapped, and count how many 1s can effectively be moved to the first string (a) under the constraints of allowed operations.

Time Complexity: O(n) per test case
Space Complexity: O(1)

Approach:
- For each position i in the string:
  * If i is even, we assign a[i] to sum1 and b[i] to sum2.
  * If i is odd, we assign b[i] to sum1 and a[i] to sum2.
- This simulates how the swaps affect which bits end up in position 0 of string a.
- Then count how many 1s are allowed at positions that can contribute to the final string a (at even indices or odd indices depending on mapping).
- Compare if sums exceed available slots to place 1s.

*/
using System;
class Program {
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    string a = Console.ReadLine();
    string b = Console.ReadLine();
    long sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; ++i) {
      if (i % 2 == 0) {
        // If even index, we can place a[i] into a's slot and b[i] into b's slot
        sum1 += a[i] - '0';
        sum2 += b[i] - '0';
      } else {
        // If odd index, we must use the opposite placement logic
        sum1 += b[i] - '0';
        sum2 += a[i] - '0';
      }
    }
    // Calculate number of positions that can be filled with 1s in final string a
    long numBSlots1 = n / 2;  // Number of even indices (where a[i] is directly used)
    long numBSlots2 = (n + 1) / 2;  // Number of odd indices (where b[i] is directly used)
    Console.WriteLine((sum1 <= numBSlots1 && sum2 <= numBSlots2) ? "YES"
                                                                 : "NO");
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/