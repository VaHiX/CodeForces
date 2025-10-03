// Contest 1571, Problem G: A Battle Against a Dragon
// URL: https://codeforces.com/contest/1571/problem/G

import kotlin.math.max

const val INF = 1L shl 58

class FenwickTree(private val N: Int) {
  private val data = LongArray(N) { -INF }
  private val h: Int

  init {
    var hTemp = 0
    while (1 shl (hTemp + 1) <= N) {
      hTemp++
    }
    h = hTemp
  }

  fun reset() {
    data.fill(-INF)
  }

  fun put(x: Int, v: Long) {
    assert(x >= 0)
    var xx = x
    while (xx < N) {
      data[xx] = max(data[xx], v)
      xx = xx or (xx + 1)
    }
  }

  fun get(x: Int): Long {
    assert(x < N)
    var xx = x
    var res = -INF
    while (xx >= 0) {
      res = max(res, data[xx])
      xx = (xx and (xx + 1)) - 1
    }
    return res
  }
}

class Solution {
  fun solve(A: Array<IntArray>, B: Array<IntArray>, m: Int): Long {
    val n = A.size

    for (i in 0 until n) {
      for (j in B[i].indices) {
        B[i][j] = m - B[i][j]
      }
    }

    val groups = Array(m + 1) { mutableListOf<Pair<Int, Int>>() }
    for (i in 0 until n) {
      val sz = A[i].size
      for (j in 0 until sz) {
        groups[B[i][j]].add(Pair(i, A[i][j]))
      }
    }

    val ft = FenwickTree(n + 4)
    ft.put(0, 0)
    var res: Long = 0
    for (k in 0..m) {
      for ((idx, value) in groups[k]) {
        val key = idx - k
        if (key >= 0) {
          var v = ft.get(key)
          v += value
          res = max(res, v)
          ft.put(key + 1, v)
        }
      }
    }
    return res
  }
}

fun main() {
  val sol = Solution()
  val (n, m) = readLine()!!.split(" ").map { it.toInt() }
  val A = Array<IntArray>(n) { i -> IntArray(0) }
  val B = Array<IntArray>(n) { i -> IntArray(0) }
  for (i in 0..n - 1) {
    val sz = readLine()!!.toInt()
    val a = readLine()!!.split(" ").map { it.toInt() }.toIntArray()
    val b = readLine()!!.split(" ").map { it.toInt() }.toIntArray()
    A[i] = a
    B[i] = b
  }

  println(sol.solve(A, B, m))
}
