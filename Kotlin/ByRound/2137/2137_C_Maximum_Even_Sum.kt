// Problem: CF 2137 C - Maximum Even Sum
// https://codeforces.com/contest/2137/problem/C

/*
C. Maximum Even Sum
Time Complexity: O(1) per test case
Space Complexity: O(1)

Algorithms/Techniques:
- Mathematical analysis of parity (odd/even properties)
- Finding optimal k such that a+b becomes even and maximized
- Analyzing powers of 2 in b to determine divisibility conditions
- Case-based logic for different parities of a and b

The problem involves choosing an integer k such that b is divisible by k,
then updating a = a * k and b = b / k to maximize a + b while ensuring it's even.
We analyze cases based on whether a and b are odd or even, considering how many
factors of 2 are in b (i.e., the power of 2 dividing b).
*/

import java.io.BufferedInputStream
import java.lang.StringBuilder

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
    
    fun nextLong(): Long {
        var c = read()
        while (c <= 32 && c >= 0) c = read()
        var sign = 1
        if (c == '-'.code) {
            sign = -1
            c = read()
        }
        var res = 0L
        while (c > 32) {
            res = res * 10 + (c - '0'.code)
            c = read()
        }
        return res * sign
    }
    
    fun nextInt(): Int = nextLong().toInt()
}

fun main() {
    val fs = FastScanner()
    val t = fs.nextInt()
    val out = StringBuilder()
    
    repeat(t) {
        val a = fs.nextLong()
        val b = fs.nextLong()
        
        var tmp = b
        var s = 0
        
        // Count how many factors of 2 are in b
        while (tmp % 2L == 0L) {
            s++
            tmp /= 2L
        }
        
        var ans = -1L
        
        if (a % 2L == 0L) { // a is even
            if (s == 0) {
                // b has no factor of 2 => b is odd
                // So a+b can never be even since a is even and b is odd
                ans = -1L
            } else {
                // b is even => we can make a+b even
                val c1 = a + b
                if (c1 % 2L == 0L) ans = maxOf(ans, c1)
                
                val half = b / 2L
                val c2 = a * half + 2L
                if (c2 % 2L == 0L) ans = maxOf(ans, c2)
            }
        } else { // a is odd
            if (s == 0) {
                // b has no factor of 2 => b is odd
                val c1 = a + b
                if (c1 % 2L == 0L) ans = maxOf(ans, c1)
                
                val c2 = a * b + 1L
                if (c2 % 2L == 0L) ans = maxOf(ans, c2)
            } else if (s == 1) {
                // b has exactly one factor of 2 => b is even but not divisible by 4
                ans = -1L
            } else {
                // b is divisible by 4 or more
                val half = b / 2L
                val c1 = a * 2L + half
                if (c1 % 2L == 0L) ans = maxOf(ans, c1)
                
                val c2 = a * half + 2L
                if (c2 % 2L == 0L) ans = maxOf(ans, c2)
            }
        }
        
        out.append(ans).append('\n')
    }
    
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/