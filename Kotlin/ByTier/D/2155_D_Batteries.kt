// Problem: CF 2155 D - Batteries
// https://codeforces.com/contest/2155/problem/D

/*
 * Problem: D. Batteries
 * Purpose: Find a working pair of batteries among n batteries where at least 2 work.
 * Algorithm: Brute-force testing pairs in a specific order to ensure we don't exceed the limit.
 * Time Complexity: O(n^2) in worst case for queries, but bounded by floor(n^2 / a) which is at most O(n^2).
 * Space Complexity: O(1) - only using a few variables for tracking.
 *
 * Techniques:
 * - Interactive problem with adaptive responses
 * - Greedy approach to avoid exceeding query count
 * - Use of nested loops in a specific order to traverse potential pairs efficiently
 */

fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    
    // Query function to test if two batteries work together
    fun q(u: Int, v: Int): Boolean {
        cout.write("$u $v\n")  // Output the pair to test
        cout.flush()           // Ensure output is sent immediately
        return cin.readLine() == "1"  // Return whether flashlight turned on
    }
    
    repeat(cin.readLine().toInt()) {  // Process each test case
        val n = cin.readLine().toInt()  // Read number of batteries
        
        var ans = false  // Flag to indicate if we found a working pair
        
        // Nested loop to iterate through all pairs (u, v) where u < v
        for (d in 1 until n) {
            for (u in 1 until n) {
                val v = u + d  // Calculate second battery index
                if (v > n) break  // Break if v exceeds n
                
                ans = q(u, v)  // Query this pair
                if (ans) break  // If found, stop searching
            }
            if (ans) break  // If found, stop outer loop too
        }
    }
    
    cout.flush()  // Flush final output
}


// https://github.com/VaHiX/CodeForces/