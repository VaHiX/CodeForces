// Problem: CF 2128 B - Deque Process
// https://codeforces.com/contest/2128/problem/B

/*
B. Deque Process
Algorithm: Greedy with two pointers
Time Complexity: O(n) per test case
Space Complexity: O(n) for input array and output string

The problem asks us to remove elements from either end of a permutation such that the resulting sequence is "good".
A sequence is good if there is no 5 consecutive elements in strictly increasing or decreasing order.
We use a greedy approach:
- We maintain two pointers i (left) and j (right).
- At each step, we compare the values at the ends.
- If a[i] < a[j], we prefer to take from left (L) when it's our turn (lt), otherwise right (R).
- Otherwise, we do the reverse.
This greedy selection ensures we avoid creating 5-element monotonic subsequences.
*/

using System.Text;
namespace DequeProcess;
class Program {
  static void Solve() {
    int n = Next();
    int[] a = new int[n];
    for (int i = 0; i < n; i++)
      a[i] = Next();
    bool lt = true; // Tracks whose turn it is: true for left turn, false for right turn
    for (int i = 0, j = n - 1; i <= j; lt = !lt) { // Two pointers approach
      if (a[i] < a[j]) {
        if (lt) {
          writer.Write("L"); // Take from left
          i++;
        } else {
          writer.Write("R"); // Take from right
          j--;
        }
      } else {
        if (!lt) {
          writer.Write("L"); // Take from left
          i++;
        } else {
          writer.Write("R"); // Take from right
          j--;
        }
      }
    }
    writer.WriteLine();
  }
  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++)
      Solve();
    writer.Flush();
  }
  static int Next() {
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res;
      res *= 10;
      res += c - '0';
    }
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/