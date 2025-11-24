// Problem: CF 2117 H - Incessant Rain
// https://codeforces.com/contest/2117/problem/H

/**
 * Problem: Incessant Rain
 * 
 * Purpose: This solution efficiently handles updates to an array and answers queries about 
 * the maximum k such that there exists a subarray where some element appears at least 
 * floor(|b|+1)/2 + k times.
 * 
 * Algorithm:
 * - Uses a treap-based data structure to maintain frequency information in a dynamic way.
 * - Each unique element in the original array is mapped to a treap storing positions with 
 *   transformed values to help determine k-majority.
 * - For each query, we update the treaps and recompute k values.
 * 
 * Time Complexity: O(n log n + q log n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Treap with lazy propagation
 * - TreeMap for frequency counting
 * - Coordinate compression via transformation (position - 2 * rank)
 */
import java.io.BufferedInputStream
import java.util.TreeMap
import java.util.Random
import kotlin.math.max
import kotlin.math.min
private const val POOL = 1_200_000
private val L = IntArray(POOL)
private val R = IntArray(POOL)
private val SZ = IntArray(POOL)
private val P = IntArray(POOL)
private val PRI = IntArray(POOL)
private val V = IntArray(POOL)
private val MX = IntArray(POOL)
private val MN = IntArray(POOL)
private val BEST = IntArray(POOL)
private val LZ = IntArray(POOL)
private var pc = 0
private val rng = Random()
private fun rnd(): Int = (rng.nextInt() shl 16) xor rng.nextInt()
private fun newNd(pos: Int, val0: Int): Int {
    val id = pc++
    L[id] = -1
    R[id] = -1
    SZ[id] = 1
    P[id] = pos
    PRI[id] = rnd()
    V[id] = val0
    MX[id] = val0
    MN[id] = val0
    BEST[id] = 0
    LZ[id] = 0
    return id
}
private fun apply(t: Int, d: Int) {
    if (t == -1) return
    V[t] += d
    MX[t] += d
    MN[t] += d
    LZ[t] += d
}
private fun pull(t: Int) {
    var s = 1
    var mx = V[t]
    var mn = V[t]
    var best = 0
    val l = L[t]
    val r = R[t]
    if (l != -1) {
        s += SZ[l]
        mx = max(mx, MX[l])
        mn = min(mn, MN[l])
        best = max(best, BEST[l])
    }
    if (l != -1) best = max(best, MX[l] - V[t])
    var mxL = V[t]
    if (l != -1) mxL = max(mxL, MX[l])
    if (r != -1) {
        s += SZ[r]
        mx = max(mx, MX[r])
        mn = min(mn, MN[r])
        best = max(best, BEST[r])
        best = max(best, mxL - MN[r])
    }
    SZ[t] = s
    MX[t] = mx
    MN[t] = mn
    BEST[t] = best
}
private fun push(t: Int) {
    if (t != -1 && LZ[t] != 0) {
        val v = LZ[t]
        apply(L[t], v)
        apply(R[t], v)
        LZ[t] = 0
    }
}
private fun merge(a: Int, b: Int): Int {
    if (a == -1 || b == -1) return if (a != -1) a else b
    return if (PRI[a] < PRI[b]) {
        push(a)
        R[a] = merge(R[a], b)
        pull(a)
        a
    } else {
        push(b)
        L[b] = merge(a, L[b])
        pull(b)
        b
    }
}
private fun split(t: Int, key: Int): Pair<Int, Int> {
    if (t == -1) return -1 to -1
    push(t)
    return if (P[t] < key) {
        val (l1, r1) = split(R[t], key)
        R[t] = l1
        pull(t)
        t to r1
    } else {
        val (l1, r1) = split(L[t], key)
        L[t] = r1
        pull(t)
        l1 to t
    }
}
private class FastScanner {
    private val buf = ByteArray(1 shl 16)
    private val `in` = BufferedInputStream(System.`in`)
    private var len = 0
    private var ptr = 0
    private fun readByte(): Int {
        if (ptr >= len) {
            len = `in`.read(buf)
            ptr = 0
            if (len <= 0) return -1
        }
        return buf[ptr++].toInt()
    }
    fun nextInt(): Int {
        var c: Int
        do {
            c = readByte()
        } while (c <= 32 && c >= 0)
        var sign = 1
        var num = 0
        if (c == '-'.code) {
            sign = -1
            c = readByte()
        }
        while (c > 32 && c >= 0) {
            num = num * 10 + (c - '0'.code)
            c = readByte()
        }
        return num * sign
    }
}
private fun addFreq(map: TreeMap<Int, Int>, v: Int) {
    map[v] = (map[v] ?: 0) + 1
}
private fun remFreq(map: TreeMap<Int, Int>, v: Int) {
    val c = map[v] ?: return
    if (c == 1) map.remove(v) else map[v] = c - 1
}
private fun process(scanner: FastScanner, out: StringBuilder) {
    val n = scanner.nextInt()
    val q = scanner.nextInt()
    val a = IntArray(n + 1)
    for (i in 1..n) a[i] = scanner.nextInt()
    pc = 0
    val root = IntArray(n + 1) { -1 }
    val curK = IntArray(n + 1)
    val posList = Array(n + 1) { mutableListOf<Int>() }
    val multiset = TreeMap<Int, Int>()
    repeat(n) { addFreq(multiset, 0) }
    for (i in 1..n) posList[a[i]].add(i)
    for (x in 1..n) {
        if (posList[x].isEmpty()) continue
        val lst = posList[x]
        for (idx in lst.indices) {
            val p = lst[idx]
            val f = p - 2 * (idx + 1)
            val nd = newNd(p, f)
            root[x] = merge(root[x], nd)
        }
        val m = BEST[root[x]] + 1
        val k = m shr 1
        remFreq(multiset, curK[x])
        curK[x] = k
        addFreq(multiset, k)
    }
    val ans = IntArray(q)
    for (qq in 0 until q) {
        val i = scanner.nextInt()
        val xn = scanner.nextInt()
        val xo = a[i]
        if (xo != xn) {
            remFreq(multiset, curK[xo])
            var l: Int
            var m: Int
            var r: Int
            var pair = split(root[xo], i)
            l = pair.first
            m = pair.second
            pair = split(m, i + 1)
            m = pair.first
            r = pair.second
            apply(r, 2)
            root[xo] = merge(l, r)
            val m1 = if (root[xo] != -1) BEST[root[xo]] + 1 else 0
            val k1 = m1 shr 1
            curK[xo] = k1
            addFreq(multiset, k1)
            remFreq(multiset, curK[xn])
            pair = split(root[xn], i)
            val l2 = pair.first
            val r2 = pair.second
            apply(r2, -2)
            val idx = if (l2 != -1) SZ[l2] else 0
            val f2 = i - 2 * (idx + 1)
            val nd = newNd(i, f2)
            root[xn] = merge(merge(l2, nd), r2)
            val m2 = BEST[root[xn]] + 1
            val k2 = m2 shr 1
            curK[xn] = k2
            addFreq(multiset, k2)
            a[i] = xn
        }
        ans[qq] = multiset.lastKey()
    }
    for (v in ans) out.append(v).append(' ')
    out.append('\n')
}
fun main() {
    val scanner = FastScanner()
    val sb = StringBuilder()
    val t = scanner.nextInt()
    repeat(t) { process(scanner, sb) }
    print(sb.toString())
}


// https://github.com/VaHiX/CodeForces/