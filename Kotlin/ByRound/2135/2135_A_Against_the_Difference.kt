// Problem: CF 2135 A - Against the Difference
// https://codeforces.com/contest/2135/problem/A

/*
 * Problem: A. Against the Difference
 * Algorithm: Dynamic Programming with Segment Tree Optimization
 *
 * Purpose:
 * This code finds the length of the longest "neat" subsequence in a given array.
 * A neat subsequence is one that can be split into blocks where each block contains
 * elements equal to the size of the block. For example, [3,3,3] is valid because
 * all elements are 3 and the block length is 3, but [1,1,1] is not valid since
 * the block size is 3, but elements are 1.
 *
 * Approach:
 * - Preprocess positions of each value in the input array.
 * - For each value v, process its occurrences to form segments.
 * - Use dynamic programming with optimized range queries (represented via pairs of indices and values).
 * - Maintain arrays `d` and `b` for DP states to track maximum lengths ending at each position.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

import java.util.StringTokenizer

fun main() {
    val br = System.`in`.bufferedReader()
    val out = StringBuilder()
    val t = br.readLine().toInt()
    repeat(t) {
        val n = br.readLine().toInt()
        val st = StringTokenizer(br.readLine())
        val a = IntArray(n + 1)
        for (i in 1..n) {
            a[i] = st.nextToken().toInt()
        }
        val p = Array(n + 1) { mutableListOf<Int>() }
        for (i in 1..n) {
            if (a[i] <= n) {
                p[a[i]].add(i)
            }
        }
        val e = Array(n + 1) { mutableListOf<Pair<Int, Int>>() }
        for (v in 1..n) {
            val c = p[v].size
            var k = v
            while (k <= c) {
                val l = p[v][k - v]
                val r = p[v][k - 1]
                e[r].add(Pair(l, v)) // Store segment information for dynamic programming.
                k++
            }
        }
        val d = IntArray(n + 1)
        val b = IntArray(n + 1)
        for (i in 1..n) {
            for (q in e[i]) {
                val l = q.first
                val w = q.second
                d[i] = maxOf(d[i], b[l - 1] + w) // Update d[i] with possible maximum value.
            }
            b[i] = maxOf(b[i - 1], d[i]) // Maintain prefix maximum for final result.
        }
        out.append(b[n]).append('\n')
    }
    print(out.toString())
}


// https://github.com/VaHiX/CodeForces/