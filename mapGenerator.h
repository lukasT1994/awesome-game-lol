//
//  mapGenerator.h
//  mapGenerator
//
//  Created by Desislav Hristov on 28/11/2013.
//  Copyright (c) 2013 Desislav Hristov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char** createEmptyLevel(int row, int col)
{
    int i, j;
    
    char** level = (char**)malloc(row * sizeof(char*));
    for (i=0; i<row; i++) level[i]=(char*)malloc(col*sizeof(char));
    
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            level[i][j] = ' ';
        }
    }
    return level;
}

void deleteLevel(char** level, int row)
{
    int i;
    for (i=0; i<row; i++) free(level[i]);
    free(level);
}

void seedLevel(char** level, int row, int col, int chanceToStartAlive)
{
    int i, j;
    srand((unsigned)time(NULL));
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if((rand()%100)<chanceToStartAlive) level[i][j] = '0';
            else level[i][j] = ' ';
        }
    }
}

int countAliveNeighbours(char** level, int x, int y, int row, int col)
{
    int count = 0;
    int i, j;
    for (i = -1; i<2; i++)
    {
        for(j = -1; j<2; j++)
        {
            if((i!=0)||(j!=0))
            {
                if(((x + i) < 0) || ((x + i) >= row) || ((y + j) < 0) || ((y + j) >= col) || (level[x+i][y+j] == '0')) count++;
            }
        }
    }
    return count;
}

void doSimulationStep(char** level, int row, int col, int birthLimit, int deathLimit)
{
    int i, j, aliveNeighbours;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            aliveNeighbours = countAliveNeighbours(level, i, j, row, col);
            if(level[i][j] == '0')
            {
                if(aliveNeighbours < deathLimit) level[i][j] = ' ';
            }
            else
            {
                if(aliveNeighbours > birthLimit) level[i][j] = '0';
            }
        }
    }
}

void placeTops(char** level, int row, int col)
{
    int i, j;
    for(i=1; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(level[i][j] != ' '){
                if(level[i-1][j] == ' '){
                    level[i][j] = 't';
                }
            }
        }
    }
}

void placeTopLefts(char** level, int row, int col)
{
    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=1; j<col; j++)
        {
            if(level[i][j] == 't'){
                if(level[i][j-1] == ' '){
                    level[i][j] = '1';
                }
            }
        }
    }
}

void placeTopRights(char** level, int row, int col)
{
    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col-1; j++)
        {
            if(level[i][j] == 't'){
                if(level[i][j+1] == ' '){
                    level[i][j] = '2';
                }
            }
        }
    }
}

void placeBots(char** level, int row, int col)
{
    int i, j;
    for(i=0; i<(row-1); i++)
    {
        for(j=0; j<col; j++)
        {
            if(level[i][j] != ' '){
                if(level[i+1][j] == ' '){
                    level[i][j] = 'b';
                }
            }
        }
    }
}

void placeBotLefts(char** level, int row, int col)
{
    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=1; j<col; j++)
        {
            if(level[i][j] == 'b'){
                if(level[i][j-1] == ' '){
                    level[i][j] = '3';
                }
            }
        }
    }
}

void placeBotRights(char** level, int row, int col)
{
    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col-1; j++)
        {
            if(level[i][j] == 'b'){
                if(level[i][j+1] == ' '){
                    level[i][j] = '4';
                }
            }
        }
    }
}

char** createLevel(int row, int col, int chanceToStartAlive, int birthLimit, int deathLimit, int numberOfSteps)
{
    int i, j, k, m;
    int initRow = row/8;
    int initCol = col/8;
    char** initLevel = createEmptyLevel(initRow, initCol);
    char** level = createEmptyLevel(row, col);
    seedLevel(initLevel, initRow, initCol, chanceToStartAlive);
    for(i=0; i<numberOfSteps; i++)
    {
        doSimulationStep(initLevel, initRow, initCol, birthLimit, deathLimit);
    }
    
    for(i=0; i<initCol; i++) {
        initLevel[0][i] = '0';
        initLevel[initRow-1][i] = '0';
    }
    for(i=0; i<initRow; i++) {
        initLevel[i][0] = '0';
        initLevel[i][initCol-1] = '0';
    }
    
    for(i=0; i<initRow; i++)
    {
        for(j=0; j<initCol; j++)
        {
            if(initLevel[i][j] == '0')
            {
                for(k=0; k<8; k++)
                {
                   for(m=0; m<8; m++)
                   {
                       level[(i*8)+k][(j*8)+m] = '0';
                   }
                }
            }
        }
    }
    
    placeTops(level, row, col);
    placeTopLefts(level, row, col);
    placeTopRights(level, row, col);
    placeBots(level, row, col);
    placeBotLefts(level, row, col);
    placeBotRights(level, row, col);
    return level;
}
