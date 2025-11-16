// Problem: CF 1777 C - Quiz Master
// https://codeforces.com/contest/1777/problem/C

/*
 * Problem: Quiz Master
 * 
 * Algorithms/Techniques:
 * - Prime factorization using Sieve of Eratosthenes
 * - Sliding window technique to find minimum range
 * 
 * Time Complexity: O(n * sqrt(max_a) + n * log(n) + m * sqrt(max_a))
 * Space Complexity: O(n + m + sqrt(max_a))
 * 
 * The solution uses prime factorization to determine which topics each student is proficient in,
 * then applies a sliding window approach to find the minimum difference between smartness levels
 * of students in a team that covers all topics.
 */

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static List<int> primes = new List<int>(); // Store prime numbers up to sqrt(100000)
  public static void genPrimes() {
    primes.Add(2);
    for (int i = 3; i < 320; i++) { // Generate primes up to 319 (sqrt(100000))
      primes.Add(i);
    }
  }
  public static Dictionary<int, List<int>> factors =
      new Dictionary<int, List<int>>(); // Memoization of factors for each number
  public static List<int> GetFactors(int v) {
    if (!factors.ContainsKey(v)) { // If factors not computed yet
      List<int> f = new List<int>();
      f.Add(1); // 1 is always a factor
      if (v > 1)
        f.Add(v); // Number itself is always a factor
      var u = Math.Sqrt(v + 1); // Compute square root once
      for (int i = 0; i < primes.Count && primes[i] < u; i++) { // Iterate through primes up to sqrt(v)
        if (v % primes[i] == 0) { // If primes[i] divides v
          f.AddRange(GetFactors(primes[i])); // Add factors of the prime
          f.AddRange(GetFactors(v / primes[i])); // Add factors of v divided by prime
        }
      }
      factors.Add(v, f.Distinct().ToList()); // Store computed factors
    }
    return factors[v];
  }
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> output = new List<string>(); // Store outputs for all test cases
    genPrimes(); // Precompute primes up to sqrt(100000)
    GetFactors(99002); // Precompute factors for a large number (just to initialize memoization)
    for (int z = 0; z < fyt; z++) {
      var a = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList(); // Read n and m
      var b = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToArray(); // Read smartness values
      long o = 100001; // Initialize result with large value
      int n = a[0]; // Number of students
      int m = a[1]; // Number of topics
      Array.Sort(b); // Sort smartness values for sliding window
      int t = m; // Target number of topics
      int[] keyDivisors = new int[m + 1]; // Track how many students are proficient in each topic
      int l = 0; // Left pointer of sliding window
      int r = 0; // Right pointer of sliding window
      int c = 0; // Count of topics covered by current window
      GetFactors(b[0]).ForEach(i => { // For the first student, add his factors to keyDivisors
        if (i <= m) { // Only consider factors within topic range
          if (keyDivisors[i] == 0) // If this topic becomes covered by this student
            c++;
          keyDivisors[i]++; // Increment coverage count for this topic
        }
      });
      while (r < n) { // Expand window until all topics are covered
        if (c >= t) { // If all topics are covered in current window
          if (r == l) { // Special case: single student in window
            o = 0; // Difference is 0
            break;
          } else {
            if (o > b[r] - b[l]) // Update minimum difference
              o = b[r] - b[l];
            GetFactors(b[l]).ForEach(i => { // Remove leftmost student from window
              if (i <= m) {
                keyDivisors[i]--; // Decrement coverage
                if (keyDivisors[i] == 0) // If topic no longer covered
                  c--; // Decrement topic counter
              }
            });
            l++; // Move left pointer
          }
        } else { // If not all topics covered yet, expand window by moving right pointer
          r++;
          if (r < n) {
            GetFactors(b[r]).ForEach(i => { // Add new rightmost student to window
              if (i <= m) {
                if (keyDivisors[i] == 0) // If this topic becomes covered now
                  c++;
                keyDivisors[i]++; // Increment coverage count for this topic
              }
            });
          }
        }
      }
      if (o == 100001) // If no valid team was found
        o = -1; // Output -1
      output.Add(o.ToString()); // Add result to output list
    }
    string on = string.Join("\n", output); // Join output with newlines
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/