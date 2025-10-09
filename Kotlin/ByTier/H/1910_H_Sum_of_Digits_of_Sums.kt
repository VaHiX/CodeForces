// Contest 1910, Problem H: Sum of Digits of Sums
// URL: https://codeforces.com/contest/1910/problem/H

import java.io.BufferedReader
import java.io.InputStreamReader
import java.lang.StringBuilder

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val n = br.readLine()!!.toInt()
  val a = br.readLine()!!.split(' ').map { it.toInt() }.toIntArray()
  val f =
      IntArray(n) {
        var s = 0
        var x = a[it]
        while (x > 0) {
          s += x % 10
          x /= 10
        }
        s
      }
  val sumF = f.sum().toLong()
  val p = LongArray(9) { 1L }.apply { for (i in 0..8) this[i] = this.getOrElse(i - 1) { 1L } * 10L }
  val m = Array(9) { IntArray(n) }
  for (k in 0..8) {
    val pk = p[k].toInt()
    for (j in 0 until n) m[k][j] = a[j] % pk
    m[k].sort()
  }
  fun lb(arr: IntArray, v: Int): Int {
    var l = 0
    var r = arr.size
    while (l < r) {
      val mid = (l + r) ushr 1
      if (arr[mid] < v) l = mid + 1 else r = mid
    }
    return l
  }
  val sb = StringBuilder()
  for (i in 0 until n) {
    var carries = 0L
    for (k in 0..8) {
      val bi = a[i] % p[k].toInt()
      val th = p[k].toInt() - bi
      carries += (n - lb(m[k], th))
    }
    val res = n.toLong() * f[i] + sumF - 9L * carries
    sb.append(res).append(' ')
  }
  println(sb.toString().trim())
}
