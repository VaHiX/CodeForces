// Problem: CF 1976 A - Verify Password
// https://codeforces.com/contest/1976/problem/A

/*
 * Purpose: Verify if a given password is strong based on specific criteria:
 *          - Contains only lowercase letters and digits
 *          - All digits appear after all letters (no mixing)
 *          - Digits are in non-decreasing order
 *          - Letters are in non-decreasing order
 * 
 * Algorithms/Techniques:
 *          - Split password into digits and letters using LINQ
 *          - Use SequenceEqual with OrderBy to check if digits and letters are sorted
 *          - Use SkipWhile and Any to verify that no digit appears after a letter
 * 
 * Time Complexity: O(n log n) due to sorting operations (OrderBy) in the worst case,
 *                  where n is the length of the password.
 * Space Complexity: O(n) for storing the separated digits and letters strings.
 */
using System;
using System.Linq;
class Program {
  static void Main() {
    long t = long.Parse(Console.ReadLine());
    for (long i = 0; i < t; i++) {
      long n = long.Parse(Console.ReadLine());
      string password = Console.ReadLine();
      Console.WriteLine(IsStrongPassword(n, password) ? "YES" : "NO");
    }
  }
  static bool IsStrongPassword(long n, string password) {
    // Extract all digits from the password
    string digits = new string(password.Where(char.IsDigit).ToArray());
    // Extract all letters from the password
    string letters = new string(password.Where(char.IsLetter).ToArray());
    // Check if digits are in non-decreasing order
    bool digitsSorted = digits.SequenceEqual(digits.OrderBy(c => c));
    // Check if letters are in non-decreasing order
    bool lettersSorted = letters.SequenceEqual(letters.OrderBy(c => c));
    // Check that after any letter, there are no more digits
    bool allDigitsBeforeLetters =
        !password.SkipWhile(char.IsDigit).Any(char.IsDigit);
    // Return true only if all conditions are satisfied
    return digitsSorted && lettersSorted && allDigitsBeforeLetters;
  }
}


// https://github.com/VaHiX/CodeForces/