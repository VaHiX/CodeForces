// Problem: CF 1884 A - Simple Design
// https://codeforces.com/contest/1884/problem/A

// #####################################################################
// Problem: Simple Design
// Algorithm: Brute Force Search
// Time Complexity: O(d * log(x)) per test case, where d is the number of digits in x
// Space Complexity: O(1)
// #####################################################################

using System;
public class SimpleDesign {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split(); // Split input line into x and k
      int x = int.Parse(parts[0]); // Parse x
      byte k = byte.Parse(parts[1]); // Parse k
      int ans = x; // Start checking from x
      // Loop until we find a number whose digit sum is divisible by k
      while (SumDigit(ans) % k > 0)
        ans++; // Increment ans if current number is not k-beautiful
      Console.WriteLine(ans); // Output the result
    }
  }
  // Function to calculate digit sum of a number
  public static byte SumDigit(int n) {
    byte sum = 0; // Initialize sum to 0
    while (n > 0) {
      sum += Convert.ToByte(n % 10); // Add last digit to sum
      n /= 10; // Remove last digit from n
    }
    return sum; // Return the calculated sum
  }
}


// https://github.com/VaHiX/CodeForces/