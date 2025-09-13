// Contest 2087, Problem I: Hamiltonian Partition
// URL: https://codeforces.com/contest/2087/problem/I

import java.util.*

fun main() {
  val (n, m) = readInts()
  val dl = IntArray(n)
  val dr = IntArray(n)
  val g = Array(n) { mutableListOf<Pair<Int, Int>>() }
  val eds = mutableListOf<Pair<Int, Int>>()
  for (i in 0 until m) {
    val (x, y) = readInts().map { it - 1 }
    g[x].add(Pair(y, i))
    eds.add(Pair(x, y))
    dl[x] += 1
    dr[y] += 1
  }
  val ans = maxOf(dl.max(), dr.max())
  var extraL = mutableListOf<Int>()
  var extraR = mutableListOf<Int>()
  for (i in 0 until n) {
    for (j in 0 until ans - dl[i]) {
      extraL.add(i)
    }
    for (j in 0 until ans - dr[i]) {
      extraR.add(i)
    }
  }
  assert(extraL.size == extraR.size)
  var ptr = m
  for (i in 0 until extraL.size) {
    g[extraL[i]].add(Pair(extraR[i], ptr))
    eds.add(Pair(extraL[i], extraR[i]))
    ptr += 1
  }
  val edges = mutableListOf<Pair<Int, Int>>()
  val res = mutableListOf<Int>()
  for (i in 0 until m) {
    res.add(-1)
  }
  val used = BooleanArray(ptr) { false }
  for (id in 0 until ans) {
    val pa = IntArray(n) { -1 }
    val pb = IntArray(n) { -1 }
    val was = IntArray(n) { -1 }
    fun dfs(v: Int, iter: Int): Boolean {
      was[v] = iter
      for ((u, idx) in g[v]) {
        if (!used[idx] && pb[u] == -1) {
          pa[v] = u
          pb[u] = v
          return true
        }
      }
      for ((u, idx) in g[v]) {
        if (!used[idx] && was[pb[u]] != iter && dfs(pb[u], iter)) {
          pa[v] = u
          pb[u] = v
          return true
        }
      }
      return false
    }
    for (i in 0 until n) {
      assert(dfs(i, i))
    }
    val nxt = IntArray(n) { -1 }
    val prv = IntArray(n) { -1 }
    for (i in 0 until ptr) {
      val (x, y) = eds[i]
      if (!used[i] && pa[x] == y) {
        used[i] = true
        pa[x] = -1
        if (i < m) {
          res[i] = id + 1
          nxt[x] = y
          prv[y] = x
        }
      }
    }
    for (i in 0 until n) {
      assert(pa[i] == -1)
    }
    val seq = mutableListOf<Int>()
    for (i in 0 until n) {
      if (prv[i] == -1) {
        seq.add(i)
        var x = i
        while (nxt[x] != -1) {
          x = nxt[x]
          seq.add(x)
        }
      }
    }
    assert(seq.size == n)
    for (i in 0 until n) {
      val j = (i + 1) % n
      if (nxt[seq[i]] == seq[j]) {
        continue
      }
      assert(nxt[seq[i]] == -1)
      edges.add(Pair(seq[i], seq[j]))
      res.add(id + 1)
    }
  }
  println(edges.size)
  for ((x, y) in edges) {
    println("${x + 1} ${y + 1}")
  }
  println(ans)
  println(res.joinToString(" "))
}

private fun readInt() = readln().toInt()

private fun readLong() = readln().toLong()

private fun readDouble() = readln().toDouble()

private fun readStrings() = readln().split(" ")

private fun readInts() = readStrings().map { it.toInt() }

private fun readLongs() = readStrings().map { it.toLong() }

private fun readDoubles() = readStrings().map { it.toDouble() }
