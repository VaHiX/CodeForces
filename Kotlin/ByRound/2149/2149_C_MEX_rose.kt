// Problem: CF 2149 C - MEX rose
// https://codeforces.com/contest/2149/problem/C

/**
 * Problem: C. MEX rose
 * 
 * Purpose:
 *   Given an array of integers and a target MEX value k, determine the minimum number of operations
 *   required to make the MEX of the array equal to k. Each operation allows changing any element
 *   in the range [0, n] to any integer in that same range.
 *
 * Algorithm:
 *   - For each test case:
 *     1. Count occurrences of elements in range [0, n] using a frequency array `cnt`.
 *     2. Determine how many numbers from [0, k) are missing (i.e., not present).
 *     3. Count how many times k appears in the array.
 *     4. The result is the maximum of:
 *        - Missing count of elements in [0, k)
 *        - Number of occurrences of k
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the frequency array and input parsing
 */
fun main() {
    val data = java.io.BufferedInputStream(System.`in`).readBytes()
    val toks = String(data).trim().split(Regex("\\s+"))
    var idx = 0
    val t = toks[idx++].toInt()
    val sb = StringBuilder()
    repeat(t) {
        val n = toks[idx++].toInt()
        val k = toks[idx++].toInt()
        val cnt = IntArray(n + 1) // Count frequency of values in [0, n]
        for (i in 0 until n) {
            val v = toks[idx++].toInt()
            if (v in 0..n) cnt[v]++ // Only count valid values within range
        }
        var missing = 0
        for (x in 0 until k) if (cnt[x] == 0) missing++ // Count how many of [0,k) are missing
        val ans = maxOf(missing, cnt[k]) // Minimum operations = max(missing, occurrences of k)
        sb.append(ans).append('\n')
    }
    print(sb.toString())
}


// https://github.com/VaHiX/CodeForces/