// Problem: CF 1488 H - Build From Suffixes
// https://codeforces.com/contest/1488/problem/H

/*
 * Problem: H. Build From Suffixes
 * 
 * Algorithm: Segment Tree with Dynamic Programming
 * 
 * Time Complexity: O(q * log(n) * d^2) where d = 4 (number of characters 'a','b','c','d')
 * Space Complexity: O(n * d^2) for the segment tree storage
 * 
 * Approach:
 * - Use a segment tree where each node stores DP transitions for suffixes
 * - Each node represents a range of suffix constraints
 * - For each update, recalculate the transitions from leaf to root
 * - The DP state tracks how many ways we can assign characters to satisfy the constraints
 * - The transition logic depends on whether a[i] == 1 (lexicographically smaller) or 0 (greater)
 */

import java.io.PrintWriter
import java.util.StringTokenizer
import kotlin.math.*
@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out
@JvmField val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
  while (_tokenizer.hasMoreTokens().not()) _tokenizer =
      StringTokenizer(_reader.readLine() ?: return "", " ")
  return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }
@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) {
  _writer.apply(block).flush()
}
fun main() {
  _writer.solve()
  _writer.flush()
}
const val mod: Long = 998244353
const val Maxn = 100005
const val Maxm = 262144
const val Maxd = 4
var st = Array(Maxm) { Array(Maxd) { LongArray(Maxd) { 0 } } }
var n = 0
var q = 0
var a = IntArray(Maxn) { 0 }
fun Union(v: Int, m: Int) {
  val lc = 2 * v
  val rc = 2 * v + 1
  for (i in 0..Maxd - 1) {
    var tmp = LongArray(Maxd) { 0 }
    if (a[m] == 1) {
      // If a[m] == 1, then suffix i is lexicographically smaller than suffix i+1
      for (j in 0..Maxd - 1) {
        st[v][i][j] = 0
        tmp[j] = st[lc][i][j]
        if (j > 0) tmp[j] += tmp[j - 1]
      }
      for (j in 0..Maxd - 1) for (k in 0..Maxd - 1) {
        // If the constraint is the same (both 0 or both 1) or we need to compare positions
        if (a[m] == a[m + 1]) st[v][i][k] += tmp[j] * st[rc][j][k]
        else if (j > 0) st[v][i][k] += tmp[j - 1] * st[rc][j][k]
        st[v][i][k] %= mod
      }
    } else {
      // If a[m] == 0, then suffix i is lexicographically greater than suffix i+1
      for (j in Maxd - 1 downTo 0) {
        st[v][i][j] = 0
        tmp[j] = st[lc][i][j]
        if (j < Maxd - 1) tmp[j] += tmp[j + 1]
      }
      for (j in 0..Maxd - 1) for (k in 0..Maxd - 1) {
        // If the constraint is the same (both 0 or both 1) or we need to compare positions
        if (a[m] == a[m + 1]) st[v][i][k] += tmp[j] * st[rc][j][k]
        else if (j < Maxd - 1) st[v][i][k] += tmp[j + 1] * st[rc][j][k]
        st[v][i][k] %= mod
      }
    }
  }
}
fun Create(v: Int, l: Int, r: Int) {
  if (l == r) for (i in 0..Maxd - 1) st[v][i][i] = 1
  else {
    val m = (l + r) / 2
    Create(2 * v, l, m)
    Create(2 * v + 1, m + 1, r)
    Union(v, m)
  }
}
fun Update(v: Int, l: Int, r: Int, x: Int) {
  if (l < r) {
    val m = (l + r) / 2
    if (x <= m) Update(2 * v, l, m, x) else Update(2 * v + 1, m + 1, r, x)
    Union(v, m)
  }
}
fun PrintWriter.solve() {
  n = readInt()
  q = readInt()
  for (i in 1..n - 1) a[i] = readInt()
  Create(1, 1, n)
  for (i in 1..q) {
    val ind = readInt()
    a[ind] = 1 - a[ind]
    Update(1, 1, n, ind)
    var res: Long = 0
    for (j in 0..Maxd - 1) for (k in 0..Maxd - 1) res += st[1][j][k]
    res %= mod
    println(res)
  }
}


// https://github.com/VaHiX/CodeForces/