// Problem: CF 2128 E1 - Submedians (Easy Version)
// https://codeforces.com/contest/2128/problem/E1

/*
 * Problem: E1. Submedians (Easy Version)
 * Purpose: Find the maximum submedian v_max and corresponding subarray [l, r] such that 
 *          v_max is a median of the subarray and length r - l + 1 >= k.
 *
 * Algorithm:
 * - Binary search on the answer (the value of the maximum submedian).
 * - For each candidate value x, check if there exists a subarray of length at least k 
 *   where x is a median. This is done using prefix sums with transformation:
 *   - Replace elements >= x by 1, others by -1.
 *   - A valid subarray exists if sum of transformed subarray is non-negative.
 *   - Use sliding window technique with prefix minimum to efficiently find such a subarray.
 *
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n)
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.max

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().toInt()
    val out = StringBuilder()
    repeat(t) {
        val st1 = StringTokenizer(br.readLine())
        val n = st1.nextToken().toInt()
        val k = st1.nextToken().toInt()
        val a = IntArray(n + 1)
        var M = 0
        val st2 = StringTokenizer(br.readLine())
        for (i in 1..n) {
            a[i] = st2.nextToken().toInt()
            M = max(M, a[i])
        }
        val p = IntArray(n + 1)
        
        // Function to check if there's a valid subarray with median >= x
        fun check(x: Int, res: IntArray, f: Boolean): Boolean {
            p[0] = 0
            for (i in 1..n) {
                p[i] = p[i - 1] + if (a[i] >= x) 1 else -1 // Transform the array: 1 if a[i] >= x, else -1
            }
            var m0 = 0L // Minimum prefix sum seen so far (for window of size k)
            var i0 = 0 // Leftmost index of the minimum prefix sum
            for (i in k..n) {
                if (p[i - k] < m0) { // Update minimum prefix sum if smaller
                    m0 = p[i - k].toLong()
                    i0 = i - k
                }
                if (p[i] - m0 >= 0) { // If valid subarray found and f is true, save indices
                    if (f) {
                        res[0] = i0 + 1 // Save left index (1-based)
                        res[1] = i // Save right index (1-based)
                    }
                    return true
                }
            }
            return false
        }
        
        var l = 1
        var h = M + 1
        while (l + 1 < h) { // Binary search on answer
            val d = l + (h - l) / 2
            if (check(d, IntArray(2), false))
                l = d
            else
                h = d
        }
        val res = IntArray(2)
        check(l, res, true) // Final check to get the actual indices for max median
        out.append("$l ${res[0]} ${res[1]}\n")
    }
    print(out)
}


// https://github.com/VaHiX/CodeForces/