// Problem: CF 2141 C - Minimum on Subarrays
// https://codeforces.com/contest/2141/problem/C

/*
C. Minimum on Subarrays
time limit per test1 second
memory limit per test256 megabytes

Algorithm: This solution uses a simulation approach to compute the sum of minimums of all subarrays.
It simulates the process by maintaining a data structure that supports push/pop from both ends,
and calculates the contribution of each element as a minimum in various subarrays.

Approach:
- For each index r (right endpoint of subarray), we simulate how elements are pushed and popped
  to maintain the correct state for computing minima.
- When r is even, we reverse the order of pushing elements from right to left to ensure
  that the minimum can be efficiently accessed during operations.
- When r is odd, we build incrementally from left to right.

Time Complexity: O(n^2)
Space Complexity: O(n^2) due to the number of operations being bounded by n*(n+2)

The algorithm ensures that for every subarray [l,r], the minimum value is added exactly once to sum.
*/
fun main() {
    val n = readLine()!!.trim().toInt()
    val out = StringBuilder()
    var k = 0
    for (r in 0 until n) {
        out.append("pushback a[$r]\n") // Push the current element to back of structure
        k++
        if (r > 0 && r % 2 == 0) { // If r is even and greater than 0, pop front
            out.append("popfront\n")
            k++
        }
        if (r % 2 == 0) { // When r is even: process from right to left
            for (l in r downTo 0) {
                out.append("min\n") // Compute minimum of current window
                k++
                if (l > 0) {
                    out.append("pushfront a[${l - 1}]\n") // Push previous element to front
                    k++
                }
            }
        } else { // When r is odd: process from left to right
            for (l in 0..r) {
                out.append("min\n")
                k++
                if (l < r) {
                    out.append("popfront\n") // Pop front to move window
                    k++
                }
            }
        }
    }
    println(k)
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/