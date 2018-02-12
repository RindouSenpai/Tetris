#include <stdlib.h>
#define GLEW_STATIC
#include "Angel.h"
#include <iostream>
#include <vector>
using namespace std;

const float EDGE = 0.93;
const float EDGE2 = EDGE-EDGE*0.1;
const float EDGE3 = EDGE+EDGE*0.1;
const float vertStep = 2*EDGE/21;
const float horStep = 2*EDGE/10;
//const float stepOffest = 
vector<vec2> squares;
vector<vec4> colorsVec;

GLuint vao,vao2;

static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 0.0, 0.0, 0.0 )
};
vec4 colors2[24];
vec4 colors3[24];
vec4 colors[88+44];
vec2 points[24];
vec2 points3[24];
vec2 points4[24];
vec2 points5[24];
vec2 points6[24];
vec2 points7[24];
//GLfloat vertices_position[44+88];
GLfloat vertices_position[88+44];

void NewShape(int num){
	if(num <7){
		squares.push_back(vec2(-EDGE,-EDGE));
		squares.push_back(vec2(-EDGE + horStep,-EDGE));
		squares.push_back(vec2(-EDGE,-EDGE + vertStep));
		    
		squares.push_back(vec2(-EDGE + horStep,-EDGE));
		squares.push_back(vec2(-EDGE,-EDGE + vertStep));
		squares.push_back(vec2(-EDGE + horStep,-EDGE + vertStep));
	}
	else{
		squares.push_back(vec2(-EDGE,-EDGE+vertStep));
		squares.push_back(vec2(-EDGE + horStep,-EDGE+vertStep));
		squares.push_back(vec2(-EDGE,-EDGE + 2*vertStep));
		    
		squares.push_back(vec2(-EDGE + horStep,-EDGE+vertStep));
		squares.push_back(vec2(-EDGE,-EDGE + 2*vertStep));
		squares.push_back(vec2(-EDGE + horStep,-EDGE + 2*vertStep));
	}

	switch(num){
		case 1:{ // BLOCK J
		    for ( int i = 6; i < 18; i++ ) {
		        static vec2 step = vec2(horStep,0.0);
		        squares.push_back(squares[squares.size()-6] + step);
		    }
		    for ( int i = 18; i < 24; i++ ) {
		        static vec2 step = vec2(0.0,vertStep);
		        squares.push_back(squares[squares.size()-18] + step);
		    }
		    break;	    
		}
		case 2:{ // BLOCK O
		    for ( int i = 6; i < 12; i++ ) {
        		static vec2 step = vec2(horStep,0.0);
        		squares.push_back(squares[squares.size()-6] + step);
    		}
    		for ( int i = 12; i < 18; i++ ) {
        		static vec2 step = vec2(0.0,vertStep);
        		squares.push_back(squares[squares.size()-6] + step);
    		}
    		for ( int i = 18; i < 24; i++ ) {
        		static vec2 step = vec2(-horStep,0.0);
        		squares.push_back(squares[squares.size()-6] + step);
    		}
    		break;
		}
		case 3:{ // BLOCK I
		    for ( int i = 6; i < 24; i++ ) {
        		static vec2 step = vec2(horStep,0.0);
        		squares.push_back(squares[squares.size()-6] + step);
    		}
    		break;
		}
		case 4:{ // BLOCK S
		    for ( int i = 6; i < 12; i++ ) {
        		static vec2 step = vec2(horStep,0.0);
        		squares.push_back(squares[squares.size()-6] + step);
    		}
    		for ( int i = 12; i < 18; i++ ) {
		        static vec2 step = vec2(0.0,vertStep);
		        squares.push_back(squares[squares.size()-6] + step);
    		}
		    for ( int i = 18; i < 24; i++ ) {
		        static vec2 step = vec2(horStep,0.0);
		       	squares.push_back(squares[squares.size()-6] + step);
		    }
    		break;
		}
		case 5:{ // BLOCK T
		    for ( int i = 6; i < 18; i++ ) {
		        static vec2 step = vec2(horStep,0.0);
		        squares.push_back(squares[squares.size()-6] + step);
		    }

		    for ( int i = 18; i < 24; i++ ) {
		        static vec2 step = vec2(0.0,vertStep);
		        squares.push_back(squares[squares.size()-12] + step);
		    }
    		break;
		}
		case 6:{ // BLOCK L
		   	for ( int i = 6; i < 18; i++ ) {
		        static vec2 step = vec2(horStep,0.0);
		        squares.push_back(squares[squares.size()-6] + step);
		    }
		    for ( int i = 18; i < 24; i++ ) {
		        static vec2 step = vec2(0.0,vertStep);
		        squares.push_back(squares[squares.size()-6] + step);
		    }
    		break;
		}
		case 7:{ // BLOCK Z
		   	 for ( int i = 6; i < 12; i++ ) {
        		static vec2 step = vec2(horStep,0.0);
        		squares.push_back(squares[squares.size()-6] + step);
    		}
    		for ( int i = 12; i < 18; i++ ) {
		        static vec2 step = vec2(0.0,vertStep);
		        squares.push_back(squares[squares.size()-6] - step);
    		}
		    for ( int i = 18; i < 24; i++ ) {
		        static vec2 step = vec2(horStep,0.0);
		       	squares.push_back(squares[squares.size()-6] + step);
		    }
    		break;
		}
	}

	for(int i=0;i<24;i++){
		colorsVec.push_back(vec4(0.5,0,0,1));
	}

}

