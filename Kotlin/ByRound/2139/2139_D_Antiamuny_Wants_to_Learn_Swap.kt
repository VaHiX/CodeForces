// Problem: CF 2139 D - Antiamuny Wants to Learn Swap
// https://codeforces.com/contest/2139/problem/D

/*
 * Problem: D. Antiamuny Wants to Learn Swap
 * 
 * Purpose:
 *   Given a permutation of integers, determine for each query whether a subarray
 *   is "perfect". A subarray is perfect if the minimum number of operations
 *   required to sort it using both adjacent swaps and swaps with gap 2 (at most once)
 *   equals the minimum required using only adjacent swaps.
 *
 * Algorithms:
 *   - For each element i, find the nearest previous element smaller than a[i] -> vecA
 *   - For each element i, find the nearest next element larger than a[i] -> mex
 *   - Dynamic programming to precompute answer for ranges
 * 
 * Time Complexity: O(n + q) per test case
 * Space Complexity: O(n) per test case
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import java.util.ArrayDeque

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().toInt()
    val out = StringBuilder()
    repeat(t) {
        val st1 = StringTokenizer(br.readLine())
        val n = st1.nextToken().toInt()
        val q = st1.nextToken().toInt()
        val a = IntArray(n + 1) // 1-indexed array for easier handling
        val st2 = StringTokenizer(br.readLine())
        for (i in 1..n) a[i] = st2.nextToken().toInt()
        
        val vecA = IntArray(n + 1) // Stores index of previous smaller element
        val mex = IntArray(n + 1) { n + 1 } // Stores index of next larger element
        val st = ArrayDeque<Int>()
        
        // Finding previous smaller element for each position
        for (i in 1..n) {
            while (st.isNotEmpty() && a[st.last] < a[i]) st.removeLast()
            vecA[i] = if (st.isEmpty()) 0 else st.last
            st.addLast(i)
        }
        
        st.clear()
        // Finding next larger element for each position
        for (i in 1..n) {
            while (st.isNotEmpty() && a[i] < a[st.last]) {
                mex[st.removeLast()] = i
            }
            st.addLast(i)
        }
        
        val MO = n + 5 // Marker value representing infinity or "no valid range"
        val ans = IntArray(n + 2) { MO } // Result array for valid ranges
        val cc = IntArray(n + 3) { MO } // Suffix minimums for efficient querying
        
        // Update answer array with valid ranges from vecA and mex
        for (j in 1..n) {
            if (vecA[j] > 0 && mex[j] <= n) {
                ans[vecA[j]] = minOf(ans[vecA[j]], mex[j])
            }
        }
        
        // Compute suffix minimums to allow efficient querying of range answers
        for (i in n downTo 1) {
            cc[i] = minOf(cc[i + 1], ans[i])
        }
        
        // Process queries
        repeat(q) {
            val stq = StringTokenizer(br.readLine())
            val l = stq.nextToken().toInt()
            val r = stq.nextToken().toInt()
            out.append(if (cc[l] <= r) "NO\n" else "YES\n") // If valid range is within [l, r], not perfect
        }
    }
    print(out)
}


// https://github.com/VaHiX/codeForces/