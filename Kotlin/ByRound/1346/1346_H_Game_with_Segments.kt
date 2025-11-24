// Problem: CF 1346 H - Game with Segments
// https://codeforces.com/contest/1346/problem/H

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
  var (tt, n) = readInts() // Read number of initial segments (tt) and terminal segments (n)
  var lstart = IntArray(tt)
  var rstart = IntArray(tt)
  for (i in 0 until tt) {
    var (x, y) = readInts()
    lstart[i] = x
    rstart[i] = y
  }
  var l = ArrayList<Int>()
  var r = ArrayList<Int>()
  for (i in 0 until n) {
    var (x, y) = readInts()
    l.add(x)
    r.add(y)
  }
  var order = ArrayList<Int>()
  for (i in 0 until n) {
    order.add(i)
  }
  // Sort terminal segments by sum of endpoints, then by left endpoint
  order.sortWith(compareBy({ l[it] + r[it] }, { l[it] }))
  val inf = 787788789 // A large value to represent infinity
  
  // Function to compute the minimum distance from a segment [L, R] to any terminal segment
  fun getDistance(L: Int, R: Int): Int {
    var low = 0
    var high = n
    while (low < high) {
      var mid = (low + high) / 2
      // Check if the current segment [l[order[mid]], r[order[mid]]] is "smaller" than [L, R] in a specific way:
      // If sum is less OR if sum is equal but left endpoint is smaller
      if (
          l[order[mid]] + r[order[mid]] < L + R ||
              (l[order[mid]] + r[order[mid]] == L + R && l[order[mid]] < L)
      ) {
        low = mid + 1
      } else {
        high = mid
      }
    }
    // If a matching terminal segment is found, return the difference in left endpoints
    if (low < n && l[order[low]] + r[order[low]] == L + R) {
      return l[order[low]] - L
    }
    return inf // No matching segment found
  }
  
  // Initialize result array
  var res = IntArray(tt) { -1 }
  for (qq in 0 until tt) {
    var L = lstart[qq] // Current initial segment's left endpoint
    var R = rstart[qq] // Current initial segment's right endpoint
    
    // Compute three distances based on variations in the segment
    var a = getDistance(L, R - 2) + 1 // Shrink from right by 2
    var b = getDistance(L, R)         // No shrink
    var c = getDistance(L + 2, R) + 1 // Shrink from left by 2
    
    // Find the minimum possible number of moves to reach terminal (or degenerate)
    res[qq] = maxOf(minOf(a, b), minOf(b, c))
    if (res[qq] >= inf) {
      res[qq] = -1 // Bob wins (Alice cannot win)
    }
  }
  println(res.joinToString(" "))
}


// https://github.com/VaHiX/CodeForces/