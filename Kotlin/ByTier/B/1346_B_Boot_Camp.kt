// Problem: CF 1346 B - Boot Camp
// https://codeforces.com/contest/1346/problem/B

/*
 * Problem: Maximum number of lectures during a boot camp with constraints on daily and consecutive lecture limits.
 * 
 * Algorithm:
 * - Split the sequence into segments of non-excursion days (where s[i] == '1').
 * - For each segment, compute the maximum lectures that can be scheduled.
 * - Use a greedy approach:
 *   - If k2 >= 2*k1, we can fill each day with k1 lectures (as there's no constraint from consecutive days).
 *   - Otherwise, alternate between k1 and k2 to maximize the number of lectures, taking into account the odd/even length of the segment.
 * 
 * Time Complexity: O(n) - single pass through the string
 * Space Complexity: O(1) - only using a few variables
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

/**
 * Calculates maximum lectures for a segment of t consecutive non-excursion days
 * @param t number of days in segment
 * @param k1 max lectures per day
 * @param k2 max lectures for any consecutive two days
 * @return maximum lectures possible for this segment
 */
fun calc(t: Int, k1: Int, k2: Int): Int {
  // If k2 is large enough, we can schedule k1 lectures per day
  if (k2 >= k1 + k1) {
    return t * k1
  }
  // Otherwise, alternate days to maximize within constraints
  // For even-length segments: (t/2) pairs, each pair contributes k2
  // For odd-length segments: (t/2) pairs contribute k2 + one last day with k1
  return (t / 2) * k2 + (t % 2) * k1
}

fun main(args: Array<String>) {
  var tt = readInt()
  for (qq in 0 until tt) {
    var (n, k1, k2) = readInts()
    var s = readLn()
    var ans = 0
    var t = 0 // length of current non-excursion segment
    for (c in s) {
      if (c == '0') {
        // End of a non-excursion segment
        ans += calc(t, k1, k2)
        t = 0 // reset segment length
      } else {
        t += 1 // extend current segment
      }
    }
    // Handle the final segment
    ans += calc(t, k1, k2)
    println(ans)
  }
}


// https://github.com/VaHiX/CodeForces/