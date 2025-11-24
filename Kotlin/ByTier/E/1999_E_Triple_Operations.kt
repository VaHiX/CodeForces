// Problem: CF 1999 E - Triple Operations
// https://codeforces.com/contest/1999/problem/E

/**
 * Problem: Triple Operations
 * 
 * Algorithms/Techniques:
 * - Preprocessing prefix sums of operations needed for numbers from 1 to n
 * - For each number, count how many times it takes to reduce it to 0 by dividing by 3
 * - Use prefix sums to quickly compute total operations for range [l, r]
 * 
 * Time Complexity: O(2*10^5) for preprocessing + O(1) per query = O(2*10^5)
 * Space Complexity: O(2*10^5) for prefix sums array
 */

fun preprocess(): LongArray {
    val size = 2_00_002 // Size of array to hold prefix sums up to 2*10^5
    val prefixSums = LongArray(size)
    
    // For each number from 0 to size-2, calculate how many divisions by 3 are needed
    for (i in 0 until size - 1) {
        var value = i
        while (value > 0) {
            value /= 3 // Divide by 3 and floor (integer division)
            prefixSums[i]++ // Count number of operations needed for this number
        }
    }
    
    // Build prefix sum array for fast range queries
    for (i in 1 until size) {
        prefixSums[i] += prefixSums[i - 1]
    }
    
    return prefixSums
}

fun solve(prefixSums: LongArray) {
    val (left, right) = readLine()!!.split(" ").map { it.toLong() }
    
    // Calculate initial operations needed to bring left to 0
    var result = 0L
    var temp = left
    while (temp > 0) {
        temp /= 3
        result++
    }
    
    // Multiply by 2 because we're processing both x and y in each operation
    result *= 2
    
    // Adjust indices for 0-based indexing and clamping
    val adjustedLeft = left + 1 // Since left is 1-based
    val leftIndex = (adjustedLeft - 1).toInt().coerceAtLeast(0) // Ensure index is at least 0
    val rightIndex = right.toInt().coerceAtMost(prefixSums.size - 1) // Ensure index is within bounds
    
    // Output result: base operations + difference in prefix sums for range
    println(result + prefixSums[rightIndex] - prefixSums[leftIndex])
}

fun main() {
    val prefixSums = preprocess() // Precompute the prefix sums
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        solve(prefixSums) // Process each test case
    }
}


// https://github.com/VaHiX/CodeForces/