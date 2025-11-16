// Problem: CF 2137 G - Cry Me a River
// https://codeforces.com/contest/2137/problem/G

/*
 * Problem: G. Cry Me a River
 *
 * Purpose:
 *   This code solves a game played on a directed acyclic graph (DAG) between two players, Cry and River.
 *   Each node starts blue; when queried with type 1, a node is painted red.
 *   Player Cry moves first, and the game ends when either:
 *     - The token reaches a node with no outgoing edges (Cry wins).
 *     - The token reaches a red node (River wins).
 *   The queries of type 2 ask whether Cry can win from a given starting node with optimal play.
 *
 * Algorithm:
 *   - Use topological sorting to process nodes from leaves up to root.
 *   - At each node, compute "A" and "B" properties:
 *     - A[v]: Player Cry wins from node v (i.e., there is a path for Cry to a leaf).
 *     - B[v]: All paths from v reach only red or leaf nodes (i.e., River cannot win from here if he plays optimally).
 *   - Maintain counters for non-red children, and red children during updates.
 *   - BFS/DFS on reverse graph to propagate changes when updating node color to red.
 *
 * Time Complexity:
 *   O(n + m + q) per test case in total amortized time due to efficient updates and propagation.
 * Space Complexity:
 *   O(n + m) for storing the graph and auxiliary arrays.
 */

import java.io.BufferedInputStream
import java.lang.StringBuilder
import java.util.ArrayDeque

private class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    private fun readByte(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }
    fun nextInt(): Int {
        var c = readByte()
        while (c <= 32 && c >= 0) c = readByte()
        var sign = 1
        if (c == '-'.code) { sign = -1; c = readByte() }
        var res = 0
        while (c > 32) {
            res = res * 10 + (c - '0'.code)
            c = readByte()
        }
        return res * sign
    }
}

fun main() {
    val fs = FastScanner()
    val t = fs.nextInt()
    val out = StringBuilder()
    repeat(t) {
        val n = fs.nextInt()
        val m = fs.nextInt()
        val q = fs.nextInt()
        val from = IntArray(m)
        val to = IntArray(m)
        val outDeg = IntArray(n)
        val inDegRev = IntArray(n)
        for (i in 0 until m) {
            val u = fs.nextInt() - 1
            val v = fs.nextInt() - 1
            from[i] = u
            to[i] = v
            outDeg[u]++
            inDegRev[v]++
        }
        val adj = Array(n) { IntArray(0) }
        val rev = Array(n) { IntArray(0) }
        for (i in 0 until n) adj[i] = IntArray(outDeg[i])
        for (i in 0 until n) rev[i] = IntArray(inDegRev[i])
        val posOut = IntArray(n)
        val posIn = IntArray(n)
        for (i in 0 until m) {
            val u = from[i]
            val v = to[i]
            adj[u][posOut[u]++] = v
            rev[v][posIn[v]++] = u
        }
        val indeg = IntArray(n)
        for (i in 0 until m) indeg[to[i]]++
        val dqTopo = ArrayDeque<Int>()
        for (i in 0 until n) if (indeg[i] == 0) dqTopo.add(i)
        val topo = IntArray(n)
        var ti = 0
        while (dqTopo.isNotEmpty()) {
            val v = dqTopo.removeFirst()
            topo[ti++] = v
            for (w in adj[v]) {
                indeg[w]--
                if (indeg[w] == 0) dqTopo.add(w)
            }
        }
        val red = BooleanArray(n) 
        val A = BooleanArray(n)   
        val B = BooleanArray(n)   
        val countNonRed = IntArray(n) 
        val numRedChildren = IntArray(n) 
        val countNonRedTrueA = IntArray(n) 
        val numGood = IntArray(n) 
        for (i in 0 until n) {
            countNonRed[i] = outDeg[i]
            numRedChildren[i] = 0
        }
        for (idx in n - 1 downTo 0) {
            val v = topo[idx]
            if (outDeg[v] == 0) {
                A[v] = true
                B[v] = true
                countNonRedTrueA[v] = 0
                numGood[v] = 0
            } else {
                var ca = 0
                var gb = 0
                for (w in adj[v]) {
                    if (A[w]) ca++
                    if (B[w] && !red[w]) gb++
                }
                countNonRedTrueA[v] = ca
                numGood[v] = gb
                A[v] = (numGood[v] > 0)
                B[v] = (numRedChildren[v] == 0 && countNonRedTrueA[v] == countNonRed[v])
            }
        }
        val queue = ArrayDeque<Int>()
        for (qi in 0 until q) {
            val type = fs.nextInt()
            val u = fs.nextInt() - 1
            if (type == 1) {
                if (red[u]) {
                } else {
                    val oldA = A[u]
                    val oldB = B[u]
                    red[u] = true
                    A[u] = false
                    B[u] = false
                    for (p in rev[u]) {
                        countNonRed[p]--
                        numRedChildren[p]++
                        if (oldA) countNonRedTrueA[p]--
                        if (oldB) numGood[p]--
                        queue.add(p)
                    }
                    while (queue.isNotEmpty()) {
                        val v = queue.removeFirst()
                        val prevA = A[v]
                        val prevB = B[v]
                        val newA: Boolean
                        val newB: Boolean
                        if (red[v]) {
                            newA = false
                            newB = false
                        } else if (outDeg[v] == 0) {
                            newA = true
                            newB = true
                        } else {
                            newA = (numGood[v] > 0)
                            newB = (numRedChildren[v] == 0 && countNonRedTrueA[v] == countNonRed[v])
                        }
                        if (newA == prevA && newB == prevB) continue
                        val deltaA = (if (newA) 1 else 0) - (if (prevA) 1 else 0)
                        val deltaB = (if (newB) 1 else 0) - (if (prevB) 1 else 0)
                        A[v] = newA
                        B[v] = newB
                        if (deltaA != 0 || deltaB != 0) {
                            for (p in rev[v]) {
                                if (deltaA != 0) countNonRedTrueA[p] += deltaA
                                if (deltaB != 0) numGood[p] += deltaB
                                queue.add(p)
                            }
                        }
                    }
                }
            } else {
                out.append(if (A[u]) "YES\n" else "NO\n")
            }
        }
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/