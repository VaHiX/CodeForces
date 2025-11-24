// Problem: CF 1431 B - Polycarp and the Language of Gods
// https://codeforces.com/contest/1431/problem/B

/*
 * Problem: B. Polycarp and the Language of Gods
 * 
 * Approach:
 * - The key insight is that we need to determine the minimum number of letters to underline
 *   such that there's no ambiguity in the string.
 * - In this language, 'w' can be confused with two 'v's, and 'v' can't be confused with anything else.
 * - We use a greedy approach where we process the string from left to right:
 *   - When we encounter a 'w', we must underline it (increment ans by 1), and reset parity to 0.
 *   - When we encounter a 'v', we check the parity:
 *     - If parity is 0, we must underline the current 'v' (increment ans by 1) and set parity to 1.
 *     - If parity is 1, we do not underline the 'v' (ans remains same) and set parity to 0.
 * 
 * Time Complexity: O(n), where n is the length of the string.
 * Space Complexity: O(1), only using a constant amount of extra space.
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
    var s = readLn()
    var ans = 0
    var parity = 0 // parity = 0 means we expect to see a 'w' next, or we are not in a 'v' pair
    for (c in s) {
      if (c == 'w') {
        ans += 1 // Must underline 'w' to avoid confusion with 'vv'
        parity = 0 // Reset expectation after encountering a 'w'
      } else {
        // c == 'v'
        ans += parity // If parity is 1, we should underline this 'v'
        parity = 1 - parity // Toggle parity (we alternated between expecting 'w' or not)
      }
    }
    println(ans)
  }
}


// https://github.com/VaHiX/CodeForces/