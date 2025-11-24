// Problem: CF 1488 F - Dogecoin
// https://codeforces.com/contest/1488/problem/F

/*
 * Problem: Dogecoin
 * Purpose: Calculate maximum profit Ann can get from mining Dogecoin over given time periods.
 * Algorithm: Segment tree with lazy propagation + monotonic stack approach
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 * Techniques:
 *   - Segment tree with range updates and queries
 *   - Monotonic stack to efficiently process elements
 *   - Range maximum profit calculation using segment tree
 */

import java.lang.AssertionError
private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }
private fun myAssert(x: Boolean) {
  if (!x) {
    throw AssertionError()
  }
}
var sum = LongArray(0)
var add = IntArray(0)
fun modify(x: Int, l: Int, r: Int, ll: Int, rr: Int, v: Int) {
  if (r < ll || rr < l) {
    return
  }
  if (ll <= l && r <= rr) {
    add[x] += v
    sum[x] += v.toLong() * (r - l + 1)
    return
  }
  val y = (l + r) shr 1
  if (add[x] != 0) {
    add[x + x] += add[x]
    sum[x + x] += add[x].toLong() * (y - l + 1)
    add[x + x + 1] += add[x]
    sum[x + x + 1] += add[x].toLong() * (r - y)
    add[x] = 0
  }
  if (ll <= y) {
    modify(x + x, l, y, ll, rr, v)
  }
  if (rr > y) {
    modify(x + x + 1, y + 1, r, ll, rr, v)
  }
  sum[x] = sum[x + x] + sum[x + x + 1]
}
fun getSum(x: Int, l: Int, r: Int, ll: Int, rr: Int): Long {
  if (r < ll || rr < l) {
    return 0
  }
  if (ll <= l && r <= rr) {
    return sum[x]
  }
  val y = (l + r) shr 1
  if (add[x] != 0) {
    add[x + x] += add[x]
    sum[x + x] += add[x].toLong() * (y - l + 1)
    add[x + x + 1] += add[x]
    sum[x + x + 1] += add[x].toLong() * (r - y)
    add[x] = 0
  }
  var res = 0L
  if (ll <= y) {
    res += getSum(x + x, l, y, ll, rr)
  }
  if (rr > y) {
    res += getSum(x + x + 1, y + 1, r, ll, rr)
  }
  sum[x] = sum[x + x] + sum[x + x + 1]
  return res
}
fun main(args: Array<String>) {
  var n = readInt()
  var a = readInts()
  var q = readInt()
  var l = IntArray(q)
  var r = IntArray(q)
  var at = Array(n) { ArrayList<Int>() }
  var ans = LongArray(q)
  for (i in 0 until q) {
    var (x, y) = readInts()
    l[i] = x - 1
    r[i] = y - 1
    at[r[i]].add(i)
  }
  sum = LongArray(4 * n + 10)
  add = IntArray(4 * n + 10)
  var st = IntArray(n + 1)
  st[0] = -1
  var sz = 1
  for (i in 0 until n) {
    while (sz > 1 && a[i] > a[st[sz - 1]]) {
      modify(1, 0, n - 1, st[sz - 2] + 1, st[sz - 1], a[i] - a[st[sz - 1]])
      sz -= 1
    }
    modify(1, 0, n - 1, i, i, a[i])
    st[sz++] = i
    for (it in at[i]) {
      ans[it] = getSum(1, 0, n - 1, l[it], r[it])
    }
  }
  println(ans.joinToString(" "))
}


// https://github.com/VaHiX/CodeForces/