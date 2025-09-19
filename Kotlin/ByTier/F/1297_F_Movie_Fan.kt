// Contest 1297, Problem F: Movie Fan
// URL: https://codeforces.com/contest/1297/problem/F

import java.util.*

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readLong() = readLn().toLong()

private fun readDouble() = readLn().toDouble()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map { it.toInt() }

private fun readLongs() = readStrings().map { it.toLong() }

private fun readDoubles() = readStrings().map { it.toDouble() }

fun main(args: Array<String>) {
  var t = readInt()
  while (t-- > 0) {
    var (n, m) = readInts()
    var a = IntArray(n + 1)
    var b = IntArray(n + 1)
    for (i in 0 until n) {
      var (x, y) = readInts()
      a[i] = x
      b[i] = y
    }
    a[n] = 2e9.toInt()
    b[n] = a[n]
    var c = Array<Pair<Int, Int>>(n + 1, { i -> Pair(a[i], i) })
    c.sortWith(compareBy({ it.first }, { it.second }))
    var ans = 0
    var s = TreeSet<Long>()
    var w = IntArray(n)
    var day = 0
    for (id in 0..n) {
      while (day < c[id].first && !s.isEmpty()) {
        for (tmp in 1..m) {
          if (s.isEmpty()) {
            break
          }
          var p = s.first()
          ans = maxOf(ans, day - (p shr 32).toInt())
          w[(p and 1048575).toInt()] = day
          s.remove(p)
        }
        ++day
      }
      day = c[id].first
      var i = c[id].second
      s.add(((b[i].toLong()) shl 32) + i)
    }
    println(ans)
    println(w.joinToString(" "))
  }
}
