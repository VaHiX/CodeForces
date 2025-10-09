// Problem: CF 2149 B - Unconventional Pairs
// https://codeforces.com/contest/2149/problem/B

/*
B. Unconventional Pairs
Algorithms/Techniques: Sorting, Greedy Approach

Time Complexity: O(n log n) per test case due to sorting; overall O(∑n log n) for all test cases
Space Complexity: O(n) for storing the list of integers

The approach is based on greedy selection after sorting:
1. Sort the array.
2. Pair adjacent elements in the sorted array (i, i+1), (i+2, i+3), etc.
3. This minimizes the maximum difference because we always pair close values.
4. Iterate through pairs with step 2 and compute max absolute difference.
*/

import kotlin.math.abs
import kotlin.math.max

fun main() {
    var n = readLine()!!.toInt()
    while (n-- > 0) {
        val x = readLine()!!.toInt() // Read array size
        var list = readLine()!!.split(" ").map { it.toInt() } // Read and convert to integer list
        list = list.sorted() // Sort the list to apply greedy pairing
        var i = 0 // Initialize index for traversal
        var mx = 0 // Variable to store maximum difference
        while (list.size > i) {
            mx = max(mx, abs(list[i] - list[i + 1])) // Compute difference between pair and update max
            i += 2 // Move to next pair
        }
        println(mx)
    }
}


// https://github.com/VaHiX/CodeForces/