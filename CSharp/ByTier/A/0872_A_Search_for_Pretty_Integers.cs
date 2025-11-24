// Problem: CF 872 A - Search for Pretty Integers
// https://codeforces.com/contest/872/problem/A

using System.Linq;
using System;
public class hello {
  static void Main() {
    Console.ReadLine(); // Read and discard n and m
    string[] line = Console.ReadLine().Trim().Split(' '); // Read first list of digits
    var a = Array.ConvertAll(line, int.Parse); // Convert to int array
    line = Console.ReadLine().Trim().Split(' '); // Read second list of digits
    var b = Array.ConvertAll(line, int.Parse); // Convert to int array
    getAns(a, b); // Find and print the smallest pretty integer
  }
  static void getAns(int[] a, int[] b) {
    Array.Sort(a); // Sort the first array to allow early termination in loop
    foreach (var x in a) // Go through each digit in sorted first array
      if (b.Contains(x)) { // If this digit is also in second array
        Console.WriteLine(x); // Output it as the answer (smallest possible)
        return; // Exit early
      }
    var bmin = b.Min(); // Find minimum digit in second array
    if (a[0] < bmin) // If the smallest digit in first array is smaller than smallest in second
      Console.WriteLine("{0}{1}", a[0], bmin); // Concatenate them
    else
      Console.WriteLine("{0}{1}", bmin, a[0]); // Else concatenate second's min with first's
  }
}
/*
Purpose: Find the smallest positive integer that contains at least one digit from each of two given lists of digits.

Algorithms/Techniques:
- Sorting and early termination for checking intersection
- Greedy approach to concatenate smallest digits from both lists

Time Complexity: O(n log n + m + n) where n and m are lengths of the lists, dominated by sorting.
Space Complexity: O(n + m) for storing the input arrays.

*/

// https://github.com/VaHiX/CodeForces/