// Problem: CF 2141 D - Avoid Minimums
// https://codeforces.com/contest/2141/problem/D

/*
 * Problem: D. Avoid Minimums
 * Purpose: Given an array of integers and a limited number of operations (increase elements),
 *          determine the maximum coins that can be earned by making all elements equal,
 *          where increasing an element greater than current minimum yields one coin.
 *
 * Algorithm:
 *   - For each test case, calculate what value all elements should be increased to.
 *   - Use binary search or direct calculation to find optimal target value.
 *   - Compute how many operations are needed and how many coins can be earned.
 *
 * Time Complexity: O(n) per test case (linear scan for sum, min, max)
 * Space Complexity: O(n) for storing the array
 */

import java.io.BufferedInputStream

private class F {
    private val i = BufferedInputStream(System.`in`)
    
    fun ni(): Int {
        var c = i.read()
        while (c <= 32) c = i.read() // Skip whitespace
        var s = 1
        if (c == 45) { // Handle negative sign
            s = -1
            c = i.read()
        }
        var r = 0
        while (c > 32) {
            r = r * 10 + (c - 48) // Convert digit to number
            c = i.read()
        }
        return r * s
    }
    
    fun nl(): Long {
        var c = i.read()
        while (c <= 32) c = i.read() // Skip whitespace
        var s = 1L
        if (c == 45) { // Handle negative sign
            s = -1
            c = i.read()
        }
        var r = 0L
        while (c > 32) {
            r = r * 10 + (c - 48) // Convert digit to number
            c = i.read()
        }
        return r * s
    }
}

fun main() {
    val f = F()
    val t = f.ni()
    val o = StringBuilder()
    
    repeat(t) {
        val n = f.ni()
        val k = f.nl()
        val a = LongArray(n)
        var s = 0L
        var mn = Long.MAX_VALUE
        var mx = Long.MIN_VALUE
        
        // Read input array and compute sum, min, max
        for (i in 0 until n) {
            val v = f.nl()
            a[i] = v
            s += v
            if (v < mn) mn = v
            if (v > mx) mx = v
        }
        
        // Calculate target value if all elements should be equal
        val T = (k + s) / n
        
        // If even the minimal possible target is too high to achieve, impossible
        if (T < mx) {
            o.append("-1\n")
            return@repeat
        }
        
        // If current minimum is already equal to target, no coins can be earned
        if (T == mn) {
            o.append("0\n")
            return@repeat
        }
        
        // Calculate how many elements are at the minimum value
        var c = 0
        for (v in a) if (v == mn) c++
        
        // Subtract contribution of minimum values from total sum
        val g = s - mn * c
        val cg = n - c
        
        // Optimal calculation for maximum coins
        val ans = cg.toLong() * T - g + (c - 1).toLong() * (T - mn - 1)
        o.append(ans).append('\n')
    }
    
    print(o.toString())
}


// https://github.com/VaHiX/codeForces/