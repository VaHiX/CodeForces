// Problem: CF 1431 D - Used Markers
// https://codeforces.com/contest/1431/problem/D

/**
 * Problem: D. Used Markers
 * 
 * Algorithm: Greedy approach with sorting.
 * 
 * Approach:
 * - We want to maximize the number of used markers.
 * - Each lecturer has an "acceptance value" a[i], meaning they won't use a marker that was used 
 *   in at least a[i] previous lectures.
 * - We can only replace a marker when asked by a lecturer.
 * - Strategy:
 *   - Sort lecturers by their acceptance values ascending.
 *   - Use a two-pointer technique to assign lectures to minimize marker usage.
 *   - Assign higher acceptance value lecturers earlier (to allow more reuse of markers).
 * 
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(n) for storing the input and intermediate arrays.
 */

fun answer(v: ArrayList<Int>) {
  println(v.joinToString(" "))
}

fun solve(a: List<Int>) {
  val n = a.size
  var p = ArrayList<Int>() // Store indices of lecturers
  for (i in 0 until n) p.add(i)
  // Sort by acceptance values
  p.sortWith(compareBy({ a[it] }))
  
  var q = ArrayList<Int>() // Result order
  var i = 0
  var j = n
  while (i < j) {
    // Calculate how many lectures can be scheduled before this one
    var k = a[p[i]] - (if (i != 0) 1 else 0)
    // Assign lectures from the end (higher acceptance values) to reuse markers
    while (k-- != 0 && --j > i) q.add(1 + p[j])
    // Add the current lecturer
    q.add(1 + p[i++])
  }
  answer(q)
}

fun test_case() {
  val n = readLine()!!.toInt()
  val a = readLine()!!.split(" ").map(String::toInt)
  solve(a)
}

fun main() {
  var t = readLine()!!.toInt()
  repeat(t) { test_case() }
}


// https://github.com/VaHiX/CodeForces/