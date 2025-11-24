// Problem: CF 1431 G - Number Deletion Game
// https://codeforces.com/contest/1431/problem/G

import java.util.*
private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun <T> printColl(a: Collection<T>) {
  for (x in a) print("$x ")
  println()
}

/*
 * Purpose: Solve the Number Deletion Game problem where Alice and Bob play optimally.
 * Algorithm: Dynamic Programming with prefix sums.
 * Time Complexity: O(n^2 * k), where n is the size of the array and k is the number of turns.
 * Space Complexity: O(n * k), for the DP table.
 *
 * The game proceeds in k turns, each turn Alice chooses an element (not the maximum),
 * Bob chooses an element greater than Alice's, then both are removed and (Bob's - Alice's) is added to the score.
 * Both play optimally: Alice maximizes score, Bob minimizes score.
 * Strategy: Sort the array and use DP where dp[nn][kk] represents the maximum score possible
 * using the first nn elements in kk turns.
 * For each state, we try all valid numbers of pairs to take (from 1 to min(kk, nn/2)).
 * We compute prefix sums to efficiently calculate score differences.
 */
fun main() {
  val (n, k) = readInts()
  val A = readInts().toIntArray()
  A.sort()
  val dp = Array<IntArray>(n + 2) { IntArray(k + 2) { 0 } }
  val pref = IntArray(n + 1) { 0 }
  for (i in 1..n) {
    pref[i] = pref[i - 1] + A[i - 1]
  }
  for (nn in 1..n) {
    for (kk in 0..k) {
      dp[nn][kk] = dp[nn - 1][kk] // Base case: don't take any pair from this prefix
      for (j in 1..minOf(kk, nn / 2)) {
        // Try taking j pairs, which consumes 2*j elements
        // From nn elements and taking j pairs, we get (2*j) elements consumed
        // The score is calculated as the sum of differences between pairs
        // pref[nn] - 2 * pref[nn - j] + pref[nn - 2 * j] computes the optimal score for j pairs
        dp[nn][kk] =
            maxOf(
                dp[nn][kk],
                dp[nn - 2 * j][kk - j] + pref[nn] - 2 * pref[nn - j] + pref[nn - 2 * j],
            )
      }
    }
  }
  println(dp[n][k])
}


// https://github.com/VaHiX/CodeForces/