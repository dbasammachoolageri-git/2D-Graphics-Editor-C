#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 40
#define MAXOBJ 20

char canvas[ROWS][COLS];

typedef struct
{
    int type;   //1-Line 2-Rectangle 3-Triangle 4-Circle
    int p[6];
} Shape;

Shape shapes[MAXOBJ];
int count = 0;

/* Initialize Canvas */
void initCanvas()
{
    int i,j;
    for(i=0;i<ROWS;i++)
        for(j=0;j<COLS;j++)
            canvas[i][j]='_';
}

/* Display Canvas */
void displayCanvas()
{
    int i,j;
    for(i=0;i<ROWS;i++)
    {
        for(j=0;j<COLS;j++)
            printf("%c",canvas[i][j]);
        printf("\n");
    }
}

/* Rectangle */
void drawRectangle(int x,int y,int w,int h)
{
    int i,j;

    for(i=y;i<y+h && i<ROWS;i++)
        for(j=x;j<x+w && j<COLS;j++)
            canvas[i][j]='*';
}

/* Horizontal Line */
void drawLine(int x1,int y1,int x2,int y2)
{
    int i;

    if(y1==y2)
        for(i=x1;i<=x2 && i<COLS;i++)
            canvas[y1][i]='*';

    else if(x1==x2)
        for(i=y1;i<=y2 && i<ROWS;i++)
            canvas[i][x1]='*';
}

/* Triangle */
void drawTriangle(int x,int y,int size)
{
    int i,j;

    for(i=0;i<size;i++)
        for(j=0;j<=i;j++)
            if(y+i<ROWS && x+j<COLS)
                canvas[y+i][x+j]='*';
}

/* Circle */
void drawCircle(int cx,int cy,int r)
{
    int x,y;

    for(y=0;y<ROWS;y++)
    {
        for(x=0;x<COLS;x++)
        {
            int d=(x-cx)*(x-cx)+(y-cy)*(y-cy);

            if(abs(d-r*r)<=r)
                canvas[y][x]='*';
        }
    }
}

/* Redraw all shapes */
void redraw()
{
    int i;

    initCanvas();

    for(i=0;i<count;i++)
    {
        switch(shapes[i].type)
        {
            case 1:
                drawLine(shapes[i].p[0],shapes[i].p[1],
                         shapes[i].p[2],shapes[i].p[3]);
                break;

            case 2:
                drawRectangle(shapes[i].p[0],shapes[i].p[1],
                              shapes[i].p[2],shapes[i].p[3]);
                break;

            case 3:
                drawTriangle(shapes[i].p[0],shapes[i].p[1],
                             shapes[i].p[2]);
                break;

            case 4:
                drawCircle(shapes[i].p[0],shapes[i].p[1],
                           shapes[i].p[2]);
                break;
        }
    }
}

/* Main */
int main()
{
    int ch,id;

    initCanvas();

    while(1)
    {
        printf("\n1.Add Shape");
        printf("\n2.Delete Shape");
        printf("\n3.Modify Shape");
        printf("\n4.Display");
        printf("\n5.Exit");
        printf("\nEnter choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
            {
                int t;

                printf("1.Line 2.Rectangle 3.Triangle 4.Circle : ");
                scanf("%d",&t);

                shapes[count].type=t;

                if(t==1)
                {
                    printf("x1 y1 x2 y2: ");
                    scanf("%d%d%d%d",
                          &shapes[count].p[0],
                          &shapes[count].p[1],
                          &shapes[count].p[2],
                          &shapes[count].p[3]);
                }
                else if(t==2)
                {
                    printf("x y width height: ");
                    scanf("%d%d%d%d",
                          &shapes[count].p[0],
                          &shapes[count].p[1],
                          &shapes[count].p[2],
                          &shapes[count].p[3]);
                }
                else if(t==3)
                {
                    printf("x y size: ");
                    scanf("%d%d%d",
                          &shapes[count].p[0],
                          &shapes[count].p[1],
                          &shapes[count].p[2]);
                }
                else if(t==4)
                {
                    printf("center_x center_y radius: ");
                    scanf("%d%d%d",
                          &shapes[count].p[0],
                          &shapes[count].p[1],
                          &shapes[count].p[2]);
                }

                count++;
                redraw();
                break;
            }

            case 2:
                printf("Enter shape index (0-%d): ",count-1);
                scanf("%d",&id);

                if(id>=0 && id<count)
                {
                    int i;
                    for(i=id;i<count-1;i++)
                        shapes[i]=shapes[i+1];

                    count--;
                    redraw();
                }
                break;

            case 3:
                printf("Enter shape index (0-%d): ",count-1);
                scanf("%d",&id);

                if(id>=0 && id<count)
                {
                    int t=shapes[id].type;

                    if(t==1)
                    {
                        printf("New x1 y1 x2 y2: ");
                        scanf("%d%d%d%d",
                              &shapes[id].p[0],
                              &shapes[id].p[1],
                              &shapes[id].p[2],
                              &shapes[id].p[3]);
                    }
                    else if(t==2)
                    {
                        printf("New x y width height: ");
                        scanf("%d%d%d%d",
                              &shapes[id].p[0],
                              &shapes[id].p[1],
                              &shapes[id].p[2],
                              &shapes[id].p[3]);
                    }
                    else if(t==3)
                    {
                        printf("New x y size: ");
                        scanf("%d%d%d",
                              &shapes[id].p[0],
                              &shapes[id].p[1],
                              &shapes[id].p[2]);
                    }
                    else if(t==4)
                    {
                        printf("New center_x center_y radius: ");
                        scanf("%d%d%d",
                              &shapes[id].p[0],
                              &shapes[id].p[1],
                              &shapes[id].p[2]);
                    }

                    redraw();
                }
                break;

            case 4:
                displayCanvas();
                break;

            case 5:
                exit(0);
        }
    }

    return 0;
}
