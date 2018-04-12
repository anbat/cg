#include<GL/glut.h>
#include<stdio.h>
int x1,y1,x2,y2;
void drawText(float x, float y, float z,char* s){
        int i;
        glRasterPos3f(x,y,z);
        for(i=0;s[i] != '\0';i++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);
}
void myInit()
{
        glClearColor(0.0,0.0,0.0,1.0);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0,500,0,500);
}
void drawpixel(int x,int y)
{
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
}
void drawline(int x1,int x2,int y1,int y2)
{
        int dx,dy,i,e;
        int incx,incy,inc1,inc2;
        int x,y;
        dx = x2-x1;
        dy = y2-y1;
        if(dx<0)
                dx = -dx;
        if(dy<0)
                dy = -dy;
        incx = 1;
        if(x2<x1)
                incx = -1;
        incy = 1;
        if(y2<y1)
                incy = -1;
        x = x1;
        y = y1;
        if(dx<dy)
        {
                drawpixel(x,y);
                e = 2*(dy-dx);
                inc1 = 2*(dy-dx);
                inc2 = 2*dy;
                for(i=0;i<dx;i++)
                {
                        if(e>=0)
                        {
                                y+=incx;
                                e+=inc1;
                        }
                        else
                                e+= inc2;
                        x+=incx;
                        drawpixel(x,y);
                }
        }
        else
        {
                drawpixel(x,y);
                e = 2*dx - dy;
                inc1 = 2*(dx=dy);
                inc2 = 2*dx;
                for(i=0;i<dy;i++)
                {
                        if(e>=0)
                        {
                                x+=incx;
                                e+=inc1;
                        }
                        else
                                e+=inc2;
                        y+=incy;
                        drawpixel(x,y);
                }
        }
}
void myDisplay()
{
        glClear(GL_COLOR_BUFFER_BIT);
        drawline(x1,x2,y1,y2);
        //drawtext(0,400,0.7,"USN-120,Name-Praveen Kamate,200,350,0.5Batch-C2");
        //drawText(0,500,0.7,"Line Drawing");
        drawText(150,400,0.7,"Praveen Kamate 1BI15CS120 Batch-C2");
        glFlush();
}
int main(int argc,char**argv)
{
        printf("\nEnter end points of line(x1,y1,x2,y2):");
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(0,0);
        glutCreateWindow("Bresenham's Line Drawing");
        myInit();
        glutDisplayFunc(myDisplay);
        glutMainLoop();
        return 0;
}
