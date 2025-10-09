// Problem: CF 2091 A - Olympiad Date
// https://codeforces.com/contest/2091/problem/A

/*
 * Problem: Olympiad Date
 * Purpose: Determine the minimum number of digits needed to form the date "01.03.2025"
 *          from a sequence of drawn digits. The date includes digits 0,1,2,3,5 with specific counts.
 * 
 * Algorithm:
 *   - For each test case, iterate through the input digits and count occurrences of each digit.
 *   - Check at each step if we have enough digits to form "01.03.2025", which requires:
 *     - At least one '1'
 *     - At least one '3' 
 *     - At least three '0's
 *     - At least two '2's
 *     - At least one '5'
 *   - Return the step (number of digits drawn) at which these conditions are first met.
 *   - If impossible, return 0.
 *
 * Time Complexity: O(n) per test case where n is the number of digits
 * Space Complexity: O(1) since we use a fixed-size array of size 10 for digit counting
 */

using System;
namespace x {
class Program {
  static void Main(string[] args) {
    int T = Convert.ToInt32(Console.ReadLine());
    while (T > 0) {
      T--;
      int n = Convert.ToInt32(Console.ReadLine()), cur = 0;
      String s = Console.ReadLine();
      int[] cnt = new int[10]; // Count of each digit (0-9)
      bool ok = false; // Flag to check if we found a valid date
      for (int i = 0; i < 2 * n - 1; ++i) {
        if (s[i] != ' ') { // Ignore spaces in input string
          cnt[Convert.ToInt32(s[i] - '0')]++; // Increment count of current digit
          cur++; // Increment step counter
          // Check if we have all required digits with sufficient counts to form the date
          if (cnt[1] >= 1 && cnt[3] >= 1 && cnt[0] >= 3 && cnt[2] >= 2 &&
              cnt[5] >= 1) {
            Console.WriteLine(cur);
            ok = true;
            break;
          }
        }
      }
      if (!ok) {
        Console.WriteLine(0); // Could not form the date
      }
    }
  }
}
}


// https://github.com/VaHiX/codeForces/