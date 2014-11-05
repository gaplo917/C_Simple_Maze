//
//  main.cpp
//  maze
//
//  Created by Gap on 5/11/14.
//
//

#include "main.h"
#include<iostream>

using namespace std;

#define WIDTH 7
#define HEIGHT 7
#define BLOCK 1
#define EXIT 9
#define START 4
#define PATH 3
#define ROAD 0 
void printMaze(int maze[][HEIGHT] ){
    for(int y=0; y < HEIGHT ; y++){
        for(int x=0; x < WIDTH ; x++){
            printf("%3d",maze[x][y]);
        }
        printf("\n");
    }

}

void drawPathOnMaze(int maze[][HEIGHT],int x, int y){
    maze[x][y] = PATH;
}
bool isBlocked(int maze[][HEIGHT],int x, int y){
    return (maze[x][y] == BLOCK);
}

bool containPoint(int *path,int x, int y,int counter){
    for(int i=0 ; i< counter ; i+=2){
        //printf("checking");
        if(path[i] == x && path[i+1] ==y){
            return true;
        }
    }
    return false;
}

void findMazeStart(int maze[][HEIGHT],int &startX,int &startY){
    for(int y=0; y < HEIGHT ; y++){
        for(int x=0; x < WIDTH ; x++){
            if(maze[x][y] == START){
                startX = x;
                startY = y;
            }
        }
    }
}

bool inMaze(int x, int y){
    return x >= 0 && x < WIDTH && y >=0 && y < HEIGHT;
}
bool isExit(int maze[][HEIGHT],int x , int y){
    return maze[x][y] == EXIT;
}
bool solveMaze(int maze[][HEIGHT],int x, int y, int *path,int counter ){

    if(!inMaze(x,y)){
        // TODO: (x,y) is in Maze
        return false;
    }
    else if (isExit(maze,x,y) && !isBlocked(maze,x,y)){
        // TODO: (x,y) is the Exit, print the solution
        printf("Solution:\n");
        for(int i =0 ; i < counter; i+=2){
            printf("(%1d,%1d),",path[i],path[i+1]);
            if(i!=0){
                // don't overwrite start 
                drawPathOnMaze(maze,path[i],path[i+1]);
            }
        }
        printf("(%1d,%1d)\n",x,y);

        return true;
    }
    else if(containPoint(path,x,y,counter) || isBlocked(maze,x,y)){
        // TODO: ignore duplicate (x,y)  OR the (x,y) is blocked
        return false;
    }
    else{

        // TODO: create an new array with currentSize+2 for each test
        int *newPath = new int[(counter+1)*2];

        // TODO: copy the currentPath to new array
        for(int i =0 ; i < counter ; i+=2){
                newPath[i] = path[i];
                newPath[i+1]=path[i+1];
        }

        // TODO: put (x,y) into the new Path
        newPath[counter] = x;
        newPath[counter+1] =y;

        // TODO: Check neighbour with resursion
        return solveMaze(maze,x+1,y,newPath,counter+2) 
            || solveMaze(maze,x,y+1,newPath,counter+2)
            || solveMaze(maze,x-1,y,newPath,counter+2)
            || solveMaze(maze,x,y-1,newPath,counter+2);
    }

}




int main(){
    printf("START\t:%3d\n",START);
    printf("BLOCK\t:%3d\n",BLOCK);
    printf("EXIT\t:%3d\n",EXIT);
    printf("ROAD\t:%3d\n",ROAD);
    printf("PATH\t:%3d\n",PATH);
    

    int maze[WIDTH][HEIGHT];
    int path[WIDTH*HEIGHT*2];
    for(int x=0; x < WIDTH ; x++){
        for(int y=0; y < HEIGHT ; y++){
            if(x == 0 || y==0 || y == HEIGHT -1 || x == WIDTH -1){
                // set outter block as boundary of maze
                maze[x][y] = BLOCK;
            }
            else{
                maze[x][y] = ROAD;
            }
        }
    }

    // Manual set the Maze
    maze[1][0] = EXIT;

    maze[1][2] = BLOCK;

    maze[2][2] = BLOCK;

    maze[3][2] = BLOCK;

    maze[4][2] = BLOCK;

    maze[4][3] = BLOCK;

    maze[4][4] = BLOCK;

    maze[3][4] = BLOCK;

    maze[2][4] = BLOCK;

    // maze[1][4] = BLOCK; // Uncoment to trigger no solution


    maze[3][3] = START;


    int startX = -1;
    int startY = -1;

    // startX , startY  passed by ref
    findMazeStart(maze,startX,startY);

    // print
    printMaze(maze);

    printf("Start at(%1d,%1d)\n\n",startX,startY);


    if(solveMaze(maze,startX,startY,path,0)){
        // can solve
        printf("%s\n", "MAZE WITH PATH");
        printMaze(maze);

    }
    else{
        // no solution
        printf("%s\n", "No Solution");
    }


}




