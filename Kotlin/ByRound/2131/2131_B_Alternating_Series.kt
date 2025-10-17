// Problem: CF 2131 B - Alternating Series
// https://codeforces.com/contest/2131/problem/B

/**
 * Problem: B. Alternating Series
 * 
 * Purpose:
 *   Generate a "good" array of length n such that:
 *   1. For all adjacent elements, their product is negative (alternating signs).
 *   2. For all subarrays of length ≥ 2, the sum is positive.
 *   3. Among all good arrays of length n, this one is lexicographically smallest 
 *      when considering absolute values (i.e., better array has smaller absolute values).
 *
 * Algorithm/Techniques:
 *   - Construct an alternating series where elements alternate in sign.
 *   - Use small absolute values to minimize the lexicographic order.
 *   - Handle edge cases like odd and even length arrays carefully.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the output array
 */

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val n = readLine()!!.toInt() // Read length of array
        val arr = IntArray(n) { i ->
            val b = i + 1 
            if (b % 2 == 1) -1 // Odd indices: use -1
            else if (b == n && n % 2 == 0) 2 // Special case for last even-indexed element in even-length array
            else 3 // Even indices (not last): use 3
        }
        println(arr.joinToString(" ")) // Output result
    }
}


// https://github.com/VaHiX/codeForces/