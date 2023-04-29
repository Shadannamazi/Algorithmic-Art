#include "qtvar.h"

/* prunable is a pure virtual function, and as such it must
     * be implemented in a derived class. Prunable takes parameters
     * root, and tol, and returns true if root can be pruned (its
     * subtrees cleared) according to the criteria specified in
     * the derived class.
     */

bool qtvar::prunable(Node * root, const int tol) const {
    
    if (root == nullptr) {
        return true;
    } else if (root->NW == nullptr && root->NE == nullptr &&
               root->SW == nullptr && root->SE == nullptr) {
        return root->var <= tol;
    } else {
        // non-leaf node
        return prunable(root->NW, tol) && prunable(root->NE, tol) &&
               prunable(root->SW, tol) && prunable(root->SE, tol);
    }
}
