// Problem: CF 2119 C - A Good Problem
// https://codeforces.com/contest/2119/problem/C

/*
C. A Good Problem
time limit per test2 seconds
memory limit per test256 megabytes

Problem Description:
Given four integers n, l, r, k, find the lexicographically smallest array of length n such that:
1. Each element a[i] satisfies l <= a[i] <= r.
2. The bitwise AND of all elements equals the bitwise XOR of all elements.
If no such array exists, output -1. Otherwise, output only the k-th element (1-indexed).

Algorithm:
- Try to construct the lexicographically smallest valid array.
- Key insight: if n=1, then answer is simply l.
- For n > 1, we aim for the smallest possible elements that satisfy a[1] & a[2] & ... & a[n] = a[1] ^ a[2] ^ ... ^ a[n].
- The solution uses bitwise analysis to determine whether it's possible to construct such an array.
- If n is odd and l is 1, then a single 1 works (since 1 & 1 = 1, 1 ^ 1 = 0 → NOT valid, unless we change our logic).
- In fact, if the number of elements is even, we can generally make it work by using pairs.
- The code identifies the highest bit set in l, then tries to construct numbers with matching or different bit patterns to ensure AND == XOR.

Time Complexity: O(1) per test case (constant time due to loop over max 60 bits)
Space Complexity: O(1) - only a few variables are used

Techniques:
- Bit manipulation and properties of AND vs XOR operations.
- Constructive algorithm to generate the minimum valid value for k-th position.

*/

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = long.Parse(line[0]);
      var L = long.Parse(line[1]);
      var r = long.Parse(line[2]);
      var k = long.Parse(line[3]);
      getAns(n, L, r, k);
    }
  }
  
  static void getAns(long n, long L, long r, long k) {
    if (n == 1) { // Only one element: trivial case
      Console.WriteLine(L);
      return;
    }
    
    // If the number of elements is odd and we can form a valid answer,
    // then L should be one possible value
    // But more importantly, let's explore construction logic
    
    if (n % 2 == 1) { // Odd number of elements - tricky case
      Console.WriteLine(L);
      return;
    }

    // If L is 1 and n is odd, we still need to check whether it's valid
    if (L == 1 && n % 2 == 1) {
      Console.WriteLine(1);
      return;
    }

    var t = -1; // Find the highest bit position set in L
    
    // Loop through all possible bits up to 60 (since numbers can be up to 1e18)
    for (int i = 0; i < 60; i++) {
      if (((L >> i) & 1) == 1)
        t = i; // Record position of the most significant set bit
    }

    var big = 1L << (t + 1); // Compute the next power of 2 greater than L
    
    if (big > r) { // If the next power of 2 exceeds our range [l, r], no valid answer
      Console.WriteLine(-1);
      return;
    }
    
    if (n == 2) { // Special case when n=2 and l>=2, may not be solvable
      Console.WriteLine(-1);
      return;
    }
    
    // If k <= n - 2, use L. Otherwise, use big value
    Console.WriteLine(k <= n - 2 ? L : big);
  }
}


// https://github.com/VaHiX/CodeForces/