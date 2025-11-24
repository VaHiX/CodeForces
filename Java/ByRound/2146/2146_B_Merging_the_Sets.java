// Problem: CF 2146 B - Merging the Sets
// https://codeforces.com/contest/2146/problem/B

/*
 * Problem: B. Merging the Sets
 * 
 * Purpose: Determine if there exist at least three different ways to choose subsets 
 * such that every integer from 1 to m is covered by at least one selected subset.
 * 
 * Algorithm:
 * 1. For each test case, read n sets and m elements.
 * 2. Count frequency of each element across all sets.
 * 3. Check if all elements from 1 to m are present in at least one set.
 *    If not, output "NO".
 * 4. Count how many sets have at least one element that appears exactly once.
 *    These represent sets which contribute uniquely to coverage of some element.
 * 5. If total number of sets minus unique-coverage sets is greater than or equal to 2,
 *    then there are at least 3 valid combinations possible (since we can always add
 *    one more set to get a third combination).
 *
 * Time Complexity: O(L) where L = sum of sizes of all sets.
 * Space Complexity: O(m + n) for storing frequency array and list of sets.
 */
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            solve(sc);
        }
        sc.close();
    }
    public static void solve(Scanner sc) {
        int n = sc.nextInt(); // number of sets
        int m = sc.nextInt(); // range of integers [1, m]
        int[] freq = new int[m + 1]; // frequency count for each integer
        List<List<Integer>> sets = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int li = sc.nextInt(); // size of current set
            List<Integer> cur = new ArrayList<>(); // current set
            for (int j = 0; j < li; j++) {
                int num = sc.nextInt();
                cur.add(num);
                freq[num]++; // increment frequency of this number
            }
            sets.add(cur);
        }
        boolean possible = true;
        for (int i = 1; i <= m; i++) {
            if (freq[i] == 0) { // if any number is missing
                possible = false;
                break;
            }
        }
        if (!possible) {
            System.out.println("NO");
            return;
        }
        int req = 0; // count of sets having at least one element that appears exactly once
        for (int i = 0; i < n; i++) {
            boolean sign = false;
            for (int num : sets.get(i)) {
                if (freq[num] == 1) { // if this number only appears in this set
                    sign = true;
                    break;
                }
            }
            if (sign) {
                req++;
            }
        }
        // If remaining sets after removing those with unique elements is at least 2,
        // then enough choices to form multiple valid combinations (> 3)
        if (n - req >= 2) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    }
}


// https://github.com/VaHiX/CodeForces/