// Problem: CF 2036 A - Quintomania
// https://codeforces.com/contest/2036/problem/A

using System;
public class Quintomania {
  /*
   * Problem: Determine if a melody is "perfect".
   * A melody is perfect if the absolute difference between every two adjacent notes is either 5 or 7 semitones.
   * 
   * Algorithms/Techniques:
   * - Single pass through the array of notes to check each adjacent pair.
   * - For each pair, compute the absolute difference and verify it's either 5 or 7.
   * 
   * Time Complexity: O(n) per melody, where n is the number of notes.
   * Space Complexity: O(n) for storing the notes in the array.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of melodies
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine()); // Read number of notes in current melody
      string[] parts = Console.ReadLine().Split(); // Read the notes as strings
      byte[] a = new byte[n]; // Create array to store notes
      for (byte j = 0; j < n; j++)
        a[j] = byte.Parse(parts[j]); // Parse and store each note
      bool ans = true; // Assume melody is perfect initially
      for (byte j = 1; j < n && ans; j++) { // Iterate from second note to last
        byte d = Convert.ToByte(Math.Abs(a[j] - a[j - 1])); // Compute absolute difference
        ans = d == 5 || d == 7; // Check if difference is valid (5 or 7)
      }
      Console.WriteLine(ans ? "YES" : "NO"); // Output result for current melody
    }
  }
}

// https://github.com/VaHiX/CodeForces/