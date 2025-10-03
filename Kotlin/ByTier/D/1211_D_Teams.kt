// Contest 1211, Problem D: Teams
// URL: https://codeforces.com/contest/1211/problem/D

import java.io.*

val reader = BufferedReader(InputStreamReader(System.`in`))

fun bufferOut(block: PrintWriter.() -> Unit) = PrintWriter(System.out).use { block(it) }

fun read() = reader.readLine()!!.split(' ').map { it.toInt() }

fun main() = bufferOut { solve() }

fun PrintWriter.solve() {
  var (n, a, b, k) = read()
  var num = IntArray(1000001) { 0 }
  for (r in read()) {
    num[r] += 1
  }
  var res = 0
  if (a < b) {
    for (i in 1000000 downTo 1) {
      if (i % k == 0) {
        var c = minOf(num[i] / b, num[i / k] / a)
        num[i / k] -= a * c
        res += c
      }
    }
  } else {
    for (i in 1..1000000) {
      if (i * k <= 1000000) {
        var c = minOf(num[i] / a, num[i * k] / b)
        num[i * k] -= b * c
        res += c
      }
    }
  }
  println(res)
}
