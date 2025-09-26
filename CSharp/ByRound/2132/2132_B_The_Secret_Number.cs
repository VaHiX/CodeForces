// Problem: CF 2132 B - The Secret Number
// https://codeforces.com/contest/2132/problem/B

/*
B. The Secret Number
Algorithm: For a given number n = x + y where y is x with some trailing zeros appended,
we need to find all valid values of x.

Approach:
- Iterate through possible lengths of x (from 1 to 17 digits since n <= 10^18).
- For each length d, consider the divisor (10^d + 1) and check if n is divisible by it.
- If divisible, then x = n / (10^d + 1), provided x > 0.
- Store all such valid x in a hash set to avoid duplicates, then sort before returning.

Time Complexity: O(17 * log(n)) ≈ O(log(n))
Space Complexity: O(k), where k is the number of valid x values (at most ~17 since d up to 17).

*/

using System;
using System.Collections.Generic;
using System.Linq;

namespace CodeForces.Problems.Round2132.B {
    public static class SecretNumberSolver {
        public static List<long> FindSecretNumbers(long n) {
            var result = new HashSet<long>();
            long powerOfTen = 10; // Start with 10^1
            
            for (int d = 1; d <= 17; d++) { // Try all possible digit lengths of x
                long divisor = powerOfTen + 1; // divisor = 10^d + 1
                
                if (n >= divisor && n % divisor == 0) { // Check if n is divisible by divisor and not too small
                    long x = n / divisor; // Compute candidate x
                    
                    if (x > 0) { // Only consider positive x
                        result.Add(x);
                    }
                }
                
                powerOfTen *= 10; // Move to next power of 10 for next iteration
            }
            
            var sortedResult = result.ToList();
            sortedResult.Sort();
            return sortedResult;
        }
        
        public static void Solve() {
            long n = long.Parse(Console.ReadLine());
            var secretNumbers = FindSecretNumbers(n);
            Console.WriteLine(secretNumbers.Count);
            
            if (secretNumbers.Count > 0) {
                Console.WriteLine(string.Join(" ", secretNumbers));
            }
        }
        
        public static void Main() {
            int testCases = int.Parse(Console.ReadLine());
            for (int i = 0; i < testCases; i++) {
                Solve();
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/