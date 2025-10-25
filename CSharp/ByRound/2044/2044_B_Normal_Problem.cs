// Problem: CF 2044 B - Normal Problem
// https://codeforces.com/contest/2044/problem/B

/*
 * Problem: ReverseView Transformation
 * Description:
 *   Given a string 'a' consisting only of characters 'p', 'q', and 'w',
 *   transform it to string 'b' such that:
 *   - If a character is 'p', it becomes 'q' in the reversed position.
 *   - If a character is 'q', it becomes 'p' in the reversed position.
 *   - If a character is 'w', it becomes 'w' in the reversed position.
 * 
 * Algorithm:
 *   - Traverse the input string from left to right.
 *   - For each character, place the transformed version at the mirrored index
 *     in the result array.
 * 
 * Time Complexity: O(n), where n is the length of the input string.
 * Space Complexity: O(n), for storing the output string of size n.
 */

using System;
class Program {
  static string ReverseView(string a) {
    char[] b = new char[a.Length]; // Initialize result array with same length as input
    for (int i = 0; i < a.Length; i++) { // Iterate through each character in input
      if (a[i] == 'p')
        b[a.Length - 1 - i] = 'q'; // Transform 'p' to 'q' at reverse index
      else if (a[i] == 'q')
        b[a.Length - 1 - i] = 'p'; // Transform 'q' to 'p' at reverse index
      else
        b[a.Length - 1 - i] = 'w'; // Keep 'w' as 'w' at reverse index
    }
    return new string(b); // Convert char array back to string
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    for (int i = 0; i < t; i++) { // Process each test case
      string a = Console.ReadLine().Trim(); // Read input string
      Console.WriteLine(ReverseView(a)); // Output transformed string
    }
  }
}


// https://github.com/VaHiX/codeForces/