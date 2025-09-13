// Contest 2141, Problem E: Perfect Cut
// URL: https://codeforces.com/contest/2141/problem/E

import java.io.BufferedReader
import java.io.InputStreamReader

const val MOD: Long = 998244353L

fun modPow2(exp: Int): Long {
  var e = exp
  var base = 2L
  var res = 1L
  while (e > 0) {
    if ((e and 1) == 1) res = (res * base) % MOD
    base = (base * base) % MOD
    e = e ushr 1
  }
  return res
}

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val t = br.readLine().trim().toInt()
  val out = StringBuilder()
  repeat(t) {
    val s = br.readLine().trim()
    val n = s.length
    val q = s.count { it == '?' }
    val pow = modPow2(q)

    var patternPossible = true
    if (s[0] == '1') patternPossible = false
    for (i in 1 until n) if (s[i] == '0') patternPossible = false

    var ans = (pow - if (patternPossible) 1L else 0L) % MOD
    if (ans < 0) ans += MOD
    out.append(ans).append('\n')
  }
  print(out.toString())
}
