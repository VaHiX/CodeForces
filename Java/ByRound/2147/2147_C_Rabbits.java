// Problem: CF 2147 C - Rabbits
// https://codeforces.com/contest/2147/problem/C

/*
 * Problem: Rabbits
 * Purpose: Determine if it's possible to place rabbits in empty pots such that none jump,
 *          respecting the rules about direction and interference between rabbits.
 *
 * Approach:
 * - For each group of consecutive zeros (empty pots), check if we can assign directions
 *   to rabbits so no two rabbits jump into the same pot or interfere.
 * - A greedy approach is used: for each group of zeros, try to assign left/right
 *   directions optimally, ensuring that rabbits don't cause conflict.
 *
 * Time Complexity: O(n) where n is the length of the string s. Each character is visited at most a few times.
 * Space Complexity: O(n) due to storing indices of zeros and boolean arrays for checking validity.
 */
import java.util.*;
public class Main {
    static boolean isValidBinary(String bin) {
        int len = bin.length();
        List<Integer> zeros = new ArrayList<>();
        for (int i = 0; i < len; i++) {
            if (bin.charAt(i) == '0') zeros.add(i); // Collect indices of all zeros
        }
        if (zeros.isEmpty()) return true; // No empty pots, no conflicts possible
        
        boolean[] leftOk = new boolean[len];
        boolean[] rightOk = new boolean[len];
        for (int z : zeros) {
            // Check if placing a rabbit at position z allows it to look left
            leftOk[z] = z == 0 || bin.charAt(z - 1) == '0' || (z >= 2 && bin.charAt(z - 2) == '0' && bin.charAt(z - 1) == '1');
            // Check if placing a rabbit at position z allows it to look right
            rightOk[z] = z == len - 1 || bin.charAt(z + 1) == '0' || (z + 2 < len && bin.charAt(z + 1) == '1' && bin.charAt(z + 2) == '0');
        }
        
        int index = 0;
        while (index < zeros.size()) {
            int groupEnd = index;
            // Find the end of current group of consecutive zeros
            while (groupEnd + 1 < zeros.size() && zeros.get(groupEnd + 1) == zeros.get(groupEnd) + 2 
                   && bin.charAt(zeros.get(groupEnd) + 1) == '1') {
                groupEnd++;
            }
            
            // Process this group of zeros
            if (!processZeroGroup(zeros, leftOk, rightOk, index, groupEnd)) return false;
            index = groupEnd + 1;
        }
        return true;
    }
    
    static boolean processZeroGroup(List<Integer> zeros, boolean[] leftOk, boolean[] rightOk, int start, int end) {
        // Check if the first position in the group can look left or right
        boolean canLeft = leftOk[zeros.get(start)];
        boolean canRight = rightOk[zeros.get(start)];
        if (!canLeft && !canRight) return false; // No valid direction for first rabbit
        
        // Traverse rest of the group, updating allowed directions greedily
        for (int i = start + 1; i <= end; i++) {
            boolean nextLeft = canRight && leftOk[zeros.get(i)];
            boolean nextRight = canLeft && rightOk[zeros.get(i)];
            canLeft = nextLeft;
            canRight = nextRight;
            if (!canLeft && !canRight) return false;
        }
        
        return true;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            int n = sc.nextInt();
            String s = sc.next();
            System.out.println(isValidBinary(s) ? "YES" : "NO");
        }
    }
}


// https://github.com/VaHiX/CodeForces/