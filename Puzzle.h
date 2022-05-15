#ifndef PUZZLE_H
#define PUZZLE_H
#define WIDTH 3
#define HEIGHT 3
#include <string>
#include <sstream>
#include <vector>
#include <iostream>


using namespace std;

class Puzzle
{
    public:
        Puzzle();
        Puzzle(int[HEIGHT][WIDTH]);

        void swap_values(int first, int second);
        void setEmpty_pos(int e) { empty_pos=e; }
        void setPrev(Puzzle *p) { prev = p; }
        void setActionname(string action ) { actionName = action; }
        string getActionname() { return actionName; }
        Puzzle* getPrev() const { return prev; }
        void print()
        {
            if(this==nullptr) {cout<<"This is the starting point"; return;}

            cout<<"_______"<<endl;
            for (int i = 0; i < HEIGHT*WIDTH; i++)
            {
               cout<<linear_puzzle[i]<<" ";
               if((i+1)%WIDTH==0) cout<<endl;
            }
            cout<<"_______"<<endl;
        }

        bool goUp(Puzzle &p);
        bool goDown(Puzzle &p);
        bool goLeft(Puzzle &p);
        bool goRight(Puzzle &p);
        vector<Puzzle*> expand();

        bool operator==(const Puzzle& o) const ;
        Puzzle operator= (Puzzle o);
        int getDepth();
        string getKey()
        {
            string key = "";
            for(int i=0;i<WIDTH*HEIGHT;i++)
            {
                key.append(to_string(linear_puzzle[i]));
            }
            return key;
        }
        void printSolution()
        {
            Puzzle *p = this;
            while (p->prev!=nullptr)
            {
                //p->print();
                cout<<p->getActionname();
                p = p->prev;
                if(p->prev!=nullptr)
                    cout<<"->";
            }
        }

        void setHvalue(int v){ Hvalue = v; }
        int getHvalue() { return Hvalue; }
        int heuristic(Puzzle*);
    protected:

    private:
        int linear_puzzle[HEIGHT*WIDTH];
        string actionName;
        Puzzle *prev;
        int empty_pos; // Position of the "empty" square in the linear puzzle.
        int Hvalue;    // Heuristic value.
};

class myComparator
{
public:
    int operator() (Puzzle *p1 , Puzzle *p2) const
    {
        return p1->getHvalue()>p2->getHvalue();
    }
};

class myComparator2
{
public:
    int operator() (Puzzle *p1 , Puzzle *p2) const
    {
        return (p1->getHvalue()+p1->getDepth()) > (p2->getHvalue()+p2->getDepth());
    }
};

#endif // PUZZLE_H
