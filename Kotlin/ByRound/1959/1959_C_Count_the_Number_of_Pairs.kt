// Contest 1959, Problem C: Count the Number of Pairs
// URL: https://codeforces.com/contest/1959/problem/C

fun main() {
  repeat(readln().toInt()) { run() }
}

fun run() {
  var (n, k) = readln().split(" ").map(String::toInt)
  val s = readln()

  val up = IntArray('z' - 'a' + 1)
  val lo = IntArray('z' - 'a' + 1)

  for (ch in s) {
    if (ch in 'a'..'z') {
      ++lo[ch - 'a']
    }
    if (ch in 'A'..'Z') {
      ++up[ch - 'A']
    }
  }

  var res = 0
  for (i in up.indices) {
    val cur = minOf(up[i], lo[i])
    res += cur
    up[i] -= cur
    lo[i] -= cur

    val can = maxOf(up[i], lo[i]) / 2
    val tk = minOf(can, k)
    res += tk
    k -= tk
  }
  println(res)
}
