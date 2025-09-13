// Contest 1571, Problem D: Sweepstake
// URL: https://codeforces.com/contest/1571/problem/D

import java.util.*
import kotlin.math.max

private fun IN(): Int {
  var num = 0
  var c = System.`in`.read().toChar()
  var f = false
  while (c != '-' && (c < '0' || c > '9')) c = System.`in`.read().toChar()
  if (c == '-') {
    f = true
    c = System.`in`.read().toChar()
  }
  while (c >= '0' && c <= '9') {
    num = num * 10 + (c - '0')
    c = System.`in`.read().toChar()
  }
  return if (f) -num else num
}

const val N = 10002010
val cntsFull = IntArray(N)
val cntsFirst = IntArray(1010)
val cntsSecond = IntArray(1010)

fun sol() {
  val n = IN()
  val m = IN()

  for (i in 1..n) {
    cntsFirst[i] = 0
    cntsSecond[i] = 0
  }
  for (i in 1..(n + 1) * (n + 1)) cntsFull[i] = 0

  var f: Int
  var l: Int
  var f1 = 0
  var l1 = 0

  for (i in 1..m) {
    f = IN()
    l = IN()
    if (i == 1) {
      f1 = f
      l1 = l
    }
    cntsFirst[f]++
    cntsSecond[l]++
    cntsFull[f * (n + 1) + l]++
  }

  var ans = 1

  for (i in 1..n) {
    for (j in 1..n) {
      if (i == j) continue

      if (i == f1 && j == l1) continue

      val full = i * (n + 1) + j

      if (i == f1 || j == l1) ans = max(ans, cntsFull[full] + 1)
      else {
        ans = max(ans, cntsFirst[i] + cntsSecond[j] - cntsFull[full] + 1)
      }
    }
  }
  println(ans)
}

fun main() {
  sol()
}
