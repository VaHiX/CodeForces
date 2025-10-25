// Problem: CF 1958 D - Staircase
// https://codeforces.com/contest/1958/problem/D

/**
 * Problem: D. Staircase
 * 
 * Purpose: This code solves the problem of finding the minimum effort to repair all broken steps in a staircase,
 *          where each broken step has a difficulty value, and we can either repair one step or two adjacent steps
 *          in one day with specific costs.
 * 
 * Algorithm:
 *   - Greedily process consecutive broken steps.
 *   - For every pair of adjacent broken steps, consider repairing them together (cost = 2*(a[i] + a[i+1]))
 *     if it's cheaper than repairing them separately (cost = a[i] + a[i+1]).
 *   - Use bit manipulation to track whether the current sequence length is even or odd.
 * 
 * Time Complexity: O(n), where n is the number of steps in the staircase.
 * Space Complexity: O(n), for storing the list of step difficulties.
 */
fun main() {
    repeat(readln().toInt()) { println(solve()) }
}

fun solve(): Long {
    readln() // Read n, but not used here since we're reading the next line anyway
    val list = readln().split(' ').map(String::toLong) // Convert input to list of longs
    var sum = list.sum().shl(1) // Double the total sum because we may repair some pairs
    var max = 0L // Tracks the maximum difficulty in current sequence of broken steps
    var count = 0 // Counts how many consecutive broken steps we have seen so far
    
    list.forEach {
        if (it != 0L) { // If step is broken
            if (count.and(1) == 0 && it > max) max = it // Update max if this is an odd-indexed step in the sequence and greater than current max
            count++ // Increment counter for consecutive broken steps
        } else { // If step is not broken (i.e., 0)
            if (count.and(1) != 0) sum -= max // If we ended on an odd-numbered step, subtract maximum from total effort
            max = 0L
            count = 0
        }
    }
    
    if (count.and(1) != 0) sum -= max // Final check if the last sequence ended with an odd number of steps
    
    return sum
}


// https://github.com/VaHiX/codeForces/