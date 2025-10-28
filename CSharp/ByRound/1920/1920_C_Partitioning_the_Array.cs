// Problem: CF 1920 C - Partitioning the Array
// https://codeforces.com/contest/1920/problem/C

/*
 * Problem: Partitioning the Array
 * 
 * Purpose: For each divisor k of n, we check if there exists a modulus m >= 2 such that
 *          when all elements in the array are replaced by their remainder mod m,
 *          all the k-length subarrays become identical.
 * 
 * Algorithm:
 * 1. For each divisor k of n, we group the elements of the array based on their index modulo k.
 *    This creates k groups, each representing a potential subarray pattern.
 * 2. For each group, we compute the GCD of the differences between consecutive elements.
 *    If this GCD is not 1, it indicates that there exists a common modulus m >= 2 that
 *    makes all elements in the group equivalent mod m.
 * 3. We check for all such k and sum up how many of them satisfy the condition.
 * 
 * Time Complexity: O(n * sqrt(n) * log(n)) where n is the size of the array.
 *   - Finding divisors of n takes O(sqrt(n))
 *   - For each divisor k, sorting and GCD computation takes O(n * log(n)) in worst case
 *  
 * Space Complexity: O(n) for storing the groups and intermediate lists.
 */

using System;
using System.Collections.Generic;
class Program {
  static List<int>[] mp; // Global array to store groups based on index mod k
  
  // Calculate GCD of two numbers using Euclidean algorithm
  static int GCD(int a, int b) {
    while (b != 0) {
      int temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }
  
  // Find all divisors of a number n and store in divs list
  static void PrintDivisors(int n, List<int> divs) {
    for (int i = 1; i <= Math.Sqrt(n); i++) {
      if (n % i == 0) {
        if (n / i == i) {
          divs.Add(i);    // Add the square root only once
        } else {
          divs.Add(i);    // Add both divisors
          divs.Add(n / i);
        }
      }
    }
  }
  
  // Main solution logic
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    int[] arr = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
    List<int> divs = new List<int>();
    divs.Clear();
    PrintDivisors(n, divs);  // Get all divisors of n
    int ans = 1;             // Start with 1 because k=n always gives a point (n subarrays of size 1)
    
    foreach (int div in divs) {
      if (div == n) {
        continue;   // Skip k=n since it's always valid
      }
      
      mp = new List<int>[div];  // Initialize lists for each group
      for (int j = 0; j < div; j++) {
        mp[j] = new List<int>();
      }
      
      // Distribute elements into their respective groups
      for (int j = 1; j <= n; j++) {
        mp[j % div].Add(arr[j - 1]); // Groups are 0 to div-1
      }
      
      int hue = 0;  // Resultant GCD among groups
      
      // Iterate through all groups to determine if a common modulus m exists
      foreach (List<int> list in mp) {
        list.Sort();  // Sort elements to calculate differences
        int pp = 0;   // GCD of differences in this group
        
        for (int i = 1; i < list.Count; i++) {
          pp = GCD(pp, list[i] - list[i - 1]);
        }
        
        hue = GCD(hue, pp);  // Combine across groups
      }
      
      if (hue != 1) {
        ans++;   // Increment if there's a valid m >= 2
      }
    }
    
    Console.WriteLine(ans);
  }
  
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/CodeForces/