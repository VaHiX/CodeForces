// Problem: CF 2139 A - Maple and Multiplication
// https://codeforces.com/contest/2139/problem/A

/*
 * Problem: A. Maple and Multiplication
 * Purpose: Determine the minimum number of operations to make two positive integers a and b equal.
 *          Each operation allows multiplying either a or b by any positive integer.
 *
 * Algorithms/Techniques:
 * - Mathematical analysis of divisibility and equality conditions
 * - Greedy approach based on modular arithmetic checks
 *
 * Time Complexity: O(1) per test case (constant time operations)
 * Space Complexity: O(1) (only using a fixed amount of extra space)
 */

fun main() {
    var v = readLine()!!.toInt() // Read number of test cases
    while(v > 0) {
        val input = readLine()!! // Read the two integers a and b
        val parts = input.split(" ") // Split input string into parts
        val a = parts[0].toInt() // First integer
        val b = parts[1].toInt() // Second integer
        if(a == b) {
            println(0) // Already equal, no operations needed
        } else if(a % b == 0 || b % a == 0) {
            println(1); // One is divisible by the other, one operation suffices
        } else {
            println(2); // Neither divides the other, two operations required
        }
        v--; // Decrement counter for next test case
    }
}


// https://github.com/VaHiX/codeForces/