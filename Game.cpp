/*
* -1 - None, 0 - Red, 1 - Green 
*/
#include <SFML/Graphics.hpp>
#include<Windows.h>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

enum Direction { PLUS = 1, MINUS = -1 };

const int HEIGHT = 15;
bool Right = true, Left = true, Up = true, Down = true;
const int WIDTH = 20;
float CUBE_SIZE = 32.f;
int Count = 0, finalValue = 5, step = 1, score_1 = 0;
Direction direction;
string score = to_string(int(score_1));
string status;

int field[WIDTH][HEIGHT];
int PreviousFigure[2];
int Snake_Axis[HEIGHT * WIDTH][2];
int Size_Snake_Axis = 0;
int Cake_Axis[1][2];
char Direction_axis = ' ';

void spawn_snake();
void spawn_cake();
bool Crash();

int main()
{ 
    ifstream file("Best Score.txt");
    if (!file.is_open())
    {
        cout << "Файл не открылся";
        return 0;
    }
    string best_record;
    file >> best_record;
    file.close();

    srand(time(NULL));
    spawn_snake();
    spawn_cake();
    sf::RenderWindow window(sf::VideoMode(HEIGHT * int(CUBE_SIZE) + 280, WIDTH * int(CUBE_SIZE)), "Snake");
    sf::Texture texture;
    sf::Font font_1;
    sf::Text text_1;
    sf::Text text_2;
    sf::Text text_3;

    sf::Color color(40, 40, 40);

    if (!texture.loadFromFile("1550642135_3.jpg"))
        return EXIT_FAILURE;

    if (!font_1.loadFromFile("Serifiqo 4F Free Capitals.otf"))
        return EXIT_FAILURE;

    text_1.setFont(font_1);
    text_2.setFont(font_1);
    text_3.setFont(font_1);
    text_1.setString("Game Over!");
    text_2.setString("Score: " + score);
    text_3.setString("Best record: " + best_record);
    text_1.setFillColor(sf::Color::Red);
    text_2.setFillColor(sf::Color::White);
    text_3.setFillColor(sf::Color::White);
    text_1.setCharacterSize(52);
    text_1.setStyle(sf::Text::Bold);
    text_2.setCharacterSize(32);
    text_2.setStyle(sf::Text::Bold);
    text_3.setCharacterSize(32);
    text_3.setStyle(sf::Text::Bold);
    text_2.setPosition(500.f, 50.f);
    text_3.setPosition(500.f, 100.f);
    text_1.setPosition(500.f, 200.f);

    texture.setSmooth(true);
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        score = to_string(int(score_1));
        PreviousFigure[0] = Snake_Axis[Size_Snake_Axis - 1][0];
        PreviousFigure[1] = Snake_Axis[Size_Snake_Axis - 1][1];
        text_2.setString("Score: " + score);
        text_1.setString(status);
        Count += step;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Right)
            {
                    direction = PLUS;
                    status = "";
                    Left = false;
                    Up = true;
                    Down = true;
                    Direction_axis = 'x';
                    cout << 2;
             }
             else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Left)
              {
                    direction = MINUS;
                    status = "";
                    Right = false;
                    Up = true;
                    Down = true;
                    Direction_axis = 'x';
                    cout << 1;
              }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Up)
                {
                    direction = MINUS;
                    status = "";
                    Down = false;
                    Right = true;
                    Left = true;
                    Direction_axis = 'y';
                    cout << 3;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Down)
                {
                    direction = PLUS;
                    status = "";
                    Up = false;
                    Right = true;
                    Left = true;
                    Direction_axis = 'y';
                    cout << 4;
                }  
        }

        if (Count == finalValue)
        {
            if (Direction_axis == 'x')
            {
                int headSnake[2]{};
                headSnake[0] = Snake_Axis[0][0];
                headSnake[1] = Snake_Axis[0][1];
                Snake_Axis[0][1] += direction;
                for (int index = 1; index < Size_Snake_Axis; index++)
                {
                    int PreviousRect[2]{};
                    PreviousRect[0] = Snake_Axis[index][0];
                    PreviousRect[1] = Snake_Axis[index][1];
                    Snake_Axis[index][0] = headSnake[0];
                    Snake_Axis[index][1] = headSnake[1];
                    headSnake[0] = PreviousRect[0];
                    headSnake[1] = PreviousRect[1];
                    
                }
            }
            else if (Direction_axis == 'y')
            {
                int headSnake[2]{};
                headSnake[0] = Snake_Axis[0][0];
                headSnake[1] = Snake_Axis[0][1];
                Snake_Axis[0][0] += direction;
                for (int index = 1; index < Size_Snake_Axis; index++)
                {
                    int PreviousRect[2]{};
                    PreviousRect[0] = Snake_Axis[index][0];
                    PreviousRect[1] = Snake_Axis[index][1];
                    Snake_Axis[index][0] = headSnake[0];
                    Snake_Axis[index][1] = headSnake[1];
                    headSnake[0] = PreviousRect[0];
                    headSnake[1] = PreviousRect[1];
                }
            }
            Count = 0;
        }
        // Logic
        //__________________
        if (Cake_Axis[0][0] == Snake_Axis[0][0] && Cake_Axis[0][1] == Snake_Axis[0][1])
        {
            Size_Snake_Axis++;
            Snake_Axis[Size_Snake_Axis - 1][0] = PreviousFigure[0];
            Snake_Axis[Size_Snake_Axis - 1][1] = PreviousFigure[1];
            //add_snake();
            spawn_cake();
            score_1 += 5;
        }

        if (Crash())
        {
            status = "Game Over!";
            Sleep(1000);
            if (score_1 > stoi(best_record))
            {
                ofstream file("Best Score.txt");
                if (!file.is_open())
                    cout << "Файл не открыт!";
                file << score_1;
                file.close();
            }
            Right = true, Left = true, Up = true, Down = true;
            score_1 = 0;
            Size_Snake_Axis = 0;
            Direction_axis = ' ';
            spawn_snake();
            spawn_cake();
        }

        window.clear(sf::Color::Black);

        window.draw(text_1);
        window.draw(sprite);
        window.draw(text_2);
        window.draw(text_3);
        for(int i = 0; i < WIDTH; i++)
            for (int j = 0; j < HEIGHT; j++)
            {
                sf::RectangleShape shape(sf::Vector2f(CUBE_SIZE, CUBE_SIZE));
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineThickness(1.f);
                shape.setOutlineColor(color);
                shape.setPosition(float(j) * CUBE_SIZE, float(i) * CUBE_SIZE);
                window.draw(shape);
            }
        //window.draw(sprite);
        // Drawing Gaming_Field
        // _________________________________________________________________________________________________________
        for (int index = 0; index < Size_Snake_Axis; index++)
        {
            sf::RectangleShape shape(sf::Vector2f(CUBE_SIZE - 3.f, CUBE_SIZE - 3.f));
            shape.setFillColor(sf::Color::Green);
            shape.setOutlineThickness(3.f);
            shape.setOutlineColor(sf::Color::Red);
            shape.setPosition( float(Snake_Axis[index][1])  * CUBE_SIZE, float(Snake_Axis[index][0])* CUBE_SIZE);
            window.draw(shape);
        }

        sf::RectangleShape shape(sf::Vector2f(CUBE_SIZE, CUBE_SIZE));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(float(Cake_Axis[0][1])* CUBE_SIZE, float(Cake_Axis[0][0])* CUBE_SIZE);
        window.draw(shape);
        // _____________________________________________________________________________________________________________________
        window.display();
        window.setFramerateLimit(60);
    }
    system("pause");
    return 0;
}

