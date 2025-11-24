// Problem: CF 2060 C - Game of Mathletes
// https://codeforces.com/contest/2060/problem/C

/*
 * Problem: C. Game of Mathletes
 * 
 * Purpose:
 *   This code computes the maximum score achievable in a two-player game where:
 *   - Alice and Bob take turns selecting numbers from a list.
 *   - Each turn, one number is selected by each player.
 *   - If the sum of their selected numbers equals k, the score increases by 1.
 *   - Alice tries to minimize the score, while Bob tries to maximize it.
 *   - Both players play optimally.
 *
 * Approach:
 *   - For each unique number in the list, we compute how many times it appears.
 *   - We iterate through all unique numbers and pair them with their complement (k - num).
 *   - If a number is its own complement (i.e., num * 2 == k), then pairs are formed among themselves.
 *   - For other numbers, the count of pairs is limited by the minimum of occurrences of both numbers.
 *   - We use a greedy strategy: for each number we process, we pair it with its complement if exists,
 *     and mark those numbers as used to avoid double counting.
 *
 * Time Complexity:
 *   O(n) where n is the total number of elements in input lists. 
 *   This is achieved by using Dictionary for frequency counting and HashSet for tracking used elements.
 *
 * Space Complexity:
 *   O(n) due to storing frequencies in dictionary and used elements in hash set.
 */

using System;
using System.Collections.Generic;
using System.Linq;

class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      var nk = Console.ReadLine().Split().Select(int.Parse).ToArray(); // Read n and k
      int n = nk[0];
      int k = nk[1];
      var numbers = Console.ReadLine().Split().Select(int.Parse).ToList(); // Read the list of numbers
      
      var freq = new Dictionary<int, int>(); // Count frequency of each number
      
      foreach (var num in numbers) { // Build frequency map
        if (freq.ContainsKey(num))
          freq[num]++;
        else
          freq[num] = 1;
      }
      
      int score = 0;
      var used = new HashSet<int>(); // Track which numbers are already paired
      
      foreach (var num in numbers) {
        if (used.Contains(num)) // Skip if already used
          continue;
          
        int complement = k - num; // Calculate the required complement
        
        if (freq.ContainsKey(complement)) { // Check if complement exists in the frequency map
          if (complement == num) { // If number is its own complement, pair elements among themselves
            score += freq[num] / 2;
            used.Add(num);
          } else { // Otherwise, count pairs between num and complement
            int min = Math.Min(freq[num], freq[complement]);
            score += min;
            used.Add(num);
            used.Add(complement);
          }
        }
      }
      
      Console.WriteLine(score); // Output the result for current test case
    }
  }
}


// https://github.com/VaHiX/codeForces/