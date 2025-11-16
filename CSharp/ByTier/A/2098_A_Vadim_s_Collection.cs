// Problem: CF 2098 A - Vadim's Collection
// https://codeforces.com/contest/2098/problem/A

/*
 * Problem: Rearrange digits of a beautiful phone number to form the smallest possible beautiful phone number.
 * 
 * Algorithm:
 * - For each test case, we sort the digits in ascending order.
 * - Then, we greedily assign the largest available digit that satisfies the constraint for each position.
 *   Specifically, at position i (0-based), the digit must be at least (10 - i).
 * - This greedy approach ensures minimal lexicographical result under constraints.
 * 
 * Time Complexity: O(10 * log(10) + 10^2) = O(1) per test case since the input size is fixed to 10 digits.
 * Space Complexity: O(1) per test case as all arrays have fixed size (10 elements).
 */

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var s = Console.ReadLine().Trim(); // Read the phone number string
      getAns(s); // Process and print the result for current input
    }
  }

  static void getAns(string s) {
    var a = new int[10]; // Array to store individual digits from input string
    
    // Extract digits from string
    for (int i = 0; i < 10; i++)
      a[i] = s[i] - '0';
      
    Array.Sort(a); // Sort digits in ascending order to allow greedy selection
    
    var used = new bool[10]; // Boolean array to track which digits are already used
    var b = new int[10]; // Result array to build the final beautiful number
    
    // Greedily assign largest valid digit at each position
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (!used[j] && (a[j] >= 9 - i)) { // Check if digit is unused and meets requirement
          used[j] = true;
          b[i] = a[j];
          break;
        }
      }
    }
    
    Console.WriteLine(string.Join("", b)); // Print the resulting beautiful number
  }
}


// https://github.com/VaHiX/codeForces/