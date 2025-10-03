// Contest 2011, Problem B: Shuffle
// URL: https://codeforces.com/contest/2011/problem/B

fun main() =
    repeat(readln().toInt()) {
      val n = readln().toInt()
      println((listOf(1) + (n downTo 2)).joinToString(" "))
    }
