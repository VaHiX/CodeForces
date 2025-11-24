// Problem: CF 2153 A - Circle of Apple Trees
// https://codeforces.com/contest/2153/problem/A

/*
 * Task: A. Circle of Apple Trees
 * Purpose: Determine the maximum number of apples that can be eaten from a circular arrangement
 *          of apple trees, where each tree has an apple with a certain beauty value.
 *          You may only eat an apple if its beauty is strictly greater than the last eaten apple.
 * 
 * Algorithm: Greedy approach using Set to track unique beauties in order
 * Time Complexity: O(n) per test case, where n is the number of trees
 * Space Complexity: O(n) for storing the set of unique beauties
 * 
 * Techniques:
 * - Use a Set for tracking unique beauty values encountered so far
 * - Iterating through all elements once to simulate optimal eating strategy
 * 
 * Input:
 *   t - Number of test cases
 *   n - Number of apple trees
 *   b - Array of beauty values for apples on each tree
 *   
 * Output:
 *   Maximum number of apples that can be eaten
 */

fun main() {
    val t = readln().toInt() // Read number of test cases
    repeat(t) {
        val n = readln().toInt() // Read number of trees
        val b = readln().split(' ').map { it.toInt() }.toSet() // Read beauty values and convert to set (unique values only)
        println(b.size) // Print the count of unique values in the set, which corresponds to max apples eaten
    }
}


// https://github.com/VaHiX/CodeForces/