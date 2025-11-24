// Problem: CF 2044 F - Easy Demon Problem
// https://codeforces.com/contest/2044/problem/F

/*
F. Easy Demon Problem
Time Complexity: O(n + m + Q * sqrt(max(|x|))) where Q is number of queries and max(|x|) is the maximum absolute value among all queries.
Space Complexity: O(n + m)

Algorithms/Techniques:
- Preprocessing sums of arrays a and b
- Compute set of possible values from removing one element from a and b (referred to as s1 - ai and s2 - bi)
- For each query x, check if there exists a valid pair (j, x/j) such that j is in the precomputed set for a, and x/j is in the set for b
- Use square root optimization when checking divisors

The key insight:
If we remove row r and column c, then the new beauty of the grid becomes:
original_beauty - a[r] * m - b[c] * n + a[r] * b[c]
Let S1 = sum(a), S2 = sum(b)
New beauty = S1 * m + n * S2 - a[r] * m - b[c] * n + a[r] * b[c]
          = S1 * m + n * S2 - m * (S1 - a[r]) - n * (S2 - b[c]) + a[r] * b[c]
          = S1 * m + n * S2 - m * S1 + m * a[r] - n * S2 + n * b[c] + a[r] * b[c]
          = m * a[r] + n * b[c] + a[r] * b[c]
          = a[r] * (m + b[c]) + n * b[c]

But this can be rederived as: 
original_beauty - a[r] * m - b[c] * n + a[r] * b[c] = S1 * m + n * S2 - m * a[r] - n * b[c] + a[r] * b[c]
Let's denote the change to beauty as x where:
x = (S1 * m + n * S2) - (m * a[r] + n * b[c]) + a[r] * b[c]
If we simplify this expression by letting X = sum(a)*m + n*sum(b), then:
new_beauty = X - m*a[r] - n*b[c] + a[r]*b[c]

We can compute all possible contributions (S1 - a[i]) and (S2 - b[j]) for each i, j in arrays a and b. 
These represent the sums of elements excluding one element from array a or b respectively.
We then iterate over all divisors d of x to see if there exist two numbers d and x/d such that:
d is in set of (s1 - ai) and x/d is in set of (s2 - bi)

*/

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    const long M = 1000000007; // Modulo value, not used here but defined
    const int N = 100010;       // Not directly used in the code, likely for safety or other use

    string[] input = Console.ReadLine().Split();
    long n = long.Parse(input[0]);     // Length of array a
    long m = long.Parse(input[1]);     // Length of array b
    long q = long.Parse(input[2]);     // Number of queries

    long[] a = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);   // Input array a
    long[] b = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);   // Input array b

    long s1 = a.Sum();   // Sum of all elements in array a
    long s2 = b.Sum();   // Sum of all elements in array b

    HashSet<long> sa = new HashSet<long>();  // Set containing (s1 - a[i]) for all i
    HashSet<long> sb = new HashSet<long>();  // Set containing (s2 - b[i]) for all i

    foreach (long ai in a)
      sa.Add(s1 - ai);   // Build set of sums excluding each element of a

    foreach (long bi in b)
      sb.Add(s2 - bi);   // Build set of sums excluding each element of b

    for (int i = 0; i < q; i++) {
      long x = long.Parse(Console.ReadLine());   // Read query value x
      bool krish = false;     // Flag indicating if solution exists for current query
      
      for (long j = 1; j * j <= Math.Abs(x); j++) {   // Check divisors up to sqrt(|x|)
        if (Math.Abs(x) % j == 0) {
          long x1 = j;
          long x2 = x / j;

          // Check four conditions with positive and negative combinations
          if ((sa.Contains(x1) && sb.Contains(x2)) ||
              (sa.Contains(x2) && sb.Contains(x1)) ||
              (sa.Contains(-x1) && sb.Contains(-x2)) ||
              (sa.Contains(-x2) && sb.Contains(-x1))) {
            krish = true; // If any condition matches, we've found a valid pair
            break;
          }
        }
      }

      if (krish)
        Console.WriteLine("YES");   // Output result
      else
        Console.WriteLine("NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/