void init(){
    //int edge =0.93;
    for(int i=0;i<88+44;i++){
        vertices_position[i]=0;
    }
    for(int i=0;i<11;i++){
        vertices_position[0+(i*4)]= -EDGE + float(i)*2*EDGE/10;
        vertices_position[1+(i*4)]= -EDGE;
        vertices_position[2+(i*4)]= -EDGE + float(i)*2*EDGE/10;
        vertices_position[3+(i*4)]= EDGE;
    }

    for(int i=0;i<22;i++){
        vertices_position[1+(i*4)+44]= -EDGE + float(i)*2*EDGE/21;
        vertices_position[0+(i*4)+44]= -EDGE;
        vertices_position[3+(i*4)+44]= -EDGE + float(i)*2*EDGE/21;
        vertices_position[2+(i*4)+44]= EDGE;
    }

    for(int i=0;i<88+44;i++){
        colors[i] = vec4(0,0,0,1);
    }

    for(int i=0;i<24;i++){
        colors2[i] = vec4(0.5,0,0,1);
    }

NewShape(1);

//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    /*-----------------------------------------------------------------------------
     *  CREATE THE VERTEX BUFFER OBJECT
     *-----------------------------------------------------------------------------*/
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices_position)+sizeof(colors), vertices_position, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices_position), vertices_position );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertices_position), sizeof(colors), colors );

    /*-----------------------------------------------------------------------------
     *  Load shaders and use the resulting shader program
     *-----------------------------------------------------------------------------*/
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    /*-----------------------------------------------------------------------------
     *  ENABLE VERTEX ATTRIBUTES
     *-----------------------------------------------------------------------------*/
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(vertices_position)) );

glLineWidth(1.5);
glClearColor( 0.2, 0.2, 0.2, 1.0 );

}


void drawTriangle(){

     /*-----------------------------------------------------------------------------
     *  CREATE THE VERTEX ARRAY OBJECT
     *-----------------------------------------------------------------------------*/
    glGenVertexArrays( 1, &vao2 );
    glBindVertexArray( vao2 );

    /*-----------------------------------------------------------------------------
     *  CREATE THE VERTEX BUFFER OBJECT
     *-----------------------------------------------------------------------------*/
    GLuint buffer2;
    glGenBuffers( 1, &buffer2 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer2 );

    glBufferData( GL_ARRAY_BUFFER, squares.size()* sizeof(vec2)+colorsVec.size()*sizeof(vec4), squares.data(), GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, squares.size()* sizeof(vec2), squares.data() );
    glBufferSubData( GL_ARRAY_BUFFER, squares.size()* sizeof(vec2), colorsVec.size()*sizeof(vec4), colorsVec.data());

    /*-----------------------------------------------------------------------------
     *  Load shaders and use the resulting shader program
     *-----------------------------------------------------------------------------*/
    GLuint program1 = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program1 );

    /*-----------------------------------------------------------------------------
     *  ENABLE VERTEX ATTRIBUTES
     *-----------------------------------------------------------------------------*/
    GLuint loc2 = glGetAttribLocation( program1, "vPosition" );
    glEnableVertexAttribArray( loc2 );
    glVertexAttribPointer( loc2, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint vColor2 = glGetAttribLocation( program1, "vColor" );
    glEnableVertexAttribArray( vColor2 );
    glVertexAttribPointer( vColor2, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(squares.size()* sizeof(vec2)) );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

     glBindVertexArray( vao2 );
    glDrawArrays( GL_TRIANGLES, 0, squares.size() );

    glBindVertexArray( vao );
    glDrawArrays( GL_LINES, 0, 44+88 );

    
    //glutSwapBuffers();
    glFlush();
}

void draw(){

    drawTriangle();
}


