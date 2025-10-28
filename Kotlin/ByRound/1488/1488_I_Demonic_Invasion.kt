// Problem: CF 1488 I - Demonic Invasion
// https://codeforces.com/contest/1488/problem/I

/*
 * Problem: Demonic Invasion
 * 
 * Algorithm: Maximum Flow (Dinic's Algorithm)
 * 
 * Approach:
 * - Model the problem as a flow network where:
 *   - Each bridge is a node in the graph
 *   - Each island is a node in the graph
 *   - We create a bipartite flow graph:
 *     - Source connects to each bridge node (capacity 1)
 *     - Each bridge node connects to its two endpoints (capacity 1)
 *     - Each island connects to sink (capacity 1) if it's at odd distance from source
 *   - We model the constraint that stones decay in 2 days using the bipartite nature of the graph.
 *   - We run maximum flow algorithm using Dinic's algorithm to find maximum number of mages that can be saved.
 * 
 * Time Complexity: O(V^2 * E) where V = n + m + 2 and E = 3*m + 2*n (for the edges in the flow graph)
 * Space Complexity: O(V + E) for storing the graph and flow edges
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
class Edge(val from: Int, val to: Int, val c: Int, var f: Int)
fun main(args: Array<String>) {
  var (n, m, k) = readInts()
  var g = Array(n) { ArrayList<Pair<Int, Int>>() }
  for (i in 0 until m) {
    var (x, y) = readInts()
    g[x - 1].add(Pair(y - 1, i))
    g[y - 1].add(Pair(x - 1, i))
  }
  var d = IntArray(n) { -1 }
  var que = ArrayList<Int>()
  d[0] = 0
  que.add(0)
  var edges = ArrayList<Edge>()
  var st = n + m
  var fin = n + m + 1
  var qIt = 0
  while (qIt < que.size) {
    var u = que[qIt++]
    for ((v, it) in g[u]) {
      if (d[v] == -1) {
        que.add(v)
        d[v] = d[u] + 1
      }
      if (d[v] == d[u] + 1) {
        // Build bipartite graph based on BFS levels
        if (d[u] % 2 == 0) {
          // Even level -> from source to bridge
          edges.add(Edge(st, n + it, 1, 0))
          edges.add(Edge(n + it, st, 0, 0))
          edges.add(Edge(n + it, u, 1, 0))
          edges.add(Edge(u, n + it, 0, 0))
          edges.add(Edge(n + it, v, 1, 0))
          edges.add(Edge(v, n + it, 0, 0))
        } else {
          // Odd level -> from island to sink
          edges.add(Edge(u, n + it, 1, 0))
          edges.add(Edge(n + it, u, 0, 0))
          edges.add(Edge(v, n + it, 1, 0))
          edges.add(Edge(n + it, v, 0, 0))
          edges.add(Edge(n + it, fin, 1, 0))
          edges.add(Edge(fin, n + it, 0, 0))
        }
      }
    }
  }
  var out = Array(n + m + 2) { ArrayList<Int>() }
  for (i in 0 until edges.size) {
    out[edges[i].from].add(i)
  }
  var ptr = IntArray(n + m + 2)
  var dst = IntArray(n + m + 2)
  var q = IntArray(n + m + 2)
  var ans = 0
  while (true) {
    for (i in 0 until n + m + 2) {
      dst[i] = -1
    }
    q[0] = fin
    dst[fin] = 0
    var beg = 0
    var end = 1
    var found = false
    while (beg < end) {
      var i = q[beg++]
      for (it in out[i]) {
        var e = edges[it]
        var back = edges[it xor 1]
        if (back.c > back.f && dst[e.to] == -1) {
          dst[e.to] = dst[i] + 1
          if (e.to == st) {
            found = true
            break
          }
          q[end++] = e.to
        }
      }
      if (found) {
        break
      }
    }
    if (!found) {
      break
    }
    for (i in 0 until n + m + 2) {
      ptr[i] = out[i].size - 1
    }
    fun dfs(v: Int, w: Int): Int {
      if (v == fin) {
        return w
      }
      while (ptr[v] >= 0) {
        var it = out[v][ptr[v]]
        var e = edges[it]
        if (e.c > e.f && dst[e.to] == dst[v] - 1) {
          var t = dfs(e.to, minOf(e.c - e.f, w))
          if (t > 0) {
            edges[it].f += t
            edges[it xor 1].f -= t
            return t
          }
        }
        ptr[v] -= 1
      }
      return 0
    }
    var bigAdd = 0
    while (true) {
      var add = dfs(st, n + m + 2)
      if (add == 0) {
        break
      }
      bigAdd += add
    }
    if (bigAdd == 0) {
      break
    }
    ans += bigAdd
  }
  println(minOf(ans, k))
}


// https://github.com/VaHiX/CodeForces/