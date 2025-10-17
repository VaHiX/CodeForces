// Problem: CF 2137 F - Prefix Maximum Invariance
// https://codeforces.com/contest/2137/problem/F

/*
 * Problem: F. Prefix Maximum Invariance
 * 
 * Purpose:
 *   Given two arrays a and b of size n, compute the sum of f(a[l:r], b[l:r]) over all subarrays [l,r].
 *   Where f(x,y) is the maximum number of positions where z[i] = y[i] such that z has same prefix maxima as x.
 *   
 * Algorithm:
 *   - For each subarray [l,r], we compute how many elements in the prefix can be matched between b and valid z.
 *   - We use a monotonic stack to calculate for each position, the leftmost index where value is strictly less than current.
 *   - We maintain a segment tree to query maximum indices efficiently for values >= b[i].
 *   - The final formula counts for each element how many valid choices there are to match it with b[i] in z,
 *     using prefix max constraints and valid segment queries.
 *   
 * Time Complexity: O(n log n) per test case due to monotonic stack and segment tree operations
 * Space Complexity: O(n) for arrays and segment tree storage
 */

import java.io.BufferedInputStream
import kotlin.math.max
import kotlin.math.min

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
        if (c == '-'.code) {
            sign = -1
            c = readByte()
        }
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
        val a = IntArray(n + 1)
        val b = IntArray(n + 1)
        for (i in 1..n) a[i] = fs.nextInt()
        for (i in 1..n) b[i] = fs.nextInt()
        val left = IntArray(n + 1) // Stores index of previous element smaller than current for monotonic stack
        val stack = IntArray(n + 1)
        var top = 0
        for (i in 1..n) {
            while (top > 0 && a[stack[top - 1]] < a[i]) top-- // Pop elements from stack that are smaller than current
            left[i] = if (top == 0) 0 else stack[top - 1] // If stack is empty, no smaller previous element; else take last index
            stack[top++] = i // Push current index to stack
        }
        val maxVal = 2 * n // Max possible value for elements in arrays
        var base = 1
        while (base <= maxVal) base = base shl 1 // Build segment tree size as power of 2
        val seg = IntArray(base shl 1) // Segment tree to store indices
        
        // Update value at position pos to value in segment tree
        fun segUpdate(pos: Int, value: Int) {
            var idx = pos + base - 1
            seg[idx] = value
            idx = idx shr 1
            while (idx >= 1) { // Propagate update up the tree
                seg[idx] = max(seg[idx shl 1], seg[(idx shl 1) + 1])
                idx = idx shr 1
            }
        }
        
        // Query maximum value between l and r in segment tree
        fun segQuery(l: Int, r: Int): Int {
            if (l > r) return 0
            var L = l + base - 1
            var R = r + base - 1
            var res = 0
            while (L <= R) { // Traverse the tree to find max in interval
                if ((L and 1) == 1) { // If current node is a right child, process it
                    res = max(res, seg[L])
                    L++
                }
                if ((R and 1) == 0) { // If current node is a left child, process it
                    res = max(res, seg[R])
                    R--
                }
                L = L shr 1
                R = R shr 1
            }
            return res
        }

        var ans = 0L
        for (i in 1..n) {
            segUpdate(a[i], i) // Update segment tree with current a[i]
            val j = if (b[i] <= maxVal) segQuery(b[i], maxVal) else 0 // Find max index with value >= b[i]
            val leftGE = left[i] // Previous element smaller than current
            val countNonForced = min(leftGE, j) // Number of elements before i that can be matched without forcing
            val countForced = if (b[i] == a[i]) (i - leftGE) else 0 // If b[i] equals a[i], we must match from leftGE to i
            val validLefts = countNonForced + countForced
            ans += validLefts.toLong() * (n - i + 1).toLong() // Add to total sum multiplied by remaining suffix length
        }
        out.append(ans).append('\n')
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/