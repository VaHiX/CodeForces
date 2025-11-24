// Problem: CF 1431 I - Cyclic Shifts
// https://codeforces.com/contest/1431/problem/I

import java.util.*
/*
 * Problem: Cyclic Shifts
 * 
 * Approach:
 * 1. Preprocess the matrix to build a sorted order of rows based on column values.
 * 2. For each query, use binary search to find the position of the required character
 *    in the current window of rows for each column.
 * 3. If a character can't be found in the current window, increment the operation count
 *    and reset the window to full matrix.
 * 
 * Time Complexity: O(n * m * log(n) + q * m * log(n))
 * Space Complexity: O(n * m)
 * 
 * Algorithms/Techniques:
 * - Preprocessing with sorting by columns
 * - Binary search for character positioning
 * - Greedy approach with window adjustment
 */

fun main() =
    with(Scanner(System.`in`)) {
      val n = nextInt()
      val m = nextInt()
      val q = nextInt()
      val c = Array(n) { next().toCharArray() }
      val ord = Array(m + 1) { IntArray(n) { it } } // ord[j][i] = row index of i-th element in column j
      val b = Array(26) { mutableListOf<Int>() } // buckets for each character
      val sb = StringBuilder()
      
      // Preprocessing step: build sorted order of rows for each column
      for (j in m - 1 downTo 0) {
        for (x in 0..25) b[x].clear() // clear buckets
        for (i in 0..n - 1) {
          val k = ord[j + 1][i] // get row index of element from next column
          b[c[k][j] - 'a'].add(k) // bucket sort by character
        }
        var pos = 0
        for (x in 0..25) {
          b[x].forEach { k ->
            ord[j][pos] = k // assign sorted positions
            pos++
          }
        }
      }
      
      // Process each query
      repeat(q) {
        val s = next()
        var ans = 0
        var left = 0 // left boundary of column range
        var up = 0 // up boundary of row range
        var down = n // down boundary of row range
        var j = 0 // current column index
        
        // For each column in the query string
        while (j < m) {
          // Find lower bound: first element >= s[j]
          var lb = 0
          var lo = up - 1
          var hi = down
          while (hi - lo > 1) {
            val mid = (hi + lo) / 2
            val tmp = c[ord[left][mid]][j]
            if (tmp < s[j]) lo = mid else hi = mid
          }
          lb = hi
          
          // Find upper bound: first element > s[j]
          var ub = 0
          lo = up - 1
          hi = down
          while (hi - lo > 1) {
            val mid = (hi + lo) / 2
            val tmp = c[ord[left][mid]][j]
            if (tmp <= s[j]) lo = mid else hi = mid
          }
          ub = hi
          
          if (lb == ub) {
            // Character not found in current window
            if (left == j) {
              // Cannot find character even at the beginning
              ans = -1
              break
            } else {
              // Need another operation
              ans++
              left = j
              up = 0
              down = n
            }
          } else {
            // Character found, advance to next column
            j++
            up = lb
            down = ub
          }
        }
        sb.appendLine(ans)
      }
      println(sb)
    }


// https://github.com/VaHiX/CodeForces/