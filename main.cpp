#include <iostream>
#include "Puzzle.h"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;



Puzzle* DFS(Puzzle *initial, Puzzle *goal, long long &examined, long long &mem)
{
    stack<Puzzle*> frontier;
    unordered_map<string, Puzzle*> closed;

    frontier.push(initial);
    examined = 0;
    mem = 1;

    while(frontier.size()>0)
    {
        if(frontier.size()+closed.size()>mem)
            mem = frontier.size()+closed.size();
        Puzzle *p = frontier.top();
        frontier.pop();
        if(closed.find(p->getKey())==closed.end())
        {
            examined++;
            if(*p==*goal)
                return p;
            pair<string, Puzzle*> k(p->getKey(), p);
            closed.insert(k);
            vector<Puzzle *> children =p->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.find(children[i]->getKey())==closed.end())
                    frontier.push(children[i]);
        }
    }
    return nullptr;
}

Puzzle* BFS(Puzzle *initial, Puzzle *goal, long long &examined, long long &mem)
{
    queue<Puzzle*> frontier;
    unordered_map<string, Puzzle*> closed;

    frontier.push(initial);
    examined = 0;
    mem = 1;

    while(frontier.size()>0)
    {
        if(frontier.size()+closed.size()>mem)
            mem = frontier.size()+closed.size();
        Puzzle *p = frontier.front();
        frontier.pop();
        if(closed.find(p->getKey())==closed.end())
        {
            examined++;
            if(*p==*goal)
                return p;
            pair<string, Puzzle*> k(p->getKey(), p);
            closed.insert(k);
            vector<Puzzle *> children =p->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.find(children[i]->getKey())==closed.end())
                    frontier.push(children[i]);
        }
    }
    return nullptr;
}


Puzzle *BestFS(Puzzle *initial,Puzzle *goal, long long &examined, long long &mem)
{
    priority_queue <Puzzle*, vector<Puzzle *>, myComparator > frontier;
    unordered_map <string,Puzzle*> closed;
    frontier.push(initial);
    examined = 0;
    mem=1;
    while (frontier.size()>0)
    {
        if (frontier.size() + closed.size() > mem)
            mem = frontier.size() + closed.size();
        Puzzle *p = frontier.top();
        frontier.pop();

        if(closed.find(p->getKey())==closed.end())
        {
            examined++;
            if (*p==*goal)
                return p;
            pair<string,Puzzle*> k (p->getKey(),p);
            closed.insert(k);
            vector<Puzzle *> children = p->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (closed.find(children[i]->getKey())==closed.end())
                {
                    children.at(i)->setHvalue(children.at(i)->heuristic(goal));
                    frontier.push(children.at(i));
                }
            }
        }
    }
    return nullptr;
}


Puzzle *A_star(Puzzle *initial,Puzzle *goal, long long &examined, long long &mem)
{
    priority_queue <Puzzle*, vector<Puzzle *>, myComparator2 > frontier;
    unordered_map <string,Puzzle*> closed;
    frontier.push(initial);
    examined = 0;
    mem=1;
    while (frontier.size()>0)
    {
        if (frontier.size() + closed.size() > mem)
            mem = frontier.size() + closed.size();
        Puzzle *p = frontier.top();
        frontier.pop();

        if(closed.find(p->getKey())==closed.end())
        {
            examined++;
            if (*p==*goal)
                return p;
            pair<string,Puzzle*> k (p->getKey(),p);
            closed.insert(k);
            vector<Puzzle *> children = p->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (closed.find(children[i]->getKey())==closed.end())
                {
                    children.at(i)->setHvalue(children.at(i)->heuristic(goal));
                    frontier.push(children.at(i));
                }
            }
        }
    }
    return nullptr;
}

int main()
{
    //-----------------------------------------------------
    // project description puzzle
    int a[HEIGHT][WIDTH] = { {3,6,0}, {1,4,2}, {7,5,8} };
    int b[HEIGHT][WIDTH] = { {1,2,3}, {4,5,6}, {7,8,0} };
    //-----------------------------------------------------

    //-----------------------------------------------------
    // Random 3x3 SOLVABLE puzzle
    //int a[HEIGHT][WIDTH] = { {7,2,3}, {1,0,6}, {8,4,5} };
    //int b[HEIGHT][WIDTH] = { {1,2,3}, {4,5,6}, {7,8,0} };
    //-----------------------------------------------------

    /*
    4x4
    int a[HEIGHT][WIDTH] = { {11,2,14,13}, {3,12,15,7}, {1,5,0,8}, {9,10,6,4} };
    int b[HEIGHT][WIDTH] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0} };
    */
    Puzzle s(a);
    Puzzle g(b);
    long long mem, examined;


    Puzzle *initial = &s;
    Puzzle *goal = &g;
    Puzzle *bsol;

    cout<<"Initial:"<<endl;initial->print();
    cout<<endl;
    cout<<"Goal:"<<endl;goal->print();

    cout<<endl<<"DFS: ";
    bsol = DFS(initial, goal, examined, mem);
    if (bsol!=nullptr)
    {
        cout<<"depth = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;

    cout<<endl<<"BFS: ";
    bsol = BFS(initial, goal, examined, mem);
    if (bsol!=nullptr)
    {
        cout<<"depth = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;

    cout<<endl<<"BestFS: ";
    bsol = BestFS(initial, goal, examined, mem);
    if (bsol!=nullptr)
    {
        cout<<"depth = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;


    cout<<endl<<"A*: ";
    bsol = A_star(initial, goal, examined, mem);
    if (bsol!=nullptr)
    {
        cout<<"depth = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;


    return 0;
}
