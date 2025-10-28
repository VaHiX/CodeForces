// Problem: CF 2156 B - Strange Machine
// https://codeforces.com/contest/2156/problem/B

/**
 * Problem: Strange Machine
 * 
 * This solution simulates the process of moving through a circular array of machines,
 * where each machine performs an operation on a value 'a' (either divide by 2 or subtract 1).
 * The simulation continues until 'a' becomes 0.
 * 
 * Algorithm:
 * - For each query (initial value a), simulate the process:
 *   - Start at machine 1 (index 0)
 *   - Apply the operation of the current machine on 'a'
 *   - Move to the next machine (circular)
 *   - Repeat until 'a' becomes 0
 * 
 * Optimization:
 * - When there are no 'B' machines, 'a' can only be reduced by 1 each step, so the time is just 'a'.
 * - When processing consecutive 'A's, instead of applying one by one (which could be slow for large 'a'),
 *   we group them and reduce 'a' by the count of A's in sequence.
 * 
 * Time Complexity: O(n * q * log a) where n is number of machines, q queries, a is max initial value
 * Space Complexity: O(1) excluding input storage
 */
fun main() {
    val testCases = readLine()!!.toInt()
    repeat(testCases) {
        val (strLen, queryCount) = readLine()!!.split(" ").map { it.toInt() }
        val sequence = readLine()!!
        val queries = readLine()!!.split(" ").map { it.toLong() }
        val containsB = sequence.contains('B')
        queries.forEach { value ->
            if (!containsB) {
                // If there are no 'B' machines, we only have 'A' operations which subtract 1 each time.
                println(value)
                return@forEach
            }
            var remaining = value
            var result = 0L // Total seconds elapsed
            var index = 0
            while (remaining > 0) {
                when (sequence[index]) {
                    'B' -> {
                        // Perform floor division by 2
                        remaining = remaining shr 1
                        result++
                        index = (index + 1) % strLen
                    }
                    else -> {
                        // Process consecutive 'A's efficiently
                        var current = index
                        var count = 0
                        while (sequence[current] == 'A') {
                            count++
                            current = (current + 1) % strLen
                        }
                        if (remaining > count) {
                            // If remaining > count of A's, subtract the entire count
                            remaining -= count
                            result += count
                            index = current
                        } else {
                            // If remaining <= count, then it's the last 'A' that will make it zero
                            result += remaining
                            remaining = 0
                        }
                    }
                }
            }
            println(result)
        }
    }
}


// https://github.com/VaHiX/CodeForces/