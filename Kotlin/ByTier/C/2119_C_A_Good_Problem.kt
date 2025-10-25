// Problem: CF 2119 C - A Good Problem
// https://codeforces.com/contest/2119/problem/C

/**
 * Problem: C. A Good Problem
 *
 * Purpose: Find the k-th element of the lexicographically smallest array of length n,
 *          where each element is between l and r, and the bitwise AND of all elements
 *          equals the bitwise XOR of all elements.
 *
 * Algorithm:
 * - For special cases (n=1, n=2), return early with base logic.
 * - For odd n and k > n, no valid array exists → return -1.
 * - Otherwise, compute a value x such that it satisfies the constraint by adjusting bits
 *   to avoid conflicts in AND and XOR results.
 *
 * Time Complexity: O(1) per test case (since bit manipulation is bounded by 64 bits)
 * Space Complexity: O(1)
 */
fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val (n, l, r, k) = readLine()!!.split(" ").map { it.toULong() }
        println(solve(n, l, r, k))
    }
}

/**
 * Solves the problem for given parameters n, l, r, k.
 */
fun solve(n: ULong, l: ULong, r: ULong, k: ULong): String {
    if (n == 1UL) {
        return l.toString() // Only one element, return it directly
    }
    if (n.toInt() and 1 == 1) { 
        // If n is odd and k <= n, the solution exists; otherwise, no valid array
        return if (k <= n) l.toString() else "-1"
    }
    if (n == 2UL) {
        return "-1" // For n=2, no valid array can satisfy the constraint
    }
    
    val x = findX(n, l, r)
    return when {
        x > r -> "-1" // If computed x exceeds range [l,r], invalid
        k <= n - 2UL -> l.toString() // If k is small enough to allow first elements as l
        else -> x.toString() // Return computed value x
    }
}

/**
 * Finds a valid X that satisfies the constraints for AND = XOR.
 */
fun findX(n: ULong, l: ULong, r: ULong): ULong {
    var x = l
    while (true) {
        var ok = true
        // Check each bit from 0 to 63
        for (i in 0 until 64) {
            val bit = 1UL shl i
            if ((l and bit) != 0UL && (x and bit) != 0UL) {
                x += bit // Set the next higher bit
                x = x and (bit - 1UL).inv() // Clear all lower bits
                ok = false
                break
            }
        }
        if (ok) break // Break loop if no conflict found at any bit
    }
    return x
}


// https://github.com/VaHiX/CodeForces/