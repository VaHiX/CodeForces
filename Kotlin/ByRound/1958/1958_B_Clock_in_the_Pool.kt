// Contest 1958, Problem B: Clock in the Pool
// URL: https://codeforces.com/contest/1958/problem/B

fun main() {
  val testCases = readLine()!!.toInt()

  repeat(testCases) {
    val (k, m) = readLine()!!.split(" ").map { it.toInt() }
    val waitTime = maxOf(0, 2 * k - m % (3 * k))
    println(waitTime)
  }
}
