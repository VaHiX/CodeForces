// Problem: CF 2011 H - Strange Matrix
// https://codeforces.com/contest/2011/problem/H

/*
 * H. Strange Matrix
 *
 * Problem: Given a matrix of size n x m with values from 0 to 31, determine the minimum cost to make it "strange".
 * A matrix is strange if for any two rows i and j:
 *   1. For every subset of k columns, the bitwise AND of elements in those positions is 0.
 *   2. For every subset of k columns, the bitwise OR of elements in those positions is 31.
 *
 * Techniques Used:
 *   - Bit manipulation
 *   - Strongly Connected Components (SCC) using Kosaraju's algorithm
 *   - 2-SAT reduction
 *   - Greedy selection of SCC components to minimize cost
 *
 * Time Complexity: O(n^2 * m + n * m * log(32))
 * Space Complexity: O(n * m)
 */

import java.io.*
import java.io.BufferedInputStream
import java.io.PrintWriter
import java.util.*
import kotlin.math.*

object io {
    private const val BS = 1 shl 16
    private const val NC = 0.toChar()
    private val buf = ByteArray(BS)
    private var bId = 0
    private var size = 0
    private var c = NC
    private var IN: BufferedInputStream = BufferedInputStream(System.`in`, BS)
    val OUT: PrintWriter = PrintWriter(System.out)
    private val char: Char
        get() {
            while (bId == size) {
                size = IN.read(buf)
                if (size == -1) return NC
                bId = 0
            }
            return buf[bId++].toChar()
        }
    fun nextint(): Int {
        return nextlong().toInt()
    }
    fun nextlong(): Long {
        var neg = false
        if (c == NC) c = char
        while (c < '0' || c > '9') {
            if (c == '-') neg = true
            c = char
        }
        var res = 0L
        while (c in '0'..'9') {
            res = (res shl 3) + (res shl 1) + (c - '0')
            c = char
        }
        return if (neg) -res else res
    }
    fun nextstring(): String {
        val ret = StringBuilder()
        while (true) {
            c = char
            if (!iswhitespace(c)) {
                break
            }
        }
        ret.append(c)
        while (true) {
            c = char
            if (iswhitespace(c)) {
                break
            }
            ret.append(c)
        }
        return ret.toString()
    }
    fun iswhitespace(c: Char): Boolean {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t'
    }
    fun put(aa: Any) {
        io.OUT.print(aa)
    }
    fun done() {
        io.OUT.close()
    }
}

var inn: MutableList<MutableList<Int>> = mutableListOf()
var outt: MutableList<MutableList<Int>> = mutableListOf()
var scc: MutableList<MutableList<Int>> = mutableListOf()
var visited: MutableList<Boolean> = mutableListOf()
var belong: MutableList<Int> = mutableListOf()
var st = Stack<Int>()

fun dfs1(cur: Int) {
    visited[cur] = true
    for (i in outt[cur]) {
        if (!visited[i]) {
            dfs1(i)
        }
    }
    st.push(cur)
}

fun dfs2(cur: Int) {
    visited[cur] = true
    scc[scc.size - 1].add(cur)
    belong[cur] = scc.size
    for (i in inn[cur]) {
        if (!visited[i]) {
            dfs2(i)
        }
    }
}

fun addedge(u: Int, v: Int) {
    outt[u].add(v)
    inn[v].add(u)
    outt[v].add(u)
    inn[u].add(v)
}

fun solve() {
    var n = io.nextint()
    var m = io.nextint()
    var k = io.nextint()
    var a: MutableList<MutableList<Int>> = mutableListOf()
    for (i in 0..n) a.add(mutableListOf())
    for (i in 1..n) {
        a[i].add(0)
        for (j in 1..m) {
            var t = io.nextint()
            a[i].add(t)
        }
    }
    var ans = 0L
    for (b in 0..4) { // Loop over bits from 0 to 4 (since values are up to 31)
        var mask = LongArray(n + 1) // Each row represented as a bitmask of columns where the bit is set
        for (i in 1..n) {
            mask[i] = 0L
            for (j in 1..m) {
                var tp = (1 shl b)
                if (a[i][j] and tp > 0) {
                    mask[i] += (1L shl (j - 1)) // Set the bit corresponding to column index in mask
                }
            }
        }
        
        inn.clear()
        outt.clear()
        scc.clear()
        visited.clear()
        belong.clear()

        for (i in 0..2 * n) {
            inn.add(mutableListOf())
            outt.add(mutableListOf())
            visited.add(false)
            belong.add(0)
        }
        
        // Build implication graph for 2-SAT
        for (i in 1..n) {
            for (j in i + 1..n) {
                var notswap = 1
                if (
                    (mask[i] and mask[j]).countOneBits() >= k ||
                    (((1L shl m) - 1L - mask[i]) and ((1L shl m) - 1L - mask[j])).countOneBits() >= k
                )
                    notswap = 0
                
                var okswap = 1
                if (
                    (mask[i] and ((1L shl m) - 1L - mask[j])).countOneBits() >= k ||
                    (mask[j] and ((1L shl m) - 1L - mask[i])).countOneBits() >= k
                )
                    okswap = 0
                
                if (notswap == 0 && okswap == 0) {
                    io.put("-1\n")
                    return
                }
                
                // Imply edge for 2-SAT representation
                if (okswap == 0) {
                    addedge(i, j)
                    addedge(i + n, j + n)
                }
                
                if (notswap == 0) {
                    addedge(i + n, j)
                    addedge(i, j + n)
                }
            }
        }
        
        // Kosaraju's algorithm to find SCCs
        for (i in 1..2 * n) {
            if (!visited[i]) {
                dfs1(i)
            }
        }
        
        for (i in 0..2 * n) visited[i] = false
        
        while (!st.empty()) {
            var tp = st.peek()
            st.pop()
            if (visited[tp]) continue
            scc.add(mutableListOf())
            dfs2(tp)
        }

        // Check if assignment is valid - no conflicting SCCs
        for (i in 1..n) {
            if (belong[i] == belong[i + n]) {
                io.put("-1\n")
                return
            }
        }

        var req = 0
        for (i in scc) {
            var lar = 0
            var sma = 0
            for (j in i) {
                if (j <= n) lar += 1 else sma += 1
            }
            req += minOf(lar, sma)
        }
        req /= 2 // Pairing required SCCs optimally
        ans += 1L * req * (1L shl b) // Accumulate cost from this bit
    }
    io.put(ans)
    io.put('\n')
}

fun main() {
    var t = 1
    t = io.nextint()
    for (i in 1..t) {
        solve()
    }
    io.done()
}


// https://github.com/VaHiX/codeForces/