// Contest 1346, Problem H: Game with Segments
// URL: https://codeforces.com/contest/1346/problem/H

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
  var (tt, n) = readInts()
  var lstart = IntArray(tt)
  var rstart = IntArray(tt)
  for (i in 0 until tt) {
    var (x, y) = readInts()
    lstart[i] = x
    rstart[i] = y
  }
  var l = ArrayList<Int>()
  var r = ArrayList<Int>()
  for (i in 0 until n) {
    var (x, y) = readInts()
    l.add(x)
    r.add(y)
  }
  var order = ArrayList<Int>()
  for (i in 0 until n) {
    order.add(i)
  }
  order.sortWith(compareBy({ l[it] + r[it] }, { l[it] }))
  val inf = 787788789
  fun getDistance(L: Int, R: Int): Int {
    var low = 0
    var high = n
    while (low < high) {
      var mid = (low + high) / 2
      if (
          l[order[mid]] + r[order[mid]] < L + R ||
              (l[order[mid]] + r[order[mid]] == L + R && l[order[mid]] < L)
      ) {
        low = mid + 1
      } else {
        high = mid
      }
    }
    if (low < n && l[order[low]] + r[order[low]] == L + R) {
      return l[order[low]] - L
    }
    return inf
  }
  var res = IntArray(tt) { -1 }
  for (qq in 0 until tt) {
    var L = lstart[qq]
    var R = rstart[qq]
    var a = getDistance(L, R - 2) + 1
    var b = getDistance(L, R)
    var c = getDistance(L + 2, R) + 1
    res[qq] = maxOf(minOf(a, b), minOf(b, c))
    if (res[qq] >= inf) {
      res[qq] = -1
    }
  }
  println(res.joinToString(" "))
}
