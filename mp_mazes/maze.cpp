/* Your code here! */
#include "maze.h"
#include <time.h>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
using namespace cs225;


SquareMaze::SquareMaze()
{}


void SquareMaze::randomlyRemoveWall(int width, int height)
{
    int decide, currentIdx, rightIdx, downIdx;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            decide=rand()%2;
            currentIdx=i*width+j;
            rightIdx=currentIdx+1;
            downIdx=currentIdx+width;
            
            if(j==width-1 && i!=height-1 && dsets.find(currentIdx)!=dsets.find(downIdx))
            {
                maze[i][j].downW=false;
                dsets.setunion(currentIdx, downIdx);
            }
            else if(j!=width-1 && i==height-1 && dsets.find(currentIdx)!=dsets.find(rightIdx))
            {
                maze[i][j].rightW=false;
                dsets.setunion(currentIdx, rightIdx);
            }
            else if(i!=height-1 && j!=width-1 )
            {
                if(decide==0 && dsets.find(currentIdx)!=dsets.find(rightIdx))
                {
                    maze[i][j].rightW=false;
                    dsets.setunion(currentIdx, rightIdx);
                }
                else if(decide==1 && dsets.find(currentIdx)!=dsets.find(downIdx))
                {
                    maze[i][j].downW=false;
                    dsets.setunion(currentIdx, downIdx);
                }
            }
        }
    }
}


void SquareMaze::makeMaze(int width, int height)
{
    if(maze.size()!=0)
    {
        dsets.clearSets();
        maze.clear();
    }
    
    dsets.addelements(width*height);
    for(int i=0;i<height;i++)
    {
        vector<Grid> temp;
        for(int j=0;j<width;j++)
        {
            temp.push_back(Grid(true,true));
        }
        maze.push_back(temp);
    }
    randomlyRemoveWall(width,height);
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if(dir==0)
        return maze[y][x].rightW==false;
    else if(dir==1)
        return maze[y][x].downW==false;
    else if(dir==2 && x-1>=0)
        return maze[y][x-1].rightW==false;
    else if(dir==3 && y-1>=0)
        return maze[y-1][x].downW==false;
    return false;
}

bool SquareMaze::isolated(int x, int y)
{
    bool flag0=canTravel(x,y,0);
    bool flag1=canTravel(x,y,1);
    bool flag2=canTravel(x,y,2);
    bool flag3=canTravel(x,y,3);
    bool res = flag0 || flag1 || flag2 || flag3;
    if(res)
        return false;
    return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    int width = maze[0].size();
    int height = maze.size();
    int currentIdx=y*width+x;
    int rightIdx=currentIdx+1;
    int downIdx=currentIdx+width;
    if(dir==0 && exists)
        maze[y][x].rightW=true;
    else if(dir==0 && !exists && x!=width-1)
        maze[y][x].rightW=false;
    else if(dir==1 && exists)
        maze[y][x].downW=true;
    else if(y!=height-1)
        maze[y][x].downW=false; 
}

vector<int> SquareMaze::solveMaze()
{
    int height=maze.size();
    int width=maze[0].size();

    vector<int> winning_path;
    /*queue<int> toVisit;
    vector<vector<bool>> visited;
    vector<vector<int>> dist;

    for(int i=0;i<height;i++)
    {
        vector<bool> temp1;
        vector<int> temp2;
        for(int j=0;j<width;j++)
        {
            temp1.push_back(false);
            temp2.push_back(-1);
        }
        visited.push_back(temp1);
        dist.push_back(temp2);
    }
    
    dist[0][0]=0;
    int current;
    toVisit.push(0);
    while(toVisit.size()!=0)
    {
        current=toVisit.front();
        toVisit.pop();
        int x=current%width;
        int y=current/width;
        visited[y][x]=true;
        if(canTravel(x,y,0) && !visited[y][x+1])
        {
            dist[y][x+1]=dist[y][x]+1;
            toVisit.push(current+1);
        }
        if(canTravel(x,y,1) && !visited[y+1][x])
        {
            dist[y+1][x]=dist[y][x]+1;
            toVisit.push(current+width);
        }
        if(canTravel(x,y,2) && !visited[y][x-1])
        {
            dist[y][x-1]=dist[y][x]+1;
            toVisit.push(current-1);
        }
        if(canTravel(x,y,3) && !visited[y-1][x])
        {
            dist[y-1][x]=dist[y][x]+1;
            toVisit.push(current-width);
        }
    }

    maxX=0;    
    for(int x=0;x<width;x++)
    {
        if(dist[maxX][height-1]<dist[x][height-1])
            maxX=x;
    }

    int btX=maxX;
    int btY=height-1;
    while(btX!=0 || btY!=0)
    {

    }*/
    return winning_path;
}

PNG* SquareMaze::drawMaze() const
{
    unsigned int height=maze.size();
    unsigned int width=maze[0].size();
    PNG* mazePNG = new PNG(width*10+1, height*10+1);

    //Blaken
    for(unsigned int x=0;x<mazePNG->width();x++)
    {
        if(x<1 || x >9)
            mazePNG->getPixel(x,0).l=0;
    }
    for(unsigned int y=0;y<mazePNG->height();y++)
    {
        mazePNG->getPixel(0,y).l=0;
    }

    for(unsigned int y=0;y<height;y++)
    {
        for(unsigned int x=0;x<width;x++)
        {
            if(maze[y][x].rightW)
            {
                for(int k=0;k<=10;k++)
                {
                    mazePNG->getPixel((x+1)*10,y*10+k).l=0;
                }
            }
            if(maze[y][x].downW)
            {
                for(int k=0;k<=10;k++)
                {
                    mazePNG->getPixel(x*10+k,(y+1)*10).l=0;
                }
            }
        }
    }
    return mazePNG;
}

PNG* SquareMaze::drawMazeWithSolution()
{
    PNG* toReturn = new PNG();
    return toReturn;
}