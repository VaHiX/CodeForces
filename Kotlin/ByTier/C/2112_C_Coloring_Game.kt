// Problem: CF 2112 C - Coloring Game
// https://codeforces.com/contest/2112/problem/C

/*
C. Coloring Game

Purpose:
This solution counts the number of ways Alice can choose 3 elements from an array such that no matter which element Bob chooses to color blue (from the 3 chosen), the sum of the red elements is strictly greater than the value of the blue element.

Algorithm:
- The approach leverages sorting and a two-pointer technique on sorted arrays.
- For each potential triplet (i, j, k) where i < j < k, we check if the sum of the first two elements in the triplet is > the third element.
- This ensures that regardless of which element Bob picks (including the one with smallest value), Alice still wins.

Time Complexity:
O(n^3) for brute-force triplets checking + sorting O(n log n)
Overall: O(n^3 + n log n)

Space Complexity:
O(n) for storing the array and temporary variables.
*/

fun main() {
    val t = readln().toInt()
    repeat(t) {
        val n = readln().toInt()
        val arr = readln().split(" ").map { it.toInt() }.sorted() // Sort input array
        val max = arr.last() // Maximum element
        var count = 0L // Count valid triplets
        
        // Iterate in reverse to optimize comparisons using two pointers
        for (c in n - 1 downTo 2) {
            var a = c - 2 // Start pointer
            var bDelta = 1 // Distance between a and b
            
            while (a >= 0) {
                // Adjust bDelta while conditions hold
                while (a + bDelta < c &&
                        (arr[a] + arr[a + bDelta] <= arr[c] ||
                                arr[a] + arr[a + bDelta] + arr[c] <= max)) {
                    bDelta++ // Increase delta to find valid b pointer
                }
                
                // Compute how many valid b values exist between a and c
                val toAdd = c - (a + bDelta)
                count += toAdd
                
                if (bDelta > 1) {
                    bDelta-- // Backtrack if necessary
                }
                a-- // Move a pointer left
            }
        }
        println(count)
    }
}


// https://github.com/VaHiX/CodeForces/