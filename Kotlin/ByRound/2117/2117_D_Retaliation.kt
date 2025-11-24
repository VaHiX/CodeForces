// Problem: CF 2117 D - Retaliation
// https://codeforces.com/contest/2117/problem/D

/**
 * Problem: D. Retaliation
 *
 * Purpose: Determine if an array can be reduced to all zeros using two specific operations:
 *          1. Decrease each element `a[i]` by its index `i`.
 *          2. Decrease each element `a[i]` by `n - i + 1`.
 *
 * Algorithm:
 * - For a valid solution to exist, the initial array must be an arithmetic progression.
 * - If it's an arithmetic progression:
 *   - Let the first element be `x`, common difference be `d`, and length `n`.
 *   - We derive equations based on the operations:
 *     - Operation 1: subtracts `i` from each element → contributes `-i` to the sum.
 *     - Operation 2: subtracts `n-i+1` from each element → contributes `-(n-i+1)` to the sum.
 *   - The net effect can be modeled as:
 *     - Total reduction = (k1 * sum of indices) + (k2 * sum of (n-i+1)) where k1, k2 are number of operations.
 *   - After simplifying and solving for valid non-negative integer solutions:
 *     - Let firstElement = x, difference = d, length = n
 *     - We compute derived values y and x such that they satisfy the constraints.
 *
 * Time Complexity: O(n) per test case.
 * Space Complexity: O(1) excluding input reading.
 */
fun main() {
    val reader = System.`in`.bufferedReader()
    val testCases = reader.readLine().toInt()
    repeat(testCases) {
        val length = reader.readLine().toInt()
        val sequence = reader.readLine().split(" ").map { it.toInt() }
        println(if (isRetaliationPossible(sequence)) "YES" else "NO")
    }
}

/**
 * Main function to decide if array can be reduced to zeros.
 */
fun isRetaliationPossible(sequence: List<Int>): Boolean {
    if (!isArithmeticProgression(sequence)) return false // Check if it's arithmetic progression
    val difference = getCommonDifference(sequence)
    val totalElements = sequence.size
    return hasValidSolution(sequence[0], difference, totalElements)
}

/**
 * Checks whether the list forms an arithmetic progression.
 */
fun isArithmeticProgression(sequence: List<Int>): Boolean {
    if (sequence.size < 2) return false // Any array with less than 2 elements can't form a valid AP
    val diff = sequence[1] - sequence[0]
    for (i in 2 until sequence.size) {
        if (sequence[i] - sequence[i - 1] != diff) return false
    }
    return true
}

/**
 * Returns the common difference between elements.
 */
fun getCommonDifference(sequence: List<Int>): Int {
    return sequence[1] - sequence[0]
}

/**
 * Determines whether the given arithmetic sequence has a valid integer solution for transformation.
 *
 * @param firstElement First element of the sequence.
 * @param difference Common difference.
 * @param length Length of the sequence.
 * @return true if a valid non-negative x, y exists, otherwise false.
 */
fun hasValidSolution(firstElement: Int, difference: Int, length: Int): Boolean {
    val numerator = firstElement - difference // Derivation from mathematical relationship
    val denominator = length + 1
    if (numerator < 0 || numerator % denominator != 0) return false // Check for valid integer division
    val y = numerator / denominator // Derived value based on equations
    val x = difference + y // Calculate final value of x based on system of linear equations
    return x >= 0 && y >= 0 // Ensure both values are non-negative
}


// https://github.com/VaHiX/CodeForces/