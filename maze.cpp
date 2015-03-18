#include "maze.h"
#include <qdebug.h>

const float Maze::SCALE = 0.17;
const float Maze::SPEED = 15;

Maze::Maze(sf::RenderWindow &_window)
    : window(&_window),
      isMoving(false)
{

}

Maze::~Maze()
{

}

bool *Maze::getMoving()
{
    return &isMoving;
}

void Maze::move(int int_dir)
{
    if(!isMoving)
    {
        switch(int_dir)
        {
        case UP:
            dir = sf::Vector2i(0,-1);
            qDebug() << "trying to move up";
            break;
        case DOWN:
            dir = sf::Vector2i(0,1);
            qDebug() << "trying to move down";
            break;
        case LEFT:
            dir = sf::Vector2i(-1,0);
            qDebug() << "trying to move left";
            break;
        case RIGHT:
            dir = sf::Vector2i(1,0);
            qDebug() << "trying to move right";
            break;
        }
        sf::Vector2i temp = currentPos + dir;
        sf::Vector2i test90;
        sf::Vector2i test270;
        while(!(temp.x < 0 || temp.y < 0 || spriteArray[temp.x][temp.y]->getTexture() == &wallTexture))
        {
            qDebug() << "can move in that direction!";
            isMoving = true;
            currentPos = temp;
            temp = currentPos + dir;
            test90 = currentPos + sf::Vector2i(dir.y,dir.x);
            test270 = currentPos + sf::Vector2i(-dir.y,-dir.x);
            if(spriteArray[test90.x][test90.y]->getTexture() == &pathTexture ||
               spriteArray[test270.x][test270.y]->getTexture() == &pathTexture)
                break;
        }
    }
    else
        qDebug() << "cannot move, already moving";
}

void Maze::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(int colonne = 0; colonne < width*2+1; colonne++)
    {
        for(int ligne = 0; ligne < height*2+1; ligne++)
        {
            target.draw(*spriteArray[colonne][ligne], states);
        }
    }
}

void Maze::initialize(int _width,int _height, sf::Texture _wall, sf::Texture _path)
{
    width = _width;
    height = _height;
    wallTexture = _wall;
    pathTexture = _path;
    CELL = width*height;

    srand((unsigned)time(NULL));
    int index = 0;
    int* backtrack_x = new int[CELL];
    int* backtrack_y = new int[CELL];
    init_array();
    backtrack_x[index] = 1;
    backtrack_y[index] = 1;
    maze_generator(index, backtrack_x, backtrack_y, 1, 1, 1);
    currentPos = sf::Vector2i(1,0);

	delete[] backtrack_x;
	delete[] backtrack_y;
}

void Maze::init_array()
{
    int x_offset = window->getSize().x/2 - wallTexture.getSize().x*SCALE*1.5;
    int y_offset = window->getSize().y/2 - wallTexture.getSize().y*SCALE*0.5;

    spriteArray = std::vector<std::vector<sf::Sprite*> >(width*2+1);

    for(int colonne = 0; colonne < width*2+1; colonne++)
    {
        spriteArray[colonne] = std::vector<sf::Sprite*>(height*2+1);
        for(int ligne = 0; ligne < height*2+1; ligne++)
        {
            spriteArray[colonne][ligne] = new sf::Sprite();
            spriteArray[colonne][ligne]->setScale(SCALE,SCALE);
            spriteArray[colonne][ligne]->setPosition(x_offset+(wallTexture.getSize().x*SCALE*colonne),y_offset+(wallTexture.getSize().y*SCALE*ligne));
            if(colonne % 2 == 0 || ligne % 2 == 0)
                spriteArray[colonne][ligne]->setTexture(wallTexture);
            else
                spriteArray[colonne][ligne]->setTexture(pathTexture);
        }
    }
}

