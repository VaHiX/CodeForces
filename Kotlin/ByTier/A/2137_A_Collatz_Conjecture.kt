// Problem: CF 2137 A - Collatz Conjecture
// https://codeforces.com/contest/2137/problem/A

/*
 * Problem: Collatz Conjecture Reverse Engineering
 * 
 * Purpose: Given k iterations and final value x, find any possible initial value of x
 *          that would lead to the given final value after k operations.
 * 
 * Algorithm:
 * - For each test case, start from the given x and reverse engineer the process.
 * - At each step:
 *   - If x is odd and (x-1) is divisible by 3, then a previous value could be (x-1)/3.
 *     This corresponds to reversing a "3*x + 1" operation.
 *   - Otherwise, reverse a "x/2" operation by multiplying by 2.
 * 
 * Time Complexity: O(k), where k is the number of iterations per test case.
 * Space Complexity: O(1), only using constant extra space.
 */

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val (kStr, xStr) = readLine()!!.split(" ")
        var k = kStr.toLong()
        var x = xStr.toLong()
        while (k > 0) {
            // Check if we can reverse a "3*x + 1" operation
            if ((x - 1) % 3 == 0L) {
                val prev = (x - 1) / 3
                // Ensure the previous value is positive and odd (to make sense of reverse operation)
                if (prev > 0 && prev % 2 == 1L) {
                    x = prev
                    k--
                    continue
                }
            }
            // Otherwise, reverse a "x/2" operation by multiplying by 2
            x *= 2
            k--
        }
        println(x)
    }
}


// https://github.com/VaHiX/codeForces/