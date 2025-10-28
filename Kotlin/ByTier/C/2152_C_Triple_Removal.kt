// Problem: CF 2152 C - Triple Removal
// https://codeforces.com/contest/2152/problem/C

/*
 * Problem: C. Triple Removal
 * Purpose: For each query on a subarray [l, r], compute the minimum total cost to make the subarray empty using triple removal operations.
 * Algorithms/Techniques:
 *   - Preprocessing with prefix sums of 0s and 1s
 *   - Identifying consecutive equal elements to check if a valid sequence exists
 *   - Binary search for finding positions of repeated elements in range
 *
 * Time Complexity: O(n + q * log n) per test case, where n is the length of the array and q is the number of queries.
 * Space Complexity: O(n) for storing prefix sums and consecutive element indices.
 */

import java.util.StringTokenizer
import java.util.TreeMap

fun main() {
    val br = System.`in`.bufferedReader()
    val t = br.readLine().toInt()
    val out = StringBuilder()
    
    repeat(t) {
        val st = StringTokenizer(br.readLine())
        val n = st.nextToken().toInt()
        val q = st.nextToken().toInt()
        val a = LongArray(n + 1)
        a[0] = -1 // dummy value to make indexing easier
        
        // Read input array and populate 'a'
        val inputArr = br.readLine().split(" ").map { it.toLong() }
        for (i in 1..n) {
            a[i] = inputArr[i - 1]
        }
        
        // m[i] stores prefix count of zeros and ones up to index i
        val m = Array(n + 1) { Pair(0L, 0L) }
        val v = mutableListOf<Int>() // Stores indices where consecutive elements are equal

        // Build prefix sums and find consecutive duplicates
        for (i in 1..n) {
            val prev = m[i - 1]
            if (a[i] == 0L) {
                m[i] = Pair(prev.first + 1, prev.second)
            } else {
                m[i] = Pair(prev.first, prev.second + 1)
            }
            // If current element equals previous, add index to list of consecutive matches
            if (a[i] == a[i - 1]) {
                v.add(i - 1)
            }
        }
        
        val queries = mutableListOf<Pair<Int, Int>>()
        repeat(q) {
            val st2 = StringTokenizer(br.readLine())
            val l = st2.nextToken().toInt()
            val r = st2.nextToken().toInt()
            queries.add(Pair(l, r))
        }
        
        // Process each query
        for ((l, r) in queries) {
            var ans: Long = 0
            
            // Get prefix sums for range [l-1, r]
            val left = m[l - 1]
            val right = m[r]
            val zeroCount = right.first - left.first
            val oneCount = right.second - left.second

            // If counts of 0s and 1s are divisible by 3, then it's possible to remove all elements optimally
            if (zeroCount % 3 == 0L && oneCount % 3 == 0L) {
                // Binary search for the first index >= l in v
                val it = v.binarySearch(l)
                val pos = if (it < 0) -(it + 1) else it
                
                // Check if there's a valid consecutive pair within [l, r] that can be used to split removal step
                if (pos < v.size && v[pos] + 1 <= r) {
                    ans = zeroCount / 3 + oneCount / 3 // No extra cost needed
                } else {
                    ans = zeroCount / 3 + oneCount / 3 + 1 // Extra cost for handling leftover elements
                }
            } else {
                ans = -1 // Not possible to make array empty
            }
            
            out.append(ans).append("\n")
        }
    }
    print(out)
}


// https://github.com/VaHiX/CodeForces/