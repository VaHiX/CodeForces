// Problem: CF 2067 B - Two Large Bags
// https://codeforces.com/contest/2067/problem/B

/*
B. Two Large Bags
Algorithm: Greedy with frequency counting and simulation
Time Complexity: O(n) per test case
Space Complexity: O(n) due to auxiliary array b of size n+5

The problem asks whether we can make two bags equal by:
1. Moving elements from bag 1 to bag 2
2. Increasing an element in bag 1 if it's also present in bag 2

Key idea:
- Use frequency counting to track how many times each number appears
- For each number from 1 to n:
  - If it appears 0 times, we need to check if we can "create" it via incrementing (but only one such creation allowed)
  - If it appears more than 0 times, we can derive how to manage the surplus for future operations
- The logic uses a counter (cnt) to track pending increments that can't be resolved yet.
*/

using System;
class Program {
  static bool Solve() {
    int n = int.Parse(Console.ReadLine());
    int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
    int[] b = new int[n + 5]; // Frequency array to track counts of numbers from 1 to n
    for (int i = 0; i < n; i++) {
      if (a[i] < 1 || a[i] > n)
        return false;
      b[a[i]]++; // Count frequency of each number in input array
    }
    int cnt = 0; // Tracks how many numbers we have to resolve via incrementing later
    for (int i = 1; i <= n; i++) {
      if (b[i] == 0) { // Number i does not appear in original array
        if (cnt == 1)
          return false; // We already had one unresolved incrementable number, can't handle another
        if (cnt >= 2)
          cnt -= 2; // Resolve two increments (i.e., two numbers which we could create with one increment each)
      } else {
        int asa = b[i] + cnt; // Total available of number i + pending increments
        if (asa == 1)
          return false; // Cannot have exactly 1 after resolving previous increments, not enough to form pair
        cnt = asa - 2; // Remaining numbers after using some for pairing and creating new ones
      }
    }
    return true;
  }
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      Console.WriteLine(Solve() ? "Yes" : "No");
    }
  }
}


// https://github.com/VaHiX/codeForces/