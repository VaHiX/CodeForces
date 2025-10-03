// Contest 1959, Problem B: Compare T-Shirt Sizes
// URL: https://codeforces.com/contest/1959/problem/B

fun main() {
  repeat(readLine()!!.toInt()) {
    val input = readLine()!!.split(" ")
    val first = input[0]
    val second = input[1]
    val fv = getSize(first)
    val sv = getSize(second)
    println(if (fv < sv) "<" else if (fv > sv) ">" else "=")
  }
}

fun getSize(string: String): Int {
  var value = 0
  if (string.contains('S')) {
    value -= 1
    value -= string.count { it == 'X' }
  } else if (string.contains('L')) {
    value += 1
    value += string.count { it == 'X' }
  }
  return value
}
