#include "Puzzle.h"

Puzzle::Puzzle()
{
    //ctor
}

Puzzle::Puzzle(int grid[HEIGHT][WIDTH])
{
    int k = 0;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(grid[i][j]==0){ empty_pos = k; }
            linear_puzzle[k] = grid[i][j];
            k++;
        }
    }
    actionName = "";
    prev = nullptr;
}

void Puzzle::swap_values(int first, int second)
{
    int temp = linear_puzzle[first];
    linear_puzzle[first] = linear_puzzle[second];
    linear_puzzle[second] = temp;
}

bool Puzzle::goUp(Puzzle &p)
{
    if(empty_pos>=WIDTH)
    {
        p = *this;
        p.swap_values(empty_pos, empty_pos-WIDTH);
        p.setActionname("up");
        p.setEmpty_pos(empty_pos-WIDTH);
        p.setPrev(this);
        return true;
    }
    return false;
}
bool Puzzle::goDown(Puzzle &p)
{
    if(empty_pos<WIDTH*HEIGHT - WIDTH)
    {
        p = *this;
        p.swap_values(empty_pos, empty_pos+WIDTH);
        p.setActionname("down");
        p.setEmpty_pos(empty_pos+WIDTH);
        p.setPrev(this);
        return true;
    }
    return false;
}
bool Puzzle::goLeft(Puzzle &p)
{
    if(empty_pos%WIDTH!=0)
    {
        p = *this;
        p.swap_values(empty_pos, empty_pos-1);
        p.setActionname("left");
        p.setEmpty_pos(empty_pos-1);
        p.setPrev(this);
        return true;
    }
    return false;
}
bool Puzzle::goRight(Puzzle &p)
{
    if((empty_pos+1)%WIDTH!=0)
    {
        p = *this;
        p.swap_values(empty_pos, empty_pos+1);
        p.setActionname("right");
        p.setEmpty_pos(empty_pos+1);
        p.setPrev(this);
        return true;
    }
    return false;
}
vector<Puzzle*> Puzzle::expand()
{
    vector<Puzzle*> children;
    Puzzle* child;

    child = new Puzzle(*this);
    if(goUp(*child))
    { children.push_back(child); }
    else
    { delete child; }

    child = new Puzzle(*this);
    if(goDown(*child))
    { children.push_back(child); }
    else
    { delete child; }

    child = new Puzzle(*this);
    if(goLeft(*child))
    { children.push_back(child); }
    else
    { delete child; }

    child = new Puzzle(*this);
    if(goRight(*child))
    { children.push_back(child); }
    else
    { delete child; }


    return children;
}

bool Puzzle::operator==(const Puzzle& o) const
{
    for(int i=0;i<WIDTH*HEIGHT;i++)
    {
        if(linear_puzzle[i]!=o.linear_puzzle[i])
            return false;
    }
    return true;
}

Puzzle Puzzle::operator= (Puzzle o)
{

    *linear_puzzle = *o.linear_puzzle;
    empty_pos = o.empty_pos;
    prev = o.prev;
    actionName = o.actionName;
    return *this;
}

int Puzzle::getDepth()
{
    int counter =0;
    Puzzle *p = this;
    while (p->prev!=nullptr)
    {
        p=p->prev;
        counter++;
    }
    return counter;
}


int Puzzle::heuristic(Puzzle *goal)
{
    int  counter = 0;
    for(int i=0;i<HEIGHT*WIDTH;i++)
    {
        if(linear_puzzle[i]!=goal->linear_puzzle[i])
            counter++;
    }
    return counter;
}













