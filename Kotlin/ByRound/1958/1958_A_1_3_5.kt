// Contest 1958, Problem A: 1-3-5
// URL: https://codeforces.com/contest/1958/problem/A

fun main() =
    repeat(readln().toInt()) {
      val s = readln().toInt()
      println(if ((s < 8) && (s != 5)) s % 3 else 0)
    }
