#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  this->png=png;
  visited=new bool*[png.width()];
  for(unsigned int i=0;i<png.width();i++)
  {
    visited[i]=new bool[png.height()];
    for(unsigned int j=0;j<png.height();j++)
    {
      visited[i][j]=false;
    }
  }
  this->start=start;
  this->tolerance=tolerance;
  toVisit.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal::Iterator it(this,start);
  pop();
  unsigned x=start.x;
  unsigned y=start.y;
  if((x+1) <png.width())
  {
    if(!visited[x+1][y]&&withinTol(tolerance,png.getPixel(start.x,start.y),png.getPixel(x+1,y)))
    {
      add(Point(x+1,y));
    }
  }
  if((y+1) <png.height())
  {
    if(!visited[x][y+1]&&withinTol(tolerance,png.getPixel(start.x,start.y),png.getPixel(x,y+1)))
    {
      add(Point(x,y+1));
    }
  }
  if((x-1)>=0)
  {
    if(!visited[x-1][y]&&withinTol(tolerance,png.getPixel(start.x,start.y),png.getPixel(x-1,y)))
    {
      add(Point(x-1,y));
    }
  }
  if((y-1)>=0)
  {
    if(!visited[x][y-1]&&withinTol(tolerance,png.getPixel(start.x,start.y),png.getPixel(x,y-1)))
    {
      add(Point(x,y-1));
    }
  }
  visited[x][y]=true;
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  toVisit.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point current=toVisit.front();
  toVisit.pop();
  return current;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return empty() ? Point() : toVisit.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return toVisit.empty();
}
