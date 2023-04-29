#include "qtcount.h"

//A node is pruned if all of the leaves in its 
//subtree have colour-distance within tolerance 
//of its average. Distances between colours are 
//computed as the sum, over each colour channel, 
//of the pixel value differences, squared. 
//For reference, to create the pruned totem pole above, 
//we used a tolerance of 4000.
bool qtcount::prunable(Node * root, const int tol) const {
    if (root == nullptr) {
        return true;
    } else if (root->NW == nullptr && root->NE == nullptr &&
               root->SW == nullptr && root->SE == nullptr) {
        return (root->avg.r - root->avg.g) * (root->avg.r - root->avg.g) +
               (root->avg.g - root->avg.b) * (root->avg.g - root->avg.b) +
               (root->avg.b - root->avg.r) * (root->avg.b - root->avg.r) <= tol;
    } else {
        // non-leaf node
        return prunable(root->NW, tol) && prunable(root->NE, tol) &&
               prunable(root->SW, tol) && prunable(root->SE, tol);
    }
}
