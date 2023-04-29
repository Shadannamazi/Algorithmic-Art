
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
using namespace std;

// Node constructor, given.
quadtree::Node::Node(pair<int, int> ul, int d, RGBAPixel a, double v)
    : upLeft(ul), dim(d), avg(a), var(v), NW(nullptr), NE(nullptr), SE(nullptr), SW(nullptr) {}

// quadtree destructor, given.
quadtree::~quadtree() {
    clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree& other) {
    copy(other);
}
// quadtree assignment operator, given.
quadtree& quadtree::operator=(const quadtree& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

quadtree::quadtree(PNG& imIn) {
    int min_edge = fmin(imIn.height(),imIn.width());
    int num = floor(log2(min_edge));
    edge = pow(2,num);
    
    imIn.resize(edge,edge);
   
    int dim = log2(edge);

    stats stat(imIn);
	pair<int,int> ul (0,0);
    //idk???

    
	root = buildTree(stat, ul, dim);
}


quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    Node* node = new Node(ul,dim,s.getAvg(ul,dim),s.getVar(ul,dim));
 
    if (dim < 1){
        return node;
    }
    int off = pow(2,dim);

    //pair<int,int> new_ul = ul;
    int new_dim = dim/2;

    //computeNewUl(new_ul,new_dim);

    pair<int,int> ul_nw = {ul.first,ul.second};
    pair<int,int> ul_ne = {ul.first + off/2,ul.second};
    pair<int,int> ul_sw = {ul.first,ul.second + off/2};
    pair<int,int> ul_se = {ul.first + off/2,ul.second + off/2};

    
    node->NW = buildTree(s,ul_nw,new_dim);
    node->NE = buildTree(s,ul_ne,new_dim);
    node->SE = buildTree(s,ul_se,new_dim);
    node->SW = buildTree(s,ul_sw,new_dim);

    
	return node;
}


PNG quadtree::render() const {
    PNG img (edge, edge);
	Node* node = root;
	renderHelper(img, node);
	return img;
}

void quadtree::renderHelper(PNG &img, Node* n)const {

	if (n->NE == NULL && n->NW == NULL && n->SW == NULL && n->SE == NULL){													
		pair<int,int> ul = n->upLeft;
		int dim = n->dim;
        int off = pow(2,dim) - 1;
		
		for (int i = ul.first; i <= ul.first+off; i++){
			for (int j = ul.second; j <= ul.second+off; j++){
                *img.getPixel(i,j) = n->avg;
			}
		}
	}
	
	else{
		if (n->NE != NULL)
			renderHelper(img, n->NE);
		if (n->NW != NULL)
			renderHelper(img, n->NW);
        if (n->SE != NULL)
			renderHelper(img, n->SE);
        if (n->SW != NULL)
			renderHelper(img, n->SW);
		
	}
}


/*
     * The idealPrune function can be considered to be the inverse
     * of the pruneSize function. It takes as input a number of leaves
     * and returns the minimum tolerance that would produce that resolution
     * upon a prune. It does not change the structure of the tree.
     */
int quadtree::idealPrune(const int leaves) const{
    int left = 0, right = 256;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (pruneSize(mid) <= leaves) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int quadtree::pruneSize(int tol)  const{
    if (prunable(root,tol)){
        return 1;
    }
    return 0;
}

void quadtree::prune(const int tol) {
    pruneHelper(root,tol);
}

void quadtree::pruneHelper(Node* node, int tol) {
    if (prunable(node, tol)) {
        clear();

    } else {
        pruneHelper(node->NW, tol);
        pruneHelper(node->NE, tol);
        pruneHelper(node->SW, tol);
        pruneHelper(node->SE, tol);
    }
}

void quadtree::clear() {
    clearQuadTree(root);
    
}

void quadtree::clearQuadTree(Node* subTree){
    if (subTree == NULL)
        return;
	
    else {
        
        clearQuadTree(subTree->NW);
        clearQuadTree(subTree->NE);
        clearQuadTree(subTree->SW);
        clearQuadTree(subTree->SE);

        delete subTree;
    }
}

void quadtree::copy(const quadtree& orig) {
    
    root = copyQuadTree(orig.root);
}

quadtree::Node* quadtree::copyQuadTree(Node* subTree){
    Node* nn = new Node(subTree->upLeft, subTree->dim, subTree->avg,subTree->var);

    if (subTree->NE != NULL){
        nn->NE = copyQuadTree(subTree->NE);
    }
    if (subTree->NW != NULL){
        nn->NW = copyQuadTree(subTree->NW);
    }
    if (subTree->SE != NULL){
        nn->SE = copyQuadTree(subTree->SE);
    }
    if (subTree->SW != NULL){
        nn->SW = copyQuadTree(subTree->SW);
    }

	return nn;

}
