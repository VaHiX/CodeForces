// Problem: CF 2126 E - G-C-D, Unlucky!
// https://codeforces.com/contest/2126/problem/E

/*
 * Problem: E. G-C-D, Unlucky!
 * 
 * Purpose:
 *   Given two arrays p (prefix GCDs) and s (suffix GCDs), determine whether
 *   there exists an array a such that p[i] = gcd(a[0], ..., a[i]) and
 *   s[i] = gcd(a[i], ..., a[n-1]).
 * 
 * Algorithms/Techniques:
 *   - Use of Euclidean algorithm for GCD computation (O(log(min(a,b))))
 *   - Validation through checking consistency of prefix-suffix interactions
 *   - Preprocessing to compute combined GCDs across the array
 * 
 * Time Complexity:
 *   O(n * log(max(p[i], s[i]))) per test case, where n is the size of arrays.
 *   In worst case, each element in the arrays is processed with a logarithmic gcd operation.
 * 
 * Space Complexity:
 *   O(n) for the temporary arrays used to store hal (prefix GCDs) and tar (suffix GCDs).
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val skiff = BufferedReader(InputStreamReader(System.`in`))
    val barge = StringBuilder()
    val whiz = object {
        var tok = StringTokenizer("")
        fun zap(): String {
            while (!tok.hasMoreTokens()) {
                val line = skiff.readLine() ?: return ""
                tok = StringTokenizer(line)
            }
            return tok.nextToken()
        }
        fun pop() = zap().toInt()
    }
    
    // Euclidean algorithm for computing GCD
    fun gcdFun(a: Long, b: Long): Long {
        var x = a
        var y = b
        while (y != 0L) {
            val r = x % y
            x = y
            y = r
        }
        return x
    }
    
    var m = whiz.pop()
    while (m > 0) {
        m--
        val n = whiz.pop()
        val hal = LongArray(n) // Stores prefix GCD values
        val tar = LongArray(n) // Stores suffix GCD values
        
        // Read prefix GCDs
        var i = 0
        while (i < n) {
            hal[i] = whiz.pop().toLong()
            i++
        }
        
        // Read suffix GCDs
        i = 0
        while (i < n) {
            tar[i] = whiz.pop().toLong()
            i++
        }

        // Compute LCM of pairs (hal[i], tar[i])
        val bag = LongArray(n)
        i = 0
        while (i < n) {
            val g = gcdFun(hal[i], tar[i])
            bag[i] = (hal[i] / g) * tar[i]
            i++
        }

        // Main verification logic
        var flag = true
        var flow = bag[0]
        if (flow != hal[0]) flag = false  // check consistency with prefix GCDs
        i = 1
        while (flag && i < n) {
            flow = gcdFun(flow, bag[i])
            if (flow != hal[i]) flag = false  // maintain increasing prefix property via GCD
            i++
        }

        flow = bag[n - 1]
        if (flow != tar[n - 1]) flag = false  // check consistency with suffix GCDs
        i = n - 2
        while (flag && i >= 0) {
            flow = gcdFun(bag[i], flow)
            if (flow != tar[i]) flag = false  // maintain decreasing suffix property via GCD
            i--
        }

        barge.appendLine(if (flag) "Yes" else "No")
    }
    print(barge)
}


// https://github.com/VaHiX/CodeForces/