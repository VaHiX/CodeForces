// Problem: CF 2136 E - By the Assignment
// https://codeforces.com/contest/2136/problem/E

// Problem: E. By the Assignment
// Purpose: Count number of ways to assign weights to vertices so that graph becomes balanced.
// Algorithms Used:
// 1. Bridge detection using DFS (Tarjan's algorithm)
// 2. Bipartite checking on components formed by non-bridge edges
// 3. Modular exponentiation for final answer calculation
// Time Complexity: O(n + m) per test case
// Space Complexity: O(n + m)

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.StringTokenizer
import java.util.ArrayDeque
import kotlin.math.min
import kotlin.math.max

const val MOD: Long = 998244353

// Fast modular exponentiation
fun modpow(a0: Long, e0: Long): Long {
    var a = a0 % MOD
    var e = e0
    var r = 1L % MOD
    while (e > 0) {
        if ((e and 1L) == 1L) r = (r * a) % MOD
        a = (a * a) % MOD
        e = e shr 1
    }
    return r
}

// Global variables for bridge detection
lateinit var aVals: LongArray
lateinit var tin: IntArray
lateinit var low: IntArray
lateinit var isBridge: IntArray
lateinit var adj: Array<MutableList<Pair<Int, Int>>>
var timer_dfs = 0

// DFS to find bridges in the graph
fun dfsBridge(u: Int, pe: Int) {
    tin[u] = ++timer_dfs
    low[u] = tin[u]
    for ((v, id) in adj[u]) {
        if (id == pe) continue // Skip parent edge
        if (tin[v] == 0) { // If not visited
            dfsBridge(v, id)
            low[u] = min(low[u], low[v])
            if (low[v] > tin[u]) isBridge[id] = 1 // Bridge found
        } else {
            low[u] = min(low[u], tin[v]) // Back edge
        }
    }
}

fun solve(br: BufferedReader, out: PrintWriter) {
    val st1 = StringTokenizer(br.readLine())
    val n = st1.nextToken().toInt()
    val m = st1.nextToken().toInt()
    val V = st1.nextToken().toLong()
    aVals = LongArray(n)
    val st2 = StringTokenizer(br.readLine())
    for (i in 0 until n) {
        aVals[i] = st2.nextToken().toLong()
    }
    adj = Array(n) { mutableListOf<Pair<Int, Int>>() }
    val edges = Array(m) { Pair(0, 0) }
    repeat(m) { i ->
        val st = StringTokenizer(br.readLine())
        var u = st.nextToken().toInt() - 1
        var v = st.nextToken().toInt() - 1
        edges[i] = Pair(u, v)
        adj[u].add(Pair(v, i))
        adj[v].add(Pair(u, i))
    }
    tin = IntArray(n)
    low = IntArray(n)
    isBridge = IntArray(m)
    timer_dfs = 0
    dfsBridge(0, -1)
    
    // Build component graph with only non-bridge edges
    val H = Array(n) { mutableListOf<Int>() }
    val inH = IntArray(n)
    for (i in 0 until m) {
        if (isBridge[i] == 0) {
            val (u, v) = edges[i]
            H[u].add(v)
            H[v].add(u)
            inH[u] = 1
            inH[v] = 1
        }
    }
    
    var freeVars = 0L
    val vis = IntArray(n)
    val color = IntArray(n) { -1 }
    
    // Check each connected component for bipartiteness and count free variables
    for (s in 0 until n) {
        if (inH[s] == 1 && vis[s] == 0) {
            val q: ArrayDeque<Int> = ArrayDeque()
            val comp = mutableListOf<Int>()
            var bip = true
            vis[s] = 1
            color[s] = 0
            q.add(s)
            while (q.isNotEmpty()) {
                val u = q.removeFirst()
                comp.add(u)
                for (v in H[u]) {
                    if (vis[v] == 0) {
                        vis[v] = 1
                        color[v] = color[u] xor 1
                        q.add(v)
                    } else if (color[v] == color[u]) {
                        bip = false // Not bipartite
                    }
                }
            }
            if (!bip) { // If not bipartite, check if fixed values are valid
                for (v in comp) {
                    if (aVals[v] != -1L && aVals[v] != 0L) {
                        out.println(0)
                        return
                    }
                }
            } else { // If bipartite, check for conflicts or count free variables
                var fixedVal = -1L
                var bad = false
                for (v in comp) {
                    if (aVals[v] != -1L) {
                        if (fixedVal == -1L) fixedVal = aVals[v]
                        else if (fixedVal != aVals[v]) {
                            bad = true
                            break
                        }
                    }
                }
                if (bad) {
                    out.println(0)
                    return
                }
                if (fixedVal == -1L) freeVars++ // Free variable found
            }
        }
    }
    
    // Count remaining free variables from isolated vertices not part of any component
    for (i in 0 until n) {
        if (inH[i] == 0) {
            if (aVals[i] == -1L) freeVars++
        }
    }
    
    // Output number of valid assignments using modular exponentiation
    out.println(modpow(V % MOD, freeVars))
}

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val out = PrintWriter(System.out, false)
    val t = br.readLine().toInt()
    repeat(t) {
        solve(br, out)
    }
    out.flush()
}


// https://github.com/VaHiX/CodeForces/