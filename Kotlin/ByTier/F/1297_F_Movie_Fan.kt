// Problem: CF 1297 F - Movie Fan
// https://codeforces.com/contest/1297/problem/F

import java.util.*
private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

/**
 * Problem: Movie Fan
 * 
 * Algorithm: Greedy with TreeSet for scheduling
 * 
 * Time Complexity: O(n log n) per test case due to sorting and TreeSet operations
 * Space Complexity: O(n) for storing movie data and TreeSet
 * 
 * Approach:
 * 1. Sort movies by start time (and by index as tie-breaker)
 * 2. For each movie, we schedule it as early as possible within its time range
 * 3. Use TreeSet to track when movies finish (to know when we can watch more)
 * 4. Process events in chronological order to determine optimal schedule
 * 5. Calculate maximum delay if not all can be watched in time
 */
fun main(args: Array<String>) {
  var t = readInt()
  while (t-- > 0) {
    var (n, m) = readInts()
    var a = IntArray(n + 1)
    var b = IntArray(n + 1)
    for (i in 0 until n) {
      var (x, y) = readInts()
      a[i] = x
      b[i] = y
    }
    a[n] = 2e9.toInt() // sentinel value
    b[n] = a[n]
    var c = Array<Pair<Int, Int>>(n + 1, { i -> Pair(a[i], i) })
    c.sortWith(compareBy({ it.first }, { it.second }))
    var ans = 0
    var s = TreeSet<Long>() // TreeSet to store (end_time << 32) + index
    var w = IntArray(n)
    var day = 0
    for (id in 0..n) {
      while (day < c[id].first && !s.isEmpty()) {
        // Process up to m movies per day
        for (tmp in 1..m) {
          if (s.isEmpty()) {
            break
          }
          var p = s.first()
          // Calculate delay as difference between current day and when movie ended
          ans = maxOf(ans, day - (p shr 32).toInt())
          w[(p and 1048575).toInt()] = day // Extract index and assign day
          s.remove(p)
        }
        ++day
      }
      day = c[id].first
      var i = c[id].second
      s.add(((b[i].toLong()) shl 32) + i) // Store end_time and index
    }
    println(ans)
    println(w.joinToString(" "))
  }
}


// https://github.com/VaHiX/CodeForces/