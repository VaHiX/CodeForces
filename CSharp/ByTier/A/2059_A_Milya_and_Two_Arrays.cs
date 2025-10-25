// Problem: CF 2059 A - Milya and Two Arrays
// https://codeforces.com/contest/2059/problem/A

/*
 * Problem: Milya and Two Arrays
 * 
 * Purpose:
 *   Determine whether it's possible to rearrange array 'a' such that the resulting array 'c'
 *   (where c[i] = a[i] + b[i]) contains at least 3 distinct elements.
 * 
 * Approach:
 *   - Convert both arrays into sets to count unique elements.
 *   - If either array has more than 2 unique elements, then we can always rearrange 'a' to produce at least 3 distinct sums.
 *   - If both arrays have exactly 2 unique elements, we must check all possible pairings of the two elements.
 *   - For two-element sets, we enumerate all 4 combinations of summing elements from both sets and see if at least 3 distinct sums are possible.
 * 
 * Time Complexity: O(n)
 *   - Converting input arrays to sets takes O(n) time.
 *   - The logic for handling 2-element sets is constant time (O(1)).
 *   - Total time per test case is linear with respect to input size.
 * 
 * Space Complexity: O(n)
 *   - Storing the unique elements in hash sets requires up to O(n) space.
 *   - Additional variables are constant in space.
 */

using System;
using System.Collections.Generic;
public class MilyaAndTwoArrays {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine()); // Read array length (n)
      string[] parts = Console.ReadLine().Split(); // Read elements of array a
      HashSet<int> a = InputToSet(parts); // Convert a to a set to know unique elements
      parts = Console.ReadLine().Split(); // Read elements of array b
      HashSet<int> b = InputToSet(parts); // Convert b to a set to know unique elements
      
      // If either set has more than 2 elements, we can definitely get at least 3 distinct sums
      bool ans = a.Count > 2 || b.Count > 2;
      
      // If both sets have exactly 2 elements, we need to check all pairings manually
      if (!ans && a.Count == 2 && b.Count == 2) {
        int[] a2 = new int[2]; // Create array to hold elements of set a
        int[] b2 = new int[2]; // Create array to hold elements of set b
        a.CopyTo(a2, 0); // Copy elements from set a to array
        b.CopyTo(b2, 0); // Copy elements from set b to array
        
        HashSet<int> c = new HashSet<int>(); // Store possible sums
        // Compute all 4 possible sums
        c.Add(a2[0] + b2[0]);
        c.Add(a2[0] + b2[1]);
        c.Add(a2[1] + b2[0]);
        c.Add(a2[1] + b2[1]);
        
        // If there are more than 2 distinct sums, it's possible to get 3 or more
        ans = c.Count > 2;
      }
      Console.WriteLine(ans ? "YES" : "NO"); // Output result
    }
  }
  
  private static HashSet<int> InputToSet(string[] parts) {
    HashSet<int> set = new HashSet<int>(); // Create a set to store unique elements
    for (byte i = 0; i < parts.Length; i++)
      set.Add(int.Parse(parts[i])); // Add each parsed element to the set
    return set; // Return the set of unique elements
  }
}


// https://github.com/VaHiX/CodeForces/