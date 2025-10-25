// Problem: CF 2120 F - Superb Graphs
// https://codeforces.com/contest/2120/problem/F

/*
 * Problem: Superb Graphs
 * 
 * Purpose: Determine if there exist k graphs H1, H2, ..., Hk such that each Gi is a superb graph of Hi.
 * 
 * Key Concepts:
 * - A fun graph G' of G maps each vertex v' in G' to a disjoint partition of vertices in G,
 *   where each part is either an independent set or clique in G.
 * - A superb graph is a fun graph with minimum number of vertices.
 * - Harshith needs to find if there is a valid assignment of H_i for each G_i.
 * 
 * Approach:
 * - For each graph Gi, we identify "twin" vertices that have same neighborhood (true twins) or
 *   opposite neighborhoods (false twins). This allows us to merge vertices in the construction
 *   of the corresponding Hi.
 * - We construct a 2-SAT instance from these constraints:
 *   - Each vertex in Gi can represent either an independent set or a clique in Hi.
 *   - For vertices that are twins, we impose constraints on their representation.
 * - The algorithm uses Tarjan's strongly connected components (SCC) to check if the 2-SAT is satisfiable.
 * 
 * Time Complexity: O(n^2 * k + n^2) where n is the number of vertices and k is the number of graphs.
 * Space Complexity: O(n^2 + n) for storing graphs, twins, and 2-SAT variables.
 * 
 * Algorithms/Techniques:
 * - 2-SAT (2-satisfiability)
 * - Tarjan's Algorithm for finding strongly connected components (SCC)
 * - Twin detection (true twins and false twins)
 */

import java.util.*

const val N = 305
var n = 0
var k = 0
val g = Array(N + 1) { IntArray(N + 1) }

// Checks if vertices u and v are false twins (have opposite neighborhoods)
fun falseTwin(u: Int, v: Int): Boolean {
    if (g[u][v] != 0) return false
    for (w in 1..n) if (w != u && w != v && g[u][w] != g[v][w]) return false
    return true
}

// Checks if vertices u and v are true twins (have identical neighborhoods)
fun trueTwin(u: Int, v: Int): Boolean {
    if (g[u][v] == 0) return false
    for (w in 1..n) if (w != u && w != v && g[u][w] != g[v][w]) return false
    return true
}

// Tarjan's algorithm variables for SCC
lateinit var low: IntArray
lateinit var num: IntArray
lateinit var cmp: IntArray
lateinit var stk: MutableList<Int>
lateinit var onstk: IntArray
var timer = 0
var scnt = 0

// Tarjan's algorithm implementation for finding strongly connected components
fun tarjan(v: Int, adj: Array<MutableList<Int>>) {
    low[v] = ++timer
    num[v] = timer
    stk.add(v)
    onstk[v] = 1
    for (u in adj[v]) {
        if (num[u] == 0) {
            tarjan(u, adj)
            low[v] = minOf(low[v], low[u])
        } else if (onstk[u] == 1) {
            low[v] = minOf(low[v], num[u])
        }
    }
    if (low[v] == num[v]) {
        while (true) {
            val u = stk.removeAt(stk.size - 1)
            cmp[u] = scnt
            onstk[u] = 0
            if (u == v) break
        }
        scnt++
    }
}

// Adds clause to 2-SAT graph representation
fun add(adj: Array<MutableList<Int>>, a: Int, b: Int, n: Int) {
    val na = if (a > 0) a + n else -a
    val A = if (a > 0) a else -a + n
    val nb = if (b > 0) b + n else -b
    val B = if (b > 0) b else -b + n
    adj[na].add(B)
    adj[nb].add(A)
}

// Segment Tree (not used in this specific solution but present in code)
class SegmentTree(private val n: Int) {
    private val tree = LongArray(4 * n)
    private val lazy = LongArray(4 * n)
    private fun push(id: Int, l: Int, r: Int) {
        if (lazy[id] != 0L) {
            tree[id] += (r - l + 1) * lazy[id]
            if (l != r) {
                lazy[id * 2] += lazy[id]
                lazy[id * 2 + 1] += lazy[id]
            }
            lazy[id] = 0L
        }
    }
    fun update(ql: Int, qr: Int, v: Long, id: Int = 1, l: Int = 0, r: Int = n - 1) {
        push(id, l, r)
        if (qr < l || r < ql) return
        if (ql <= l && r <= qr) {
            lazy[id] += v
            push(id, l, r)
            return
        }
        val mid = (l + r) / 2
        update(ql, qr, v, id * 2, l, mid)
        update(ql, qr, v, id * 2 + 1, mid + 1, r)
        tree[id] = tree[id * 2] + tree[id * 2 + 1]
    }
    fun query(ql: Int, qr: Int, id: Int = 1, l: Int = 0, r: Int = n - 1): Long {
        push(id, l, r)
        if (qr < l || r < ql) return 0
        if (ql <= l && r <= qr) return tree[id]
        val mid = (l + r) / 2
        return query(ql, qr, id * 2, l, mid) + query(ql, qr, id * 2 + 1, mid + 1, r)
    }
}

fun main() {
    val input = Scanner(System.`in`)
    val t = input.nextInt()
    repeat(t) {
        n = input.nextInt()
        k = input.nextInt()
        val cs = mutableListOf<Pair<Int, Int>>()
        repeat(k) {
            val m = input.nextInt()
            for (u in 1..n) Arrays.fill(g[u], 0)
            repeat(m) {
                val u = input.nextInt()
                val v = input.nextInt()
                g[u][v] = 1
                g[v][u] = 1
            }
            // Identify twin relationships for current graph
            for (u in 1..n)
                for (v in u + 1..n) {
                    if (falseTwin(u, v)) cs.add(Pair(u, v))
                    if (trueTwin(u, v)) cs.add(Pair(-u, -v))
                }
        }
        val varCnt = n
        val tot = 2 * varCnt + 1
        val adj = Array(tot) { mutableListOf<Int>() }
        // Build the 2-SAT constraint graph
        for ((a, b) in cs) {
            add(adj, a, b, varCnt)
        }
        low = IntArray(tot)
        num = IntArray(tot)
        cmp = IntArray(tot) { -1 }
        onstk = IntArray(tot)
        stk = mutableListOf()
        timer = 0
        scnt = 0
        // Find SCCs to check 2-SAT satisfiability
        for (v in 1 until tot)
            if (num[v] == 0) tarjan(v, adj)
        var ok = true
        // Check for contradictory assignments
        for (i in 1..varCnt)
            if (cmp[i] == cmp[i + varCnt]) {
                ok = false
                break
            }
        println(if (ok) "Yes" else "No")
    }
}


// https://github.com/VaHiX/CodeForces/