#include <GL/glut.h>
#include <stdio.h>

float et[4][4]= { { 100,250,200,-1},
                  {100,250,200,1},
                  {200,150,300,1},
                  {200,350,300,-1}};

int np=4;
float ae[4][3];
float js;
int net=0;
int iaet=0;
int ymax=0;
static int submenu_id;
static int menu_id;
static int window;
static int value=0;


void drawText(float x, float y, float z,char* s){
        int i;
        glRasterPos3f(x,y,z);
        for(i=0;s[i] != '\0';i++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);
}
void addaet()
{
        int i;
        for(i=0;i<np;i++)
        {
                printf("Scan line= %f & iate = %d \n",js,iaet);
                if(js==et[i][0])
                {
                        ae[iaet][0]=et[i][1];
                        ae[iaet][1]=et[i][2];
                        ae[iaet][2]=et[i][3];
                        if(ae[iaet][1]>ymax)
                                ymax=ae[iaet][1];
                                iaet++;
                }
        }
}
void upaet()
{
        int i;
        for(i=0;i<np;i++)
        ae[i][0]=ae[i][0]+ae[i][2];
}
void draw_pixel(float x1,float x2)
{
        int i;
        float n;
        for(n=x1;n<=x2;n++)
        {
                glBegin(GL_POINTS);
                glVertex2f(n,js);
                glEnd();
        }
        glFlush();
        printf("x1=%f,x2=%f \n",x1,x2);
}

void fill_poly()
{
        float x[3]={0,0,0};
        int i=0,j;
        do
        {
                i=0;
                addaet();
                printf("1=%f 2=%f %f\n",ae[0][1],ae[1][1],js);
                for(j=0;j<np;j++)
                if(ae[j][1]>js)
                {
                        x[i]=ae[j][0];
                        i++;
                }
                draw_pixel(x[0],x[1]);
                upaet();
                js++;
        }
        while(js<=ymax);
}
void empty_ae()
{
        js= et[0][0];
        iaet=0;
}

void display()
{
        int i,j;
        glClear(GL_COLOR_BUFFER_BIT);

        switch(value)
        {
                case 1 : return;
                         break;
                case 2 : glColor3f(1.0,0.0,0.0);
                         fill_poly();
                         empty_ae();
                         break;
                case 3 : glColor3f(0.0,1.0,0.0);
                         fill_poly();
                         empty_ae();
                         break;
                case 4 : glColor3f(0.0,0.0,1.0);
                         fill_poly();
                         empty_ae();
                         break;
        }
        drawText(20,50,0.10,"Scan line drawing");
        drawText(20,30,0.20,"Prathiksha CM 1BI15CS119");
}
void myInit()
{
        glClearColor(1.0,1.0,1.0,1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0,1000.0,0.0,1000.0);
        glMatrixMode(GL_MODELVIEW);
}

void menu(int num)
{
        if(num==0)
        {
                glutDestroyWindow(window);
                exit(0);
        }
        else
                value=num;
}

void createMenu(void)
{
        submenu_id= glutCreateMenu(menu);
        glutAddMenuEntry("Red",2);
        glutAddMenuEntry("Green",3);
        glutAddMenuEntry("Blue",4);
        menu_id = glutCreateMenu(menu);
        glutAddMenuEntry("Clear",1);
        glutAddSubMenu("color",submenu_id);
        glutAddMenuEntry("Quit",0);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc,char **argv)
{
        js= et[0][0];
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(0,0);
        glutCreateWindow("Polygon filling algorithm");
        createMenu();
        glutDisplayFunc(display);
        myInit();
        glutMainLoop();
        return 0;
}
