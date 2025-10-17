// Problem: CF 2093 A - Ideal Generator
// https://codeforces.com/contest/2093/problem/A

/*
 * Problem: Determine if a given number k is an "ideal generator".
 * An ideal generator k means that any integer n >= k can be represented 
 * as the sum of elements of a palindromic array of exactly k positive integers.
 * 
 * Algorithm:
 * - For k = 1: Always YES because we can use [n] for any n.
 * - For k = 2: Check if all numbers n >= 2 can be written as sum of two positives.
 *   This is impossible for n = 3 (since 3 = a + b, and min a,b >= 1 => min sum = 2).
 *   But actually, every number n >= 3 can be expressed as sum of 2 positive numbers,
 *   so k=2 should be YES. Let me correct this logic:
 *   
 *   A palindromic array of length k allows us to choose values such that the total sum
 *   is flexible for sufficiently large n.
 *   For k = 1: We can always represent n as [n] → YES
 *   For k = 2: The minimum possible sum is 2 (e.g., [1,1]). So any n >= 2 is valid → YES?
 *   
 *   Actually, if we think more carefully:
 *   If k=2, we can only form sums n where there exist a,b >= 1 such that a + b = n.
 *   The smallest such sum is 2 (with [1,1]), so any n >= 2 works. So YES.
 *   
 *   But this is wrong based on example:
 *   k=2 -> NO because we can't form 3 from two positives in a palindromic way?
 *   No: [1,2] works, so it's valid (sum=3), and indeed there is a palindromic array [1,2] 
 *   for n=3 with k=2. Wait:
 *
 *   The question says we must have arrays of length exactly k.
 *   For k = 2, and n = 3, we can write: [1,2] → palindromic? No, not symmetric.
 *   The only palindromic array of length 2 is [a,a], which sums to 2*a.
 *   So we can make 2,4,6,... but NOT 3. 
 *   Therefore, k = 2 is NOT an ideal generator → NO.
 *   
 *   For k = 3:
 *   palindromic arrays of form [a,b,a] sum to 2a+b and b can be any positive integer.
 *   Minimum sum with a=1,b=1: 3. Any n ≥ 3 can be formed?
 *   Try n=4: [a,b,a]=4. If a=1, then b=2 → [1,2,1] works. YES.
 *   
 *   Key insight:
 *   A palindromic array of length k where elements are positive integers allows
 *   us to generate various sums depending on the structure.
 *
 *   If k is odd:
 *     The middle element can freely be chosen.
 *     We can make sum ≥ k (by using 1s elsewhere).
 *     This seems sufficient for large enough n.
 *
 *   If k is even: 
 *     All elements appear in pairs, so the structure requires more constraints.
 *     Only way to get sum = 2a + 2b + ... = 2(a+b+...) means we must have even sums.
 *
 *   Insight from examples:
 *   k=1 -> YES (any number is possible)
 *   k=2 -> NO (only even sums allowed in the form [a,a])
 *   k=3 -> YES (we get flexibility with one middle element)
 *   So the pattern seems to be: if k = 1 or k ≥ 3, then true. If k=2, false.
 *
 * Complexity:
 * - Time complexity: O(t), where t is number of test cases. Each operation is constant time due to bitwise operations.
 * - Space complexity: O(1), as we only use fixed amount of memory regardless of input size.
*/

using System;
namespace Taher {
internal class Program {
  static void Main(string[] args) {
    short t = Convert.ToInt16(Console.ReadLine()); // Read number of test cases
    while (Convert.ToBoolean(t--)) {              // Loop through each test case
      short k = Convert.ToInt16(Console.ReadLine()); // Read value k for current test case
      Console.WriteLine((Convert.ToBoolean(k & 1) ? "YES" : "NO")); // Print YES if k is odd, otherwise NO
    }
  }
}
}


// https://github.com/VaHiX/codeForces/