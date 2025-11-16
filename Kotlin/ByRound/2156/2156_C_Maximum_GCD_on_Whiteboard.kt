// Problem: CF 2156 C - Maximum GCD on Whiteboard
// https://codeforces.com/contest/2156/problem/C

/*
 * Problem: Maximum GCD on Whiteboard
 * 
 * Algorithm:
 * - Use a frequency histogram to count occurrences of each number.
 * - For each candidate gcd value (from n down to 1), determine how many numbers
 *   can be transformed or removed to make all remaining numbers divisible by this candidate.
 * - Use prefix sums to efficiently calculate how many numbers are ≤ some threshold.
 * - A number x can be split into three parts (a, b, c) such that a + b + c = x,
 *   and only a and c are kept. This effectively allows us to "reduce" x to a value
 *   that's at most x/3 in some contexts, but more importantly, it lets us increase
 *   our ability to find common factors.
 * 
 * Time Complexity: O(n * sqrt(n)) in the worst case due to checking candidates
 * Space Complexity: O(n) for histogram and prefix sum arrays
 */

fun main() {
    repeat(readLine()!!.toInt()) {
        val input = readLine()!!.split(" ").map { it.toInt() }
        val arraySize = input[0]
        val allowedChanges = input[1]
        val dataPoints = readLine()!!.split(" ").map { it.toInt() }
        val histogram = IntArray(arraySize + 1)
        for (value in dataPoints) {
            histogram[value]++
        }
        val cumulative = IntArray(arraySize + 1)
        for (i in 1..arraySize) {
            cumulative[i] = cumulative[i - 1] + histogram[i]
        }
        var answer = 1
        for (candidate in arraySize downTo 1) {
            // Calculate the threshold for numbers that are at most 4*candidate - 1
            val threshold = minOf(arraySize, (candidate shl 2) - 1)
            val totalBelow = if (threshold >= 1) cumulative[threshold] else 0
            var acceptableCount = 0
            // Count numbers that are exactly candidate, 2*candidate, or 3*candidate
            if (candidate <= arraySize) {
                acceptableCount += histogram[candidate]
            }
            val double = candidate shl 1
            if (double <= arraySize) {
                acceptableCount += histogram[double]
            }
            val triple = candidate * 3
            if (triple <= arraySize) {
                acceptableCount += histogram[triple]
            }
            // Invalid are the ones that are less than or equal to threshold but 
            // not one of the acceptable candidates
            val invalid = totalBelow - acceptableCount
            // If number of invalid moves needed is within allowedChanges, we can try this candidate
            if (invalid <= allowedChanges) {
                answer = candidate
                break
            }
        }
        println(answer)
    }
}


// https://github.com/VaHiX/CodeForces/