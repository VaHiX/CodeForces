// Problem: CF 2162 A - Beautiful Average
// https://codeforces.com/contest/2162/problem/A

/*
 * Problem: Beautiful Average
 * Purpose: Find the maximum possible average value of any subarray in the given array.
 * 
 * Algorithm: 
 * - For each test case, read the array elements.
 * - Since we are looking for the maximum average, and all elements are positive integers,
 *   the maximum average will always be the maximum element in the array.
 *   This is because taking a single element as a subarray gives the highest possible average
 *   when all elements are non-negative.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */
import java.util.*
fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        val n = scanner.nextInt()
        var m = Long.MIN_VALUE  // Initialize maximum to negative infinity
        repeat(n) {
            val x = scanner.nextLong()
            if (x > m) m = x  // Update maximum if current element is greater
        }
        println(m)  // Output the maximum element
    }
}


// https://github.com/VaHiX/CodeForces/