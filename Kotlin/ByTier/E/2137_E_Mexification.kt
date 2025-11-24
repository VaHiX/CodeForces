// Problem: CF 2137 E - Mexification
// https://codeforces.com/contest/2137/problem/E

/*
 * Problem: E. Mexification
 * Purpose: Given an array of size n and k operations, each operation replaces every element
 *          with the MEX (minimum excluded) of all other elements in the array.
 *          Return the sum of elements after k operations.
 *
 * Algorithms/Techniques:
 * - Fast input/output using BufferedInputStream and StringBuilder
 * - Cycle detection using HashMap to detect repeating states when k is large
 * - Efficient MEX computation with frequency counting
 * - Hashing for state comparison to detect cycles
 *
 * Time Complexity:
 *   O(n^2) per test case in worst-case (due to MEX computation), but due to cycle detection,
 *   the actual simulation stops early when a repeated state is found.
 *   Overall complexity is amortized much better than O(k*n).
 *
 * Space Complexity:
 *   O(n + k) for storing the array, frequency table, and the HashMap of seen states.
 */

import java.io.BufferedInputStream
import java.lang.StringBuilder
import kotlin.math.min

private class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    private fun read(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }
    fun nextInt(): Int {
        var c = read()
        while (c <= 32 && c >= 0) c = read()
        var sign = 1
        if (c == '-'.code) { sign = -1; c = read() }
        var res = 0
        while (c > 32) {
            res = res * 10 + (c - '0'.code)
            c = read()
        }
        return res * sign
    }
    fun nextLong(): Long = nextInt().toLong()
}

fun computeMexFromFreq(freq: IntArray): Int {
    var m = 0
    while (m < freq.size && freq[m] > 0) m++
    return m
}

fun hashArray(arr: IntArray): Long {
    var h = 1469598103934665603L 
    val P = 1000003L
    for (v in arr) {
        h = h * P + (v.toLong() + 1L) // Add 1 to avoid issues with zero values
    }
    return h
}

fun nextStep(curr: IntArray, n: Int): IntArray {
    val freq = IntArray(n + 2) // Frequency array for MEX computation
    for (v in curr) if (v <= n) freq[v]++ // Count occurrences of valid elements
    var mex = 0
    while (mex <= n && freq[mex] > 0) mex++ // Compute MEX of current set
    val next = IntArray(n)
    for (i in curr.indices) {
        val v = curr[i]
        // If element < mex and occurs only once, keep it; otherwise replace with mex
        next[i] = if (v < mex && freq[v] == 1) v else mex
    }
    return next
}

fun main() {
    val fs = FastScanner()
    val t = fs.nextInt()
    val out = StringBuilder()
    repeat(t) {
        val n = fs.nextInt()
        var k = fs.nextInt().toLong()
        var a = IntArray(n) { fs.nextInt() }
        if (k == 0L) {
            var s = 0L
            for (v in a) s += v.toLong()
            out.append(s).append('\n')
            return@repeat
        }
        val seen = HashMap<Long, Long>() // Store hash of state and the step it was seen at
        var step: Long = 0
        val initialHash = hashArray(a)
        seen[initialHash] = step
        var finished = false
        while (step < k) {
            val nxt = nextStep(a, n)
            step++
            val h = hashArray(nxt)
            if (seen.containsKey(h)) { // Detect cycle
                val prevStep = seen[h]!!
                val cycleLen = step - prevStep
                val remaining = (k - step) % cycleLen
                var cur = nxt
                val rem = remaining.toInt()
                for (r in 0 until rem) {
                    cur = nextStep(cur, n)
                }
                var s = 0L
                for (v in cur) s += v.toLong()
                out.append(s).append('\n')
                finished = true
                break
            } else {
                seen[h] = step
                a = nxt
                if (step == k) { // Reached exactly k steps
                    var s = 0L
                    for (v in a) s += v.toLong()
                    out.append(s).append('\n')
                    finished = true
                    break
                }
            }
        }
        if (!finished) {
            var s = 0L
            for (v in a) s += v.toLong()
            out.append(s).append('\n')
        }
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/