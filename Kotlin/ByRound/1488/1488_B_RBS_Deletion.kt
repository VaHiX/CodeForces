// Contest 1488, Problem B: RBS Deletion
// URL: https://codeforces.com/contest/1488/problem/B

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  var st = StringTokenizer(br.readLine())
  val t = st.nextToken().toInt()
  repeat(t) {
    st = StringTokenizer(br.readLine())
    val n = st.nextToken().toLong()
    var ans = n / 2
    var ans2 = st.nextToken().toLong()

    val s = br.readLine()
    var open = 0L
    var close = 0L

    for (ch in s) {
      if (ch == '(') open++ else close++
      if (open == close) {
        ans2++
      }
    }

    println(minOf(ans, ans2))
  }
}
