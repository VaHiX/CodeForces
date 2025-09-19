// Contest 2141, Problem F: Array Reduction
// URL: https://codeforces.com/contest/2141/problem/F

import java.io.BufferedInputStream
import java.io.InputStream
import java.lang.StringBuilder
import java.util.Arrays

private class FastScanner(private val input: InputStream = BufferedInputStream(System.`in`)) {
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
    while (c <= 32 && c >= 0) c = readByte()
    var sgn = 1
    if (c == '-'.code) {
      sgn = -1
      c = readByte()
    }
    var res = 0
    while (c > 32) {
      res = res * 10 + (c - '0'.code)
      c = readByte()
    }
    return if (sgn == 1) res else -res
  }
}

fun main() {
  val fs = FastScanner()
  val t = fs.nextInt()
  val out = StringBuilder()

  repeat(t) {
    val n = fs.nextInt()
    val cnt = IntArray(n + 1)
    for (i in 0 until n) {
      val x = fs.nextInt()
      cnt[x]++
    }

    var k = 0
    val freq = IntArray(n)
    for (v in 1..n) {
      if (cnt[v] > 0) {
        freq[k++] = cnt[v]
      }
    }

    Arrays.sort(freq, 0, k)

    val pref = LongArray(k + 1)
    for (i in 1..k) {
      val fi = freq[k - i]
      pref[i] = pref[i - 1] + fi.toLong()
    }

    val maxF = if (k == 0) 0 else freq[k - 1]
    val M = LongArray(n + 1)
    var p = k
    var bestAll = Int.MAX_VALUE

    for (tOps in 0..maxF) {
      while (p > 0 && freq[k - p] <= tOps) p--
      val pNow = p
      val tL = tOps.toLong()

      val S = n.toLong() - (pref[pNow] - tL * pNow.toLong())

      var r = 0
      while (r <= pNow) {
        val U = tOps + r
        if (U <= n) {
          val add = pref[r] - tL * r.toLong()
          val candidate = S + add
          if (candidate > M[U]) M[U] = candidate
        }
        r++
      }
      val h = tOps + pNow
      if (h < bestAll) bestAll = h
    }

    if (bestAll <= n) {
      for (u in bestAll..n) M[u] = n.toLong()
    }

    for (u in 1..n) if (M[u] < M[u - 1]) M[u] = M[u - 1]

    for (x in 0 until n) {
      val R = n - x
      var lo = 1
      var hi = n
      while (lo < hi) {
        val mid = (lo + hi) ushr 1
        if (M[mid] >= R.toLong()) hi = mid else lo = mid + 1
      }
      out.append(lo).append(' ')
    }
    out.append('\n')
  }

  print(out.toString())
}
