// Contest 2011, Problem C: Split the Expression
// URL: https://codeforces.com/contest/2011/problem/C

import java.util.*

fun main() {
  repeat(readln().toInt()) {
    val str = readln()
    var cur = 0L
    val n = str.length
    val v = mutableListOf<Long>()
    for (i in 0 until n) {
      if (str[i] == '+') {
        v.add(cur)
        cur = 0
      } else {
        cur = cur * 10 + (str[i] - '0')
      }
    }
    v.add(cur)
    var ans = v[0] + v[v.size - 1]
    for (i in 1 until v.size - 1) {
      val cand1 = v[i] / 10 + v[i] % 10
      var kat = 1L
      while (kat * 10 <= v[i]) {
        kat *= 10
      }
      val cand2 = v[i] / kat + v[i] % kat
      ans += maxOf(cand1, cand2)
    }
    println(ans)
  }
}
