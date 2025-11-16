// Problem: CF 2036 B - Startup
// https://codeforces.com/contest/2036/problem/B

/*
 * Problem: B. Startup
 * Purpose: Maximize earnings by placing bottles on shelves such that each shelf holds only one brand,
 *          and we select top k bottles (where k is number of shelves) with highest costs per brand.
 * 
 * Algorithm:
 * 1. For each test case, group all bottles by their brand and accumulate the total cost per brand.
 * 2. Sort brands in descending order of their total cost.
 * 3. Select top 'n' brands (where n is number of shelves) and sum up their total costs.
 * 
 * Time Complexity: O(k log k + n), where k is number of bottles, n is number of shelves.
 * Space Complexity: O(k), for storing the brand-cost mapping.
 */

using System;
using System.Collections.Generic;
using System.Linq;

public class HelloWorld {
  static void program() {
    string[] str = Console.ReadLine().Split();
    int a = Convert.ToInt32(str[0]), b = Convert.ToInt32(str[1]); // a: shelves, b: bottles
    
    Dictionary<int, int> map = new Dictionary<int, int>(); // Map to store brand -> total cost
    
    for (int i = 0; i < b; ++i) {
      string[] input = Console.ReadLine().Split();
      int c = Convert.ToInt32(input[0]), d = Convert.ToInt32(input[1]);
      if (map.ContainsKey(c) == false) {
        map.Add(c, d); // If brand not seen before, add it
      } else {
        map[c] += d; // Otherwise, accumulate the cost
      }
    }
    
    int sum = 0, f = 0;
    // Sort brands by total cost in descending order and take top 'a' brands
    foreach (var pair in map.OrderBy(pair => pair.Value).Reverse()) {
      if (f++ < a) { // Take only up to 'a' brands (number of shelves)
        sum += pair.Value;
      }
    }
    
    Console.WriteLine(sum);
  }
  
  public static void Main() {
    int t = Convert.ToInt32(Console.ReadLine());
    while (t-- > 0) {
      program();
    }
  }
}


// https://github.com/VaHiX/codeForces/