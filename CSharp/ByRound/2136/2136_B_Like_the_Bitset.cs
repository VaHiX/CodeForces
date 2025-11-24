// Problem: CF 2136 B - Like the Bitset
// https://codeforces.com/contest/2136/problem/B

/*
B. Like the Bitset
Algorithm: Greedy assignment of permutation values based on the positions marked '1' in string s.
Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(n) for storing the result array.

Approach:
- First, we assign increasing numbers to all '1's in the string. If more than k such positions are found consecutively, it's impossible (NO).
- Then, we assign remaining numbers to '0's in order.
- This greedy approach ensures that the constraint is satisfied for each '1'-position:
    - For any interval [l,r] with length >= k covering a '1' at position i,
      the maximum value in that interval is NOT p[i], which holds because
      values assigned to '1's are less than those assigned to '0's.

Key observations:
- Each '1' must be part of some interval of size >= k.
- To avoid violating the constraint, ensure every '1' has a larger value in overlapping intervals.
- Assigning all '1's first with numbers 1,2,... (up to q) ensures these values are smaller than those for '0's.
*/
using System.Text;
namespace LikeTheBitset;
class Program {
  static void Solve() {
    var p = reader.ReadLine()
                .Split(' ')
                .Where(e => !string.IsNullOrEmpty(e))
                .Select(int.Parse)
                .ToList();
    int n = p[0];
    int k = p[1];
    string s = reader.ReadLine();
    int[] ans = new int[n];
    int q = 1;
    for (int i = 0, c = 0; i < s.Length; i++) {
      if (s[i] == '1') { // Process all positions marked '1'
        ans[i] = q++; // Assign increasing integers to '1' positions
        c++;
        if (c == k) { // If we find k consecutive ones, impossible to satisfy constraints
          writer.WriteLine("NO");
          return;
        }
      } else
        c = 0; // Reset counter when encountering a '0'
    }
    for (int i = 0; i < s.Length; i++) {
      if (s[i] == '0') // Assign larger values to '0' positions
        ans[i] = q++;
    }
    writer.WriteLine("YES");
    foreach (var i in ans) {
      writer.Write(i);
      writer.Write(' ');
    }
    writer.WriteLine();
  }
  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();
    }
    writer.Flush();
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/