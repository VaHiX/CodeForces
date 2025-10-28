// Problem: CF 1346 E - Magic Tricks
// https://codeforces.com/contest/1346/problem/E

/*
 * Problem: Magic Tricks
 * 
 * Algorithm: Breadth-First Search (BFS) on a graph where nodes are positions
 *            and edges represent possible swaps. We simulate the effect of
 *            swaps on the position of the special ball. Each swap can be
 *            either faked or performed. We model this as a graph traversal where
 *            we calculate minimum fakes needed for the special ball to reach
 *            each position.
 * 
 * Time Complexity: O(n + m), where n is the number of balls and m is the number of swaps.
 * Space Complexity: O(n), for storing the array of minimum fakes for each position.
 * 
 * Approach:
 * 1. Initialize an array a where a[i] represents the minimum number of swaps to be faked
 *    so that the special ball reaches position i (0-indexed).
 * 2. Set a[k-1] = 0 since the special ball starts at position k.
 * 3. For each swap (x, y), update the minimum fake counts for both positions:
 *    - a[x] = min(a[x], a[y] + 1) // Fake the swap if needed
 *    - a[y] = min(a[y], a[x] + 1) // Fake the swap if needed
 * 4. If a position remains unreachable (inf), set it to -1.
 * 5. Output the results.
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
  var (n, m, k) = readInts()
  val inf = 787788
  var a = IntArray(n)
  for (i in 0 until n) {
    a[i] = inf // Initialize all positions with infinity (unreachable)
  }
  a[k - 1] = 0 // Special ball starts at position k (convert to 0-indexed)
  for (i in 0 until m) {
    var (x, y) = readInts()
    x -= 1 // Convert to 0-indexed
    y -= 1 // Convert to 0-indexed
    var ax = minOf(a[x] + 1, a[y]) // Minimum swaps to reach x, considering we might fake the swap
    var ay = minOf(a[y] + 1, a[x]) // Minimum swaps to reach y, considering we might fake the swap
    a[x] = ax
    a[y] = ay
  }
  for (i in 0 until n) {
    if (a[i] == inf) {
      a[i] = -1 // Mark unreachable positions as -1
    }
  }
  println(a.joinToString(" "))
}


// https://github.com/VaHiX/CodeForces/