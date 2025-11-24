// Problem: CF 2121 H - Ice Baby
// https://codeforces.com/contest/2121/problem/H

/*
 * Problem: H. Ice Baby
 * Algorithm: Segment Tree with Coordinate Compression
 * Purpose: For each k from 1 to n, find the maximum length of the longest non-decreasing subsequence among all arrays of length k where each element a[i] satisfies l[i] <= a[i] <= r[i].
 * 
 * Key Techniques:
 * - Coordinate compression on ranges [l[i], r[i]]
 * - Segment tree with range updates and queries for tracking max values
 * - Binary search for mapping compressed coordinates
 * 
 * Time Complexity: O(n^2 log n) per test case due to segment tree operations and nested loops.
 * Space Complexity: O(n) for storing arrays, segment tree, and coordinate compression.
 */

import java.io.DataInputStream
import java.io.ByteArrayOutputStream

fun main() {
    val din = DataInputStream(System.`in`)
    val buf = ByteArray(1 shl 16)
    var bufLen = 0
    var bufPos = 0
    fun readByte(): Int {
        if (bufPos >= bufLen) {
            bufLen = din.read(buf)
            bufPos = 0
            if (bufLen <= 0) return -1
        }
        return buf[bufPos++].toInt()
    }
    fun nextLong(): Long {
        var c = readByte()
        while (c <= ' '.code && c != -1) c = readByte()
        var sign = 1L
        if (c == '-'.code) {
            sign = -1L
            c = readByte()
        }
        var x = 0L
        while (c > ' '.code) {
            x = x * 10 + (c - '0'.code)
            c = readByte()
        }
        return x * sign
    }
    fun nextInt() = nextLong().toInt()
    val t = nextInt()
    val sb = StringBuilder()
    repeat(t) {
        val n = nextInt()
        val leftArr = LongArray(n)
        val rightArr = LongArray(n)
        for (i in 0 until n) {
            leftArr[i] = nextLong()
            rightArr[i] = nextLong()
        }
        // Coordinate compression
        val compressed = leftArr.toMutableList().apply { sort() }.distinct()
        val m = compressed.size
        val st = SegmentTree(m)
        val ans = IntArray(n)
        for (i in 0 until n) {
            val pL = compressed.binarySearch(leftArr[i]).let { if (it < 0) -it - 1 else it }
            val pR = compressed.binarySearch(rightArr[i]).let { if (it < 0) -it - 2 else it }
            if (pR >= pL) {
                st.rangeAdd(pL, pR, 1)
            }
            // Find maximum value among previous positions
            val bestBefore = if (pL > 0) st.rangeMax(0, pL - 1) else 0
            val needed = bestBefore + 1
            val current = st.pointQuery(pL)
            if (needed > current) {
                st.rangeAdd(pL, pL, needed - current)
            }
            ans[i] = st.rangeMax(0, m - 1)
        }
        ans.forEachIndexed { idx, v ->
            if (idx > 0) sb.append(' ')
            sb.append(v)
        }
        sb.append('\n')
    }
    print(sb.toString())
}

class SegmentTree(val size: Int) {
    private val tree = IntArray(size * 4)
    private val lazy = IntArray(size * 4)
    
    // Apply value to node
    private fun apply(node: Int, v: Int) {
        tree[node] += v
        lazy[node] += v
    }
    
    // Push lazy propagation down
    private fun push(node: Int) {
        val v = lazy[node]
        if (v != 0) {
            val l = node * 2
            val r = l + 1
            apply(l, v)
            apply(r, v)
            lazy[node] = 0
        }
    }
    
    // Update range with value 'v'
    private fun update(node: Int, l: Int, r: Int, ql: Int, qr: Int, v: Int) {
        if (ql > r || qr < l) return
        if (ql <= l && r <= qr) {
            apply(node, v)
            return
        }
        push(node)
        val mid = (l + r) ushr 1
        update(node * 2, l, mid, ql, qr, v)
        update(node * 2 + 1, mid + 1, r, ql, qr, v)
        tree[node] = maxOf(tree[node * 2], tree[node * 2 + 1])
    }
    
    // Query maximum in range [ql, qr]
    private fun query(node: Int, l: Int, r: Int, ql: Int, qr: Int): Int {
        if (ql > r || qr < l) return 0
        if (ql <= l && r <= qr) return tree[node]
        push(node)
        val mid = (l + r) ushr 1
        return maxOf(
            query(node * 2, l, mid, ql, qr),
            query(node * 2 + 1, mid + 1, r, ql, qr)
        )
    }
    
    fun rangeAdd(l: Int, r: Int, v: Int) = update(1, 0, size - 1, l, r, v)
    fun rangeMax(l: Int, r: Int) = if (l > r) 0 else query(1, 0, size - 1, l, r)
    fun pointQuery(pos: Int) = query(1, 0, size - 1, pos, pos)
}


// https://github.com/VaHiX/CodeForces/