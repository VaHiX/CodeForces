// Problem: CF 2124 C - Subset Multiplication
// https://codeforces.com/contest/2124/problem/C

/*
 * Problem: C. Subset Multiplication
 *
 * Description:
 * Given an array b that could have been derived from a "beautiful" array a (where each element divides the next)
 * by multiplying some subset of elements by a positive integer x, find any valid value of x.
 *
 * Algorithm:
 * - For each test case:
 *   1. Compute the GCD of all elements in b to get the base GCD.
 *   2. Normalize each element by dividing by this GCD.
 *   3. Iterate through consecutive pairs and compute their GCD.
 *   4. If normalized[i] / gcd > 1, then include that quotient in LCM calculation.
 *   5. Return the final LCM as a candidate for x.
 *
 * Time Complexity: O(n * log(max(b))) per test case
 * Space Complexity: O(n) for storing the array and intermediate calculations
 */

import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        val n = scanner.nextInt()
        val b = LongArray(n) { scanner.nextLong() }
        println(solveTestCase(n, b))
    }
}

fun gcd(a: Long, b: Long): Long {
    return if (b == 0L) a else gcd(b, a % b)
}

fun lcm(a: Long, b: Long): Long {
    if (a == 0L || b == 0L) return 0L
    val g = gcd(a, b)
    return (a / g) * b
}

fun solveTestCase(n: Int, b: LongArray): Long {
    // Step 1: Find the GCD of all elements in b
    var globalGcd = b[0]
    for (i in 1 until n) {
        globalGcd = gcd(globalGcd, b[i])
    }
    
    // Step 2: Normalize the array by dividing each element by the global GCD
    val normalized = LongArray(n) { b[it] / globalGcd }
    
    // Step 3: Build result LCM based on normalized differences
    var resultLcm = 1L
    for (i in 0 until n - 1) {
        val g = gcd(normalized[i], normalized[i + 1])
        val a = normalized[i] / g
        if (a != 1L) {
            // Include only non-trivial factors in LCM
            resultLcm = lcm(resultLcm, a)
        }
    }
    
    return resultLcm
}


// https://github.com/VaHiX/CodeForces/