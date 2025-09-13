// Contest 1488, Problem E: Palindromic Doubles
// URL: https://codeforces.com/contest/1488/problem/E

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
    var n = readInt()
    var a = readInts()
    var occ = IntArray(n + 1) { -1 }
    var b = ArrayList<Int>()
    for (i in 0 until n) {
      if (occ[a[i]] != -1) {
        b.add(2 * occ[a[i]] + 1)
        if (i > occ[a[i]] + 1) {
          b.add(2 * occ[a[i]])
        }
      }
      occ[a[i]] = i
    }

    var u = ArrayList<Int>()
    for (x in b.reversed()) {
      var low = 0
      var high = u.size
      while (low < high) {
        var mid = (low + high) shr 1
        if (x > u[mid]) {
          low = mid + 1
        } else {
          high = mid
        }
      }
      if (low == u.size) {
        u.add(x)
      } else {
        u[low] = x
      }
    }
    println(u.size + 1)
  }
}
