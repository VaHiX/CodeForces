// Problem: CF 2148 A - Sublime Sequence
// https://codeforces.com/contest/2148/problem/A

/**
 * Problem: Sublime Sequence
 * 
 * Algorithm/Technique: Mathematical pattern recognition
 * 
 * Approach:
 * - Create a sequence of length n alternating between x and -x starting with x
 * - For example: x, -x, x, -x, x, ...
 * - The sum depends on whether n is even or odd:
 *   - If n is even: pairs of (x, -x) cancel out, giving sum = 0
 *   - If n is odd: all pairs cancel out except the last element which is x, giving sum = x
 * 
 * Time Complexity: O(t) where t is the number of test cases
 * Space Complexity: O(1) - only using constant extra space
 */
fun main() {
    val t = readLine()!!.toInt()  // Read number of test cases
    repeat(t) {
        val (x, n) = readLine()!!.split(" ").map { it.toInt() }  // Read x and n for current test case
        println(if (n % 2 == 0) 0 else x)  // If n is even, sum is 0; otherwise sum is x
    }
}


// https://github.com/VaHiX/codeForces/