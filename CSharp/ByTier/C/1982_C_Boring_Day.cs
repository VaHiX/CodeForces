// Problem: CF 1982 C - Boring Day
// https://codeforces.com/contest/1982/problem/C

/*
 * Problem: C. Boring Day
 * 
 * Algorithm/Techniques:
 * - Sliding window technique with greedy approach
 * - We aim to maximize the number of rounds by taking cards such that each round's sum falls within [l, r]
 * - Using a two-pointer approach to efficiently find valid subarrays (rounds)
 * 
 * Time Complexity: O(n) where n is the number of cards, as each element is visited at most twice (once by end, once by start)
 * Space Complexity: O(n) for storing the array of cards
 */

using System;
class Program {
  static void Main() {
    string inputLine = Console.ReadLine();
    int t = int.Parse(inputLine.Trim());
    for (int cn = 0; cn < t; ++cn) {
      inputLine = Console.ReadLine();
      string[] fl = inputLine.Split();
      int n = int.Parse(fl[0]);
      long l = long.Parse(fl[1]);
      long r = long.Parse(fl[2]);
      inputLine = Console.ReadLine();
      string[] sl = inputLine.Split();
      long[] a = new long[n];
      for (int i = 0; i < n; ++i) {
        a[i] = long.Parse(sl[i]);
      }
      int maxR = 0;
      long sum = 0;
      int start = 0;
      for (int end = 0; end < n; ++end) {
        sum += a[end]; // Add current card to the running sum
        // Shrink the window from the left until sum is within [l, r]
        while (sum > r && start <= end) {
          sum -= a[start++]; // Remove the leftmost element and move start pointer
        }
        // If current window sum is valid (within [l, r]), count it as a round
        if (sum >= l && sum <= r) {
          ++maxR; // Increment round counter
          sum = 0; // Reset sum for next round
          start = end + 1; // Move start to next position after current round
        }
      }
      Console.WriteLine(maxR);
    }
  }
}


// https://github.com/VaHiX/CodeForces/