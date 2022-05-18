#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>


typedef struct Points {
    float x;
    float y;
    } Point;

FILE *readF;
FILE *writeF;
int nr = 0;
Point A[10];
bool dataWithFiles = false;


// Save points and close writeFile
void Exit(){
    int i;
    if(dataWithFiles){
        for(i=0; i< nr; i++){
            fprintf(writeF, "%f %f \n", A[i].x , A[i].y);
        }
    }
    fclose(writeF);
}

void Read(){
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
                printf("\nx and y coordinates of point %d are: ", i);
                scanf("%f %f", &A[i].x, &A[i].y);
		    }

			break;
		case 2:
			readF = fopen("readVals.in", "r");
			if(readF==NULL){
                printf("\nRead file did not open\n");
                break;
			}
			int j = 0;
			while(!feof(readF)){
                float xval;
                float yval;
                fscanf(readF, "%f", &xval);
                fscanf(readF, "%f", &yval);
                A[j].x = xval;
                A[j].y = yval;
                nr++;
                j++;

			}
			nr--;
            fclose(readF);

            dataWithFiles = true;

            //check if we use files, and check if file opened
            if(dataWithFiles && writeF==NULL){
            writeF = fopen("writeVals.txt", "w");
                if (writeF == NULL)
                {
                    printf("\nWrite file did not open\n");
                }
            }
			break;
		}
    }

}

void Scale(){
    float scaleVal;
    printf("\n\nScale by = ");
    scanf("%f", &scaleVal);

    //reset file pointer
    fseek(writeF, 0, SEEK_SET);

    int i;
    //write values in file
    for(i=0; i< nr; i++){
        A[i].x *= scaleVal;
        A[i].y *= scaleVal;

        if(dataWithFiles){
            fprintf(writeF, "%f %f \n", A[i].x , A[i].y);

        }
    }
}

void Translate(){
    float translateValX;
    float translateValY;
    printf("\n\nScale by x, y: ");
    scanf("%f %f", &translateValX, &translateValY);

    //reset file pointer
    fseek(writeF, 0, SEEK_SET);

    int i;
    //write values in file
    for(i=0; i< nr; i++){
        A[i].x += translateValX;
        A[i].y += translateValY;

        if(dataWithFiles){
            fprintf(writeF, "%f %f \n", A[i].x , A[i].y);

        }
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

    //reset file pointer
    fseek(writeF, 0, SEEK_SET);
    int i;
    for(i=0; i< nr; i++){
        // translate point back to origin:
        A[i].x -= originX;
        A[i].y -= originY;

        // rotate point
        float xnew = A[i].x * c - A[i].y * s;
        float ynew = A[i].x * s + A[i].y * c;

        // translate point back:
        A[i].x = xnew + originX;
        A[i].y = ynew + originY;
    }
}

void Display(){
    int i;
    for(i=0; i< nr; i++){
        printf("\nPoint%d has coordonates x = %.2f, y = %.2f ", i, A[i].x, A[i].y);
        printf("\n");

    }

}



int main()
{

    int opt = 32000;
    while(opt==32000 || opt!=0){
        printf("\n0.Exit\n1.Read\n2.Scale\n3.Translate\n4.Rotate\n5.Display");
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
		}
    }

    return 0;
}
