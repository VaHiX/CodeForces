// Contest 1431, Problem A: Selling Hamburgers
// URL: https://codeforces.com/contest/1431/problem/A

import java.util.*

fun solve() {
  val n = readLine()!!.toInt()
  val a = LongArray(n)

  val input = readLine()!!.split(" ").map { it.toLong() }
  for (i in 0 until n) {
    a[i] = input[i]
  }

  a.sort()
  var res = 0L

  for (i in 0 until n) {
    res = maxOf(a[i] * (n - i), res)
  }
  println(res)
}

fun main() {
  val t = readLine()!!.toInt()
  repeat(t) { solve() }
}
