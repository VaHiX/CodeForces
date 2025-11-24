// Problem: CF 2132 A - Homework
// https://codeforces.com/contest/2132/problem/A

/*
 * Problem: A. Homework
 * Purpose: Simulates appending characters from a string to another based on
 *          distribution rules (Vlad adds to front, Dima adds to back).
 * Algorithms/Techniques: String manipulation with StringBuilder for efficient operations.
 *
 * Time Complexity: O(m * n), where m is the length of the character string and n is the average length of initial string.
 * Space Complexity: O(n + m), for storing the result string and input strings.
 */
using System;
using System.Text;
namespace CodeForces.Problems.Round2132.A {
public static class HomeworkSolver {
  public static string ProcessTestCase(string initialString, string characters,
                                       string directions) {
    var result = new StringBuilder(initialString); // Initialize result with the initial string
    for (int i = 0; i < directions.Length; i++) {
      if (directions[i] == 'V') {
        result.Insert(0, characters[i]); // Vlad appends to front
      } else if (directions[i] == 'D') {
        result.Append(characters[i]); // Dima appends to back
      }
    }
    return result.ToString(); // Convert StringBuilder back to string
  }
  public static void Main(string[] args) {
    int testCases = int.Parse(Console.ReadLine());
    var results = new string[testCases];
    for (int i = 0; i < testCases; i++) {
      _ = int.Parse(Console.ReadLine()); // Read n (length of initial string)
      string initialString = Console.ReadLine(); // Read the initial string
      _ = int.Parse(Console.ReadLine()); // Read m (length of character and direction strings)
      string characters = Console.ReadLine(); // Read the characters to be added
      string directions = Console.ReadLine(); // Read the distribution pattern
      results[i] = ProcessTestCase(initialString, characters, directions);
    }
    foreach (var result in results) {
      Console.WriteLine(result);
    }
  }
}
}


// https://github.com/VaHiX/codeForces/