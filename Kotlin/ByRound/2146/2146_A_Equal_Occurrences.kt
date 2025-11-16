// Problem: CF 2146 A - Equal Occurrences
// https://codeforces.com/contest/2146/problem/A

/*
 * Problem: Equal Occurrences
 * Task: Find the length of the longest balanced subsequence in a non-decreasing array.
 *
 * Algorithm:
 * - Count frequency of each element.
 * - For each possible frequency f (from 1 to max frequency):
 *   - Calculate total length of subsequence where all elements appear at least f times.
 *   - Maximize this length across all f values.
 *
 * Time Complexity: O(n^2) in worst case, where n is the size of array.
 * Space Complexity: O(n) for storing frequencies and array.
 */
import java.util.StringTokenizer

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val n = readLine()!!.toInt() // Read size of array
        val st = StringTokenizer(readLine()!!) // Parse the input line
        val arr = IntArray(n) { st.nextToken().toInt() } // Convert to integer array
        
        // Count frequency of each element
        val freqMap = mutableMapOf<Int, Int>()
        for (num in arr) {
            freqMap[num] = freqMap.getOrDefault(num, 0) + 1
        }
        
        // Extract frequencies
        val frequencies = freqMap.values.toList()
        val maxFreq = frequencies.maxOrNull() ?: 0 // Get maximum frequency
        
        var answer = 0
        // For each possible frequency f from 1 to max frequency
        for (f in 1..maxFreq) {
            var length = 0
            // Count how many elements have frequency >= f
            for (cnt in frequencies) {
                if (cnt >= f) length += f // Add f to total length for each such element
            }
            answer = maxOf(answer, length) // Keep maximum length found
        }
        println(answer)
    }
}


// https://github.com/VaHiX/CodeForces/