void resize(GLsizei w, GLsizei h){

glViewport(0,0,w,h);
    glClearColor(0.2,0.2,0.2,1);           //CLEAR WINDOW CONTENTS
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

bool CollisionTest(int num){

	switch(num){
		case 1:{
			for(int i=0;i<24;i++){

				if(points5[i].y >= EDGE+ 2*EDGE/21){
					cout << points5[i].y << endl;
					return true;
				}
			}
			break;
		}
		case 2:{
			for(int i=0;i<24;i++){

				if(points5[i].y == -EDGE- 2*EDGE/21){
					cout << points5[i].y << endl;
					return true;
				}
			}
			break;
		}
		case 3:{
			for(int i=0;i<24;i++){

				if(points5[i].x > EDGE){
					cout << points5[i].x << endl;
					return true;
				}
			}
			break;
		}
		case 4:{
			for(int i=0;i<24;i++){

				if(points5[i].x <= -EDGE- 2*EDGE/10){
					cout << points5[i].x << endl;
					return true;
				}
			}
			break;
		}


		default:
			return false;
	}
	return false;
}

void keyboardSpecial( int key, int x, int y )
{
    switch ( key ) {
    //similar to the stuff inside the keyboard class, but applying the translaton only to the third triangle.
    case  GLUT_KEY_UP:{
         printf("up arrow pressed!\n");
         static vec2 upstep = vec2( 0.0, vertStep );

         for ( int i = 0; i < 24; ++i ) {
        //points5[i] = points5[i] + upstep;
         	squares[squares.size()-24+i] = squares[squares.size()-24+i] +upstep;
     	}	
	     //if(CollisionTest(1)){
	     //	for ( int i = 0; i < 24; ++i ) {
	     //   points5[i] = points5[i] - upstep;
	     //	}
     	//}
      	glutPostRedisplay();
         break;
     }
    case  GLUT_KEY_DOWN:{
         printf("down arrow pressed!\n");
         static vec2 downstep = vec2( 0.0, -vertStep );

         for ( int i = 0; i < 24; ++i ) {
        points5[i] = points5[i] + downstep;
     	}
     	 //if(CollisionTest(2)){
	     //	for ( int i = 0; i < 24; ++i ) {
	     //   points5[i] = points5[i] - downstep;
	     //	}
     	//}
         glutPostRedisplay();
         break;
     }
    case  GLUT_KEY_RIGHT:
         printf("right arrow pressed!\n");
         static vec2 rightstep = vec2( horStep, 0.0 );

         for ( int i = 0; i < 24; ++i ) {
        points5[i] = points5[i] + rightstep;
     }
     	 //if(CollisionTest(3)){
	     //	for ( int i = 0; i < 24; ++i ) {
	     //   points5[i] = points5[i] - rightstep;
	     //	}
     	//}
         glutPostRedisplay();
         break;
    case  GLUT_KEY_LEFT:
         printf("left arrow pressed!\n");
         static vec2 leftstep = vec2( -horStep, 0.0 );

         for ( int i = 0; i < 24; ++i ) {
        points5[i] = points5[i] + leftstep;
     }
     	 //if(CollisionTest(4)){
	     //	for ( int i = 0; i < 24; ++i ) {
	     //   points5[i] = points5[i] - leftstep;
	     //	}
     	//}
         glutPostRedisplay();
         break;
    case  GLUT_KEY_F1:{
         printf("space arrow pressed!\n");
        GLfloat angle = M_PI / 2;

        //This is the 2x2 rotation matrix for 2D points.
        static mat2 rotate10degccw = mat2 ( cos(angle), -sin(angle), sin(angle), cos(angle));

        vec2 center = points5[13];
        vec2 center2 = vec2((points5[12].x+points5[16].x)/2.0,(points5[12].y+points5[16].y)/2.0);

        for ( int i = 0; i < 24; i++ ) {
            points5[i] = points5[i]-center2;
        }
  

        for ( int i = 0; i < 24; i++ ) {
        //finally, we apply the transformation. The idea here is just to translate the points to origin, rotate and then translate it back
            points5[i] = mat2((float)2.1,0,0,(float)10/21)*(rotate10degccw *points5[i]) + center2;
        }
            //Always remember to update your canvas
         glutPostRedisplay();
         break;
     }
     case  GLUT_KEY_F2:{
        printf("F2 arrow pressed!\n");
        NewShape(7);
        glutPostRedisplay();
         break;
     }
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
    



}
int main(int argc, char **argv){

    glutInit( &argc, argv );

    int w = 300; int h = 600;

    glutInitDisplayMode( GLUT_RGBA );

    glutInitWindowSize( w, h );

    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "Tetris" );

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST);
    glEnable( GL_BLEND );

    glewExperimental = GL_TRUE; 
    glewInit();
                 //Set Viewport in pixels

    //put drawing code in here
    init();
    glutDisplayFunc( draw );
    glutSpecialFunc( keyboardSpecial );
    //glutReshapeFunc(resize);
    

    glutMainLoop();                       //<-- LISTEN FOR WINDOW EVENTS
}