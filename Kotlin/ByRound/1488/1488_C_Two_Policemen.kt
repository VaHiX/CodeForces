// Contest 1488, Problem C: Two Policemen
// URL: https://codeforces.com/contest/1488/problem/C

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.max
import kotlin.math.min

private class FastScanner {
  private val br = BufferedReader(InputStreamReader(System.`in`))
  private var st: StringTokenizer? = null

  fun nextInt(): Int {
    while (st == null || !st!!.hasMoreElements()) {
      st = StringTokenizer(br.readLine())
    }
    return st!!.nextToken().toInt()
  }
}

fun main() {
  val fs = FastScanner()
  val t = fs.nextInt()
  val out = StringBuilder()

  repeat(t) {
    var n = fs.nextInt()
    var x = fs.nextInt()
    var y = fs.nextInt()

    if (x > y) {
      val tmp = x
      x = y
      y = tmp
    }

    var ans = 1_000_000_000L

    for (i in x until y) {
      val leftGap = i - x
      val leftBound = x - 1
      val rightGap = y - i - 1
      val rightBound = n - y

      val left = (min(leftGap, leftBound) * 2L) + max(leftGap, leftBound)
      val right = (min(rightGap, rightBound) * 2L) + max(rightGap, rightBound)

      ans = min(ans, max(left, right))
    }

    out.append(ans).append('\n')
  }

  print(out.toString())
}
