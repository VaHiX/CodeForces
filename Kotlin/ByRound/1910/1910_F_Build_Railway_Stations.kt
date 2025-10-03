// Contest 1910, Problem F: Build Railway Stations
// URL: https://codeforces.com/contest/1910/problem/F

fun main() {
  val t = readInt()
  repeat(t) {
    val (n, k) = readInts()
    val g = List(n) { mutableListOf<Int>() }
    for (i in 0 until n - 1) {
      val (x, y) = readInts()
      g[x - 1].add(y - 1)
      g[y - 1].add(x - 1)
    }
    val sz = IntArray(n)
    fun dfs(v: Int, pr: Int) {
      sz[v] = 1
      for (u in g[v]) {
        if (u != pr) {
          dfs(u, v)
          sz[v] += sz[u]
        }
      }
    }
    dfs(0, -1)
    val sub = LongArray(n - 1)
    var ans = 0L
    for (i in 1 until n) {
      val cur = sz[i].toLong() * (n - sz[i])
      ans += cur * 2
      sub[i - 1] = cur
    }
    sub.sortDescending()
    for (i in 0 until k - 1) {
      ans -= sub[i]
    }
    println(ans)
  }
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readLong() = readLn().toLong()

private fun readDouble() = readLn().toDouble()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map { it.toInt() }

private fun readLongs() = readStrings().map { it.toLong() }

private fun readDoubles() = readStrings().map { it.toDouble() }
