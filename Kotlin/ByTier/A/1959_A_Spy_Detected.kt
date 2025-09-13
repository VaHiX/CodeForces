// Contest 1959, Problem A: Spy Detected!
// URL: https://codeforces.com/contest/1959/problem/A

fun main() {
  val t = readLine()!!.toInt()
  repeat(t) {
    val n = readLine()!!.toInt()
    val array = readLine()!!.split(" ").map(String::toInt)
    val distinctValue = array.groupBy { it }.filterValues { it.size == 1 }.keys.first()
    println(array.indexOf(distinctValue) + 1)
  }
}
