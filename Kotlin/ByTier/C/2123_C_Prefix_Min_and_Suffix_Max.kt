// Problem: CF 2123 C - Prefix Min and Suffix Max
// https://codeforces.com/contest/2123/problem/C

/*
 * Problem: C. Prefix Min and Suffix Max
 * Purpose: For each element in the array, determine if it's possible to reduce the array to a single element equal to that value using operations:
 *          - Replace any prefix with its minimum value
 *          - Replace any suffix with its maximum value
 *
 * Algorithm:
 * 1. For each position i, check if a[i] can be the final remaining element.
 *    This happens if and only if:
 *    - a[i] is the minimum of all elements to its left (including itself)
 *    - a[i] is the maximum of all elements to its right (including itself)
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the result array
 */
fun Solve(a: IntArray): String {
    val n = a.size
    val vecA = CharArray(n) { '0' }
    
    // Mark positions that can be the minimum of some prefix (from left to right)
    var minLeft = a[0]
    vecA[0] = '1'  // First element can always be the minimum of prefix [0..0]
    for (i in 1 until n) {
        if (a[i] < minLeft) {
            minLeft = a[i]
            vecA[i] = '1'
        }
    }
    
    // Mark positions that can be the maximum of some suffix (from right to left)
    var maxRight = a[n - 1]
    vecA[n - 1] = '1'  // Last element can always be the maximum of suffix [n-1..n-1]
    for (i in n - 2 downTo 0) {
        if (a[i] > maxRight) {
            maxRight = a[i]
            vecA[i] = '1'
        }
    }
    
    return vecA.joinToString("")
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val a = readLine()!!.split(" ").map { it.toInt() }.toIntArray()
        println(Solve(a))
    }
}


// https://github.com/VaHiX/CodeForces/