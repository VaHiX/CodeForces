// Contest 2141, Problem A: Furniture Store
// URL: https://codeforces.com/contest/2141/problem/A

fun main() {
  val t = readln().toInt()
  repeat(t) {
    val n = readln().toInt()
    val prices = readln().split(" ").map { it.toInt() }
    val result = mutableListOf<Int>()
    var minPrice = Int.MAX_VALUE
    for (i in prices.indices) {
      if (prices[i] > minPrice) result.add(i + 1) else minPrice = prices[i]
    }
    println(result.size)
    if (result.isNotEmpty()) println(result.joinToString(" "))
  }
}
