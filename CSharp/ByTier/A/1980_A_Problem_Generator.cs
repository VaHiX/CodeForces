// Problem: CF 1980 A - Problem Generator
// https://codeforces.com/contest/1980/problem/A

/*
 * Problem: Minimum Number of Problems to Create
 * 
 * Algorithm:
 * - For each test case, count how many problems of each difficulty level (A to G) are available.
 * - Determine how many problems of each difficulty level are needed (m rounds, each needs one of each difficulty).
 * - Calculate the deficit for each difficulty level and sum all deficits to get the minimum number of new problems needed.
 * 
 * Time Complexity: O(n + 1) per test case, where n is the number of problems in the bank. 
 *                  The "1" accounts for the fixed number of difficulty levels (7). 
 *                  Since n and m are bounded, this is effectively O(1) per test case.
 * 
 * Space Complexity: O(1) - only using fixed-size dictionaries (7 characters) and a few variables.
 */

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  public static List<int>
  MinProblemsNeeded(int t, List<Tuple<int, int, string>> testCases) {
    var results = new List<int>();
    for (int i = 0; i < t; i++) {
      var testCase = testCases[i];
      int n = testCase.Item1;
      int m = testCase.Item2;
      string a = testCase.Item3;
      // Initialize counts for each difficulty level to 0
      var problemCounts =
          new Dictionary<char, int> { { 'A', 0 }, { 'B', 0 }, { 'C', 0 },
                                      { 'D', 0 }, { 'E', 0 }, { 'F', 0 },
                                      { 'G', 0 } };
      // Count available problems of each difficulty
      foreach (char ch in a) {
        problemCounts[ch]++;
      }
      // Each difficulty level is needed m times for m rounds
      var neededCounts =
          new Dictionary<char, int> { { 'A', m }, { 'B', m }, { 'C', m },
                                      { 'D', m }, { 'E', m }, { 'F', m },
                                      { 'G', m } };
      int totalDeficit = 0;
      // Calculate total deficit across all difficulty levels
      foreach (char ch in "ABCDEFG") {
        if (problemCounts[ch] < neededCounts[ch]) {
          totalDeficit += neededCounts[ch] - problemCounts[ch];
        }
      }
      results.Add(totalDeficit);
    }
    return results;
  }
  static void Main(string[] args) {
    string input = Console.In.ReadToEnd();
    string[] data = input.Split(new[] { ' ', '\n', '\r' },
                                StringSplitOptions.RemoveEmptyEntries);
    int index = 0;
    int t = int.Parse(data[index]);
    index++;
    var testCases = new List<Tuple<int, int, string>>();
    for (int i = 0; i < t; i++) {
      int n = int.Parse(data[index]);
      int m = int.Parse(data[index + 1]);
      string a = data[index + 2];
      testCases.Add(Tuple.Create(n, m, a));
      index += 3;
    }
    var results = MinProblemsNeeded(t, testCases);
    foreach (int result in results) {
      Console.WriteLine(result);
    }
  }
}


// https://github.com/VaHiX/CodeForces/