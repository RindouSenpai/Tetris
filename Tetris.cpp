#include <stdlib.h>
#define GLEW_STATIC
#include "Angel.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>


using namespace std;
#define RED 0
#define SILVER 1
#define PURPLE 2
#define BLUE 3
#define GREEN 4
#define BROWN 5
#define TEAL 6
#define PINK 7

const float CENTER = 0.00;
const float EDGE = 0.93;
const float EDGE2 = EDGE-EDGE*0.1;
const float EDGE3 = EDGE+EDGE*0.1;
const float vertStep = 2*EDGE/21;
const float horStep = 2*EDGE/10;
float highestNew=-0.93;
float lowestNew=0.93;

vec2 center;
//const float stepOffest = 
vector<vec2> squares;
vector<vec4> colorsVec;
vector<vec2> currentVec;
vector<vec2> placed;
vector<vec4> placedColors;
std::vector<int> killIndex;
std::vector<int> moveDownIndex;
bool flag;

GLuint vao,vao2,vao3;
int currentBlock=0;
static vec3  base_colors[] = {
        vec3( 0.5, 0.0, 0.0 ),
        vec3( 0.66, 0.66, 0.66 ),
        vec3( 0.54, 0.0, 0.54 ),
        vec3( 0.0, 0.0, 0.7 ),
        vec3( 0.13, 0.54, 0.13 ),
        vec3( 0.54, 0.20, 0.07 ),
        vec3( 0.0, 0.5, 0.5 ),
        vec3( 1, 0.35, 0.6 )

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
    if(num <7){ //fix!!!
        squares.push_back(vec2(-EDGE,EDGE-2*vertStep));
        squares.push_back(vec2(-EDGE + horStep,EDGE-2*vertStep));
        squares.push_back(vec2(-EDGE,EDGE-vertStep));
            
        squares.push_back(vec2(-EDGE + horStep,EDGE-vertStep));
        squares.push_back(vec2(-EDGE,EDGE-vertStep));
        squares.push_back(vec2(-EDGE + horStep,EDGE-2*vertStep));
    }
    else{
        squares.push_back(vec2(-EDGE,EDGE-vertStep));
        squares.push_back(vec2(-EDGE + horStep,EDGE-vertStep));
        squares.push_back(vec2(-EDGE,EDGE));
            
        squares.push_back(vec2(-EDGE + horStep,EDGE-vertStep));
        squares.push_back(vec2(-EDGE,EDGE));
        squares.push_back(vec2(-EDGE + horStep,EDGE));
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
            for(int i=0;i<24;i++){
                colorsVec.push_back(vec4(base_colors[SILVER],1));
            }
            currentBlock=num;
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
            for(int i=0;i<24;i++){
                colorsVec.push_back(vec4(base_colors[BLUE],1));
            }
            currentBlock=num;
            break;
        }
        case 3:{ // BLOCK I
            for ( int i = 6; i < 24; i++ ) {
                static vec2 step = vec2(horStep,0.0);
                squares.push_back(squares[squares.size()-6] + step);
            }
            for(int i=0;i<24;i++){
                colorsVec.push_back(vec4(base_colors[RED],1));
            }
            currentBlock=num;
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
            for(int i=0;i<24;i++){
                colorsVec.push_back(vec4(base_colors[GREEN],1));
            }
            currentBlock=num;
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
            for(int i=0;i<24;i++){
                colorsVec.push_back(vec4(base_colors[BROWN],1));
            }
            currentBlock=num;
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
            for(int i=0;i<24;i++){
                colorsVec.push_back(vec4(base_colors[PURPLE],1));
            }
            currentBlock=num;
            break;
        }
        default:{ // BLOCK Z
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
            for(int i=0;i<24;i++){
                colorsVec.push_back(vec4(base_colors[TEAL],1));
            }
            currentBlock=num;
            break;
        }
    }


}

