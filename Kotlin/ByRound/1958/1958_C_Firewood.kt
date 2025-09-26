// Contest 1958, Problem C: Firewood
// URL: https://codeforces.com/contest/1958/problem/C

fun main() {
  repeat(readln().toInt()) {
    val (n, k) = readln().split(' ').map { it.toLong() }
    println(n - k.countTrailingZeroBits())
  }
}
