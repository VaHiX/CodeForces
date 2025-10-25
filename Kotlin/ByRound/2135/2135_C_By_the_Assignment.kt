// Problem: CF 2135 C - By the Assignment
// https://codeforces.com/contest/2135/problem/C

/*
 * Problem: C. By the Assignment
 * 
 * Purpose: This code determines the number of ways to assign weights to vertices in a graph such that 
 *          all simple paths between any pair of vertices have the same XOR value. This condition 
 *          defines a "balanced" graph. The solution uses DSU (Disjoint Set Union) with path compression 
 *          and union by rank, along with cycle detection in graphs.
 * 
 * Algorithms/Techniques:
 * - Disjoint Set Union (DSU) with path compression and union by rank
 * - Tree construction using BFS (to extract spanning tree)
 * - Lowest Common Ancestor (LCA) using binary lifting technique
 * - Cycle detection and handling in graphs
 * - Modular exponentiation for counting valid assignments
 * 
 * Time Complexity: O(n * α(n) + m * log n) where α is the inverse Ackermann function and m is number of edges
 * Space Complexity: O(n + m) for storing graph and DSU structures
 * 
 * Key Points:
 * - A graph is balanced if and only if for every pair of vertices p,q, all simple paths from p to q have the same XOR value
 * - We build a spanning tree of the graph and then process remaining edges (back edges)
 * - For odd-length cycles, all nodes are forced to have weight 0
 * - For even-length cycles, nodes can be grouped in pairs with the same weight
 * - Free variables (not constrained by cycles) can each take V values
 * - Answer is V^(number of free components) mod 998244353
 */

import java.util.StringTokenizer
import kotlin.math.max
import kotlin.system.exitProcess
typealias ll = Long
const val M: Long = 998244353
const val A = 200005
const val B = 18
fun pw(b0: Long, e0: Long): Long {
    var b = b0 % M
    var e = e0
    var r = 1L
    while (e > 0) {
        if (e and 1L == 1L) r = (r * b) % M
        b = (b * b) % M
        e = e shr 1
    }
    return r
}
class D(n: Int = 0) {
    val p = IntArray(n + 1) { it }
    val c = IntArray(n + 1) { -1 }
    var ok = true
    fun f(x: Int): Int {
        if (p[x] == x) return x
        p[x] = f(p[x])
        return p[x]
    }
    fun u(x: Int, y: Int) {
        if (!ok) return
        val rx = f(x)
        val ry = f(y)
        if (rx != ry) {
            if (c[rx] != -1 && c[ry] != -1 && c[rx] != c[ry]) {
                ok = false
                return
            }
            p[ry] = rx
            if (c[ry] != -1) c[rx] = c[ry]
        }
    }
    fun s(x: Int, v: Int) {
        if (!ok) return
        val rx = f(x)
        if (c[rx] != -1 && c[rx] != v) {
            ok = false
            return
        }
        c[rx] = v
    }
}
val g = Array(A) { mutableListOf<Int>() }
val b = IntArray(A)
val h = IntArray(A)
val up = Array(A) { IntArray(B) }
var n = 0
var m = 0
var W = 0L
fun dfs(u: Int, par: Int, dep: Int) {
    h[u] = dep
    up[u][0] = par
    for (v in g[u]) {
        if (v != par) dfs(v, u, dep + 1)
    }
}
fun build() {
    dfs(1, 1, 0)
    for (j in 1 until B) {
        for (i in 1..n) {
            up[i][j] = up[up[i][j - 1]][j - 1]
        }
    }
}
fun lca(x0: Int, y0: Int): Int {
    var x = x0
    var y = y0
    if (h[x] < h[y]) {
        val tmp = x
        x = y
        y = tmp
    }
    for (j in B - 1 downTo 0) {
        if (h[x] - (1 shl j) >= h[y]) {
            x = up[x][j]
        }
    }
    if (x == y) return x
    for (j in B - 1 downTo 0) {
        if (up[x][j] != up[y][j]) {
            x = up[x][j]
            y = up[y][j]
        }
    }
    return up[x][0]
}
fun solve(scanner: FastScanner) {
    n = scanner.nextInt()
    m = scanner.nextInt()
    W = scanner.nextLong()
    for (i in 1..n) g[i].clear()
    for (i in 1..n) b[i] = scanner.nextInt()
    val e = mutableListOf<Pair<Int, Int>>()
    val t = BooleanArray(m)
    val tmp = Array(n + 1) { mutableListOf<Pair<Int, Int>>() }
    for (i in 0 until m) {
        val x = scanner.nextInt()
        val y = scanner.nextInt()
        e.add(Pair(x, y))
        tmp[x].add(Pair(y, i))
        tmp[y].add(Pair(x, i))
    }
    val q = mutableListOf<Int>()
    q.add(1)
    val vis = BooleanArray(n + 1)
    vis[1] = true
    var hd = 0
    while (hd < q.size) {
        val u = q[hd++]
        for ((v, id) in tmp[u]) {
            if (!vis[v]) {
                vis[v] = true
                g[u].add(v)
                g[v].add(u)
                t[id] = true
                q.add(v)
            }
        }
    }
    build()
    val dsu = D(n)
    for (i in 1..n) {
        if (b[i] != -1) dsu.s(i, b[i])
    }
    if (!dsu.ok) {
        println(0)
        return
    }
    for (i in 0 until m) {
        if (!t[i]) {
            val u = e[i].first
            val v = e[i].second
            val c = lca(u, v)
            val len = h[u] + h[v] - 2 * h[c] + 1
            val cyc = mutableListOf<Int>()
            var cur = u
            while (cur != c) {
                cyc.add(cur)
                cur = up[cur][0]
            }
            cyc.add(c)
            val tmpv = mutableListOf<Int>()
            cur = v
            while (cur != c) {
                tmpv.add(cur)
                cur = up[cur][0]
            }
            tmpv.reverse()
            cyc.addAll(tmpv)
            if (len % 2 != 0) {
                for (node in cyc) dsu.s(node, 0)
            } else {
                for (k in 1 until cyc.size) dsu.u(cyc[0], cyc[k])
            }
            if (!dsu.ok) {
                println(0)
                return
            }
        }
    }
    if (!dsu.ok) {
        println(0)
        return
    }
    var freec = 0
    for (i in 1..n) {
        if (dsu.p[i] == i && dsu.c[i] == -1) freec++
    }
    println(pw(W, freec.toLong()))
}
fun main() {
    val scanner = FastScanner()
    val tt = scanner.nextInt()
    repeat(tt) {
        solve(scanner)
    }
}
class FastScanner {
    private val br = System.`in`.bufferedReader()
    private var st = StringTokenizer("")
    fun next(): String {
        while (!st.hasMoreTokens()) {
            st = StringTokenizer(br.readLine())
        }
        return st.nextToken()
    }
    fun nextInt(): Int = next().toInt()
    fun nextLong(): Long = next().toLong()
}


// https://github.com/VaHiX/CodeForces/