// Problem: CF 2140 D - A Cruel Segment's Thesis
// https://codeforces.com/contest/2140/problem/D

/*
 * Problem: D. A Cruel Segment's Thesis
 * 
 * Purpose:
 *   This code solves a problem where given n segments on a number line,
 *   we perform operations to combine pairs of segments into new segments, 
 *   aiming to maximize the total length of all marked segments.
 *   
 *   The key idea is that in each operation, two segments are combined into one
 *   such that the resulting segment covers the union of their ranges optimally.
 *   
 *   The approach uses a greedy strategy with ordering:
 *   1. For even number of segments: we can pair them up greedily to form optimal combinations.
 *   2. For odd number of segments: one segment remains unpaired and may be chosen to optimize the result.
 *   
 * Algorithm:
 *   - Compute base sum of all original segments (initial total length)
 *   - Create array of sum l[i] + r[i] and sort indices by this value
 *   - Use prefix sums and dynamic programming logic for selecting optimal pairs
 *   - Handle odd vs even case carefully in the calculation
 *   
 * Time Complexity: O(n log n) due to sorting operations across all test cases.
 * Space Complexity: O(n) for storing arrays and auxiliary data structures.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().trim().toInt()
    val outSb = StringBuilder()
    
    repeat(t) {
        val n = br.readLine().trim().toInt()
        val l = LongArray(n)
        val r = LongArray(n)
        
        repeat(n) { i ->
            val st = StringTokenizer(br.readLine())
            l[i] = st.nextToken().toLong()
            r[i] = st.nextToken().toLong()
        }
        
        var baseSum = 0L
        for (i in 0 until n) {
            baseSum += (r[i] - l[i]) // sum of all original segment lengths
        }
        
        val a = LongArray(n)
        var sr = 0L
        for (i in 0 until n) {
            a[i] = l[i] + r[i] // sum of left and right bounds for each segment
            sr += r[i] // running sum of right bounds
        }
        
        // Sort indices based on value of l[i] + r[i]
        val sortedIdx = (0 until n).sortedBy { a[it] }
        
        // dp1 stores the values of a[sortedIdx[i]] 
        val dp1 = LongArray(n) { a[sortedIdx[it]] }
        
        // dp2 stores the values of r[sortedIdx[i]]
        val dp2 = LongArray(n) { r[sortedIdx[it]] }
        
        // prefix sum array
        val pre = LongArray(n)
        if (n > 0) pre[0] = dp1[0]
        for (i in 1 until n) pre[i] = pre[i - 1] + dp1[i]
        
        var mx = Long.MIN_VALUE
        
        if (n % 2 == 0) {
            // When even number of segments, all can be paired up
            val m = n / 2
            val sum = if (m > 0) pre[m - 1] else 0
            mx = sr - sum // Maximize benefit by removing unnecessary overlaps from prefix sums
        } else {
            // When odd, leave one segment unpaired — try all positions for optimal choice
            val m = (n - 1) / 2
            for (i in 0 until n) {
                val rem = sr - dp2[i] // remaining sum after excluding r[i]
                val sum = if (m > 0) {
                    if (i >= m) pre[m - 1] else pre[m] - dp1[i] 
                } else 0L
                mx = maxOf(mx, rem - sum) 
            }
        }
        
        outSb.append(baseSum + maxOf(0L, mx)).append('\n') // Add base sum and positive gain
    }
    print(outSb.toString())
}


// https://github.com/VaHiX/codeForces/