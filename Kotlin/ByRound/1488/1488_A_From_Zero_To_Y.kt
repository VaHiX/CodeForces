// Contest 1488, Problem A: From Zero To Y
// URL: https://codeforces.com/contest/1488/problem/A

fun main() =
    repeat(readLine()!!.toInt()) {
      val (x, y) = readLine()!!.split(" ").map { it.toInt() }
      println((y / x).toString().sumOf { it - '0' } + y % x)
    }
