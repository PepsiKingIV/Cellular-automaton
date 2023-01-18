#include <iostream>
// #include <thread>
// #include <chrono>
#include <ctime>
class Cell
{
private:
    bool behavior;

public:
    Cell()
    {
        behavior = false;
    }

    void set_behavior(const bool &a)
    {
        this->behavior = a;
    }

    bool get_behavior()
    {
        return behavior;
    }

    ~Cell(){};
};

class Menu
{
public:
    void set_position_menu(const int &i)
    {
        std::cout << "enter pjsotion of " << i << " :";
    }
};

class Game
{
private:
    int numberOfCells = 5;
    Cell *gameField = new Cell[80 * 24];
    Cell *bufGameField = new Cell[80 * 24];
    Menu game;

    enum argument
    {
        enother,
        leftWall,
        rightWall
    };

    argument arg;

    void
    set_behavior_in_game(const int &j)
    {
        arg = argument::enother;
        int sum = 0;
        if (j % 80 == 79)
            arg = argument::rightWall;
        if (j % 80 == 0)
            arg = argument::leftWall;
        try
        {
            if (gameField[j + 1].get_behavior() && arg != rightWall)
                sum++;
            if (gameField[j - 1].get_behavior() && arg != leftWall)
                sum++;
            if (gameField[j - 80 - 1].get_behavior() && arg != leftWall)
                sum++;
            if (gameField[j - 80].get_behavior())
                sum++;
            if (gameField[j - 80 + 1].get_behavior() && arg != rightWall)
                sum++;
            if (gameField[j + 80 - 1].get_behavior() && arg != leftWall)
                sum++;
            if (gameField[j + 80].get_behavior())
                sum++;
            if (gameField[j + 80 + 1].get_behavior() && arg != rightWall)
                sum++;
        }
        catch (const std::exception &e)
        {
        }
        if (gameField[j].get_behavior() && sum > 1)
            bufGameField[j].set_behavior(true);
        if (sum >= 3)
            bufGameField[j].set_behavior(true);
        // if (sum > 4)
        //     bufGameField[j].set_behavior(false);
    }

public:
    void enter_cells()
    {
        // srand(time(NULL));
        // int j = rand() % 100;
        // for (int i = j ; i < numberOfCells + j; i++)
        // {
        //     gameField[i].set_behavior(true);
        // }
        gameField[1].set_behavior(true);
        gameField[1 + 80].set_behavior(true);
        gameField[80*2 + 1].set_behavior(true);
    }

    bool get_beh_cell(const int &i)
    {
        return gameField[i].get_behavior();
    }

    void event()
    {
        for (size_t j = 0; j < 80 * 24; j++)
        {
            set_behavior_in_game(j);
        }
        for (size_t i = 0; i < 80 * 24; i++)
        {
            gameField[i] = bufGameField[i];
            bufGameField[i].set_behavior(false);
        }
    }
};

class Graphic
{
private:
    float aspect = (float)80 / 24;
    float aspectPixel = 11.0f / 24.0f;
    char *screen = new char[80 * 24 + 1];
    Game test;

    void end_screen()
    {
        screen[24 * 80] = '\0';
    }

public:
    void set_pixel(const int &i)
    {
        screen[i] = ' ';
        if (test.get_beh_cell(i))
        {
            screen[i] = '#';
        }
    }

    void print_screen()
    {
        test.enter_cells();
        for (size_t i = 0; i < 200; i++)
        {
            int a;
            std::cin >> a;
            for (size_t j = 0; j < 80 * 24; j++)
            {
                set_pixel(j);
            }
            std::cout << screen;
            test.event();
        }
    }
};

int main()
{
    Graphic a;
    a.print_screen();
}