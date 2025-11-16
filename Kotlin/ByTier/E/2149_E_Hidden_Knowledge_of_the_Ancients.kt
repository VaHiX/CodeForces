// Problem: CF 2149 E - Hidden Knowledge of the Ancients
// https://codeforces.com/contest/2149/problem/E

/*
E. Hidden Knowledge of the Ancients

Purpose:
This program counts the number of continuous subarrays in a given sequence that meet specific criteria:
- The subarray must contain exactly k distinct numbers.
- The length of the subarray must be between l and r (inclusive).

Algorithms/Techniques:
- Sliding window technique to efficiently count valid subarrays with at most x distinct elements.
- Two-pointer approach for maintaining a window with bounded distinct elements.
- Prefix sum-like approach using difference of counts: countAtMost(k) - countAtMost(k - 1)
  to get exactly k distinct elements.

Time Complexity:
O(n) per test case, where n is the length of the sequence.
Each element is visited at most twice in the sliding window (once by right pointer, once by left), 
and the computation for each element takes constant time.

Space Complexity:
O(n) due to the HashMap used for frequency tracking during sliding window operations,
in worst case storing all distinct elements.

*/

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.max
import kotlin.math.min

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().toInt()
    val out = StringBuilder()
    repeat(t) {
        val st = StringTokenizer(br.readLine())
        val n = st.nextToken().toInt()
        val k = st.nextToken().toInt()
        val L = st.nextToken().toInt()
        val R = st.nextToken().toInt()
        val arr = IntArray(n)
        val st2 = StringTokenizer(br.readLine())
        for (i in 0 until n) arr[i] = st2.nextToken().toInt()

        // Function to count subarrays with at most x distinct elements
        fun countAtMost(x: Int): Long {
            if (x == 0) return 0L
            val freq = HashMap<Int, Int>() // Frequency map for elements in current window
            var l = 0 // Left pointer of sliding window
            var distinct = 0 // Count of distinct elements in window
            var result = 0L // Total count of valid subarrays

            for (r in 0 until n) { // Right pointer of sliding window
                freq[arr[r]] = (freq[arr[r]] ?: 0) + 1 // Add current element to frequency map
                if (freq[arr[r]] == 1) distinct++ // If new distinct element, increment counter

                // Shrink window from left until distinct count <= x
                while (distinct > x) {
                    freq[arr[l]] = freq[arr[l]]!! - 1 // Decrease frequency of leftmost element
                    if (freq[arr[l]] == 0) distinct-- // If frequency becomes zero, decrease distinct count
                    l++ // Move left pointer forward
                }

                val maxLen = r - l + 1 // Length of current window
                if (maxLen >= L) { // Only consider windows with length >= L
                    val add = min(maxLen, R) - L + 1 // Number of valid subarrays in this window of length [L, R]
                    if (add > 0) result += add // Add to total count
                }
            }
            return result
        }

        // Difference gives number of subarrays with exactly k distinct elements
        val ans = countAtMost(k) - countAtMost(k - 1)
        out.append(ans).append('\n')
    }
    print(out.toString())
}


// https://github.com/VaHiX/CodeForces/