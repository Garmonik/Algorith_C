#include <stdio.h>
#include <stdlib.h>

/* T(x) := x, L, R 
 *         x
 *      /     \
 *   y = L(x)  z=R(x)
 * tree := empty
 *       | element, left, right
 * left := tree
 * right := tree
 */


typedef struct _tree {
	int element;
	int h;
	struct _tree* left;
	struct _tree* right;
} Tree;

/* V(x) --- значение элемента узла дерева
 * \forall l \in L*(x) V(l) <= V(x) 
 * \forall r \in R*(x) V(r) >  V(x)
 */

/* a <-> b <-> c <-> d ... */
 /*           3
  *         /   \
  *        2     4
  *       / \   / \
  *      1   3 4   5
  *      h = log(N)
  *      N*log(N)
  */
  
 /*        root
  *         |
  *         v
  *         () -> [element, left, right]
  *
  *         root -> ()-> [x, NULL, NULL]
  *
  *         root->  () -> [element, left, right] 
  *                                  ^
  *                                  |
  *                                  () <- root
  */

/*  AVL-tree:
 *  forall x  |h(L(x)) - h(R(x))| <= 1
 *  
 *
 *               3
 *              /
 *             2
 *
 *                3   -not AVL! 
 *               /
 *              2
 *             /
 *            1
 *
 *
 *             5
 *            / \
 *           4   6
 *          /     \
 *         3       7
 *                 \
 *                  8
 *
 *                  3 (h+3)                     2(h+2)                         
 *               /   \                /       \
 *              2(h+2)    R(h)   ->    LL(h+1)     3
 *             /   \                       /     \
 *           LL(h+1)LR(h)                 LR(h)  R (h)
 *
 *                     3                   LR
 *                  /     \      ->     /       \
 *                2       R(h)         2         3   
 *             /  \                 /   \      /    \
 *           LL(h) LR(h+1)        LL(h) LRL(h) LRR(h)  R(h)
 *                /     \
 *              LRL     LRR
 *
 *                 3                          r
 *                  \               ->     3    rr
 *              l     r                   l rl
 *                 rl    rr
 * 
 *                 3                       rlh+2
 *              lh       rh+2             3           rh+1
 *                   rlh+1 rr          lh   rllx rlry    rr
 *                 rllx rlry
 */
#define MAX(a, b)  ((a)<(b)?(b):(a))
#define H(x) ((x)?(x)->h:0)

int _bal(Tree* r) {
	return  (H(r->left) - H(r->right));
}

Tree* _node(Tree*l,  int x, Tree* r) {
	Tree* n;
	int lh = H(l);
	int rh = H(r);
	if ( lh - rh == -2) {
		if (_bal(r) < 0) {
			/*   (L[h] x R[h+2] ) */
			/*   (L[h] x (rl[h] r rr[h+1])[h+2])
			 *   ((L[h] x rl[h])[h+1] r rr[h+1]))
			 */
			n = _node(_node(l, x, r->left), r->element, r->right);
			free(r);
		} else {
		    /* (L[h] x (rl[h+1] r rr[h])[h+2])
			 * (L[h] x ((rll[x] rl rlr[y])[h+1] r rr[h])[h+2])
			 * ((L[h] x rll[x])[h+1] rl (rlr[y] r rr[h])[h+1])
			 */
			Tree* rl = r->left;
			n = _node( _node(l,  x, rl->left), rl->element, _node(rl->right, r->element, r->right));
			free(r);
			free(rl);
		}
	} else if ( lh - rh == 2) {
		if (_bal(l) > 0) {
			n = _node(l->left , l->element, _node(l->right, x, r));
			free(l);
		} else {
			Tree* lr = l->right;
			n = _node(_node(l->left, l->element, lr->left), lr->element, _node(lr->right, x, r));
			free(l);
			free(lr);
		}
	} else {
		n  = malloc(sizeof(Tree));
		*n = (Tree){x, 1+MAX(lh, rh), l, r};
	}
	return n;
}

Tree* tree_insert(Tree* root, int x) {
	Tree* n;
	if (!root ) {
		return _node(NULL, x, NULL);
	} else if ( x <= root->element )
		n = _node(tree_insert(root->left, x), root->element, root->right);
	else
		n = _node(root->left, root->element, tree_insert(root->right, x));
	free(root);
	return n;
}

int tree_search(Tree* root, int x, int found(int, void*), void* ctx) {
	if ( !root ) return 0;
	if ( x == root->element) {
		found(root->element, ctx);
		return tree_search(root->left, x, found, ctx);
	} else if ( x < root->element )
		return tree_search(root->left, x, found, ctx);
	else 
		return tree_search(root->right, x, found, ctx);
}

void tree_free(Tree* root) {
	Tree* left, *right;
	if ( root ) {
		left = root->left;
		right = root->right;
		free(root);
		tree_free(left);
		tree_free(right);
	}
}

void tree_walk(Tree* root, int level, int cb(int, int, void*), void* ctx) {
	if ( !root ) return;
	tree_walk(root->left, level+1, cb, ctx);
	cb(root->element, level, ctx);
	tree_walk(root->right, level+1, cb, ctx);
}



int print_element(int x, int level, void* data) {
	char* ctx = (char*)data;
	printf("%s: ", ctx);
	while(level--) printf("  ");
	printf("%d\n", x);
	return 0;
}


int main() {
	int x;
	Tree* root = NULL;
	while ( scanf("%d", &x) == 1 ) 
		root = tree_insert(root, x);

	tree_walk(root, 0, print_element, (void*)"A");
	tree_walk(root, 0, print_element, (void*)"B");
	tree_free(root);
}
