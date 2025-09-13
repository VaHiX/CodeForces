// Contest 1958, Problem E: Yet Another Permutation Constructive
// URL: https://codeforces.com/contest/1958/problem/E

fun main() {
  val a = intArrayOf(1, 2, 3, 5, 9, 17, 33, 65)
  repeat(readln().toInt()) {
    val (n, k) = readln().split(' ').map(String::toInt)
    println(
        if (k < 8 && (n - 1).shr(k - 1) > 0) {
          IntArray(n) {
                (it.countTrailingZeroBits() + 1).let { i ->
                  if (it in 1 until a[k]) n - a[k - i] - it.shr(i) else n - it
                }
              }
              .joinToString(" ")
        } else -1
    )
  }
}
