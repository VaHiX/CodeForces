// Problem: CF 2148 F - Gravity Falls
// https://codeforces.com/contest/2148/problem/F

/*
F. Gravity Falls
Algorithms/Techniques: Greedy, Priority Queue, Sorting by Suffix Comparison

Time Complexity: O(S * log n) where S is the sum of all array lengths.
Space Complexity: O(S)

The goal is to find the lexicographically smallest bottom row after stacking arrays and applying gravity.
We process elements from left to right. For each position, we try to select an array that currently has
the smallest element at this position among unused arrays, considering potential future changes due to gravity.
A priority queue is used to compare arrays based on their suffix starting from the current position.
We greedily choose the "best" available array for each column to place in the result.
*/

import java.io.BufferedInputStream
import java.lang.StringBuilder
import java.util.PriorityQueue
import kotlin.math.min

class FastScanner {
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
        val lists = ArrayList<IntArray>(n)
        var maxLen = 0
        for (i in 0 until n) {
            val k = fs.nextInt()
            val arr = IntArray(k)
            for (j in 0 until k) arr[j] = fs.nextInt()
            lists.add(arr)
            if (k > maxLen) maxLen = k
        }
        // Preprocess to group indices by their position in arrays
        val vec = Array(maxLen) { ArrayList<Int>() }
        for (i in lists.indices) {
            val k = lists[i].size
            for (j in 0 until k) vec[j].add(i)
        }
        val used = BooleanArray(n)
        val filled = BooleanArray(maxLen)
        val bottom = IntArray(maxLen)
        var pos = 0
        
        // Compare function to determine relative order of arrays based on suffix starting at position
        fun compareSuffix(i: Int, j: Int, curPos: Int): Int {
            val ai = lists[i]
            val aj = lists[j]
            val lim = min(ai.size, aj.size)
            var p = curPos
            while (p < lim) {
                val vi = ai[p]
                val vj = aj[p]
                if (vi != vj) return if (vi < vj) -1 else 1
                p++
            }
            return if (ai.size == aj.size) 0 else if (ai.size < aj.size) -1 else 1
        }
        
        while (pos < maxLen) {
            if (filled[pos]) { pos++; continue }
            val curPos = pos
            val pq = PriorityQueue<Int> { a, b -> compareSuffix(a, b, curPos) }
            
            // Add all unused arrays that contribute to current position to priority queue
            for (idx in vec[curPos]) {
                if (!used[idx]) pq.add(idx)
            }
            
            if (pq.isEmpty()) {
                pos++
                continue
            }
            
            var selected = -1
            
            // Pick best available array from PQ and check if it's not already used
            while (pq.isNotEmpty()) {
                val cand = pq.poll()
                if (!used[cand]) { selected = cand; break }
            }
            
            if (selected == -1) { pos++; continue }
            
            val selArr = lists[selected]
            var j = curPos
            
            // Fill bottom array with values from selected array, moving forward
            while (j < selArr.size) {
                if (!filled[j]) {
                    bottom[j] = selArr[j]
                    filled[j] = true
                }
                j++
            }
            
            used[selected] = true
            
            // Advance pos to next unfilled position
            while (pos < maxLen && filled[pos]) pos++
        }
        
        var last = maxLen
        
        // Find last filled position
        while (last > 0 && !filled[last - 1]) last--
        
        if (last == 0) {
            out.append("\n")
        } else {
            for (i in 0 until last) {
                if (i > 0) out.append(' ')
                out.append(bottom[i])
            }
            out.append('\n')
        }
    }
    print(out.toString())
}


// https://github.com/VaHiX/CodeForces/