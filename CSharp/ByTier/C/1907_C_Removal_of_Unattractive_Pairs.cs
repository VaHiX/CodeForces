// Problem: CF 1907 C - Removal of Unattractive Pairs
// https://codeforces.com/contest/1907/problem/C

/*
 * Problem: Removal of Unattractive Pairs
 * 
 * Algorithm/Technique: Greedy approach using frequency counting
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1), since we use a fixed-size array of 26 elements for character frequencies.
 * 
 * Approach:
 * The key insight is that we can remove adjacent pairs of different characters until no more such pairs exist.
 * In the end, the remaining string will only contain characters that appear in groups of the same character.
 * To minimize the final length, we try to "pair up" characters optimally.
 * For each character, we count how many of that character there are.
 * Then, for each character, we calculate the maximum possible leftover after pairing:
 *   - If there are fewer or equal other characters than this one, we can pair all except possibly some.
 *   - If there are more other characters, the leftover is (other_chars - this_chars) % 2.
 * We return the maximum such value across all characters.
 */

using System;
public class RemovalOfUnattractivePairs {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      int[] freqs = new int[26]; // Array to store frequency of each character
      foreach (char c in s)
        freqs[c - 'a']++; // Increment frequency of the character
      int ans = 0;
      foreach (int freq in freqs) {
        int numOthers = n - freq; // Count of all characters that are NOT the current one
        int r = numOthers <= freq ? freq - numOthers : (numOthers - freq) % 2;
        // Calculate max leftover for this character after pairing
        ans = Math.Max(ans, r); // Keep track of the maximum leftover
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/