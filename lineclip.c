#include<stdio.h>
#include<GL/glut.h>
#include<stdbool.h>


double xmin = 50,ymin = 50, xmax= 100,ymax = 100,xvmin = 200,yvmin =
200,xvmax = 300 ,yvmax = 300;
const int TOP = 8,BOTTOM = 4, RIGHT =2, LEFT = 1;
double x[6][2] , y[6][2];

int computeoutcode(double x, double y)
{
        int code = 0;
        if(y>ymax) code|=TOP;
        else if(y<ymin) code|=BOTTOM;
        if(x>xmax) code|=RIGHT;
        else if(x<xmin) code|=LEFT;

        return code;
}

void drawtext(float x,float y,char *s)
{
        int i;
        glRasterPos2f(x,y);
        for(i=0;s[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);

}

void cohensutherland(double x0,double y0,double x1, double y1)
{

        int outcode0 = computeoutcode(x0,y0),outcode1 =
computeoutcode(x1,y1),outcodeout;
        bool accept=false,done = false;

        do
        {
                if((outcode0 | outcode1)==0)
                {       
                        accept=true;
                        done =true;
                }

                else if(outcode0 & outcode1)
                        done=true;

                else
                {
                        double x,y;
                        outcodeout=outcode0?outcode0:outcode1;
                        float slope=(y1-y0)/(x1-x0);

                        if(outcodeout&TOP)
                        {
                                x=x0+(1/slope)*(ymax-y0);
                                y=ymax;
                        }

                        else if(outcodeout&BOTTOM)
                        {
                                x=x0+(1/slope)*(ymin-y0);
                                y=ymin;
                        }
                        else if(outcodeout&RIGHT)
                        {
                                y=y0+(slope)*(xmax-x0);
                                x=xmax;
                        }
                        else
                        {
                                y=y0+(slope)*(xmin-x0);
                                x=xmin;
                        }

                        if(outcodeout == outcode0)
                        {
                                x0=x;
                                y0=y;
                                outcode0=computeoutcode(x0,y0);
                        }
                        else
                        {       x1=x;
                                y1=y;
                                outcode1=computeoutcode(x1,y1);
                        }
                }
        }while(!done);

        if(accept)
        {
                double sx = (xvmax-xvmin) / (xmax-xmin);
                double sy = (yvmax-yvmin) / (ymax-ymin);
                double vx0 = xvmin+(x0-xmin)*sx;
                double vy0 = yvmin+(y0-ymin)*sy;
                double vx1 = xvmin+(x1-xmin)*sx;
                double vy1 = xvmin+(y1-ymin)*sy;

                glColor3f(1.0,0.0,0.0);

                glBegin(GL_LINE_LOOP);
                glVertex2f(xvmin,yvmin);
                glVertex2f(xvmax,yvmin);
                glVertex2f(xvmax,yvmax);
                glVertex2f(xvmin,yvmax);
                glEnd();

                glColor3f(0.0,0.0,1.0);
                glBegin(GL_LINES);
                glVertex2f(vx0,vy0);
                glVertex2f(vx1,vy1);
                glEnd();
        }
}

void display()
{       int i;
        //double x0=30,y0=40,x1=70,y1=80;
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.0,0.0,0.0);

        drawtext(50,450,"COHEN-SUTHERLAND LINE CLIPPING");
        drawtext(50,430,"Name : PraveenKamate");
        drawtext(50,410,"USN : 1BI15CS120");
        drawtext(50,390,"Batch : C-2");

        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINES);
        for(i=0;i<6;i++)
        {       glVertex2d(x[i][0],y[i][0]);
                glVertex2d(x[i][1],y[i][1]);
        }
        glEnd();

        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
        glEnd();

        for(i=0;i<6;i++)
        cohensutherland(x[i][0],y[i][0],x[i][1],y[i][1]);

        glFlush();
}

void myinit()
{       
        glClearColor(1.0,1.0,1.0,1.0);
        glColor3f(1.0,1.0,1.0);
        glPointSize(1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,499,0,499);
}

void main(int argc, char **argv)
{
        int i;
        //printf("Enter the number of lines");
        //scanf("%d",&n);

        printf("Enter the coordinates: ((x0,y0),(x1,y1))");


        for(i=0;i<6;i++)
        scanf("%lf%lf%lf%lf",&x[i][0],&y[i][0],&x[i][1],&y[i][1]);

        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutCreateWindow("Cohen-Sutherland Line Clipping");
        glutInitWindowSize(500,500);
        glutInitWindowPosition(0,0);
        glutDisplayFunc(display);
        myinit();
        glutMainLoop();
} 
