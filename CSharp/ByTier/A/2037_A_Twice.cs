// Problem: CF 2037 A - Twice
// https://codeforces.com/contest/2037/problem/A

/*
 * Problem: Maximum Score by Pairing Equal Elements
 *
 * Description:
 * Given an array of integers, we want to find the maximum number of pairs (i,j) such that a[i] == a[j]
 * and i < j. Each element can only be used once in a pair.
 *
 * Algorithm:
 * - Count the frequency of each element in the array.
 * - For each element with frequency f, we can form f / 2 pairs.
 * - Sum all such pairs to get the result.
 *
 * Time Complexity: O(n), where n is the length of the array.
 * Space Complexity: O(n), due to the frequency counter array.
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) { // Process each test case
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert string array to int array
      getAns(n, a); // Compute and print answer for current test case
    }
  }
  
  static void getAns(int n, int[] a) {
    var c = new int[n + 1]; // Frequency counter array for values 1 to n
    foreach (var x in a)
      c[x]++; // Count frequency of each element
    
    var ans = 0;
    foreach (var x in c)
      ans += x / 2; // Add number of pairs possible for each element
    
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/