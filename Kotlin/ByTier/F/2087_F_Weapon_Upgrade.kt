// Contest 2087, Problem F: Weapon Upgrade
// URL: https://codeforces.com/contest/2087/problem/F

import java.io.*
import java.util.*
import kotlin.math.max
import kotlin.math.min

class IOStream {
  val br = BufferedReader(InputStreamReader(System.`in`))
  var st: StringTokenizer? = null

  fun nextToken(): String? {
    while (st == null || !st!!.hasMoreTokens()) st = StringTokenizer(br.readLine())
    return st!!.nextToken()
  }

  fun nextInt(): Int {
    return nextToken()!!.toInt()
  }

  fun nextLong(): Long {
    return nextToken()!!.toLong()
  }
}

fun main(args: Array<String>) {
  val inp = IOStream()
  val out = PrintWriter(System.out)
  var n = inp.nextInt()
  var a = Array(n, { i -> inp.nextInt() })
  var b = Array(n, { i -> inp.nextInt() })
  var mxa = 0
  var mxb = 0
  for (i in 0..n - 1) {
    --a[i]
    --b[i]
    mxa = max(mxa, a[i])
    mxb = max(mxb, b[i])
  }
  val INF = 1100100100
  var f = Array(mxa + 1, { j -> Array(mxb + 1, { i -> INF }) })
  var steps = Array(mxa + 1, { j -> Array(mxb + 1, { i -> 0 }) })
  var res = -1
  f[0][0] = 0
  for (i in 0..mxa) for (j in 0..mxb) if (f[i][j] < INF) {
    var cnt = 0
    for (k in 0..n - 1) if (a[k] <= i || b[k] <= j) ++cnt
    var good = (cnt == n)

    cnt = 0
    val lim = min(steps[i][j], n - 1)
    for (k in 0..lim) if (a[k] <= i || b[k] <= j) ++cnt
    var nxt = steps[i][j] + 1
    var cur = f[i][j]
    var exist = lim + 1 - i - j
    cur += exist
    if (good) {
      --exist
      --cur
      for (k in lim + 1..n - 1) cur += exist
      while (exist > 0) {
        --exist
        cur += exist
      }
      if (res == -1 || cur < res) res = cur

      continue
    }
    if (cnt <= i + j)
        for (k in lim + 1..n - 1) {
          if (a[k] <= i || b[k] <= j) ++cnt
          ++exist
          cur += exist
          if (cnt > i + j) {
            nxt = k + 1
            break
          }
        }
    if (cnt > i + j) {
      --cur

      if (i < mxa && f[i + 1][j] > cur) {
        f[i + 1][j] = cur
        steps[i + 1][j] = nxt
      }
      if (j < mxb && f[i][j + 1] > cur) {
        f[i][j + 1] = cur
        steps[i][j + 1] = nxt
      }
    }
  }
  out.println(res)
  out.close()
}
