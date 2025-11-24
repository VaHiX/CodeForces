// Problem: CF 2162 C - Beautiful XOR
// https://codeforces.com/contest/2162/problem/C

import java.util.*

/*
 * Problem: C. Beautiful XOR
 * 
 * Algorithm:
 * - The key idea is to use XOR operations to transform 'a' into 'b'.
 * - If a == b, no operations are needed.
 * - Otherwise, we determine the highest bit where a and b differ.
 * - If b is larger than the maximum value achievable with the current a, it's impossible.
 * - If the XOR of a and b is less than or equal to a, we can directly transform in one step.
 * - Otherwise, we use two steps: first transform a to a maximum value (m) using x = m XOR a,
 *   then transform m to b using y = m XOR b.
 * 
 * Time Complexity: O(1) - The algorithm performs a constant number of operations.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        val a = scanner.nextLong()
        val b = scanner.nextLong()
        if (a == b) {
            println(0)
            return@repeat
        }
        var k = 0
        var tmp = a
        while ((1L shl k) <= tmp) k++ // Find the highest bit position
        k--
        val m = (1L shl (k + 1)) - 1 // Maximum value with the same number of bits as a
        if (b > m) {
            println(-1)
            return@repeat
        }
        val s = a xor b // Difference between a and b in binary
        if (s <= a) {
            println(1)
            println(s)
        } else {
            val x = m xor a // First transformation to max value
            val y = m xor b // Second transformation to target value
            println(2)
            println("$x $y")
        }
    }
}


// https://github.com/VaHiX/CodeForces/