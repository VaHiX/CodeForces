// Problem: CF 1956 B - Nene and the Card Game
// https://codeforces.com/contest/1956/problem/B

using System;
public class NeneAndTheCardGame {
  /*
   * Problem: Nene and the Card Game
   * Purpose: Determine the maximum points you can score in a card game where you and Nene play optimally.
   * 
   * Algorithm:
   * - Since each number from 1 to n appears exactly twice in the entire deck, 
   *   and you have n cards, you know how many of each number you have.
   * - If you have two of the same number in your hand, you can gain points by playing one of them
   *   after the other has been played, but this opportunity is limited by how many of a number Nene has.
   * - The key insight is: you can score at most as many points as the number of duplicates in your hand.
   * - To maximize your score, you want to count how many numbers appear twice in your hand.
   * - Sort the array to easily count duplicates.
   * 
   * Time Complexity: O(n log n) due to sorting.
   * Space Complexity: O(1) additional space (not counting input storage).
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] a = new int[n];
      for (int j = 0; j < n; j++)
        a[j] = int.Parse(parts[j]);
      Array.Sort(a);  // Sort to group identical numbers together for easy duplicate counting
      int ans = 0;
      for (int j = 1; j < n; j++)
        if (a[j] == a[j - 1])
          ans++;  // Counting duplicates in sorted array
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/