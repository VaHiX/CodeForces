// Contest 1346, Problem B: Boot Camp
// URL: https://codeforces.com/contest/1346/problem/B

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

fun calc(t: Int, k1: Int, k2: Int): Int {
  if (k2 >= k1 + k1) {
    return t * k1
  }
  return (t / 2) * k2 + (t % 2) * k1
}

fun main(args: Array<String>) {
  var tt = readInt()
  for (qq in 0 until tt) {
    var (n, k1, k2) = readInts()
    var s = readLn()
    var ans = 0
    var t = 0
    for (c in s) {
      if (c == '0') {
        ans += calc(t, k1, k2)
        t = 0
      } else {
        t += 1
      }
    }
    ans += calc(t, k1, k2)
    println(ans)
  }
}