void spawn_snake()
{
    int x, y;
    y = rand() % 20;
    x = rand() % 15;
    Snake_Axis[Size_Snake_Axis][0] = y;
    Snake_Axis[Size_Snake_Axis][1] = x;
    Size_Snake_Axis++;
}

void spawn_cake()
{
    int x, y;
    x = rand() % 15;
    y = rand() % 20;
    bool AllRight = false;
    while (!AllRight)
    {
        bool NotBad = true;
        for (int i = 0; i < Size_Snake_Axis; i++)
        {
            if (x == Snake_Axis[i][1] && y == Snake_Axis[i][0])
            {
                NotBad = false;
                x = rand() % 15;
                y = rand() % 20;
                
            }
            if (NotBad)
            {
                AllRight = true;
                
            }
        }
    }
    Cake_Axis[0][0] = y;
    Cake_Axis[0][1] = x;
}

bool Crash()
{
    bool Crash = false;
    int HeadSnake[2];
    HeadSnake[0] = Snake_Axis[0][0];
    HeadSnake[1] = Snake_Axis[0][1];

    for (int index = 1; index < Size_Snake_Axis; index++)
    {
        if (HeadSnake[0] == Snake_Axis[index][0] && HeadSnake[1] == Snake_Axis[index][1])
        {
            Crash = true;
            break;
        }
    }

    if ((HeadSnake[0] > 19 || HeadSnake[0] < 0) || (HeadSnake[1] > 14 || HeadSnake[1] < 0))
        Crash = true;

    return Crash;
}