void GetCenter(int num){
    switch(num){
        case 1:
            center = vec2((squares[6].x+squares[9].x)/2.0,(squares[6].y+squares[9].y)/2.0);
            break;
        case 2:
            center = vec2(squares[8].x,squares[8].y);
            break;
        case 3:
            center = vec2((squares[6].x+squares[9].x)/2.0,(squares[6].y+squares[9].y)/2.0);
            break;
        case 4:
            center = vec2((squares[6].x+squares[9].x)/2.0,(squares[6].y+squares[9].y)/2.0);
            break;
        case 5:
            center = vec2((squares[6].x+squares[9].x)/2.0,(squares[6].y+squares[9].y)/2.0);
            break;
        case 6:
            center = vec2((squares[6].x+squares[9].x)/2.0,(squares[6].y+squares[9].y)/2.0);
            break;
        case 7:
            center = vec2((squares[11].x+squares[16].x)/2.0,(squares[11].y+squares[16].y)/2.0);
            break;
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

    for(int i=0;i <24;i++){
        placed.push_back(vec2(0,0));
        placedColors.push_back(vec4(0,0,0,0));
    }

NewShape(rand()%7+1);

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

void PlaceShape(){
    if(fabs(placed[0].x - 0) < 0.001 && fabs(placed[0].y - 0) < 0.001){
        placed.clear();
        placedColors.clear();
    }
    for(int i=0;i <24;i++){
        placed.push_back(squares[i]);
        placedColors.push_back(colorsVec[i]);
    }
    squares.clear();
    colorsVec.clear();
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


    //////////////////////////////////////////////////////////////////////////

    glGenVertexArrays( 1, &vao3 );
    glBindVertexArray( vao3 );

     GLuint buffer3;
    glGenBuffers( 1, &buffer3 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer3 );

    glBufferData( GL_ARRAY_BUFFER, placed.size()* sizeof(vec2)+placedColors.size()*sizeof(vec4), placed.data(), GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, placed.size()* sizeof(vec2), placed.data() );
    glBufferSubData( GL_ARRAY_BUFFER, placed.size()* sizeof(vec2), placedColors.size()*sizeof(vec4), placedColors.data());

    GLuint program2 = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program2 );

    GLuint loc3 = glGetAttribLocation( program2, "vPosition" );
    glEnableVertexAttribArray( loc3 );
    glVertexAttribPointer( loc3, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint vColor3 = glGetAttribLocation( program2, "vColor" );
    glEnableVertexAttribArray( vColor3 );
    glVertexAttribPointer( vColor3, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(placed.size()* sizeof(vec2)) );
    ////////////////////////////////////////////////////////////////////////////

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

     glBindVertexArray( vao2 );
    glDrawArrays( GL_TRIANGLES, 0, squares.size() );

    glBindVertexArray( vao3 );
    glDrawArrays( GL_TRIANGLES, 0, placed.size() );

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
    int max=-100;
    vector<float> tempx;
    vector<float> tempy;
    //float [5] tempx;
    //float [5] tempy;
	switch(num){
		case 1:{
 
			break;
		}
		case 2:{
            lowestNew=0.93;
            for(int j=0;j<squares.size();j++){
                if(squares[j].y < -0.95){
                   // cout << squares[j].y << endl;
                    return true;
                }        
            }
            for(int block=0;block < placed.size()/6;block++){
                for(int currentBlock = 0; currentBlock < 4;currentBlock++){
                    int count=0;
                    for(int placedVert =0; placedVert < 6 ; placedVert++){
                        for( int currentVert = 0; currentVert < 6 ; currentVert++){
                            float testx = fabs(placed[block*6 + placedVert].x - squares[currentBlock*6 + currentVert].x);
                            float testy = fabs(placed[block*6 + placedVert].y - squares[currentBlock*6 + currentVert].y);

                            if(squares[currentBlock*6 + currentVert].y < lowestNew){
                                lowestNew= squares[currentBlock*6 + currentVert].y;
                            }
                            if(testx <0.001 && testy < 0.001){                               
                                flag=true;
                                count++;
                               // cout << count <<  endl;
                                if(count > 5 ) {
                                    return true;
                                } 
                                continue;
                            }
                            else{
                            }
                        }
                    }
                    if(count > 5 ) {
                        return true;
                    }              
               }
            }
			break;
		}
		case 3:{
			for(int i=0;i<24;i++){

				if(squares[i].x > 0.95){
					//cout << squares[i].x << endl;
					return true;
				}
			}
            for(int block=0;block < placed.size()/6;block++){
                for(int currentBlock = 0; currentBlock < 4;currentBlock++){
                    int count=0;
                    for(int placedVert =0; placedVert < 6 ; placedVert++){
                        for( int currentVert = 0; currentVert < 6 ; currentVert++){
                            float testx = fabs(placed[block*6 + placedVert].x - squares[currentBlock*6 + currentVert].x);
                            float testy = fabs(placed[block*6 + placedVert].y - squares[currentBlock*6 + currentVert].y);

                            if(testx <0.001 && testy < 0.001){                               
                                flag=true;
                                count++;
                               // cout << count <<  endl;
                                if(count > 5 ) {
                                    return true;
                                } 
                                continue;
                            }
                            else{
                            }
                        }
                    }
                    if(count > 5 ) {
                        return true;
                    }              
               }
            }
			break;
		}
		case 4:{
			for(int i=0;i<24;i++){

				if(squares[i].x < -0.95){
					//cout << squares[i].x << endl;
					return true;
				}
			}
            for(int block=0;block < placed.size()/6;block++){
                for(int currentBlock = 0; currentBlock < 4;currentBlock++){
                    int count=0;
                    for(int placedVert =0; placedVert < 6 ; placedVert++){
                        for( int currentVert = 0; currentVert < 6 ; currentVert++){
                            float testx = fabs(placed[block*6 + placedVert].x - squares[currentBlock*6 + currentVert].x);
                            float testy = fabs(placed[block*6 + placedVert].y - squares[currentBlock*6 + currentVert].y);

                            if(testx <0.001 && testy < 0.001){                               
                                flag=true;
                                count++;
                              //  cout << count <<  endl;
                                if(count > 5 ) {
                                    return true;
                                } 
                                continue;
                            }
                            else{
                            }
                        }
                    }
                    if(count > 5 ) {
                        return true;
                    }              
               }
            }
			break;
		}
        case 5:{
            for(int i=0;i<24;i++){

                if((squares[i].x < -0.95) || (squares[i].x > 0.95) || (squares[i].y > 0.95) || (squares[i].y < -0.95)){
                   // cout << squares[i].x << endl;
                    return true;
                }

            }
            for(int block=0;block < placed.size()/6;block++){
                for(int currentBlock = 0; currentBlock < 4;currentBlock++){
                    int count=0;
                    for(int placedVert =0; placedVert < 6 ; placedVert++){
                        for( int currentVert = 0; currentVert < 6 ; currentVert++){
                            float testx = fabs(placed[block*6 + placedVert].x - squares[currentBlock*6 + currentVert].x);
                            float testy = fabs(placed[block*6 + placedVert].y - squares[currentBlock*6 + currentVert].y);

                            if(testx <0.001 && testy < 0.001){                               
                                flag=true;
                                count++;
                               // cout << count <<  endl;
                                if(count > 5 ) {
                                    return true;
                                } 
                                continue;
                            }
                            else{
                            }
                        }
                    }
                    if(count > 5 ) {
                        return true;
                    }              
               }
            }
            break;
        }


		default:
			return false;
	}
	return false;
}

void MovePlacedDown(int grid){
    float destroyPointU=-0.93;
    moveDownIndex.clear();
    for(int grid2=grid; grid2 < 24; grid2++){
        killIndex.clear();
       // cout << placed.size() << "------------" << endl;
        for(int i=0; i < placed.size()/4;i++){
            
            bool flagL=false;
            bool flagU=false;

            for(int j =0; j <6; j++){
                float testL= fabs(placed[i*6 +j].y- (-EDGE+((grid2+1)*vertStep)));
                float testU= fabs(placed[i*6 +j].y- (-EDGE+((grid2+1)*vertStep))+vertStep);
               // cout << testL << " " << testU << endl;
                if( testL < 0.001 && !flagL){
                    flagL=true;
                    j=-1;
                    cout << "TESTL" <<endl;
                }
                if( testU < 0.001 && !flagU){
                    flagU=true;
                    j=-1;
                    cout << "TESTU" <<endl;
                }

            }
            if(flagU && flagL){
                moveDownIndex.push_back(i);
            }
           
        }

    }
                static vec2 step = vec2(0.0,-vertStep);
                /*
                int size= moveDownIndex.size();
                cout << size << endl;
                for(int down=0; down < size;down++){
                    int index= moveDownIndex[down];
                    //cout << index <<endl;
                   // moveDownIndex.pop_back();
                    cout << "----------------" << endl; 
                    for(int i=0;i <6;i++){   
                        cout << placed[index+i] << endl;                
                        placed[index+i] = placed[index+i] + step;
                    }

                }
                */
                for(int i=0;i <placed.size();i++) {
                    placed[i] = placed[i] + step;
                }
               // moveDownIndex.clear();
                //return;
}


void clearRow(){
    float destroyPointU=-0.93;
    moveDownIndex.clear();
    for(int grid=0; grid < 24; grid++){
        killIndex.clear();
        int count=0;
        //cout << placed.size() << "------------" << endl;
        for(int i=0; i < placed.size()/4;i++){
            
            bool flagL=false;
            bool flagU=false;

            for(int j =0; j <6; j++){
                float testL= fabs(placed[i*6 +j].y- (-EDGE+(grid*vertStep)));
                float testU= fabs(placed[i*6 +j].y- (-EDGE+vertStep)+(grid*vertStep));

                //cout << squares[i*6 +j] <<endl;
                //cout << testL << "  " << testU <<endl;
                //cout <<  "---------------------"  <<endl;
                if( testL < 0.001 && !flagL){
                    flagL=true;
                    j=-1;
                    //cout << "TESTL" <<endl;
                }
                if( testU < 0.001 && !flagU){
                    flagU=true;
                    j=-1;
                    //cout << "TESTU" <<endl;
                }

            }
            if(flagU && flagL){
                count++;
               // cout << i << endl << "----------" << endl;
                killIndex.push_back(i);
            }

            if(count >= 10){
                for(int check=0;check <killIndex.size();check++){
                //cout << killIndex[check] <<endl;
            }
            //cout << "YES" << endl;
            int size= killIndex.size();
           // cout << size << endl;
           // sort(killIndex.begin(),killIndex.begin()+size);
                for(int kill=0; kill < size;kill++){
                    int index= killIndex.back();
                  //  cout << index <<endl;
                    killIndex.pop_back();                   
                    placed.erase(placed.begin()+(index*6),placed.begin()+(index*6)+6);
                    placedColors.erase(placedColors.begin()+(index*6),placedColors.begin()+(index*6)+6);

                }
                MovePlacedDown(grid);
                moveDownIndex.clear();
                killIndex.clear();
                grid=0;
                break;
                //return;
            }
            
        }
        
       // for(int check=0;check <squares.size();check++){
       //         cout << squares[check] <<endl;
        //    }
    }
}



void keyboardSpecial( int key, int x, int y )
{
    switch ( key ) {
    //similar to the stuff inside the keyboard class, but applying the translaton only to the third triangle.
    case  GLUT_KEY_UP:{
         printf("up arrow pressed!\n");
         GLfloat angle = M_PI / 2;

        //This is the 2x2 rotation matrix for 2D points.
        static mat2 rotate10degccw = mat2 ( cos(angle), -sin(angle), sin(angle), cos(angle));

       // vec2 center = points5[13];
        //vec2 center2 = vec2((points5[12].x+points5[16].x)/2.0,(points5[12].y+points5[16].y)/2.0);
        GetCenter(currentBlock);

        for ( int i = 0; i < 24; i++ ) {
            //points5[i] = points5[i]-center2;
            squares[i] = squares[i] -center;
            //cout << squares[squares.size()-24+i] << endl;
        }
  

        for ( int i = 0; i < 24; i++ ) {
        //finally, we apply the transformation. The idea here is just to translate the points to origin, rotate and then translate it back
            //points5[i] = mat2((float)2.1,0,0,(float)10/21)*(rotate10degccw *points5[i]) + center;
            squares[i] = mat2((float)2.1,0,0,(float)10/21)*(rotate10degccw*squares[i]) +center;
        }
        if(CollisionTest(5)){
            mat2 rotatecw = mat2 ( cos(-angle), -sin(-angle), sin(-angle), cos(-angle));
            for ( int i = 0; i < 24; i++ ) {
            squares[i] = squares[i] -center;
        }
            for ( int i = 0; i < 24; i++ ) {
            squares[i] = mat2((float)2.1,0,0,(float)10/21)*(rotatecw*squares[i]) +center;
            }
        }
            //Always remember to update your canvas
         glutPostRedisplay();
         break;
     }
    case  GLUT_KEY_DOWN:{
         printf("down arrow pressed!\n");
         static vec2 downstep = vec2( 0.0, -vertStep );

         for ( int i = 0; i < 24; ++i ) {
        squares[i] = squares[i] + downstep;
     	}
     	 if(CollisionTest(2)){
	     	for ( int i = 0; i < 24; ++i ) {
	        squares[i] = squares[i] - downstep;
	     	}
            PlaceShape();
            clearRow();
            NewShape(rand()%7+1);
     	}
         glutPostRedisplay();
         break;
     }
    case  GLUT_KEY_RIGHT:
         printf("right arrow pressed!\n");
         static vec2 rightstep = vec2( horStep, 0.0 );

         for ( int i = 0; i < 24; ++i ) {
        squares[i] = squares[i] + rightstep;
     }
     	 if(CollisionTest(3)){
	     	for ( int i = 0; i < 24; ++i ) {
	        squares[i] = squares[i] - rightstep;
	     	}
     	}
         glutPostRedisplay();
         break;
    case  GLUT_KEY_LEFT:
         printf("left arrow pressed!\n");
         static vec2 leftstep = vec2( -horStep, 0.0 );

         for ( int i = 0; i < 24; ++i ) {
        squares[i] = squares[i] + leftstep;
     }
     	 if(CollisionTest(4)){
	     	for ( int i = 0; i < 24; ++i ) {
	        squares[i] = squares[i] - leftstep;
	     	}
     	}
         glutPostRedisplay();
         break;
    case  GLUT_KEY_F1:{
         printf("space arrow pressed!\n");
        
         break;
     }
     case  GLUT_KEY_F2:{
        printf("F2 arrow pressed!\n");
        break;
     }
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

void timerDownfunc(int num){
    static vec2 downstep = vec2( 0.0, -vertStep );

         for ( int i = 0; i < 24; ++i ) {
        squares[i] = squares[i] + downstep;
        }
         if(CollisionTest(2)){
            for ( int i = 0; i < 24; ++i ) {
            squares[i] = squares[i] - downstep;
            }
            PlaceShape();
            clearRow();
            NewShape(rand()%7+1);
        }
         glutPostRedisplay();
         glutTimerFunc(1000.0, timerDownfunc,0);
}



int main(int argc, char **argv){

    srand(time(NULL));
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
    glutTimerFunc(1000.0, timerDownfunc,0);
    //glutReshapeFunc(resize);
    

    glutMainLoop();                       //<-- LISTEN FOR WINDOW EVENTS
}