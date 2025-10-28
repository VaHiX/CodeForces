// Problem: CF 2051 E - Best Price
// https://codeforces.com/contest/2051/problem/E

/*
 * Problem: Best Price
 * 
 * Approach:
 * This problem uses a sweep line algorithm with event processing.
 * For each customer, we define two events:
 *   1. When price crosses 'a[i]' (customer starts buying with positive review)
 *   2. When price crosses 'b[i]' (customer stops buying with negative review)
 * 
 * We process these events in sorted order of price to simulate the effect of changing price
 * on number of buyers and negative reviews.
 * 
 * Key variables:
 *   - pos: number of customers who will buy with positive review
 *   - neg: number of customers who will buy with negative review
 *   - buyers: total number of buyers
 *   - maxRev: maximum revenue achieved so far
 *   - lastP: previous price point
 *   - maxPrice: upper bound for prices to consider
 * 
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n)
 */
using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  private static (long pos, long neg, long buyers, long maxRev, long lastP,
                  long maxPrice) Initialize(long n, long mx) {
    long pos = n;
    long neg = 0;
    long buyers = pos + neg;
    long maxRev = 0;
    long lastP = 1;
    long maxPrice = mx + 2;
    return (pos, neg, buyers, maxRev, lastP, maxPrice);
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var i = Console.ReadLine().Split().Select(long.Parse).ToArray();
      long n = i[0], k = i[1];
      var a = Console.ReadLine().Split().Select(long.Parse).ToList();
      var b = Console.ReadLine().Split().Select(long.Parse).ToList();
      var events = new List<(long P, long Dp, long Dn)>();
      long mx = 0;
      foreach (var x in a)
        mx = Math.Max(mx, x);
      foreach (var x in b)
        mx = Math.Max(mx, x);
      for (int j = 0; j < n; j++) {
        // Add event when price goes from below a[i] to above a[i]: customer starts buying with positive review
        events.Add((a[j] + 1, -1, 1));
        // Add event when price goes from below b[i] to above b[i]: customer stops buying (negative review)
        events.Add((b[j] + 1, 0, -1));
      }
      events.Sort((x, y) => x.P.CompareTo(y.P)); // Sort events by price
      var (pos, neg, buyers, maxRev, lastP, maxPrice) = Initialize(n, mx);
      int idx = 0;
      // Initial check for valid state
      if (neg <= k)
        maxRev = Math.Max(maxRev, lastP * buyers);
      while (idx < events.Count) {
        long p = events[idx].P;
        if (p > maxPrice)
          break;
        // Potentially update max revenue if current price leads to valid state
        maxRev = (lastP < p && neg <= k && buyers > 0)
                     ? Math.Max(maxRev, (p - 1) * buyers)
                     : maxRev;
        // Process all events at current price point
        while (idx < events.Count && events[idx].P == p) {
          pos += events[idx].Dp;
          neg += events[idx].Dn;
          idx++;
        }
        buyers = pos + neg;
        lastP = p;
      }
      // Final check at maximum possible price
      maxRev = (lastP <= maxPrice && neg <= k && buyers > 0)
                   ? Math.Max(maxRev, (maxPrice - 1) * buyers)
                   : maxRev;
      Console.WriteLine(maxRev);
    }
  }
}


// https://github.com/VaHiX/CodeForces/