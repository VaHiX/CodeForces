// Contest 2087, Problem A: Password Generator
// URL: https://codeforces.com/contest/2087/problem/A

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val t = br.readLine().toInt()

  repeat(t) {
    val st = StringTokenizer(br.readLine())
    val a = st.nextToken().toInt()
    val b = st.nextToken().toInt()
    val c = st.nextToken().toInt()

    for (i in 0 until a) {
      print(i)
    }

    for (i in 1..b) {
      print((64 + i).toChar())
    }

    for (i in 1..c) {
      print((96 + i).toChar())
    }

    println()
  }
}
