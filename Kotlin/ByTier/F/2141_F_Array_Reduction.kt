// Problem: CF 2141 F - Array Reduction
// https://codeforces.com/contest/2141/problem/F

/*
F. Array Reduction

Algorithm:
This problem involves minimizing the number of operations to reduce an array to a specific size.
Each operation allows removing elements such that either:
1. All elements removed are equal (e.g., all 5s),
2. No two elements removed are equal (e.g., one 1, one 2, one 3).

This leads to the insight that for each possible number of operations tOps, we compute how many elements can be reduced (i.e., removed) 
using a greedy strategy: use as few operations as possible by combining multiple elements into one operation.

Key idea:
1. Count frequencies of all elements.
2. Sort the frequencies in descending order.
3. For each potential number of operations (tOps), compute how many elements we can remove optimally.
4. Use prefix sums and dynamic programming approach to find optimal removal strategy.
5. Binary search on final results for required output format.

Time Complexity: O(n log n) per test case due to sorting and operations on frequency array
Space Complexity: O(n) for storing frequencies, prefix sums, and other helper arrays

*/
import java.io.BufferedInputStream
import java.io.InputStream
import java.lang.StringBuilder
import java.util.Arrays

private class FastScanner(private val input: InputStream = BufferedInputStream(System.`in`)) {
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
        var sgn = 1
        if (c == '-'.code) {
            sgn = -1
            c = readByte()
        }
        var res = 0
        while (c > 32) {
            res = res * 10 + (c - '0'.code)
            c = readByte()
        }
        return if (sgn == 1) res else -res
    }
}

fun main() {
    val fs = FastScanner()
    val t = fs.nextInt()
    val out = StringBuilder()
    
    repeat(t) {
        val n = fs.nextInt()
        val cnt = IntArray(n + 1) // count of frequency for each value in [1, n]
        
        for (i in 0 until n) {
            val x = fs.nextInt()
            cnt[x]++
        }
        
        var k = 0
        val freq = IntArray(n) // frequencies array (excluding zeros)
        
        for (v in 1..n) {
            if (cnt[v] > 0) {
                freq[k++] = cnt[v]
            }
        }
        
        Arrays.sort(freq, 0, k) // sort frequencies descending
        
        val pref = LongArray(k + 1) // prefix sum of freq array
        
        for (i in 1..k) {
            val fi = freq[k - i]  // take from back because sorted descending
            pref[i] = pref[i - 1] + fi.toLong()
        }
        
        val maxF = if (k == 0) 0 else freq[k - 1]
        val M = LongArray(n + 1) // minimum elements we can remove with up to U operations
        
        var p = k
        var bestAll = Int.MAX_VALUE
        
        for (tOps in 0..maxF) {
            while (p > 0 && freq[k - p] <= tOps) p-- // decrease number of ops needed
            
            val pNow = p
            val tL = tOps.toLong()
            val S = n.toLong() - (pref[pNow] - tL * pNow.toLong()) // elements left after all operations
            
            var r = 0
            while (r <= pNow) {
                val U = tOps + r
                if (U <= n) {
                    val add = pref[r] - tL * r.toLong()
                    val candidate = S + add
                    if (candidate > M[U]) M[U] = candidate
                }
                r++
            }
            
            val h = tOps + pNow
            if (h < bestAll) bestAll = h
        }
        
        if (bestAll <= n) {
            for (u in bestAll..n) M[u] = n.toLong() // all operations valid up to full size
        }
        
        for (u in 1..n) if (M[u] < M[u - 1]) M[u] = M[u - 1] // monotonic increasing
        
        for (x in 0 until n) {
            val R = n - x // remaining elements after removal
            
            var lo = 1
            var hi = n
            while (lo < hi) {
                val mid = (lo + hi) ushr 1
                if (M[mid] >= R.toLong()) hi = mid else lo = mid + 1
            }
            out.append(lo).append(' ')
        }
        out.append('\n')
    }
    
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/