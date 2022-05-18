#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>



typedef struct node{
    int data;
    struct node *left, *right;
    int height;
}NodeT;

NodeT *p;

FILE *readF;
FILE *writeF;
int nr = 0;

int max(int a, int b){
    return (a > b)? a : b;
}
NodeT* newNode(int data)
{
  NodeT* node = (NodeT*)malloc(sizeof(NodeT));

  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return(node);
}

void printGivenLevel(NodeT* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}

NodeT* searchNode(NodeT* root, int key){

    if(root == NULL || root -> data == key){
        return root;
    }

    if(root -> data < key){
        return(searchNode(root->right, key));
    }

    if(root -> data > key){
        return(searchNode(root->left, key));
    }

}


int height(NodeT* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

void BreadthFirst(NodeT* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++){
        printGivenLevel(root, i);
    }
}


void Inorder(NodeT* node)
{
     if (node == NULL){
          //printf("* ");
          return;
     }

     /* first recur on left child */
     Inorder(node->left);

     /* then print the data of node */
     printf("%d ", node->data);

     /* now recur on right child */
     Inorder(node->right);
}

void Preorder(NodeT* node)
{
     if (node == NULL){
        //printf("* ");
        return;
     }

     /* first print data of node */
     printf("%d ", node->data);

     /* then recur on left sutree */
     Preorder(node->left);

     /* now recur on right subtree */
     Preorder(node->right);
}

void Postorder(NodeT* node)
{
     if (node == NULL){
        //printf("* ");
        return;
     }

     // first recur on left subtree
     Postorder(node->left);

     // then recur on right subtree
     Postorder(node->right);

     // now deal with the node
     printf("%d ", node->data);
}

void DepthFirst(NodeT* root){
    int newopt = 32000;
    while(newopt==32000 || newopt!=0){
        printf("\n0.Back\n1.Inorder\n2.Preorder\n3.Postorder\n\n");
        printf("\n\nYour option is = ");
        scanf("%d", &newopt);
        switch(newopt)
		{
		case 0:
			break;
		case 1:
			Inorder(root);
			break;
        case 2:
            Preorder(root);
			break;
        case 3:
            Postorder(root);
			break;
		}
    }
}

void Search(NodeT* root){
    int srchKey;
    NodeT *found;
    printf("\nThe node you are searching ");
    scanf("%d", &srchKey);
    found = searchNode(root, srchKey);
    if(found == NULL){
        printf("Node was not found in tree");
    } else {
        printf("\n%d", found -> data);
    }
}

NodeT* rightRotate(NodeT *y)
{
    NodeT *x = y->left;
    NodeT *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
NodeT* leftRotate(NodeT *x)
{
    NodeT *y = x->right;
    NodeT *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

NodeT* insertNode(NodeT* root, int key){
    if(root == NULL){
        return newNode(key);
    }

    if(key < root->data){
        root->left = insertNode(root->left, key);
    } else if(key > root->data){
        root->right = insertNode(root->right, key);
    } else {
        return root;
    }

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < root->left->data)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->data)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->data)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    /* return the (unchanged) node pointer */
    return root;

}

void Insert(NodeT* root){
    int instKey;
    printf("\nThe node you are inserting ");
    scanf("%d", &instKey);
    insertNode(root, instKey);
}

NodeT* minValueNode(NodeT* root){
    NodeT* current = root;

    while(current->left!=NULL){
        current = current->left;
    }

    return current;
}



NodeT* deleteNode(NodeT* root, int key){
    if(root == NULL){
        return root;
    }

    if(key < root->data){
        root->left = deleteNode(root->left, key);
    } else if(key > root->data){
        root->right = deleteNode(root->right, key);
    } else {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            NodeT *temp = root->left ? root->left :
                                             root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            NodeT* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

NodeT* Delete(NodeT* root){
    int delKey;
    NodeT* newRoot;
    printf("\nThe node you are deleting ");
    scanf("%d", &delKey);
    newRoot = deleteNode(root, delKey);
    return newRoot;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.


// Get Balance factor of node N
int getBalance(NodeT *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


int main()
{
    int opt = 32000;

    //create example tree
    NodeT *root;
    root = newNode(27);
    root -> left = newNode(11);
    root -> right = newNode(52);
    root -> left -> left = newNode(1);
    root -> left -> right = newNode(13);
    root -> right -> left = newNode(33);
    root -> right -> right = newNode(60);
    root -> left -> left -> right = newNode(7);
    root -> left -> right -> right = newNode(21);
    root -> right -> left -> right = newNode(47);
    root -> right -> right -> right = newNode(100);

    while(opt==32000 || opt!=0){
        printf("\n0.Exit\n1.Breadth First\n2.Depth First\n3.Search\n4.Insert\n5.Delete");
        printf("\n\nYour option is = ");
        scanf("%d", &opt);
        switch (opt)
		{
		case 0:
			break;
		case 1:
			BreadthFirst(root);
			break;
        case 2:
            DepthFirst(root);
			break;
        case 3:
            Search(root);
			break;
        case 4:
            Insert(root);
			break;
        case 5:
            root = Delete(root);
            break;
		}
    }

    return 0;
}
