/* Your code here! */
#include "maze.h"
#include <time.h>
using namespace std;
using namespace cs225;


SquareMaze::SquareMaze()
{}


void SquareMaze::randomlyRemoveWall(int width, int height)
{
    srand(time(NULL));
    int decide1, decide2, currentIdx, rightIdx, downIdx;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            decide1=rand()%2;
            decide2=rand()%2;
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
                if(decide1==0 && decide2==0 && dsets.find(currentIdx)!=dsets.find(rightIdx))
                {
                    maze[i][j].rightW=false;
                    dsets.setunion(currentIdx, rightIdx);
                }
                else if(decide1==1 && decide2==0 && dsets.find(currentIdx)!=dsets.find(rightIdx))
                {
                    maze[i][j].rightW=false;
                    dsets.setunion(currentIdx, rightIdx);
                }
                else if(decide1==0 && decide2==1 && dsets.find(currentIdx)!=dsets.find(downIdx))
                {
                    maze[i][j].downW=false;
                    dsets.setunion(currentIdx, downIdx);
                }
                else if(decide1==1 && decide2==1 && dsets.find(currentIdx)!=dsets.find(downIdx))
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

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{

}

vector<int> SquareMaze::solveMaze()
{
    vector<int> toReturn;
    return toReturn;
}

PNG* SquareMaze::drawMaze() const
{
    PNG* toReturn = new PNG();
    return toReturn;
}

PNG* SquareMaze::drawMazeWithSolution()
{
    PNG* toReturn = new PNG();
    return toReturn;
}