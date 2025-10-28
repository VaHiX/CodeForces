// Problem: CF 2008 A - Sakurako's Exam
// https://codeforces.com/contest/2008/problem/A

/*
 * Problem: A. Sakurako's Exam
 * Purpose: Determine if it's possible to assign '+' or '-' signs to an array of 'a' ones and 'b' twos such that their sum equals 0.
 * 
 * Algorithm:
 * - For the sum to be zero, we need to split the elements into two groups where one group sums to S and the other also sums to S,
 *   i.e., total_sum = 2*S => S = total_sum / 2
 * - Total sum of all elements is a*1 + b*2 = a + 2*b
 * - The target sum for each group must be (a + 2*b) / 2
 * - Since all elements are positive, the target sum must be non-negative and even if possible.
 * 
 * Key Observations:
 * - If total_sum is odd, it's impossible to split into two equal parts → return "NO"
 * - If we have no ones (a == 0), then all elements are twos.
 *   - If b is odd, sum = 2*b is even, but we can't split even numbers of twos into two groups with equal sums unless we allow negative ones.
 *      Actually: if a=0 and b is odd, we can make an odd total sum → impossible
 * - We must be able to distribute '1's and '2's optimally.
 * 
 * Mathematical Approach:
 * - Let x be number of 1s with '+', y be number of 1s with '-'
 * - Let u be number of 2s with '+', v be number of 2s with '-'
 * - Then:
 *   x + y = a
 *   u + v = b
 *   x - y = (u - v)
 *   This means: (x - y) = (u - v) = S - sum_of_ones = S - (x+y)*(1) = S - a = (u-v)*2 = 2*(u-v)
 *   So, we aim for sum of positives = sum of negatives.
 * - So, required check:
 *   - Total = a + 2*b is even
 *   - The target sum S = (a + 2*b) / 2 should be achievable using selected combinations of 1s and 2s such that we get balance.
 *   
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read input line and split into two parts
      var a = int.Parse(line[0]); 
      var b = int.Parse(line[1]);
      getAns(a, b); // Call function to compute answer for current test case
    }
  }
  
  static void getAns(int a, int b) {
    var total = a + 2 * b; // Calculate total sum of all elements
    
    if (total % 2 == 1) { // If total is odd, impossible to split into two equal groups
      Console.WriteLine("NO");
      return;
    }
    
    var target = total / 2; // Target sum each group should have
    
    // If there are no ones and the number of twos is odd,
    // we can never form a valid combination that sums to zero.
    if (a == 0 && b % 2 == 1) {
      Console.WriteLine("NO");
      return;
    }
    
    // Check if it's possible to use some 1s and 2s to reach target
    // Let x be number of ones we take with positive sign,
    // y be number of ones taken with negative sign, so x + y = a
    // And let u be number of twos taken with positive sign, v with negative sign, so u + v = b
    // Then: x - y = (u - v)*2 => (x - y) must be even
    // So x + y = a and x - y = delta => 2*x = a + delta => x = (a + delta)/2
    // Also, target = x + u = (a + delta)/2 + u => u = target - (a + delta)/2
    
    Console.WriteLine("YES");
  }
}


// https://github.com/VaHiX/codeForces/