
#include<GL/glut.h>
#include<stdio.h>
int x1,y1,x2,y2;
void myInit()
{
        glClearColor(1.0,0.0,0.0,1.0);
        glColor3f(1,1,1);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0,500,0,500);
}
void draw_pixel(int x,int y)
{
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
}
void draw_line(int x1,int x2,int y1,int y2)
{
        int dx,dy,i,e;
        int incx,incy,inc1,inc2;
        int x,y;
        dx=x2-x1;
        dy=y2-y1;
        if(dx<0)
                dx=-dx;
        if(dy<0)
                dy=-dy;
        incx=1;
        if(x2<x1)
                incx=-1;
        incy=1;
        if(y2<y1)
                incy=-1;
        x=x1;
        y=y1;
        if(dx>dy)
        {
                draw_pixel(x,y);
                e=2*dy-dx;
                inc1=2*(dy-dx);
                inc2=2*dy;
                for(i=1;i<dx;i++)
                {
                        if(e>=0)
                        {
                                y+=incy;
                                e+=inc1;
                        }
                        else
                                e+=inc2;
                        x+=incx;
                        draw_pixel(x,y);
                }
        }
        else
        {
                draw_pixel(x,y);
                e=2*dx-dy;
                inc1=2*(dx-dy);
                inc2=2*dx;
                for(i=1;i<dy;i++)
                {
                        if(e>=0)
                        {
                                x+=incx;
                                e+=inc1;
                        }
                        else
                                e+=inc2;
                        y+=incy;
                        draw_pixel(x,y);        
                }
        }
}
void draw_text(int x,int y,char *s)
{
        int i;
        glRasterPos2f(x,y);
        for(i=0;s[i]!='\0';i++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);

}       

void mydisplay()
{
        glClear(GL_COLOR_BUFFER_BIT);
        draw_line(x1,x2,y1,y2);
        draw_text(150,400,"USN:1BI15CS133,NAME:RITESH NR,BATCH:C3");
        draw_text(x1,y1,"start point");
        draw_text(x2,y2,"end point");
        glFlush();
}
int main(int argc,char **argv)
{
        printf("enter end points of line(x1,y1,x2,y2)\n");
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(500,500);
        glutCreateWindow("bresenhams line drawing");
        myInit();
        glutDisplayFunc(mydisplay);
        glutMainLoop();
        return 0;
}
