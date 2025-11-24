// Problem: CF 2151 E - Limited Edition Shop
// https://codeforces.com/contest/2151/problem/E

/*
 * Problem: E. Limited Edition Shop
 * Algorithm: Segment Tree with Lazy Propagation
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n) per test case
 *
 * Description:
 * We simulate a process where Alice and Bob buy objects in their preference order.
 * For each possible sequence of purchases, we compute the maximum sum of values
 * according to our own preferences for Alice's collected items.
 * 
 * This is solved using a segment tree with lazy propagation to efficiently track
 * max values and perform range updates and point queries.
 */

import java.io.BufferedInputStream
import java.lang.StringBuilder

private class FS {
    private val inb = BufferedInputStream(System.`in`)
    private val buf = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    private fun read(): Int {
        if (ptr >= len) { len = inb.read(buf); ptr = 0; if (len <= 0) return -1 }
        return buf[ptr++].toInt()
    }
    fun ni(): Int {
        var c = read()
        while (c <= 32) c = read()
        var s = 1
        if (c == '-'.code) { s = -1; c = read() }
        var x = 0
        while (c > 32) { x = x * 10 + (c - 48); c = read() }
        return x * s
    }
}

fun main() {
    val f = FS()
    val t = f.ni()
    val o = StringBuilder()
    val INF = 1_000_000_000_000_000_000L
    
    repeat(t) {
        val n = f.ni()
        val v = LongArray(n) { f.ni().toLong() } // Values of items
        val a = IntArray(n) { f.ni() } // Alice's preference order
        val b = IntArray(n) { f.ni() } // Bob's preference order
        
        // p[i] stores the index (1-based) of item i in Bob's preference list
        val p = IntArray(n + 1)
        for (i in 0 until n) p[b[i]] = i + 1
        
        // Build segment tree size as power of two
        var m = 1
        while (m < n + 2) m = m shl 1
        
        // Segment tree with lazy propagation
        val s = LongArray(m shl 1) { -INF } // Segment tree values
        val lz = LongArray(m) // Lazy propagation array

        // Update function for segment tree
        fun ad(i: Int, x: Long) {
            s[i] += x
            if (i < m) lz[i] += x
        }

        // Propagate lazy updates
        fun ps(i: Int) {
            val x = lz[i]
            if (x != 0L) { 
                ad(i shl 1, x); ad(i shl 1 or 1, x); lz[i] = 0 
            }
        }

        // Range update function
        fun ra(l: Int, r: Int, x: Long, i: Int = 1, lo: Int = 0, hi: Int = m) {
            if (r < lo || hi <= l) return
            if (l <= lo && hi <= r + 1) { ad(i, x); return }
            ps(i)
            val md = (lo + hi) ushr 1
            ra(l, r, x, i shl 1, lo, md)
            ra(l, r, x, i shl 1 or 1, md, hi)
            s[i] = if (s[i shl 1] > s[i shl 1 or 1]) s[i shl 1] else s[i shl 1 or 1]
        }

        // Point maximum query
        fun pm(r: Int, i: Int = 1, lo: Int = 0, hi: Int = m): Long {
            if (r < lo) return -INF
            if (hi <= r + 1) return s[i]
            ps(i)
            val md = (lo + hi) ushr 1
            return if (r < md) pm(r, i shl 1, lo, md)
            else {
                val L = s[i shl 1]
                val R = pm(r, i shl 1 or 1, md, hi)
                if (L > R) L else R
            }
        }

        // Point update function
        fun pu(pos: Int, x: Long) {
            var i = 1; var lo = 0; var hi = m
            while (i < m) {
                ps(i)
                val md = (lo + hi) ushr 1
                if (pos < md) { i = i shl 1; hi = md } else { i = i shl 1 or 1; lo = md }
            }
            if (x > s[i]) s[i] = x
            i = i shr 1
            while (i > 0) { 
                s[i] = if (s[i shl 1] > s[i shl 1 or 1]) s[i shl 1] else s[i shl 1 or 1]; i = i shr 1 
            }
        }

        // Initialize the root of the segment tree
        pu(0, 0)
        
        // Process each buy step in Alice's preference list
        for (k in 0 until n) {
            val o1 = a[k] // current item Alice wants to buy
            val q = p[o1] // position of this item in Bob's rank 
            val be = pm(q) // get the max value up to that point
            
            // Update the range [0, q - 1] with negative value of item
            if (q > 0) ra(0, q - 1, v[o1 - 1])
            
            // Update the position q with new best value
            pu(q, be)
        }
        
        // Final answer is the best possible outcome for Alice
        o.append(pm(n + 1)).append('\n')
    }
    print(o.toString())
}


// https://github.com/VaHiX/CodeForces/