void Maze::maze_generator(int index, int backtrack_x[], int backtrack_y[], int x, int y, int visited)
{
    if(visited < width * height)
    {
        int neighbour_valid = -1;
        int neighbour_x[4];
        int neighbour_y[4];
        int step[4];

        int x_next;
        int y_next;

        if(x - 2 > 0 && is_closed(x - 2, y))  // upside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x - 2;;
            neighbour_y[neighbour_valid]=y;
            step[neighbour_valid]=1;
        }

        if(y - 2 > 0 && is_closed(x, y - 2))  // leftside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x;
            neighbour_y[neighbour_valid]=y - 2;
            step[neighbour_valid]=2;
        }

        if(y + 2 < height * 2 + 1 && is_closed(x, y + 2))  // rightside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x;
            neighbour_y[neighbour_valid]=y + 2;
            step[neighbour_valid]=3;

        }

        if(x + 2 < width * 2 + 1 && is_closed(x + 2, y))  // downside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x+2;
            neighbour_y[neighbour_valid]=y;
            step[neighbour_valid]=4;
        }

        if(neighbour_valid == -1)
        {
            // backtrack
            x_next = backtrack_x[index];
            y_next = backtrack_y[index];
            index--;
        }

        if(neighbour_valid!=-1)
        {
            int randomization = neighbour_valid + 1;
            int random = rand()%randomization;
            x_next = neighbour_x[random];
            y_next = neighbour_y[random];
            index++;
            backtrack_x[index] = x_next;
            backtrack_y[index] = y_next;

            int rstep = step[random];

            if(rstep == 1)
                spriteArray[x_next+1][y_next]->setTexture(pathTexture);
            else if(rstep == 2)
                spriteArray[x_next][y_next + 1]->setTexture(pathTexture);
            else if(rstep == 3)
                spriteArray[x_next][y_next - 1]->setTexture(pathTexture);
            else if(rstep == 4)
                spriteArray[x_next - 1][y_next]->setTexture(pathTexture);
            visited++;
        }

        maze_generator(index, backtrack_x, backtrack_y, x_next, y_next, visited);
    }
    //generer entree et sortie -- temporairement hardcode
    spriteArray[1][0]->setTexture(pathTexture);
    spriteArray[width*2-1][height*2]->setTexture(pathTexture);
}

int Maze::is_closed(int x, int y)
{
    if(spriteArray[x - 1][y]->getTexture() != &pathTexture
       && spriteArray[x][y - 1]->getTexture() != &pathTexture
       && spriteArray[x][y + 1]->getTexture() != &pathTexture
       && spriteArray[x + 1][y]->getTexture() != &pathTexture
    )
        return 1;

    return 0;
}

void Maze::update(sf::Time deltaTime)
{
    if(isMoving)
    {
        if(abs((spriteArray[currentPos.x][currentPos.y]->getPosition().x + wallTexture.getSize().x*SCALE*0.5) - window->getSize().x/2) > SPEED*SCALE ||
           abs((spriteArray[currentPos.x][currentPos.y]->getPosition().y + wallTexture.getSize().y*SCALE*0.5) - window->getSize().y/2) > SPEED*SCALE)
        {
            for(int colonne = 0; colonne < width*2+1; colonne++)
            {
                for(int ligne = 0; ligne < height*2+1; ligne++)
                {
                    spriteArray[colonne][ligne]->setPosition(spriteArray[colonne][ligne]->getPosition().x - SPEED*SCALE*dir.x,
                                                             spriteArray[colonne][ligne]->getPosition().y - SPEED*SCALE*dir.y);
                }
            }
        }
        else if (int((spriteArray[currentPos.x][currentPos.y]->getPosition().x + wallTexture.getSize().x*SCALE*0.5) - window->getSize().x/2) == 0 &&
                 int((spriteArray[currentPos.x][currentPos.y]->getPosition().y + wallTexture.getSize().y*SCALE*0.5) - window->getSize().y/2) == 0)
        {
            qDebug() << "stopped moving";
            isMoving = false;
        }
        else
        {
            int x_offset = (spriteArray[currentPos.x][currentPos.y]->getPosition().x + wallTexture.getSize().x*SCALE*0.5) - window->getSize().x/2;
            int y_offset = (spriteArray[currentPos.x][currentPos.y]->getPosition().y + wallTexture.getSize().y*SCALE*0.5) - window->getSize().y/2;
            for(int colonne = 0; colonne < width*2+1; colonne++)
            {
                for(int ligne = 0; ligne < height*2+1; ligne++)
                {
                    spriteArray[colonne][ligne]->setPosition(spriteArray[colonne][ligne]->getPosition().x - x_offset,
                                                             spriteArray[colonne][ligne]->getPosition().y - y_offset);
                }
            }
        }
    }
}
