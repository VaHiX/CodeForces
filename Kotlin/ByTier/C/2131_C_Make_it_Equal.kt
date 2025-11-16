// Problem: CF 2131 C - Make it Equal
// https://codeforces.com/contest/2131/problem/C

/*
 * Problem: C. Make it Equal
 *
 * Purpose:
 *   Determine if two multisets S and T can be made equal by performing operations on S.
 *   Each operation allows removing an element x from S, then inserting either (x + k) or |x - k|.
 *   This models a transformation where elements can move in steps of k (either in positive or negative direction).
 *
 * Approach:
 *   1. If k == 0, check if S and T are already identical (after sorting).
 *   2. For k > 0:
 *      - Compute remainders of each element in S and T modulo k.
 *      - Normalize remainders to be in [0, k/2] range using min(remainder, k - remainder).
 *      - Count net difference in normalized remainders between S and T.
 *      - If all differences are zero, then S can be transformed into T.
 *
 * Time Complexity: O(n log n) per test case due to sorting when k == 0; otherwise O(n)
 * Space Complexity: O(n) for storing arrays and map of remainders
 */

import java.util.*

fun main() {
    val input = Scanner(System.`in`)
    var testCases = input.nextInt()
    
    while (testCases-- > 0) {
        val size = input.nextInt()
        val step = input.nextLong()
        val sourceSet = LongArray(size) { input.nextLong() }
        val targetSet = LongArray(size) { input.nextLong() }
        
        if (step == 0L) {
            // Sort both sets and compare directly
            sourceSet.sort()
            targetSet.sort()
            val identical = sourceSet.contentEquals(targetSet)
            println(if (identical) "YES" else "NO")
            continue
        }

        // Map to track the difference in count of normalized remainders
        val remainderCount = mutableMapOf<Long, Int>()

        // Process source set: calculate and accumulate normalized remainders
        for (value in sourceSet) {
            var remainder = value % step
            if (remainder < 0) remainder += step
            val normalized = minOf(remainder, step - remainder)
            remainderCount[normalized] = remainderCount.getOrDefault(normalized, 0) + 1
        }

        // Process target set: subtract normalized remainders
        for (value in targetSet) {
            var remainder = value % step
            if (remainder < 0) remainder += step
            val normalized = minOf(remainder, step - remainder)
            remainderCount[normalized] = remainderCount.getOrDefault(normalized, 0) - 1
        }

        // Check if all differences are zero
        val isEqual = remainderCount.values.all { it == 0 }
        println(if (isEqual) "YES" else "NO")
    }
}


// https://github.com/VaHiX/codeForces/