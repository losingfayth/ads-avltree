/**
 * Tests the implementation of a Binary Search Tree (BST) and an AVL Tree
 * and provides a comparison of the height properties of both trees across a
 * set of data.
 * 
 * 1. For every number `n` where 10 <= n <= 20, generates a list of numbers of
 *  length `m` where m = 2^n and populates that list with the values
 *  [1, 2, 3, ... m].
 * 
 * 2. For every list, performs a number of 'inversions' on the list, swapping
 *  the value at a randomly generated index `x` with the value at the index
 *  (x + 1) iff x < (x + 1). Performs such inversions m times and 100m times,
 *  generating two lists for each n that both contain partially-sorted data.
 * 
 * 3. Builds a BST and an AVL Tree for each partially-sorted list from Step 2.
 * 
 * 4. Performs Step 2 and Step 3 one hundred (100) times, keeping track of the
 *  average height of both types of structure for a list of m keys.
 * 
 * 5. Outputs the average heights for the list of m keys to the console for
 *  comparison.
 * 
 * * *
 * 
 * Dr. Coles,
 * 
 *  I recommend you revisit the writeup for this project and reword it for
 *  clarity's sake. The primary reason is that you reference `n` frequently
 *  in both the writeup and your output. The issue is, `n` is not a consistent
 *  variable. In one part of things, `n` which you want 2 to be raised to,
 *  producing 2^n keys. However, immediately after words, `n` is the number of
 *  keys produced. So, essentially, in the writeup, n = 2^n. You can see this
 *  most clearly in your "results" page where it starts with `n`, then says
 *  `2^n` right next to it, then goes on to `n inversions` and `100n`.
 *  Following this template without reading the writeup closely (or asking a
 *  classmate who'd already turned in the project for clarification, in my case)
 *  results in absolutely massive BSTs.
 * 
 *  Just a thought!
 * 
 * All the best,
 * 
 * @author fayth quinn
*/

#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <vector>

#include "bst.cpp"
#include "avl_tree.cpp"
//#include "ren/bst.cpp"
//#include "ren/avl_tree.cpp"

void trial(int m, int fact, std::vector<int> arr, int &bst_height, int &avl_height, std::mt19937 &seed);
bool invert(int &x, int &y);

int main() {
    std::random_device r;
    std::mt19937 gen(r());

    int n_lower = 10; // The lowest `n` value to test
    int n_upper = 20; // The higher `n` value to test

    int trials = 10; // The number of trials to perform

    std::cout << std::endl;

    std::cout << std::setw(4) << " ";
    std::cout << std::setw(12) << " ";
    std::cout << std::setw(24) << "m inversions";
    std::cout << std::setw(24) << "100m inversions";
    std::cout << std::endl << std::endl;

    std::cout << std::setw(4) << "n";
    std::cout << std::setw(12) << "2^n";
    std::cout << std::setw(12) << "BST";
    std::cout << std::setw(12) << "AVL";
    std::cout << std::setw(12) << "BST";
    std::cout << std::setw(12) << "AVL";
    std::cout << std::endl;

    std::cout << "--------------------------------";
    std::cout << "--------------------------------";
    std::cout << std::endl;

    for (int n = n_lower; n <= n_upper; n++) {

        int bstn_avg = 0;
        int avln_avg = 0;
        int bst100_avg = 0;
        int avl100_avg = 0;

        long m = pow(2, n);
        std::vector<int> arr(m);

        for (int i = 0; i < m; i++) arr[i] = i + 1;

        for (int i = 0; i < trials; i++) {
            trial(m, 1, arr, bstn_avg, avln_avg, gen);
            trial(m, 100, arr, bst100_avg, avl100_avg, gen);
        }

        bstn_avg /= trials;
        avln_avg /= trials;
        bst100_avg /= trials;
        avl100_avg /= trials;

        std::cout << std::setw(4) << n;
        std::cout << std::setw(12) << m;
        std::cout << std::setw(12) << bstn_avg;
        std::cout << std::setw(12) << avln_avg;
        std::cout << std::setw(12) << bst100_avg;
        std::cout << std::setw(12) << avl100_avg;
        std::cout << std::endl;
        
    }

    return 0;
}

/**
 * Performs a trial by generating a list of size `m`, inverting it (m * fact)
 * times, builds a BST and an AVL tree from the list, then adds the height of
 * those trees to the running average.
 * 
 * @param m The number of keys in the list
 * @param fact The factor to multiply m by to get the desired number of
 *          inversions (1m inversions or 100m inversions, in this
 *          implementation)
 * @param arr The ordered list of size `m`
 * @param bst_height The running total of BST heights across all trials
 * @param avl_height The running total of AVL Tree heights across all trials
 * @param seed The seed for the random number generator
*/
void trial(int m, int fact, std::vector<int> arr, int &bst_height, int &avl_height, std::mt19937 &seed) {

    // Provide the random number generator a range of values to generate for
    std::uniform_int_distribution<int> dist(0, m - 1);

    for (int i = 0; i < (m * fact); ) {
        // Generate random index with given seed
        int rand = dist(seed);
        // Increment counter iff inversion is performed
        if (invert(arr[rand], arr[rand + 1])) i++;
    }

    // Build trees with the list and record their heights
    BST<int> bst;
    AvlTree<int> avl;

    for (int i = 0; i < m; i++) {
        bst.insert(arr[i]);
        avl.insert(arr[i]);
    }

    bst_height += bst.height();
    avl_height += avl.height();
}

/**
 * Compares two numbers, `x` ane `y`, where x is the number at the lower index
 * in a list and y is the number immediately following it in that list. Swaps
 * the values of the numbers iff x < y.
 * 
 * @param x The number at the lower list index
 * @param y The number at the higher list index
 * @return True if inversion was performed, False otherwise
*/
bool invert(int &x, int &y) {
    if (x < y) {
        int z = x;
        x = y;
        y = z;
        return true;
    }
    else return false;
}