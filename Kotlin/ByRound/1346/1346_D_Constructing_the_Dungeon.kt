// Contest 1346, Problem D: Constructing the Dungeon
// URL: https://codeforces.com/contest/1346/problem/D

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.StringTokenizer

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val pw = PrintWriter(System.out)
  var st = StringTokenizer("")

  fun nextToken(): String {
    while (!st.hasMoreTokens()) {
      val line = br.readLine() ?: return ""
      st = StringTokenizer(line)
    }
    return st.nextToken()
  }
  fun nextInt() = nextToken().toInt()
  fun nextLong() = nextToken().toLong()

  val t = nextInt()
  repeat(t) {
    val n = nextInt()
    val m = nextInt()
    val u = IntArray(m)
    val v = IntArray(m)
    val w = LongArray(m)
    val a = LongArray(n + 1)

    for (i in 0 until m) {
      u[i] = nextInt()
      v[i] = nextInt()
      w[i] = nextLong()
      a[u[i]] = maxOf(a[u[i]], w[i])
      a[v[i]] = maxOf(a[v[i]], w[i])
    }

    var ok = true
    for (i in 0 until m) {
      if (minOf(a[u[i]], a[v[i]]) != w[i]) {
        ok = false
        break
      }
    }

    if (!ok) {
      pw.println("No")
    } else {
      pw.println("Yes")
      for (i in 1..n) {
        pw.print(a[i])
        pw.print(if (i == n) "\n" else " ")
      }
    }
  }
  pw.flush()
}
