// Contest 2141, Problem D: Avoid Minimums
// URL: https://codeforces.com/contest/2141/problem/D

import java.io.BufferedInputStream

private class F {
  private val i = BufferedInputStream(System.`in`)

  fun ni(): Int {
    var c = i.read()
    while (c <= 32) c = i.read()
    var s = 1
    if (c == 45) {
      s = -1
      c = i.read()
    }
    var r = 0
    while (c > 32) {
      r = r * 10 + (c - 48)
      c = i.read()
    }
    return r * s
  }

  fun nl(): Long {
    var c = i.read()
    while (c <= 32) c = i.read()
    var s = 1L
    if (c == 45) {
      s = -1
      c = i.read()
    }
    var r = 0L
    while (c > 32) {
      r = r * 10 + (c - 48)
      c = i.read()
    }
    return r * s
  }
}

fun main() {
  val f = F()
  val t = f.ni()
  val o = StringBuilder()
  repeat(t) {
    val n = f.ni()
    val k = f.nl()
    val a = LongArray(n)
    var s = 0L
    var mn = Long.MAX_VALUE
    var mx = Long.MIN_VALUE
    for (i in 0 until n) {
      val v = f.nl()
      a[i] = v
      s += v
      if (v < mn) mn = v
      if (v > mx) mx = v
    }
    val T = (k + s) / n
    if (T < mx) {
      o.append("-1\n")
      return@repeat
    }
    if (T == mn) {
      o.append("0\n")
      return@repeat
    }
    var c = 0
    for (v in a) if (v == mn) c++
    val g = s - mn * c
    val cg = n - c
    val ans = cg.toLong() * T - g + (c - 1).toLong() * (T - mn - 1)
    o.append(ans).append('\n')
  }
  print(o.toString())
}
