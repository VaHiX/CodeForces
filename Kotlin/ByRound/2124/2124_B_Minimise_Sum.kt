// Problem: CF 2124 B - Minimise Sum
// https://codeforces.com/contest/2124/problem/B

/**
 * Problem: B. Minimise Sum
 * 
 * Purpose:
 *   Given an array of non-negative integers, we can perform at most one operation:
 *   choose two indices i < j and replace a[i] with a[i] + a[j], setting a[j] to 0.
 *   After this, compute the sum of all prefix minimums and minimize it.
 * 
 * Algorithm:
 *   - Precompute prefix minimums and prefix sums for efficient calculation.
 *   - Try all possible operations (i, i+1) and see if merging improves the result.
 *   - For each operation, calculate new prefix sum after merge and update the best.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing prefix arrays
 */
import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        val n = scanner.nextInt()
        val a = LongArray(n) { scanner.nextLong() }
        println(minimizePrefixSum(n, a))
    }
}

/**
 * Computes prefix minimum array and prefix sum array
 * @param n length of the array
 * @param a input array
 * @return Pair of prefixMin and prefixSum arrays
 */
fun computePrefixMinAndSum(n: Int, a: LongArray): Pair<LongArray, LongArray> {
    val prefixMin = LongArray(n)
    val prefixSum = LongArray(n)
    prefixMin[0] = a[0]
    prefixSum[0] = a[0]
    for (i in 1 until n) {
        prefixMin[i] = minOf(prefixMin[i - 1], a[i])
        prefixSum[i] = prefixSum[i - 1] + prefixMin[i] // Sum of prefix minimums
    }
    return Pair(prefixMin, prefixSum)
}

/**
 * Minimizes the total prefix sum by possibly performing one merge operation
 * @param n length of the array
 * @param a input array
 * @return minimum possible prefix sum after at most one operation
 */
fun minimizePrefixSum(n: Int, a: LongArray): Long {
    val (prefixMin, prefixSum) = computePrefixMinAndSum(n, a)
    var best = prefixSum[n - 1] // Initial result without any operations
    
    val big = 4e18.toLong() // A large value to represent infinity
    for (i in 0 until n - 1) {
        // Previous prefix minimum before current position
        val beforeMin = if (i > 0) prefixMin[i - 1] else big
        // Prefix sum before the current position
        val beforeSum = if (i > 0) prefixSum[i - 1] else 0L
        
        // Merge adjacent elements a[i] and a[i + 1]
        val mergeVal = a[i] + a[i + 1]
        
        // Calculate total sum if we perform this merge
        val total = beforeSum + minOf(beforeMin, mergeVal)
        
        if (total < best) {
            best = total // Update minimum if a better solution is found
        }
    }
    return best
}


// https://github.com/VaHiX/CodeForces/