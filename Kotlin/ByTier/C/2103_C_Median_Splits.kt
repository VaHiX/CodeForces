// Problem: CF 2103 C - Median Splits
// https://codeforces.com/contest/2103/problem/C

/**
 * Problem: C. Median Splits
 * 
 * Description:
 * Given an array of integers and a value k, determine if it's possible to split the array into
 * three contiguous subarrays such that the median of their medians is less than or equal to k.
 *
 * Algorithms/Techniques:
 * - Two-pass greedy approach for checking valid splits.
 * - Prefix and suffix scanning to find valid subarray boundaries.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) auxiliary space (not counting input storage)
 */

fun main() {
    fun twoGood(a: List<Int>, k: Int): Boolean {
        val n = a.size
        var lecnt = 0 // count of elements <= k
        var gcnt = 0  // count of elements > k
        var cnt = 0   // number of valid segments found
        var i = 0
        while (i < n - 1) {
            if (a[i] <= k) lecnt++ // increment if element is <= k
            else gcnt++            // otherwise increment greater count
            
            if (lecnt >= gcnt) {   // if valid prefix found, reset counts and increment segment counter
                if (lecnt + gcnt % 2 == 1 && a[i+1] > k) i++ // skip one more if needed for odd length
                lecnt = 0
                gcnt = 0
                cnt++
                if (cnt >= 2) return true // found two valid segments, early return
            }
            i++
        }
        return false
    }
    
    fun prefSufGood(a: List<Int>, k: Int): Boolean {
        val n = a.size
        var lecnt = 0
        var gcnt = 0
        var smallestPrefEnd = n // minimum index where prefix is valid
        for (i in 0 until n) {
            if (a[i] <= k) lecnt++ // update count when element is <= k
            else gcnt++
            if (lecnt >= gcnt) {   // if prefix is valid, record end
                smallestPrefEnd = i
                break
            }
        }
        lecnt = 0
        gcnt = 0
        var smallestSufEnd = -1 // minimum index where suffix is valid
        for (i in n-1 downTo 2) { // start from end, check backwards till at least 2 elements remain
            if (a[i] <= k) lecnt++
            else gcnt++
            if (lecnt >= gcnt) {   // if suffix is valid, record end
                smallestSufEnd = i
                break
            }
        }
        return smallestPrefEnd + 1 < smallestSufEnd // check if there's a middle section between valid prefix and suffix
    }
    
    repeat(readln().toInt()) {
        val (n, k) = readln().split(' ').map { it.toInt() }
        val a = readln().split(' ').map { it.toInt() }
        println(if (prefSufGood(a, k) || twoGood(a, k) || twoGood(a.reversed(), k)) "YES" else "NO")
    }
}


// https://github.com/VaHiX/CodeForces/