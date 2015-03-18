#include "maze.h"

Maze::Maze(sf::RenderWindow &_window)
    : window(&_window)
{

}

Maze::~Maze()
{

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
    int backtrack_x[CELL];
    int backtrack_y[CELL];
    init_array();
    backtrack_x[index] = 1;
    backtrack_y[index] = 1;
    maze_generator(index, backtrack_x, backtrack_y, 1, 1, 1);
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

}
