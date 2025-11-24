// Problem: CF 2043 B - Digits
// https://codeforces.com/contest/2043/problem/B

/*
B. Digits
Algorithm: Determine which odd digits from 1 to 9 divide the number formed by repeating digit d exactly n! times.
Time Complexity: O(n) per test case, due to factorial computation (though n is up to 10^9, in practice limited by overflow and logic checks).
Space Complexity: O(1), since we only store a fixed-size list of digits (at most 5 elements).

Techniques:
- Logic-based pruning to determine divisibility without explicitly forming the number.
- Mathematical properties used for divisibility checks (e.g., divisibility by 3, 9, etc.).
*/

using System;
using System.Collections.Generic;
class Program {
  static List<int> DetermineDigits(long n, long d) {
    var ans = new List<int>();
    ans.Add(1); // All numbers are divisible by 1
    
    // If n >= 3 or d is divisible by 3, then the number is divisible by 3
    if (n >= 3 || d % 3 == 0) {
      ans.Add(3);
    }
    
    // If d is 5, the number ends in 5 and is divisible by 5
    if (d == 5) {
      ans.Add(5);
    }
    
    // If n >= 3 or (n == 2 && d == 7), then the number is divisible by 7
    if (n >= 3 || (n == 2 && d == 7)) {
      ans.Add(7);
    }
    
    // If n >= 6, the number is divisible by 9 due to properties of large factorials
    if (n >= 6) {
      ans.Add(9);
    } else {
      // Compute n! and check divisibility by 9 using factorial * d
      long factorial = 1;
      for (int i = 2; i <= n; i++) {
        factorial *= i;
      }
      if ((factorial * d) % 9 == 0) {
        ans.Add(9);
      }
    }
    
    return ans;
  }
  
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] inputs = Console.ReadLine().Split(' ');
      long n = long.Parse(inputs[0]);
      long d = long.Parse(inputs[1]);
      List<int> ans = DetermineDigits(n, d);
      Console.WriteLine(string.Join(" ", ans));
    }
  }
}


// https://github.com/VaHiX/codeForces/