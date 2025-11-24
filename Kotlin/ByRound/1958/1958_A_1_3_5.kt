// Problem: CF 1958 A - 1-3-5
// https://codeforces.com/contest/1958/problem/A

/*
 * Problem: Minimum number of 1-burle coins needed to pay exactly n burles
 * using coins of 1, 3, and 5 burles.
 *
 * Algorithm:
 * - For each test case, determine the minimum number of 1-burle coins required.
 * - Strategy:
 *   - Use as many 5-burle coins as possible to minimize the remaining amount.
 *   - Then use as many 3-burle coins as possible for the remainder.
 *   - If the final remainder is 1 or 2, we need to pay that with 1-burle coins.
 *   - However, if remainder is 4, we cannot use a 5-burle coin (as it would leave 4,
 *     and using 3-burle coins gives us 1 or 2 remaining, which requires fewer 1-burle coins).
 *
 * Time Complexity: O(1) per test case — constant time operation
 * Space Complexity: O(1) — only using a few variables
 */

fun main() {
    repeat(readln().toInt()) { // Read number of test cases and loop through them
        val n = readln().toInt() // Read the amount to pay
        
        // Check if n is less than 8 and not equal to 5
        // For these special cases, we compute modulo 3 to determine minimum 1-burle coins needed
        println(if ((n < 8) && (n != 5)) n % 3 else 0)
    }
}


// https://github.com/VaHiX/codeForces/