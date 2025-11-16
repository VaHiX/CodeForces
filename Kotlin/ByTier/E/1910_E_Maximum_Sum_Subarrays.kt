// Problem: CF 1910 E - Maximum Sum Subarrays
// https://codeforces.com/contest/1910/problem/E

/*
 * Problem: E. Maximum Sum Subarrays
 * 
 * Purpose: Given two arrays a and b of length n, we can swap elements at the same index between a and b.
 * We want to maximize the sum of maximum subarray sums (Kadane's algorithm result) of both arrays.
 * 
 * Algorithm:
 * - For each position i, we consider two choices:
 *   1. Keep a[i] and b[i] as they are
 *   2. Swap a[i] and b[i]
 * - We maintain state variables to track the best sums ending at current position for both arrays.
 * - Kadane's-like dynamic programming is used with auxiliary states to model choices optimally.
 * 
 * Time Complexity: O(n) per test case, where n is the length of array.
 * Space Complexity: O(1), as only a constant number of variables are used.
 */

fun main() {
    val T = readLine()!!.toInt()
    for (i in 1..T) {
        val n = readLine()!!.toInt()
        val a = readLine()!!.split(" ").map { it.toLong() }
        val b = readLine()!!.split(" ").map { it.toLong() }
        
        // State tracking variables:
        // x1, x2, x3: Track max subarray sums for array a considering swaps
        // y1, y2, y3: Track max subarray sums for array b considering swaps
        var x1 = 0L
        var x2 = -1e18.toLong() // Represents max ending at position i-1 using previous optimal value
        var x3 = -1e18.toLong() // Represents max including last element from either a[i] or b[i]
        var y1 = -1e18.toLong()
        var y2 = -1e18.toLong()
        var y3 = -1e18.toLong()
        
        var ans = 0L
        
        for (j in 0 until n) {
            val mx = maxOf(a[j], b[j]) // Max of the pair a[j] and b[j]
            val sm = a[j] + b[j]      // Sum of the pair
            
            // Update for array b: y2 tracks best sum including current element
            y2 = maxOf(y2 + mx, y3 + mx)
            
            // Update for array b: y1 tracks maximum subarray ending at j
            y1 = maxOf(mx, mx + y1)
            
            // Update for array b: y3 stores the best seen so far
            y3 = maxOf(y3, y1)

            // Update for array a: x3 tracks best using previous elements
            x3 = maxOf(x3 + mx, x2 + mx)
            
            // Update for array a: x2 uses sum of swapped pairs (sm) to compute new state
            x2 = maxOf(sm + x2, sm + x1, sm)
            
            // Update for array a: x1 tracks the local maximum ending here
            x1 = maxOf(mx, mx + x1)
            
            // Update global answer by comparing all possible values
            ans = maxOf(ans, x2, x3, y2, y1)
        }
        println(ans)
    }
}


// https://github.com/VaHiX/codeForces/