// Problem: CF 2123 E - MEX Count
// https://codeforces.com/contest/2123/problem/E

/*
E. MEX Count

Purpose:
This code calculates the number of possible MEX (Minimum Excluded Value) values 
that can be obtained by removing exactly k elements from an array of non-negative integers,
for all k from 0 to n.

Algorithm:
- For each test case:
  1. Count frequency of each number in range [0, n)
  2. Group numbers by their frequencies in a map
  3. Compute the initial MEX (which is the first missing non-negative integer)
  4. For each k from 0 to n:
     - Adjust the set of possible MEXs based on how many elements we remove
     - Count how many valid MEX values exist

Time Complexity: O(n log n) due to sorting and operations over n elements.
Space Complexity: O(n) for storing frequency counts and auxiliary structures.

*/
import java.io.FileInputStream
fun main() {
    var t = readLine()!!.toInt()
    while (t != 0) {
        var n = readLine()!!.toInt()
        val a = readLine()!!.split(" ").map { it.toInt() }.sorted() // O(n log n)
        val countByNumber = IntArray(n) { 0 } // O(n)
        for (i in 0 until n) {
            if (a[i] in 0..<n) { // Only consider values within [0, n)
                countByNumber[a[i]]++
            }
        }
        val numberSetByFrequency = mutableMapOf<Int, MutableSet<Int>>() // O(n)
        for (i in 0 until n) {
            numberSetByFrequency.putIfAbsent(countByNumber[i], mutableSetOf()) // O(1) amortized
            numberSetByFrequency[countByNumber[i]]!!.add(i) // O(1) amortized
        }
        var ans = 0 // Initialize to count of unique elements
        for (i in 0 until n) {
            if (countByNumber[i] == 0) { // Stop when we hit a missing number
                break
            } else {
                ans++
            }
        }
        val answerSet = mutableSetOf<Int>() // Stores current possible MEXs
        answerSet.add(ans)
        print(answerSet.size)
        print(" ")
        for (i in 0 until n) { // Iterating over frequencies
            answerSet.remove(n - i) // Remove those values that are no longer relevant
            numberSetByFrequency[i + 1]?.let { // If there's a frequency group
                it.forEach { x ->
                    if (x < ans) {
                        answerSet.add(x) // Add valid indices to set
                    }
                }
            }
            print(answerSet.size)
            print(" ")
        }
        println()
        --t
    }
}


// https://github.com/VaHiX/CodeForces/