// Contest 1571, Problem C: Rhyme
// URL: https://codeforces.com/contest/1571/problem/C

import java.io.BufferedReader
import java.io.InputStreamReader
import java.lang.StringBuilder
import java.util.StringTokenizer
import kotlin.math.max
import kotlin.math.min

private const val INF = 200_005

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val out = StringBuilder()

  val t = br.readLine().trim().toInt()
  repeat(t) {
    val n = br.readLine().trim().toInt()

    var kMin = 0
    var kMax = INF

    repeat(n) {
      val st = StringTokenizer(br.readLine())
      val s = st.nextToken()
      val tStr = st.nextToken()
      val r = st.nextToken().toInt()

      var i = s.length - 1
      var j = tStr.length - 1
      var L = 0
      while (i >= 0 && j >= 0 && s[i] == tStr[j]) {
        ++L
        --i
        --j
      }

      if (r == 1) {

        kMax = min(kMax, L)
      } else {

        kMin = max(kMin, L + 1)
      }
    }

    if (kMin > kMax) {
      out.append("0\n")
    } else {
      out.append("${kMax - kMin + 1}\n")
      for (k in kMin..kMax) {
        out.append(k).append(' ')
      }
      out.append('\n')
    }
  }

  print(out.toString())
}
