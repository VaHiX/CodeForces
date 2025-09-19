// Contest 2141, Problem G: Good Robot Paths
// URL: https://codeforces.com/contest/2141/problem/G

import java.io.BufferedInputStream

private class FastScanner {
  private val input = BufferedInputStream(System.`in`)
  private val buffer = ByteArray(1 shl 16)
  private var len = 0
  private var ptr = 0

  private fun readByte(): Int {
    if (ptr >= len) {
      len = input.read(buffer)
      ptr = 0
      if (len <= 0) return -1
    }
    return buffer[ptr++].toInt()
  }

  fun nextInt(): Int {
    var c = readByte()
    while (c <= 32) {
      c = readByte()
      if (c == -1) return Int.MIN_VALUE
    }
    var sign = 1
    if (c == '-'.code) {
      sign = -1
      c = readByte()
    }
    var res = 0
    while (c > 32) {
      res = res * 10 + (c - '0'.code)
      c = readByte()
    }
    return res * sign
  }
}

data class P(val x: Int, val y: Int)

fun main() {
  val fs = FastScanner()
  val T = fs.nextInt()
  val out = StringBuilder()

  repeat(T) {
    val N = fs.nextInt()
    val A = Array(N) { P(fs.nextInt(), fs.nextInt()) }

    java.util.Arrays.sort(A) { p1, p2 -> if (p1.x != p2.x) p1.x - p2.x else p1.y - p2.y }

    val idx = HashMap<Long, Int>(N * 2)
    fun key(x: Int, y: Int): Long = (x.toLong() shl 32) xor (y.toLong() and 0xffffffffL)
    for (i in 0 until N) idx[key(A[i].x, A[i].y)] = i
    fun getIdx(x: Int, y: Int): Int = idx[key(x, y)] ?: -1

    val H = IntArray(N)
    for (i in N - 1 downTo 0) {
      val x = A[i].x
      val y = A[i].y
      val j = getIdx(x + 1, y)
      H[i] = if (j == -1) 1 else H[j] + 1
    }

    fun F(B: IntArray): Long {
      val n = B.size
      var ans = 0L
      var sm = 0L
      val stA = ArrayDeque<Long>()
      val stK = ArrayDeque<Long>()
      for (i in 0 until n) {
        val b = B[i].toLong()
        var cnt = 1L
        while (stA.isNotEmpty()) {
          val a: Long = stA.last()
          val k: Long = stK.last()
          if (a >= b) {
            stA.removeLast()
            stK.removeLast()
            sm -= a * k
            cnt = cnt + k
          } else break
        }
        stA.addLast(b)
        stK.addLast(cnt)
        sm += b * cnt
        ans += sm - b
      }
      ans *= 2
      ans -= 1L * n * (n - 1) / 2
      for (x in B) ans += (x - 1)
      return ans
    }

    var L = 0
    var ANS = 0L
    while (L < N) {
      var R = L + 1
      while (R < N && A[R - 1].x == A[R].x && A[R - 1].y + 1 == A[R].y) R++
      val B = IntArray(R - L) { H[L + it] }
      ANS += F(B)
      L = R
    }

    ANS += ANS
    out.append(ANS).append('\n')
  }

  print(out.toString())
}
