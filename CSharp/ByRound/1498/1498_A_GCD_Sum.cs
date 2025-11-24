// Problem: CF 1498 A - GCD Sum
// https://codeforces.com/contest/1498/problem/A

﻿/*
Problem: Find the smallest integer >= n such that gcdSum(x) > 1.
Algorithm: For each number starting from n, compute sum of digits and check if gcd of number and digit sum > 1.
            - If digit sum is 1, increment number.
            - If number is divisible by digit sum, return number.
            - Otherwise, check for divisors of digit sum up to sqrt(digit_sum).
              If any divisor divides the number or if digit_sum/d divisor divides the number (and digit_sum/d != 1),
              return number.
            - Else increment number and continue.
Time Complexity: O(sqrt(log(n)) * log(n)) per test case, where log(n) is the number of digits.
Space Complexity: O(1) - only using a few variables.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace ConsoleApplication1 {
class A1498_GCD_Sum {
  public static void Main() {
    int test = int.Parse(Console.ReadLine());
    while (test > 0) {
      test--;
      decimal input = decimal.Parse(Console.ReadLine());
      while (true) {
        int inputsum = 0;
        decimal tempInput = input;
        while (tempInput > 0) {
          inputsum += (int)(tempInput % 10); // Extract last digit and add to sum
          tempInput /= 10;
          tempInput = decimal.Truncate(tempInput); // Remove decimal part
        }
        if (inputsum == 1) { // Special case: if digit sum is 1, next number will have digit sum > 1
          input++;
          continue;
        }
        if (input % inputsum == 0) { // If number is divisible by digit sum, gcd > 1
          Console.WriteLine(input);
          break;
        } else {
          decimal squreRoot = (decimal)Math.Sqrt(inputsum);
          squreRoot = decimal.Truncate(squreRoot);
          squreRoot += 1;
          int otherside = 0;
          bool resultInput = false;
          // Check divisors of digit sum up to sqrt(inputsum)
          for (int i = 2; i <= squreRoot; i++) {
            if (inputsum % i == 0 &&
                (input % i == 0 || // If i divides input
                 ((inputsum / i != 1) && (input % (inputsum / i) == 0)))) { // If inputsum/i > 1 and divides input
              resultInput = true;
              break;
            }
          }
          if (resultInput) { // If we found such divisor
            Console.WriteLine(input);
            break;
          }
        }
        input++; // Increment input to test next number
      }
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/