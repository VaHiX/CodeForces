// Problem: CF 2143 B - Discounts
// https://codeforces.com/contest/2143/problem/B

/*
 * Problem: B. Discounts
 * 
 * Approach:
 * - Sort the product prices in descending order to prioritize higher-cost items for discounts.
 * - Sort the voucher sizes in ascending order to use smaller vouchers first and maximize the benefit of each discount.
 * - For each voucher, apply it to the next 'size' products, paying for all but the cheapest one (which becomes free).
 * - If there are remaining products after using all vouchers, add their full cost to the total.
 * 
 * Time Complexity: O(n log n + k log k), where n is the number of products and k is the number of vouchers.
 *   - Sorting products: O(n log n)
 *   - Sorting vouchers: O(k log k)
 *   - Processing each product once: O(n)
 *   - Processing each voucher once: O(k)
 * 
 * Space Complexity: O(n + k), for storing the prices and voucher sizes.
 */

using System;
using System.Linq;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var nk = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int n = nk[0], k = nk[1];
      var a = Console.ReadLine().Split().Select(long.Parse).ToArray(); // Product prices
      var b = Console.ReadLine().Split().Select(int.Parse).ToArray(); // Voucher sizes
      Array.Sort(a); // Sort prices in ascending order
      Array.Reverse(a); // Reverse to descending order (highest price first)
      Array.Sort(b); // Sort voucher sizes in ascending order
      long total = 0; // Total cost
      int idx = 0; // Index for product array
      for (int i = 0; i < k && idx < n; i++) {
        int size = b[i]; // Current voucher size
        // Process 'size - 1' products (pay for all but the cheapest, which is free)
        for (int j = 0; j < size - 1 && idx < n; j++) {
          total += a[idx++]; // Add cost of product (excluding the cheapest one)
        }
        // Skip the cheapest product (it's free)
        if (idx < n)
          idx++;
      }
      // Add cost of remaining products (not covered by vouchers)
      while (idx < n) {
        total += a[idx++];
      }
      Console.WriteLine(total);
    }
  }
}


// https://github.com/VaHiX/CodeForces/