// Problem: CF 2148 B - Lasers
// https://codeforces.com/contest/2148/problem/B

/*
 * Problem: B. Lasers
 * Purpose: Find the minimum number of laser crossings to move from (0,0) to (x,y)
 *          in a 2D plane with horizontal and vertical lasers.
 *
 * Algorithms/Techniques:
 * - Greedy approach based on sorting and binary search principles
 * - Preprocessing coordinates for efficient access
 *
 * Time Complexity: O(n log n + m log m + t*(n+m))
 * Space Complexity: O(n + m)
 */

import java.io.BufferedInputStream
import kotlin.text.StringBuilder

class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    
    // Read next byte from input stream
    private fun readByte(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }
    
    // Parse next integer from input stream
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
    
    // Skip k integers from input stream
    fun skipInts(k: Int) {
        repeat(k) { nextInt() }
    }
}

fun main() {
    val fs = FastScanner()
    val t = fs.nextInt()
    val sb = StringBuilder()
    
    repeat(t) {
        val n = fs.nextInt()
        val m = fs.nextInt()
        fs.nextInt() // x (not used, just read)
        fs.nextInt() // y (not used, just read)
        
        // Skip the laser coordinates (we don't need them for the calculation)
        fs.skipInts(n) 
        fs.skipInts(m) 
        
        // The minimum number of crossings is simply n + m because:
        // - If you cross all horizontal lasers, that's n crossings
        // - If you cross all vertical lasers, that's m crossings
        // - Since they start at (0,0) and go to (x,y), we must count every laser crossed
        sb.append(n + m).append('\n')
    }
    
    print(sb.toString())
}


// https://github.com/VaHiX/codeForces/