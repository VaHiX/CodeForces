// Problem: CF 2141 G - Good Robot Paths
// https://codeforces.com/contest/2141/problem/G

/*
 * Problem: G. Good Robot Paths
 * Purpose: Count the number of pairs of black points such that all points on any shortest path between them are also black.
 * 
 * Algorithm:
 *   1. For each point, compute the height H[i] = max height among points (x+1,y) in the array (after sorting).
 *      This is used to determine how many consecutive upward steps are required to build a valid sequence.
 *   2. Group consecutive points that form vertical chains of adjacent y-coordinates with same x-coordinate.
 *   3. Use a monotonic stack to calculate contribution of each group efficiently.
 * 
 * Time Complexity: O(n log n) due to sorting and linear traversal
 * Space Complexity: O(n) for storing elements, indices, and auxiliary arrays
 */


import java.io.BufferedInputStream

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
        while (c <= 32) {
            c = readByte()
            if (c == -1) return Int.MIN_VALUE
        }
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

data class P(val x: Int, val y: Int)

fun main() {
    val fs = FastScanner()
    val T = fs.nextInt()
    val out = StringBuilder()
    
    repeat(T) {
        val N = fs.nextInt()
        val A = Array(N) { P(fs.nextInt(), fs.nextInt()) }
        
        // Sort points lexicographically by x, then y
        java.util.Arrays.sort(A) { p1, p2 -> if (p1.x != p2.x) p1.x - p2.x else p1.y - p2.y }
        
        // Map to store index of each point for quick lookup
        val idx = HashMap<Long, Int>(N * 2)
        
        // Create a unique key for each point
        fun key(x: Int, y: Int): Long = (x.toLong() shl 32) xor (y.toLong() and 0xffffffffL)
        for (i in 0 until N) idx[key(A[i].x, A[i].y)] = i
        
        // Get index of point (x, y), else return -1
        fun getIdx(x: Int, y: Int): Int = idx[key(x, y)] ?: -1
        
        // Compute maximum height H[i] for each point based on next valid x+1,y point in sorted array
        val H = IntArray(N)
        for (i in N - 1 downTo 0) {
            val x = A[i].x
            val y = A[i].y
            val j = getIdx(x + 1, y)
            H[i] = if (j == -1) 1 else H[j] + 1
        }

        // Calculate contribution using monotonic stack approach
        fun F(B: IntArray): Long {
            val n = B.size
            var ans = 0L
            var sm = 0L
            
            // Monotonic stack to store values and their counts
            val stA = ArrayDeque<Long>()
            val stK = ArrayDeque<Long>()
            
            for (i in 0 until n) {
                val b = B[i].toLong()
                var cnt = 1L
                
                // Maintain monotonic property from right to left
                while (stA.isNotEmpty()) {
                    val a: Long = stA.last()
                    val k: Long = stK.last()
                    if (a >= b) {
                        stA.removeLast()
                        stK.removeLast()
                        sm -= a * k
                        cnt = cnt + k
                    } else break
                }
                
                stA.addLast(b)
                stK.addLast(cnt)
                sm += b * cnt
                ans += sm - b 
            }
            
            // Final adjustments
            ans *= 2
            ans -= 1L * n * (n - 1) / 2 
            for (x in B) ans += (x - 1)
            return ans
        }

        var L = 0
        var ANS = 0L
        
        // Iterate through vertical chains of points with consecutive y-values at fixed x
        while (L < N) {
            var R = L + 1
            while (R < N && A[R - 1].x == A[R].x && A[R - 1].y + 1 == A[R].y) R++
            
            // Process current chain as an array B of heights
            val B = IntArray(R - L) { H[L + it] } 
            ANS += F(B)
            L = R
        }
        
        ANS += ANS   // Double the result according to final output rule
        out.append(ANS).append('\n')
    }
    
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/