// Contest 2087, Problem B: Showmatch
// URL: https://codeforces.com/contest/2087/problem/B

fun main() {
  repeat(readln().toInt()) {
    val n = readln().toInt()
    val a = readln().split(" ").map({ it.toInt() }).sorted()
    var flag = false
    for (i in 0..2 * (n - 1)) {
      if (flag == true) {
        break
      }
      if (i % 2 == 1) {
        if (kotlin.math.abs(a[i] - a[i - 1]) > kotlin.math.abs(a[i + 1] - a[i])) {
          flag = true
        }
      }
    }
    if (
        kotlin.math.abs(a[2 * n - 2] - a[2 * n - 3]) < kotlin.math.abs(a[2 * n - 2] - a[2 * n - 1])
    ) {
      flag = true
    }
    if (flag == true) {
      println("NO")
    } else {
      println("YES")
    }
  }
}
