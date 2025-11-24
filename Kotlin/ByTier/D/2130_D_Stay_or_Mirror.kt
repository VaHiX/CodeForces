// Problem: CF 2130 D - Stay or Mirror
// https://codeforces.com/contest/2130/problem/D

/*
 * Problem: D. Stay or Mirror
 * Purpose: Given a permutation p, for each element we can choose to keep it as p[i] or set it to 2n - p[i].
 *          We want to minimize the number of inversions in resulting array a.
 * Algorithm:
 *   - Use Binary Indexed Tree (Fenwick Tree) to efficiently count inversions and updates.
 *   - For each element, precompute how many elements are larger than current element on left (leftCount)
 *     and right (rightCount) side.
 *   - Total inversions = baseInversions + sum of (rightCount[i] - leftCount[i]) for all i where the delta is negative.
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n)
 */
import java.io.*
import java.util.*
fun main() {
    val input = BufferedReader(InputStreamReader(System.`in`))
    val output = PrintWriter(System.out)
    fun readInt(): Int {
        var token = input.readLine()
        while (token == null || token.trim().isEmpty()) {
            token = input.readLine()
        }
        return token.trim().split("\\s+".toRegex())[0].toInt()
    }
    fun readInts(): List<Int> {
        var line = input.readLine()
        while (line == null || line.trim().isEmpty()) {
            line = input.readLine()
        }
        return line.trim().split("\\s+".toRegex()).map { it.toInt() }
    }
    class BinaryIndexedTree(private val maxSize: Int) {
        private val tree = LongArray(maxSize + 5)
        fun add(position: Int, value: Long) {
            var pos = position
            while (pos <= maxSize) {
                tree[pos] += value
                pos += pos and (-pos)
            }
        }
        fun sum(position: Int): Long {
            var pos = position
            var result = 0L
            while (pos > 0) {
                result += tree[pos]
                pos -= pos and (-pos)
            }
            return result
        }
        fun clear() {
            tree.fill(0L)
        }
    }
    fun solve() {
        val n = readInt()
        val arr = readInts()
        val bit = BinaryIndexedTree(n)
        val leftCount = LongArray(n)
        val rightCount = LongArray(n)
        var baseInversions = 0L
        for (i in 0 until n) {
            leftCount[i] = bit.sum(n) - bit.sum(arr[i]) // Count of numbers greater than arr[i] to the left
            baseInversions += leftCount[i]
            bit.add(arr[i], 1L)
        }
        bit.clear()
        for (i in n - 1 downTo 0) {
            rightCount[i] = bit.sum(n) - bit.sum(arr[i]) // Count of numbers greater than arr[i] to the right
            bit.add(arr[i], 1L)
        }
        var answer = baseInversions
        for (i in 0 until n) {
            val delta = rightCount[i] - leftCount[i]
            if (delta < 0) {
                answer += delta  // Adjusting based on optimal choice
            }
        }
        output.println("$answer ")
    }
    val testCases = readInt()
    repeat(testCases) {
        solve()
    }
    output.close()
    input.close()
}


// https://github.com/VaHiX/CodeForces/