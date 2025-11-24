// Problem: CF 2132 F - Rada and the Chamomile Valley
// https://codeforces.com/contest/2132/problem/F

/*
 * Problem: F. Rada and the Chamomile Valley
 * 
 * Algorithm:
 * - Find all bridges in the graph using DFS (Tarjan's algorithm)
 * - Collapse each connected component into a node in the bridge tree
 * - Perform BFS on the bridge tree from source to target to find which bridges can be part of any path from 1 to n
 * - For each query vertex, compute shortest distances to all bridges, and return minimum index among edges used in that distance
 * 
 * Time Complexity: O((n + m) * α(n)) per test case where α is the inverse Ackermann function.
 * Space Complexity: O(n + m) for storing graph, bridge information, and auxiliary data structures.
 */
import java.util.*
import kotlin.collections.ArrayList
import kotlin.math.min

fun main() {
    val sc = Scanner(System.`in`)
    val T = sc.nextInt()
    repeat(T) {
        val n = sc.nextInt()
        val m = sc.nextInt()
        val U = IntArray(m + 1)
        val V = IntArray(m + 1)
        // Adjacency list to store the graph
        val g = Array(n + 1) { ArrayList<Pair<Int, Int>>() }
        for (i in 1..m) {
            val u = sc.nextInt()
            val v = sc.nextInt()
            U[i] = u
            V[i] = v
            // Add edge to both directions with edge index
            g[u].add(Pair(v, i))
            g[v].add(Pair(u, i))
        }
        val tin = IntArray(n + 1) { -1 }           // Time in DFS
        val low = IntArray(n + 1)                  // Low value for bridge detection
        val br = ByteArray(m + 1)                  // Mark bridge edges
        var tm = 0                                 // Timer for DFS

        // Tarjan's algorithm to detect bridges
        fun dfs(v: Int, pe: Int) {
            tm += 1
            tin[v] = tm
            low[v] = tm
            for ((to, ei) in g[v]) {
                if (ei == pe) continue           // Skip parent edge
                if (tin[to] == -1) {             // If not visited
                    dfs(to, ei)
                    low[v] = min(low[v], low[to])
                    if (low[to] > tin[v]) br[ei] = 1 // Bridge found
                } else {
                    low[v] = min(low[v], tin[to])    // Back edge
                }
            }
        }
        dfs(1, -1)

        // Component id for each vertex (collapsed nodes after removing bridges)
        val comp = IntArray(n + 1)
        var cid = 0

        // DFS to assign component ids to connected components
        fun dfs2(v: Int) {
            for ((to, ei) in g[v]) {
                if (br[ei] != 0.toByte() || comp[to] != 0) continue  // Skip if bridge or already visited
                comp[to] = cid
                dfs2(to)
            }
        }

        for (v in 1..n) {
            if (comp[v] == 0) {      // Start new component
                cid += 1
                comp[v] = cid
                dfs2(v)
            }
        }

        // Build the bridge tree (each node is a connected component, edges are bridges)
        val tg = Array(cid + 1) { ArrayList<Pair<Int, Int>>() }
        for (i in 1..m) {
            if (br[i] != 0.toByte()) {   // If it's a bridge
                val a = comp[U[i]]
                val b = comp[V[i]]
                tg[a].add(Pair(b, i))
                tg[b].add(Pair(a, i))
            }
        }

        val s = comp[1]         // Source component
        val t = comp[n]         // Target component

        // BFS to find path from source component to target component via bridges
        val par = IntArray(cid + 1) { -1 }      // Parent pointer in BFS tree
        val pare = IntArray(cid + 1) { -1 }     // Edge index of parent edge
        val q = ArrayDeque<Int>()
        q.add(s)
        par[s] = s

        while (q.isNotEmpty()) {
            val v = q.removeFirst()
            if (v == t) break                    // Reached target component
            for ((to, ei) in tg[v]) {
                if (par[to] != -1) continue       // Already visited
                par[to] = v
                pare[to] = ei
                q.add(to)
            }
        }

        // Collect the edge indices of bridges on path from s to t
        val imp = ArrayList<Int>()
        if (s != t && par[t] != -1) {
            var cur = t
            while (cur != s) {
                imp.add(pare[cur])
                cur = par[cur]
            }
        }

        // Process queries
        val qn = sc.nextInt()
        val query = IntArray(qn) { sc.nextInt() }
        if (imp.isEmpty()) {
            println(query.joinToString(" ") { "-1" })
            return@repeat
        }

        // Shortest path algorithm using priority queue from all important edges
        val INF = 1_000_000_000
        val dist = IntArray(n + 1) { INF }
        val lab = IntArray(n + 1) { Int.MAX_VALUE }   // Minimum edge index to reach node

        val pq = PriorityQueue<Triple<Int, Int, Int>>(compareBy({ it.first }, { it.second }))
        for (ei in imp) {
            val a = U[ei]
            val b = V[ei]
            for (x in listOf(a, b)) {
                if (dist[x] > 0 || (dist[x] == 0 && lab[x] > ei)) {
                    dist[x] = 0
                    lab[x] = min(lab[x], ei)
                    pq.add(Triple(dist[x], lab[x], x))
                }
            }
        }

        while (pq.isNotEmpty()) {
            val (d, id, v) = pq.poll()
            if (d != dist[v] || id != lab[v]) continue // Skip outdated entries
            for ((to, ei) in g[v]) {
                val nd = d + 1
                val nid = id
                if (nd < dist[to] || (nd == dist[to] && nid < lab[to])) {
                    dist[to] = nd
                    lab[to] = nid
                    pq.add(Triple(dist[to], lab[to], to))
                }
            }
        }

        println(query.joinToString(" ") { lab[it].toString() })
    }
}


// https://github.com/VaHiX/CodeForces/