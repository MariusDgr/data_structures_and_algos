#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>


typedef struct nodetype {
    float x;
    float y;
    struct nodetype *next;
    struct nodetype *prev;
    } NodeT;

NodeT *p, *first, *last;

FILE *readF;
FILE *writeF;
int nr = 0;


void createList(){
    //empty list
    first = NULL;
    last = NULL;

}

void swap(NodeT*a, NodeT *b){
    NodeT *auxNext, *auxPrev;
    auxNext = b -> next;
    auxPrev = b -> prev;

    a -> prev -> next = b;
    a -> next -> prev = b;

    b-> next = a-> next;
    b-> prev = a-> prev;

    auxNext -> prev = a;
    auxPrev -> next = a;

    a -> prev = auxPrev;
    a -> next = auxNext;

    free(auxNext);
    free(auxPrev);
}

void SwapNodes(){
    int a, b;
    NodeT *aNode, *bNode;
    printf("\n\nSwap points a, b= ");
    scanf("%d %d", &a, &b);
    int i = 0;
    p = first;
    while(i != a){
        p = p->next;
        i++;
    }
    aNode = p;

    i = 0;
    p = first;
    while(i != b){
        p = p->next;
        i++;
    }
    bNode = p;

    swap(aNode, bNode);
}

void appendNode(){

    p = (NodeT*)malloc(sizeof(NodeT));

    if(first == NULL){
        first = p;
        last = p;
        p->next = NULL;
        p->prev = NULL;
    } else {
        p->next = NULL;
        p->prev = last;
        last->next = p;
        last = p;

    }
}

void deleteNode(int n){
    int i = 0;
    p = first;
    while(i != n){
        p = p->next;
        i++;
    }

    if(first == p && last == p){
        first = NULL;
        last = NULL;
        free(p);
    } else if (p == first){
        first = first->next;
        first->prev = NULL;
        free(p);
    } else if(p == last){
        last = last->prev;
        if(last == NULL){
            first = NULL;
        } else {
            last->next = NULL;
        }
        free(p);

    }  else {
        p->next->prev = p->prev;
        p->prev->next = p->next;
        free(p);
    }
}
void DeletePoint(){
    int n = nr+1;
    while(n>nr){
        printf("Delete point: ");
        scanf("%d", &n);
    }
    deleteNode(n);
}

void DeleteList(){
    while(first != NULL){
        p = first;
        first = first->next;
        free(p);
    }
    last = NULL;
}

// Save points and close writeFile
void Exit(){
        fseek(writeF, 0, SEEK_SET);
        p = first;
        while(p!=NULL){
            fprintf(writeF, "%f %f \n", p->x , p->y);
            p = p->next;
        }
        fclose(writeF);
        DeleteList();

}

void Read(){

    writeF = fopen("writeVals.txt", "w");
        if (writeF == NULL)
        {
            printf("\nWrite file did not open\n");
        }
    int optR = 32000;
    while(optR==32000){
        printf("\n1.Read from keyboard\n2.Read from file");
        printf("\n\nYour option is = ");
        scanf("%d", &optR);
        switch (optR)
		{
		case 1:
		    printf("\nNumber of points =  ");
		    scanf("%d", &nr);

		    int i;
		    for(i = 0; i<nr; i++){
                appendNode();
                printf("\nx and y coordinates of point %d are: ", i);
                scanf("%f %f", &p->x, &p->y);
                p = p->next;
		    }

			break;
		case 2:
			readF = fopen("readVals.txt", "r");
			if(readF==NULL){
                printf("\nRead file did not open\n");
                break;
			}
			while(!feof(readF)){
                appendNode();
                fscanf(readF, "%f %f", &p->x, &p->y);
                p = p->next;
                nr++;
			}
			nr--;
            fclose(readF);


			break;
		}
    }

}

void Scale(){
    float scaleVal;
    printf("\n\nScale by = ");
    scanf("%f", &scaleVal);

    p = first;
    while(p!=NULL){
        p->x *= scaleVal;
        p->y *= scaleVal;

        p = p->next;
    }

}

void Translate(){
    float translateValX;
    float translateValY;
    printf("\n\nTranslate by x, y: ");
    scanf("%f %f", &translateValX, &translateValY);

    p = first;
    while(p!=NULL){
        p->x += translateValX;
        p->y += translateValY;

        p = p->next;
    }

}

void Rotate()
{
    float originX;
    float originY;
    float angle;

    printf("\n\nRotate around x, y: ");
    scanf("%f %f", &originX, &originY);
    printf("\n\nRotate by radians: ");
    scanf("%f", &angle);
    float s = sin(angle);
    float c = cos(angle);

    p = first;
    while(p!=NULL){
        p->x -= originX;
        p->y -= originY;

        // rotate point
        float xnew = p->x * c - p->y * s;
        float ynew = p->x * s + p->y * c;

        // translate point back:p->
        p->x = xnew + originX;
        p->y = ynew + originY;

        p = p->next;
    }

}

void Display(){
    p = first;
    int i = 0;
    while(p!=NULL){
        printf("\nPoint%d has coordonates x = %.2f, y = %.2f ", i, p->x, p->y);
        printf("\n");
        p = p->next;
        i++;
    }

}

int main()
{
    createList();
    int opt = 32000;

    while(opt==32000 || opt!=0){
        printf("\n0.Exit\n1.Read\n2.Scale\n3.Translate\n4.Rotate\n5.Display\n6.DeletePoint\n7.DeleteList\n8.Swap");
        printf("\n\nYour option is = ");
        scanf("%d", &opt);
        switch (opt)
		{
		case 0:
			Exit();
			break;
		case 1:
			Read();
			break;
		case 2:
			Scale();
			break;
		case 3:
			Translate();
			break;
		case 4:
		    Rotate();
			break;
        case 5:
            Display();
			break;
		case 6:
            DeletePoint();
            break;
        case 7:
            DeleteList();
            break;
		case 8:
            SwapNodes();
            break;
		}
    }

    return 0;
}
