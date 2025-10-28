// Problem: CF 1866 A - Ambitious Kid
// https://codeforces.com/contest/1866/problem/A

/*
 * Problem: Ambitious Kid
 * Purpose: Find the minimum number of operations to make the product of all elements in the array equal to zero.
 * Algorithm: 
 *   - If any element is already 0, no operations are needed.
 *   - Otherwise, we need to make at least one element 0.
 *   - The minimum number of operations is the minimum absolute value among all elements,
 *     because that's the smallest number of operations to reduce any element to 0.
 * Time Complexity: O(n) - Single pass through the array to find the minimum absolute value.
 * Space Complexity: O(1) - Only using a constant amount of extra space.
 */
using System;
using System.Linq;
namespace Practi__selling_1 {
internal class Program {
  static void Main(string[] args) {
    int n = Convert.ToInt32(Console.ReadLine()); // Read the number of elements
    string[] str = Console.ReadLine().Split(); // Read the array elements as strings
    int[] a = new int[n]; // Initialize the integer array
    for (int i = 0; i < str.Length; i++) {
      a[i] = Convert.ToInt32(str[i]); // Convert string elements to integers
    }
    int mn = 0; // Variable to store the minimum absolute value
    for (int i = 0; i < a.Length; i++) {
      if (a[i] < 0) {
        a[i] = -a[i]; // Convert negative numbers to positive
      }
    }
    Console.WriteLine(Math.Abs(a.Min())); // Output the minimum absolute value
  }
}
}


// https://github.com/VaHiX/CodeForces/