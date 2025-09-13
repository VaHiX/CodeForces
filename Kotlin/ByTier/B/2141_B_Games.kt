// Contest 2141, Problem B: Games
// URL: https://codeforces.com/contest/2141/problem/B

fun main() {
  val t = readLine()!!.toInt()
  repeat(t) {
    val (n, m) = readLine()!!.split(" ").map { it.toInt() }
    val aList = readLine()!!.split(" ").map { it.toInt() }
    val bSet = readLine()!!.split(" ").map { it.toInt() }.toSet()

    val common = aList.count { it in bSet }
    val x = n - common
    val y = m - common

    println(if (x > y) 2 * y + 2 else 2 * x + 1)
  }
}
