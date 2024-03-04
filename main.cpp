#include <iostream>
#include "source/AStar.hpp"

void find_current_go(unsigned int& need_to_go,unsigned int &n_need_to_go,unsigned int &CURRENT_ORIEN,std::vector<unsigned int>*ORIEN)
{
    if(CURRENT_ORIEN == 0)
    {
        need_to_go = n_need_to_go;
    }
    else
    {
        need_to_go =ORIEN[CURRENT_ORIEN][n_need_to_go];
    }
}

int main()
{
    AStar::Generator generator;
    generator.setWorldSize({3, 3});
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(false);

    std::vector<unsigned int> ORIEN[4];
    ORIEN[0] = {0,1,2,3};
    ORIEN[1] = {3,0,1,2};
    ORIEN[2] = {2,3,0,1};
    ORIEN[3] = {1,2,3,0};

    unsigned int CURRENT_ORIENT = 0;
    unsigned int n_need_to_go;
    unsigned int need_to_go;

    AStar::Vec2i src ;
    AStar::Vec2i des ;
    std::cout<<"Enter the Source x "<<std::endl;
    std::cin>>src.x;
    std::cout<<"Enter the Source y "<<std::endl;
    std::cin>>src.y;
    while(true)
    {

        std::cout<<"Enter the Destination x "<<std::endl;
        std::cin>>des.x;
        std::cout<<"Enter the Destination y "<<std::endl;
        std::cin>>des.y;
        std::cout << "Generate path ... \n";
        auto path = generator.findPath(src, des,CURRENT_ORIENT);
        
        std::cout<<"Directions"<<std::endl;
        for(int i = path.size()-1;i>0;i--)
        {   
            int x = path[i-1].x - path[i].x;
            int y = path[i-1].y - path[i].y;

            if(x==0 && y == 1)         
            {
            n_need_to_go = 0; 
            }
            if(x==0 && y == -1)
            {
                n_need_to_go=2;
            }
            if(x==1 && y == 0)
            {
                n_need_to_go = 1;
            }
            if(x == -1 && y == 0) 
            {
                n_need_to_go = 3;
            }
            find_current_go(need_to_go,n_need_to_go,CURRENT_ORIENT,ORIEN);
            std::cout<<need_to_go<<std::endl;
            CURRENT_ORIENT=n_need_to_go;
        }

        for(auto& coordinate : path) {
            std::cout << coordinate.x << " " << coordinate.y << "\n";
        }

        src.x = des.x;
        src.y = des.y;
    }
}