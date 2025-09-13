// Contest 1346, Problem F: Dune II: Battle For Arrakis
// URL: https://codeforces.com/contest/1346/problem/F

import java.util.*
import kotlin.math.abs
import kotlin.math.min

const val MAXN = 1005
const val INF = Long.MAX_VALUE
const val MOD = 998244353

class BIT(private val n: Int) {
  private val bit = LongArray(n + 5)

  fun update(idx: Int, value: Long) {
    var i = idx
    while (i <= n) {
      bit[i] += value
      i += i and -i
    }
  }

  fun get(idx: Int): Long {
    var i = idx
    var result = 0L
    while (i >= 1) {
      result += bit[i]
      i -= i and -i
    }
    return result
  }

  fun query(l: Int, r: Int): Long {
    if (r < l) return 0L
    return get(r) - get(l - 1)
  }
}

fun main() {
  val reader = System.`in`.bufferedReader()
  val writer = System.out.bufferedWriter()
  val (n, m, q) = reader.readLine().split(" ").map { it.toInt() }

  val a = Array(n + 1) { LongArray(m + 1) }

  val hori = BIT(n)
  val verti = BIT(m)
  val cntHori = BIT(n)
  val cntVerti = BIT(m)

  for (i in 1..n) {
    val row = reader.readLine().split(" ").map { it.toLong() }
    for (j in 1..m) {
      a[i][j] = row[j - 1]
      hori.update(i, a[i][j] * i)
      verti.update(j, a[i][j] * j)
      cntHori.update(i, a[i][j])
      cntVerti.update(j, a[i][j])
    }
  }

  fun findHori(): Int {
    var lf = 1
    var rg = n
    var ans = 1
    val sum = cntHori.query(1, n)
    while (lf <= rg) {
      val mid = (lf + rg) / 2
      if (cntHori.query(1, mid) >= (sum + 1) / 2) {
        ans = mid
        rg = mid - 1
      } else {
        lf = mid + 1
      }
    }
    return ans
  }

  fun findHori1(): Int {
    var lf = 1
    var rg = n
    var ans = 1
    val sum = cntHori.query(1, n)
    while (lf <= rg) {
      val mid = (lf + rg) / 2
      if (cntHori.query(1, mid) <= (sum + 1) / 2) {
        ans = mid
        lf = mid + 1
      } else {
        rg = mid - 1
      }
    }
    return ans
  }

  fun findVerti(): Int {
    var lf = 1
    var rg = m
    var ans = 1
    val sum = cntVerti.query(1, m)
    while (lf <= rg) {
      val mid = (lf + rg) / 2
      if (cntVerti.query(1, mid) >= (sum + 1) / 2) {
        ans = mid
        rg = mid - 1
      } else {
        lf = mid + 1
      }
    }
    return ans
  }

  fun findVerti1(): Int {
    var lf = 1
    var rg = m
    var ans = 1
    val sum = cntVerti.query(1, m)
    while (lf <= rg) {
      val mid = (lf + rg) / 2
      if (cntVerti.query(1, mid) <= (sum + 1) / 2) {
        ans = mid
        lf = mid + 1
      } else {
        rg = mid - 1
      }
    }
    return ans
  }

  fun ansHori(poi: Int): Long {
    return abs(hori.query(1, poi) - cntHori.query(1, poi) * poi) +
        abs(hori.query(poi + 1, n) - cntHori.query(poi + 1, n) * poi)
  }

  fun ansVerti(poj: Int): Long {
    return abs(verti.query(1, poj) - cntVerti.query(1, poj) * poj) +
        abs(verti.query(poj + 1, m) - cntVerti.query(poj + 1, m) * poj)
  }

  var poi = findHori()
  var poj = findVerti()
  var a1 = ansHori(poi)
  var a2 = ansVerti(poj)

  poi = findHori1()
  poj = findVerti1()
  a1 = min(a1, ansHori(poi))
  a2 = min(a2, ansVerti(poj))

  writer.write("${a1 + a2} ")

  repeat(q) {
    val (x, y, z) = reader.readLine().split(" ")
    val xi = x.toInt()
    val yi = y.toInt()
    val zi = z.toLong()
    val delta = zi - a[xi][yi]

    hori.update(xi, delta * xi)
    verti.update(yi, delta * yi)
    cntHori.update(xi, delta)
    cntVerti.update(yi, delta)
    a[xi][yi] = zi

    poi = findHori()
    poj = findVerti()
    a1 = ansHori(poi)
    a2 = ansVerti(poj)

    poi = findHori1()
    poj = findVerti1()
    a1 = min(a1, ansHori(poi))
    a2 = min(a2, ansVerti(poj))

    writer.write("${a1 + a2} ")
  }

  writer.newLine()
  writer.flush()
}
