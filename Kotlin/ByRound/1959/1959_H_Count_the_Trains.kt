// Contest 1959, Problem H: Count the Trains
// URL: https://codeforces.com/contest/1959/problem/H

import java.io.BufferedReader
import java.io.File
import java.io.FileInputStream
import java.io.InputStreamReader
import java.util.*

fun main() {
  var sin = MyScannerH()
  var T = sin.nextInt()
  for (t in 1..T) {
    var n = sin.nextInt()
    var m = sin.nextInt()
    var a = sin.nextIntArray(n)
    val message = Array(m) { IntArray(2) }
    for (i in 0..m - 1) {
      message[i][0] = sin.nextInt()
      message[i][1] = sin.nextInt()
    }
    var ans = IntArray(m)

    var lst = SegmentTree(n)
    var rst = SegmentTree(n + 1)
    rst.updateRange(0, n, n)

    var mini = 0
    var train = 0
    for (i in 0..n) {
      if (i == n || a[i] < a[mini]) {
        lst.updateRange(mini, i - 1, mini)
        rst.updateRange(mini, i - 1, i)
        mini = i
        train++
      }
    }

    for (i in 0..m - 1) {
      var k = message[i][0] - 1
      var d = message[i][1]

      var la = lst.getAt(k)
      var ra = rst.getAt(k)

      if (a[k] - d >= a[la]) {
        ans[i] = train
        a[k] -= d
        continue
      }
      a[k] -= d

      if (la < k) {
        rst.updateRange(la, k - 1, k)
        lst.updateRange(k, ra - 1, k)
        train++
      }

      if (ra < n && a[k] <= a[ra]) {

        var last = k
        var j = ra
        while (j < n && a[j] >= a[k]) {
          train--
          last = j
          j = rst.getAt(j)
        }
        lst.updateRange(k, j - 1, k)
        rst.updateRange(k, j - 1, j)
      }
      ans[i] = train
    }
    var sb = StringBuilder(100)
    for (v in ans) {
      sb.append(v)
      sb.append(' ')
    }
    println(sb.toString())
  }
}

class SegmentTree(var n: Int) {
  var tree: IntArray
  var lazy: IntArray

  init {
    var m = 1
    while (m < n) {
      m = (m shl 1)
    }
    tree = IntArray(m * 2 - 1)
    lazy = IntArray(m * 2 - 1)
    Arrays.fill(lazy, -1)
  }

  fun updateRange(b: Int, e: Int, v: Int) {
    if (b > e) {
      return
    }
    updateRangeInner(0, 0, n - 1, b, e, v)
  }

  fun set(index: Int, value: Int) {
    checkIndex(index)
    var vcurr = getRangeMax(index, index)
    var inc = value - vcurr
    updateRange(index, index, inc)
  }

  fun getAt(index: Int): Int {
    checkIndex(index)
    return getRangeMax(0, 0, n - 1, index, index)
  }

  fun checkIndex(index: Int) {
    if (index < 0 || index >= n) {
      throw RuntimeException("Invalid index " + index)
    }
  }

  fun getRangeMax(b: Int, e: Int): Int {
    if (b < 0 || e > n - 1 || b > e) {
      return Integer.MIN_VALUE
    }
    return getRangeMax(0, 0, n - 1, b, e)
  }

  fun updateRangeInner(idx: Int, lo: Int, hi: Int, b: Int, e: Int, v: Int) {
    applyLazy(idx, lo, hi)
    if (lo > hi || lo > e || hi < b) {
      return
    }
    if (lo >= b && hi <= e) {
      lazy[idx] = v
      applyLazy(idx, lo, hi)
      return
    }
    var mid = (lo + hi) / 2
    updateRangeInner(idx * 2 + 1, lo, mid, b, e, v)
    updateRangeInner(idx * 2 + 2, mid + 1, hi, b, e, v)
    tree[idx] = Math.max(tree[idx * 2 + 1], tree[idx * 2 + 2])
  }

  fun getRangeMax(idx: Int, lo: Int, hi: Int, b: Int, e: Int): Int {
    applyLazy(idx, lo, hi)
    if (lo > hi || lo > e || hi < b) {
      return Integer.MIN_VALUE
    }
    if (lo >= b && hi <= e) {
      return tree[idx]
    }
    var mid = (lo + hi) / 2
    return Math.max(
        getRangeMax(2 * idx + 1, lo, mid, b, e),
        getRangeMax(2 * idx + 2, mid + 1, hi, b, e),
    )
  }

  fun applyLazy(idx: Int, lo: Int, hi: Int) {
    if (lazy[idx] >= 0) {
      tree[idx] = lazy[idx]
      if (lo != hi) {
        lazy[idx * 2 + 1] = lazy[idx]
        lazy[idx * 2 + 2] = lazy[idx]
      }
      lazy[idx] = -1
    }
  }
}

fun mainOld() {
  var sin = MyScannerH()
  var T = sin.nextInt()
  for (t in 1..T) {
    var n = sin.nextInt()
    var m = sin.nextInt()
    var a = sin.nextIntArray(n)
    val message = Array(m) { IntArray(2) }
    for (i in 0..m - 1) {
      message[i][0] = sin.nextInt()
      message[i][1] = sin.nextInt()
    }
    var ans = IntArray(m)

    var la = IntArray(n)

    var ra = IntArray(n + 1)
    Arrays.fill(ra, n)

    var mini = 0
    var train = 1
    for (i in 0..n - 1) {
      if (a[i] < a[mini]) {
        for (j in mini..i - 1) {
          ra[j] = i
        }
        mini = i
        train++
      }
      la[i] = mini
    }

    for (i in 0..m - 1) {
      var k = message[i][0] - 1
      var d = message[i][1]

      if (a[k] - d >= a[la[k]]) {
        ans[i] = train
        a[k] -= d
        continue
      }
      a[k] -= d

      if (la[k] < k) {
        for (j in la[k]..k - 1) {
          ra[j] = k
        }
        for (j in k..ra[k] - 1) {
          la[j] = k
        }
        train++
      }

      if (ra[k] < n && a[k] <= a[ra[k]]) {

        var last = k
        for (j in ra[k]..n - 1) {
          if (a[j] < a[k]) {
            break
          }
          if (la[j] != last) {
            train--
            last = j
          }
          la[j] = k
        }
        for (j in k..last - 1) {
          ra[j] = ra[last]
        }
      }
      ans[i] = train
    }
    var sb = StringBuilder(100)
    for (v in ans) {
      sb.append(v)
      sb.append(' ')
    }
    println(sb.toString())
  }
}

class MyScannerH {
  var br: BufferedReader
  var st: StringTokenizer

  init {
    try {
      var USERDIR = "C:\\Users\\danzhi\\src\\codeforces\\io\\c195\\"
      var fin = File(USERDIR + "c1959H.in")
      br =
          BufferedReader(InputStreamReader(if (fin.exists()) FileInputStream(fin) else System.`in`))
      st = StringTokenizer(br.readLine())
    } catch (e: Exception) {
      br = BufferedReader(InputStreamReader(System.`in`))
      st = StringTokenizer(br.readLine())
    }
  }

  fun next(): String {
    while (!st.hasMoreElements()) {
      st = StringTokenizer(br.readLine())
    }
    return st.nextToken()
  }

  fun nextInt(): Int {
    return Integer.parseInt(next())
  }

  fun nextIntArray(n: Int): IntArray {
    var a = IntArray(n)
    for (i in 0..n - 1) {
      a[i] = nextInt()
    }
    return a
  }
}
