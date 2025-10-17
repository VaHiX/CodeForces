// Problem: CF 2117 B - Shrink
// https://codeforces.com/contest/2117/problem/B

/*
 * Problem: B. Shrink
 * Purpose: Construct a permutation of length n that maximizes the number of shrink operations.
 * Algorithm: 
 *   - Alternately place odd and even numbers from both ends of the array.
 *   - This creates a "zigzag" pattern that maximizes the number of peaks (local maxima),
 *     which corresponds to the maximum number of shrink operations.
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the result array
 */
fun main() {
    solve()
}

private fun solve() {
    repeat(readInt()) {
        val n = readInt()
        var item = 1
        var items = IntArray(n)
        var start = 0
        var end = n - 1
        for (i in 1..n) {
            if (i % 2 == 1) {
                // Place odd-numbered elements at the start (left side)
                items[start++] = i
            } else {
                // Place even-numbered elements at the end (right side)
                items[end--] = i
            }
        }
        println(items.joinToString(" "))
    }
}

private fun readLn() = readLine()!! 
private fun readInt() = readLn().toInt() 
private fun readLong() = readLn().toLong() 
private fun readStrings() = readLn().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } 
private fun readLongs() = readStrings().map { it.toLong() } 


// https://github.com/VaHiX/CodeForces/