#ifndef MAZEGEN
#define MAZEGEN

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include <QGraphicsScene>
#include <SFML/Graphics.hpp>
#include <QDebug>

#define MAX 31  // 15 * 2 + 1
#define CELL 225  // 15 * 15
#define WALL 1
#define PATH 0

class MazeGen{
private:
    static void init_maze(sf::Sprite* maze[MAX][MAX])
    {
        for(int a = 0; a < MAX; a++)
        {
            for(int b = 0; b < MAX; b++)
            {
                maze[a][b] = new sf::Sprite();
                maze[a][b]->setScale(0.125f,0.125f);
                maze[a][b]->setPosition(wallTexture.getSize().x*b,wallTexture.getSize().y*a);
                if(a % 2 == 0 || b % 2 == 0)
                    maze[a][b]->setTexture(wallTexture);
                else
                    maze[a][b]->setTexture(pathTexture);
            }
        }
    }

    static void maze_generator(int indeks, sf::Sprite* maze[MAX][MAX], int backtrack_x[CELL], int backtrack_y[CELL], int x, int y, int n, int visited)
    {
        if(visited < n * n)
        {
            int neighbour_valid = -1;
            int neighbour_x[4];
            int neighbour_y[4];
            int step[4];

            int x_next;
            int y_next;

            if(x - 2 > 0 && is_closed(maze, x - 2, y))  // upside
            {
                neighbour_valid++;
                neighbour_x[neighbour_valid]=x - 2;;
                neighbour_y[neighbour_valid]=y;
                step[neighbour_valid]=1;
            }

            if(y - 2 > 0 && is_closed(maze, x, y - 2))  // leftside
            {
                neighbour_valid++;
                neighbour_x[neighbour_valid]=x;
                neighbour_y[neighbour_valid]=y - 2;
                step[neighbour_valid]=2;
            }

            if(y + 2 < n * 2 + 1 && is_closed(maze, x, y + 2))  // rightside
            {
                neighbour_valid++;
                neighbour_x[neighbour_valid]=x;
                neighbour_y[neighbour_valid]=y + 2;
                step[neighbour_valid]=3;

            }

            if(x + 2 < n * 2 + 1 && is_closed(maze, x + 2, y))  // downside
            {
                neighbour_valid++;
                neighbour_x[neighbour_valid]=x+2;
                neighbour_y[neighbour_valid]=y;
                step[neighbour_valid]=4;
            }

            if(neighbour_valid == -1)
            {
                // backtrack
                x_next = backtrack_x[indeks];
                y_next = backtrack_y[indeks];
                indeks--;
            }

            if(neighbour_valid!=-1)
            {
                int randomization = neighbour_valid + 1;
                int random = rand()%randomization;
                x_next = neighbour_x[random];
                y_next = neighbour_y[random];
                indeks++;
                backtrack_x[indeks] = x_next;
                backtrack_y[indeks] = y_next;

                int rstep = step[random];

                if(rstep == 1)
                    maze[x_next+1][y_next]->setTexture(pathTexture);
                else if(rstep == 2)
                    maze[x_next][y_next + 1]->setTexture(pathTexture);
                else if(rstep == 3)
                    maze[x_next][y_next - 1]->setTexture(pathTexture);
                else if(rstep == 4)
                    maze[x_next - 1][y_next]->setTexture(pathTexture);
                visited++;
            }

            maze_generator(indeks, maze, backtrack_x, backtrack_y, x_next, y_next, n, visited);
        }
        //generer entree et sortie -- temporairement hardcode
        maze[0][1]->setTexture(pathTexture);
        maze[MAX-1][MAX-2]->setTexture(*pathTexture);

    }

    static int is_closed(sf::Sprite* maze[MAX][MAX], int x, int y)
    {
        if(maze[x - 1][y]->getTexture() != pathTexture
           && maze[x][y - 1]->getTexture() != pathTexture
           && maze[x][y + 1]->getTexture() != pathTexture
           && maze[x + 1][y]->getTexture() != pathTexture
        )
            return 1;

        return 0;
    }

public:
    static void Generate(sf::Sprite* maze[MAX][MAX])
    {
        srand((unsigned)time(NULL));
        int index = 0;
        int backtrack_x[CELL];
        int backtrack_y[CELL];

        init_maze(maze);

        backtrack_x[index] = 1;
        backtrack_y[index] = 1;

        maze_generator(index, maze, backtrack_x, backtrack_y, 1, 1, (MAX-1)/2, 1);

        return;
    }

//    static void PrintMaze(QGraphicsPixmapItem* maze[MAX][MAX])
//    {
//         for(int a = 0; a < MAX; a++)
//         {
//             for(int b = 0; b < MAX; b++)
//             {
//                 if(maze[a][b]->isVisible())
//                     std::cout << "#";
//                 else
//                     std::cout << " ";
//             }
//             std::cout << std::endl;
//         }
//    }

//    static void AddToScene(QGraphicsPixmapItem* maze[MAX][MAX], QGraphicsScene* scene)
//    {
//        for(int a = 0; a < MAX; a++)
//        {
//            for(int b = 0; b < MAX; b++)
//            {
//                scene->addItem(maze[a][b]);
//            }
//            std::cout << std::endl;
//        }
//    }
};



#endif // MAZEGEN

