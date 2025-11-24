// Problem: CF 2137 B - Fun Permutation
// https://codeforces.com/contest/2137/problem/B

/*
B. Fun Permutation
Algorithms/Techniques: Greedy construction, permutation manipulation
Time Complexity: O(n) amortized over all test cases
Space Complexity: O(n) for input and output arrays

Given a permutation p of size n, we need to construct a permutation q such that 
GCD(p[i] + q[i], p[i+1] + q[i+1]) >= 3 for all valid i.
The solution constructs q by mapping each element p[i] to (n + 1) - p[i].
This guarantees that adjacent sums will be at least 3 due to the structure of the permutation.
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
    
    fun nextInt(): Int {
        var c = read()
        while (c <= 32 && c >= 0) c = read() // skip whitespace
        var sign = 1
        if (c == '-'.code) { sign = -1; c = read() } // handle negative
        var res = 0
        while (c > 32) {
            res = res * 10 + (c - '0'.code)
            c = read()
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
        val p = IntArray(n) { fs.nextInt() }
        for (i in 0 until n) {
            val q = (n + 1) - p[i] // mapping to ensure GCD condition
            out.append(q)
            if (i + 1 < n) out.append(' ')
        }
        out.append('\n')
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/