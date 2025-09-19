// Contest 1431, Problem G: Number Deletion Game
// URL: https://codeforces.com/contest/1431/problem/G

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
      dp[nn][kk] = dp[nn - 1][kk]
      for (j in 1..minOf(kk, nn / 2)) {
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
