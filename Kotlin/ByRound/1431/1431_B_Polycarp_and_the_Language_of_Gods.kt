// Contest 1431, Problem B: Polycarp and the Language of Gods
// URL: https://codeforces.com/contest/1431/problem/B

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
    var parity = 0
    for (c in s) {
      if (c == 'w') {
        ans += 1
        parity = 0
      } else {
        ans += parity
        parity = 1 - parity
      }
    }
    println(ans)
  }
}
