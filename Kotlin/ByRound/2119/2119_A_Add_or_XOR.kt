// Problem: CF 2119 A - Add or XOR
// https://codeforces.com/contest/2119/problem/A

/*
 * Problem: Make 'a' equal to 'b' using two operations:
 *          1. Increment (a += 1), cost = x
 *          2. XOR with 1 (a ^= 1), cost = y
 *
 * Algorithms/Techniques: Simulation, Bit manipulation
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

fun main() {
    val T = readln().toInt()
    repeat(T) {
        val (a, b, x, y) = readln().split(" ").map { it.toLong() }
        val result = when {
            a == b -> 0L // No operations needed if a already equals b
            a > b -> {
                // If a > b, we can only decrease a using XOR with 1 (a ^= 1)
                // This only works if b = a - 1 because XOR with 1 toggles last bit
                if ((a and 1L) == 1L && b == a - 1) y
                else -1L // Otherwise impossible to reach b from a
            }
            else -> {
                // If a < b, we increase a using +1 operations
                // For the number of steps (b - a), we decide for each step:
                //   - Use XOR if it's an odd number: cost is y
                //   - Else use +1 operation: cost is min(x, y)
                var r = 0L
                for (i in a until b) {
                    r += if ((i and 1L) == 1L) x else minOf(x, y)
                }
                r
            }
        }
        println(result)
    }
}


// https://github.com/VaHiX/CodeForces/