// Contest 1346, Problem E: Magic Tricks
// URL: https://codeforces.com/contest/1346/problem/E

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
    a[i] = inf
  }
  a[k - 1] = 0
  for (i in 0 until m) {
    var (x, y) = readInts()
    x -= 1
    y -= 1
    var ax = minOf(a[x] + 1, a[y])
    var ay = minOf(a[y] + 1, a[x])
    a[x] = ax
    a[y] = ay
  }
  for (i in 0 until n) {
    if (a[i] == inf) {
      a[i] = -1
    }
  }
  println(a.joinToString(" "))
}
