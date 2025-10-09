// Problem: CF 2114 A - Square Year
// https://codeforces.com/contest/2114/problem/A

/*
 * Problem: Square Year
 * 
 * Purpose: Given a 4-digit year string s, determine if it can be expressed as (a + b)^2,
 *          where a and b are non-negative integers. If possible, output such a and b;
 *          otherwise, output -1.
 *
 * Algorithm:
 *   - For each test case:
 *     1. Convert the string s to an integer n.
 *     2. Compute the square root of n, take its integer part sqrt.
 *     3. Check if sqrt^2 equals n (i.e., n is a perfect square).
 *     4. If it's a perfect square, output "0 sqrt" (a=0, b=sqrt).
 *     5. Otherwise, output "-1".
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), only using constant extra space.
 */

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val s = readLine()!! // Read the 4-digit year string
        val n = s.toInt() // Convert string to integer
        val sqrt = kotlin.math.sqrt(n.toDouble()).toInt() // Calculate integer square root
        
        if (sqrt * sqrt == n) { // Check if n is a perfect square
            println("0 $sqrt") // If yes, output 0 and the square root
        } else {
            println("-1") // If not, output -1
        }
    }
}


// https://github.com/VaHiX/CodeForces/