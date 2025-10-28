// Problem: CF 1488 E - Palindromic Doubles
// https://codeforces.com/contest/1488/problem/E

/*
 * Problem: E. Palindromic Doubles
 * 
 * Algorithm: 
 *   - Use a greedy approach with dynamic programming principles.
 *   - For each element in the array, if it has appeared before:
 *     * Add indices of the previous occurrence and current occurrence to a list 'b'.
 *     * This helps identify potential palindromic pairs.
 *   - Reverse the list 'b' and apply binary search to find the longest increasing subsequence (LIS).
 *     * This gives the maximum number of non-overlapping palindromic pairs.
 *   - The final answer is the length of LIS + 1 (the center element).
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */
import java.lang.AssertionError
private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }
private fun myAssert(x: Boolean) {
  if (!x) {
    throw AssertionError()
  }
}
fun main(args: Array<String>) {
  var tt = readInt()
  for (qq in 0 until tt) {
    var n = readInt()
    var a = readInts()
    var occ = IntArray(n + 1) { -1 } // Stores the last occurrence index of each number
    var b = ArrayList<Int>() // Stores indices for forming palindromic subsequences
    for (i in 0 until n) {
      if (occ[a[i]] != -1) {
        // If the number has appeared before, add indices for potential palindromic pair
        b.add(2 * occ[a[i]] + 1) // Index of previous occurrence
        if (i > occ[a[i]] + 1) {
          b.add(2 * occ[a[i]]) // Special case for non-consecutive elements
        }
      }
      occ[a[i]] = i // Update the last occurrence index
    }
    var u = ArrayList<Int>() // For storing LIS elements
    for (x in b.reversed()) { // Process in reverse order
      var low = 0
      var high = u.size
      while (low < high) {
        var mid = (low + high) shr 1 // Binary search for the correct position
        if (x > u[mid]) {
          low = mid + 1
        } else {
          high = mid
        }
      }
      if (low == u.size) {
        u.add(x) // Add to LIS if larger than all elements
      } else {
        u[low] = x // Replace the element at position 'low'
      }
    }
    println(u.size + 1) // Result is LIS size + 1 (as we can include one central element)
  }
}


// https://github.com/VaHiX/CodeForces/