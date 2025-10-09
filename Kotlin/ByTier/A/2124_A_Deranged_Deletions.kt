// Problem: CF 2124 A - Deranged Deletions
// https://codeforces.com/contest/2124/problem/A

/*
 * Problem: A. Deranged Deletions
 * 
 * Purpose:
 *   Given an array of integers, determine if we can delete some elements to form a derangement.
 *   A derangement is defined as an array where no element equals its sorted counterpart.
 * 
 * Algorithm:
 *   - For each test case, check if the array already forms a derangement.
 *   - If not, find any pair of elements (i,j) such that a[i] > a[j].
 *   - Delete one of them (preferably a[i]) to make sure that sorted version is different from original.
 *   - This approach works because even after deleting a single element, if we have at least 2 non-unique elements,
 *     a derangement can be formed by deleting only one copy of the duplicate element.
 * 
 * Time Complexity:
 *   O(n^2) in worst case due to nested loops for finding violating pair.
 *   However, since n <= 100, this is acceptable.
 * 
 * Space Complexity:
 *   O(n) for storing the input array.
 */

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val n = readLine()!!.toInt() // Read length of array
        val a = readLine()!!.split(" ").map { it.toInt() }.toIntArray() // Read the array elements
        var ok = false // Flag to check if we found a violation (a[i] > a[j])
        var x = 0 // Index of first element in violating pair
        var y = 0 // Index of second element in violating pair
        for (i in 0 until n) {
            if (ok) break // If we already found a violation, stop searching
            for (j in i + 1 until n) {
                if (a[i] > a[j]) { // Found a pair where current element is greater than next element
                    x = i
                    y = j
                    ok = true // Mark that we've found such a pair
                    break
                }
            }
        }
        if (!ok) {
            println("NO") // No violation meaning array is already sorted or all equal - not derangement
        } else {
            println("YES")
            println("2") // We will output 2 elements (since we only delete one element to get a valid derangement)
            println("${a[x]} ${a[y]}") // Output both elements involved in violation
        }
    }
}


// https://github.com/VaHiX/CodeForces/