// Problem: CF 1488 G - Painting Numbers
// https://codeforces.com/contest/1488/problem/G

/*
Purpose: 
This code solves the problem of maximizing the cost of painting numbers from 1 to n,
where cost is defined as the number of pairs (x, y) such that y mod x = 0, y is red, and x is blue.
The algorithm computes for each possible number of red elements k (from 1 to n), 
the maximum possible cost by strategically choosing which numbers to paint red.

Approach:
1. For each number i from 1 to n, we precompute how many multiples of i exist in the range [1, n].
   This value is stored in ANS[i-1] (0-based indexing).
2. Then, for each i, we subtract (n/i - 1) from ANS[i-1] to adjust for the self-pairing (i mod i = 0).
3. The adjusted ANS array is then sorted in ascending order.
4. To compute the maximum cost for k red elements, we accumulate from largest to smallest values of ANS,
   effectively choosing the k largest contributions to maximize cost.
5. The result for each k is stored in ANSLIST and printed.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the ANS and ANSLIST arrays.

Algorithms/Techniques:
- Sieve-like preprocessing to count multiples
- Sorting and greedy selection for maximum cost calculation
*/

fun main() {
  val n = readLine()!!.toInt()
  var ANS = IntArray(n)
  for (i in 1..n) {
    // For each i, increment count for all multiples of i
    for (j in i + i..n step i) {
      ANS[j - 1] += 1
    }
    // Subtract self-pairing count (i mod i = 0)
    ANS[i - 1] -= n / i - 1
  }
  
  // Sort the adjusted counts in ascending order
  ANS.sort()
  
  val ANSLIST = IntArray(n)
  var k = 0
  // Greedily accumulate the maximum values to get max costs for k red elements
  for (i in 0..n - 1) {
    k += ANS[n - 1 - i]
    ANSLIST[i] = k
  }
  
  println(ANSLIST.joinToString(" "))
}


// https://github.com/VaHiX/CodeForces/