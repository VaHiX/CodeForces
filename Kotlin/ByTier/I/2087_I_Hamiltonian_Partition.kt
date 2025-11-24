// Problem: CF 2087 I - Hamiltonian Partition
// https://codeforces.com/contest/2087/problem/I

/*
 * Problem: Hamiltonian Partition
 * Algorithm: Maximum Flow + Augmenting Path (Hungarian Algorithm approach)
 * Time Complexity: O(n^3 * m) where n is number of vertices and m is number of edges.
 * Space Complexity: O(n^2 + m) for adjacency list, edge tracking, and auxiliary arrays.
 *
 * The task requires partitioning all edges of a directed acyclic graph (DAG) into
 * Hamiltonian cycles after adding the minimum number of edges. 
 * A Hamiltonian cycle visits each vertex exactly once in a cycle.
 * 
 * The approach:
 * 1. Compute in-degrees and out-degrees for each node.
 * 2. Add dummy edges to balance in/out degrees, ensuring that every node has
 *    equal in-degree and out-degree (required for Eulerian decomposition).
 * 3. Use a greedy matching approach via maximum flow logic to decompose the new graph
 *    into cycles, assigning each edge to a cycle.
 */
import java.util.*
fun main() {
    val (n, m) = readInts()
    val dl = IntArray(n)
    val dr = IntArray(n)
    val g = Array(n) { mutableListOf<Pair<Int, Int>>() }
    val eds = mutableListOf<Pair<Int, Int>>()
    for (i in 0 until m) {
        val (x, y) = readInts().map { it - 1 } // Convert to 0-based indexing
        g[x].add(Pair(y, i))
        eds.add(Pair(x, y))
        dl[x] += 1
        dr[y] += 1
    }
    val ans = maxOf(dl.max(), dr.max()) // Maximum of in/out degree - determines cycles needed

    var extraL = mutableListOf<Int>() // Extra vertices to add outgoing edges from
    var extraR = mutableListOf<Int>() // Extra vertices to add incoming edges to
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
        g[extraL[i]].add(Pair(extraR[i], ptr)) // Add dummy edges to balance degrees
        eds.add(Pair(extraL[i], extraR[i]))
        ptr += 1
    }

    val edges = mutableListOf<Pair<Int, Int>>()
    val res = mutableListOf<Int>()
    for (i in 0 until m) {
        res.add(-1)
    }
    val used = BooleanArray(ptr) { false } // Track if an edge was assigned to a cycle

    for (id in 0 until ans) { // For each step in the flow algorithm (cycle assignment)
        val pa = IntArray(n) { -1 } // pa[v] = u means v matched with u in current matching
        val pb = IntArray(n) { -1 } // pb[v] = u means v matched with u in current matching
        val was = IntArray(n) { -1 } // Track visitation during DFS

        fun dfs(v: Int, iter: Int): Boolean {
            was[v] = iter
            for ((u, idx) in g[v]) {
                if (!used[idx] && pb[u] == -1) { // Found an unmatched node u
                    pa[v] = u // Match v to u
                    pb[u] = v
                    return true
                }
            }
            for ((u, idx) in g[v]) {
                if (!used[idx] && was[pb[u]] != iter && dfs(pb[u], iter)) { // Try augmenting path
                    pa[v] = u
                    pb[u] = v
                    return true
                }
            }
            return false
        }

        for (i in 0 until n) {
            assert(dfs(i, i)) // Ensure matching exists for each node
        }

        val nxt = IntArray(n) { -1 } // nxt[i] = j means i->j in current cycle
        val prv = IntArray(n) { -1 } // prv[i] = j means j->i in current cycle

        // Assign found matchings to result and mark used
        for (i in 0 until ptr) {
            val (x, y) = eds[i]
            if (!used[i] && pa[x] == y) {
                used[i] = true
                pa[x] = -1
                if (i < m) {
                    res[i] = id + 1 // Assign original edge to cycle id+1
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
            if (prv[i] == -1) { // Starting node of a path
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
                continue // Already connected in cycle, no need to add dummy edge
            }
            assert(nxt[seq[i]] == -1)
            edges.add(Pair(seq[i], seq[j])) // Add back-edge to form a cycle
            res.add(id + 1) // Assign this edge to same cycle as previous ones for consistency
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


// https://github.com/VaHiX/codeForces/