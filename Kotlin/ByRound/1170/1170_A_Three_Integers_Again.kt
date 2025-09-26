// Contest 1170, Problem A: Three Integers Again
// URL: https://codeforces.com/contest/1170/problem/A

fun main() =
    repeat(readLine()!!.toInt()) {
      val (a, b) = readLine()!!.split(" ").map { it.toInt() }
      val x = minOf(a, b) - 1
      println("$x ${a - x} ${b - x}")
    }
