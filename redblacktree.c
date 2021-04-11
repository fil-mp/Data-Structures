#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
enum Color {
	RED = 1, BLACK = 0
};
typedef struct rb *redblack;
struct rb {
	int key;
	bool color;
	redblack left, right, parent;
};
redblack insert(redblack *root, redblack *temp);
void rotateLeft(redblack *root, redblack *temp);
void rotateRight(redblack *root, redblack *temp);
void inorder(redblack *root);
void fixDeleteViolation(redblack *root, redblack *temp);
redblack findNode(int key);
redblack delete(redblack *root, redblack *temp);
void fixInsertViolation(redblack *root, redblack *temp);
redblack root, temp;
int main(void) {
	char c1;
	c1 = 'a';
	root = NULL;
		while (c1 != 'q') {
			printf("\n\n Previous choice was %c \n", c1);
			printf("\n Your options are (i)nsert, (p)rint, (d)elete, (q)uit");
			if (c1 != 'q') {
				printf("\n Give new choice: ");
				c1 = 'a';
				fflush(stdin);
				c1 = getchar();
				getchar();
			if (c1 == 'q')
				exit(0);
			if (c1 == 'i') {
				printf("\n INSERT \n");
				int key;
				temp = (redblack) malloc(sizeof(struct rb));
				do {
					printf("\n Give a key\n");
					scanf("%d", &key);
					getchar();
				} while (key < 1);
				temp->key = key;
				temp->left = temp->right = NULL;
				temp->color = RED;
				root = insert(&root, &temp);
				fixInsertViolation(&root, &temp);
				inorder(&root);
			}
			if (c1 == 'd') {
				printf("\n DELETE \n");
				int key;
			do {
				printf("\n Give a key\n");
				scanf("%d", &key);
				getchar();
			} while (key < 1);
			temp = findNode(key);
			delete(&root, &temp);
			}
			if (c1 == 'p') {
				printf("\n PRINT \n");
				inorder(&root);
			}
		}
	}
} 
// inserts a new node
redblack insert(redblack *root, redblack *temp) {
	// tree is empty, return a new node
	if (*root == NULL) {
	return *temp;
	}
	printf("root %d\n", (*root)->key);
	// find the correct position with recurrency
	if ((*temp)->key < (*root)->key) {
		(*root)->left = insert(&(*root)->left, temp);
		(*root)->left->parent = (*root);
	} else if ((*temp)->key > (*root)->key) {
		(*root)->right = insert(&(*root)->right, temp);
		(*root)->right->parent = (*root);
	}
	return *root;
} 
void rotateLeft(redblack *root, redblack *temp) {
	redblack temp_right = (*temp)->right;
	(*temp)->right = temp_right->left;
	if ((*temp)->right != NULL)
		(*temp)->right->parent = (*temp);
	temp_right->parent = (*temp)->parent;
	if ((*temp)->parent == NULL)
		*root = temp_right;
	else if ((*temp) == (*temp)->parent->left)
		(*temp)->parent->left = temp_right;
	else
		(*temp)->parent->right = temp_right;
	temp_right->left = (*temp);
	(*temp)->parent = temp_right;
} 
void rotateRight(redblack *root, redblack *temp) {
	redblack temp_left = (*temp)->left;
	(*temp)->left = temp_left->right;
	if ((*temp)->left != NULL)
		(*temp)->left->parent = (*temp);
	temp_left->parent = (*temp)->parent;
	if ((*temp)->parent == NULL)
		*root = temp_left;
	else if ((*temp) == (*temp)->parent->left)
		(*temp)->parent->left = temp_left;
	else
		(*temp)->parent->right = temp_left;
	temp_left->right = (*temp);
	(*temp)->parent = temp_left;
} 
// in order traversal
void inorder(redblack *root) {
	if (*root == NULL) return;
	//visit left subtree
	inorder(&(*root)->left);
	printf("%d -> %d\n", (*root)->key, (*root)->color);
	if ((*root)->parent != NULL)
		printf(" (parent -> %d)\n", (*root)->parent->key);
	// visit right subtree
	inorder(&(*root)->right);
} 
void fixInsertViolation(redblack *root, redblack *temp) {
	redblack parent = NULL;
	redblack grand_parent = NULL;
	while ((*temp != *root) && ((*temp)->color != BLACK) && ((*temp)->parent->color == RED)) {
		parent = (*temp)->parent;
		grand_parent = (*temp)->parent->parent;
		//parent of temp is left child of grand-parent
	if (parent == grand_parent->left) {
		redblack uncle = grand_parent->right;
		// uncle of temp is also red
		// only recoloring is required
		if (uncle != NULL && uncle->color == RED) {
			grand_parent->color = RED;
			parent->color = BLACK;
			uncle->color = BLACK;
			*temp = grand_parent;
		} else {
			// temp is right child
			// left-rotation required
			if (*temp == parent->right) {
			rotateLeft(&(*root), &parent);
			*temp = parent;
			parent = (*temp)->parent;
			}
			// temp is left child
			// right-rotation required
			rotateRight(&(*root), &grand_parent);
			bool col = grand_parent->color;
			grand_parent->color = parent->color;
			parent->color = col;
			*temp = parent;
			}
			}
			// parent of temp is right child of grand-parent
			// same as above with left and right exchanged
	else {
		redblack uncle_pt = grand_parent->left;
		if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
			grand_parent->color = RED;
			parent->color = BLACK;
			uncle_pt->color = BLACK;
			*temp = grand_parent;
		} else {
			if (*temp == parent->left) {
			rotateRight(&(*root), &parent);
			*temp = parent;
			parent = (*temp)->parent;
			}
			rotateLeft(&(*root), &grand_parent);
			bool col = grand_parent->color;
			grand_parent->color = parent->color;
			parent->color = col;
			*temp = parent;
			}
		}
	}
	(*root)->color = BLACK;
} 
// find node with no left child based on the node given
redblack successor(redblack *x) {
redblack temp = *x;
while (temp->left != NULL)
	temp = temp->left;
return temp;
} 
//find the node to be deleted by the key given
redblack findNode(int key) {
	redblack temp = root;
	while (temp != NULL) {
		if (key < temp->key) {
			if (temp->left == NULL)
				break;
			else
				temp = temp->left;
		} else if (key == temp->key) {
			break;
		} else {
			if (temp->right == NULL)
				break;
			else
				temp = temp->right;
		}
		}
	return temp;
} 
//return the sibling of node given
redblack sibling(redblack *temp) {
	if ((*temp)->parent == NULL)
		return NULL;
	if ((*temp) == (*temp)->parent->left)
		return (*temp)->parent->right;
	return (*temp)->parent->left;
} //returns the node that replaces the node to be deleted
redblack replaced(redblack *temp) {
	// when node has two children
	if ((*temp)->left != NULL && (*temp)->right != NULL){
	return successor(&(*temp)->right);}
	// when node is leaf
	if ((*temp)->left == NULL && (*temp)->right == NULL){
	return NULL;}
	// when node has single child
	if ((*temp)->left != NULL){
		return (*temp)->left;}
	else{
		return (*temp)->right;}
} //deletes the node given
redblack delete(redblack *root, redblack *temp) {
	redblack u = replaced(&*temp);
	redblack parent = (*temp)->parent;
	// the temp is leaf
	if (u == NULL) {
		// temp is the root
		if (*temp == *root) {
			*root = NULL;
		} else {
			// u and temp are both black
			// v is leaf, fix double black at v
			if ((u == NULL || u->color == BLACK) && ((*temp)->color == BLACK)) {
			fixDeleteViolation(&*root, &(*temp));
		} else {
			// u or temp is red
			// sibling is not null
			if (sibling(&*temp) != NULL)
				sibling(&*temp)->color = RED;
			}
			// delete temp from the tree
			if ((*temp) == (*temp)->parent->left) {
				parent->left = NULL;
			} else {
				parent->right = NULL;
			}
			}
		free(*temp);
		return NULL;
		}
	//temp has a child
	if ((*temp)->left == NULL || (*temp)->right == NULL) {
		// temp is the root, assign the value of u to temp and delete u
		if ((*temp) == *root) {
			(*temp)->key = u->key;
			(*temp)->left = (*temp)->right = NULL;
			free(u);
		} else {
			// Detach temp from tree and move u up
			if ((*temp) == (*temp)->parent->left) {
				(*temp)->parent->left = u;
			} else {
				(*temp)->parent->right = u;
			}
			free(*temp);
			u->parent = parent;
			if ((u == NULL || u->color == BLACK) && ((*temp)->color == BLACK)) {
				// u and temp are both black, fix violation
				fixDeleteViolation(&*root, &u);
			} else {
				// u or v red, color u black
				u->color = BLACK;
			}
			}
			return NULL;
	}
	// temp has two children, swap temp key with successor's key and recurse
	int key;
	key = u->key;
	u->key = (*temp)->key;
	(*temp)->key = key;
	delete(&*root, &u);
} 
void fixDeleteViolation(redblack *root, redblack *temp) {
	if (*temp == *root)
		return;
	redblack sibl = sibling(&*temp), parent = (*temp)->parent;
	// No sibling, fix for parent
	if (sibl == NULL) {
		fixDeleteViolation(&*root, &parent);
	} else {
		// Sibling is red
		if (sibl->color == RED) {
			parent->color = RED;
			sibl->color = BLACK;
			if (sibl == sibl->parent->left) {
			// left case
			rotateRight(&*root, &parent);
			} else {
			// right case
			rotateLeft(&*root, &parent);
			}
			fixDeleteViolation(&*root, (&*temp));
		} else {
			// Sibling is black
			if ((sibl->left != NULL && sibl->left->color == RED) ||
				(sibl->right != NULL && sibl->right->color == RED)) {
				// at least one red child
				if (sibl->left != NULL && sibl->left->color == RED) {
					if (sibl == sibl->parent->left) {
					// left left
					sibl->left->color = sibl->color;
					sibl->color = parent->color;
					rotateRight(&*root, &parent);
					} else {
					// right left
					sibl->left->color = parent->color;
					rotateRight(&*root, &sibl);
					rotateLeft(&*root, &parent);
					}
				} else {
					if (sibl == sibl->parent->left) {
					// left right
					sibl->right->color = parent->color;
					rotateLeft(&*root, &sibl);
					rotateRight(&*root, &parent);
				} else {
					// right right
					sibl->right->color = sibl->color;
					sibl->color = parent->color;
					rotateLeft(&*root, &parent);
					}
				}
				parent->color = BLACK;
		} else {
			// two black children
			sibl->color = RED;
			if (parent->color == BLACK)
				fixDeleteViolation(&*root, &parent);
			else
				parent->color = BLACK;
			}
		}
	}
}