// Contest 1958, Problem J: Necromancer
// URL: https://codeforces.com/contest/1958/problem/J

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val (n, q) = readInts(br)
  val a = readInts(br).toIntArray()
  val b = readInts(br).toIntArray()
  val l = IntArray(q)
  val r = IntArray(q)

  repeat(q) {
    val (x, y) = readInts(br)
    l[it] = x - 1
    r[it] = y - 1
  }

  if (n < 4) {
    val result = IntArray(q)
    repeat(q) { i ->
      var res = 0
      var str = b[l[i]]
      for (j in l[i] + 1..r[i]) {
        res += modceil(a[j], str)
        str += b[j]
      }
      result[i] = res
    }
    result.forEach { println(it) }
    return
  }

  val acc = IntArray(n + 1)
  for (i in 1..n) {
    acc[i] = acc[i - 1] + b[i - 1]
  }

  val toadd = Array(n) { mutableListOf<Int>() }
  for (i in 0 until n) {
    for (j in 1 until K) {
      val x = acc[i] - modceil(a[i], j)
      val pos = bsearch(acc, x, 0, i)
      if (pos < i) {
        toadd[pos].add(i)
      }
    }
  }

  val qr = Array(n) { mutableListOf<Int>() }
  for (i in 0 until q) {
    qr[l[i]].add(i)
  }

  val tree = FenwickTree(IntArray(n) { 1 })
  val res = IntArray(q)
  val firstm = IntArray(M)

  for (i in 0 until n) {
    for (j in toadd[i]) {
      tree.add(j, 1)
    }
    if (qr[i].isEmpty()) {
      continue
    }
    var str = b[i]
    for (j in 1 until minOf(M, n - i)) {
      firstm[j] = firstm[j - 1] + modceil(a[i + j], str)
      str += b[i + j]
    }
    for (j in qr[i]) {
      val right = r[j]
      res[j] = if (right - i < M) firstm[right - i] else firstm.last() + tree.range(i + M, right)
    }
  }

  res.forEach { println(it) }
}

fun modceil(n: Int, k: Int): Int = (n + k - 1) / k

fun bsearch(acc: IntArray, x: Int, l: Int, r: Int): Int {
  var low = l
  var high = r
  var res = r
  while (low <= high) {
    val mid = (low + high) / 2
    if (acc[mid] > x) {
      res = mid
      high = mid - 1
    } else {
      low = mid + 1
    }
  }
  return res
}

const val M = 1000
const val K = 10

class FenwickTree(private val a: IntArray) {
  private val tree = IntArray(a.size + 1)

  init {
    for (i in a.indices) {
      add(i, a[i])
    }
  }

  fun add(i: Int, added: Int) {
    var idx = i + 1
    while (idx < tree.size) {
      tree[idx] += added
      idx += idx and -idx
    }
  }

  fun range(i: Int, j: Int): Int = sum(j + 1) - sum(i)

  private fun sum(i: Int): Int {
    var res = 0
    var idx = i
    while (idx > 0) {
      res += tree[idx]
      idx -= idx and -idx
    }
    return res
  }
}

fun readInts(br: BufferedReader): List<Int> {
  val tokenizer = StringTokenizer(br.readLine())
  return List(tokenizer.countTokens()) { tokenizer.nextToken().toInt() }
}
