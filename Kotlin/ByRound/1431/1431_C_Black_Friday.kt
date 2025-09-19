// Contest 1431, Problem C: Black Friday
// URL: https://codeforces.com/contest/1431/problem/C

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.StringTokenizer

fun main() {
  val sc = FastReader()
  val out = PrintWriter(System.out)
  val t = sc.nextInt()

  repeat(t) {
    val n = sc.nextInt()
    val k = sc.nextInt()
    val a = LongArray(n)

    for (i in 0 until n) {
      a[i] = sc.nextLong()
    }

    val p = LongArray(n)
    for (i in 0 until n) {
      p[i] = if (i == 0) a[i] else p[maxOf(i - 1, 0)] + a[i]
    }

    var max = 0L
    for (i in 0 until n) {
      val purchased = n - i
      val free = purchased / k

      if (free == 0) break

      max =
          if (i == 0) {
            maxOf(p[i + (free - 1)], max)
          } else {
            maxOf(p[i + (free - 1)] - if (i - 1 >= 0) p[i - 1] else 0, max)
          }
    }

    out.println(max)
  }

  out.flush()
}

class FastReader {
  private val br: BufferedReader = BufferedReader(InputStreamReader(System.`in`))
  private var st: StringTokenizer? = null

  fun next(): String {
    while (st == null || !st!!.hasMoreElements()) {
      try {
        st = StringTokenizer(br.readLine())
      } catch (e: Exception) {
        e.printStackTrace()
      }
    }
    return st!!.nextToken()
  }

  fun nextInt(): Int {
    return next().toInt()
  }

  fun nextLong(): Long {
    return next().toLong()
  }
}
