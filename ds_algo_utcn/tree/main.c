#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>



typedef struct node{
    int data;
    struct node *left, *right;
}NodeT;

NodeT *p;

FILE *readF;
FILE *writeF;
int nr = 0;

NodeT* newNode(int data)
{
  NodeT* node = (NodeT*)malloc(sizeof(NodeT));

  node->data = data;

  node->left = NULL;
  node->right = NULL;
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
    for (i=1; i<=h; i++)
        printGivenLevel(root, i);
}


void Inorder(NodeT* node)
{
     if (node == NULL){
          printf("* ");
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
        printf("* ");
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
        printf("* ");
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
        printf("\n1.Inorder\n2.Preorder\n3.Postorder\n\n");
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


int main()
{
    int opt = 32000;

    //create example tree
    NodeT *root;
    root = newNode(1);
    root -> left = newNode(2);
    root -> right = newNode(3);
    root -> left -> left = newNode(4);
    root -> left -> right = newNode(5);

    while(opt==32000 || opt!=0){
        printf("\n0.Exit\n1.Breadth First\n2.Depth First\n");
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
		}
    }

    return 0;
}
