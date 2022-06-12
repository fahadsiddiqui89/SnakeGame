#include <iostream>
#include <conio.h>   //console input/output header file; has inbuilt functions like _getch() and _kbhit()
#include <windows.h> // for the sleep function
#include <fstream>   // to save high score of file

using namespace std;

bool endgame = false;
char input;
int mode;
int width, height;
int slow;
int h, v; // h = horizontal; v = vertical
int score;
int fruith, fruitv;
int hearth, heartv;
int lessh, lessv;
int greatest1 = 0;
int greatest2 = 0;
int greatest3 = 0;
string direction;
int size;
int *lengthh = new int[0];
int *lengthv = new int[0];
int length;
double life;
char key_pressed;

void box();
void move();

int main()
{
    system("color 2");

    fstream score_file1("High Score 1.txt");
    score_file1 >> greatest1;
    fstream score_file2("High Score 2.txt");
    score_file2 >> greatest2;
    fstream score_file3("High Score 3.txt");
    score_file3 >> greatest3;

    cout << "\t\t\t\tSnake Game\n";
    cout << "Controls: ";
    cout << "W to move up; ";
    cout << "S to move down; ";
    cout << "A to move left; ";
    cout << "D to move right\n";

    do
    {
        endgame = false;
        direction = "none";
        size = 0;
        slow = 20;
        length = 0;
        score = 0;
        life = 1;
        width = 40;
        height = 15;
        h = width / 2;
        v = height / 2;
        fruith = rand() % width;
        fruitv = rand() % height;
        hearth = rand() % width;
        heartv = rand() % height;
        lessh = rand() % width;
        lessv = rand() % height;

        cout << "Press 's' to start\n";
        cout << "Press 'e' to exit\n";
        cin >> input;

        if (input == 'e')
        {
            break;
        }
        if (input != 's') // if user enters a char other than s or e
        {
            cout << "Inavlid input\n";
            cin.clear();
            cin.ignore(1);
            continue;
        }

        cout << "Which mode would you like to play?\n";
        cout << "Mode 1: Snake dies when you hit wall\n";
        cout << "Mode 2: Snake passes through the wall\n";
        cout << "Mode 3: Special items mode (like mode 1) ";
        cout << "Special items are: '$' and '&'\n";
        cout << "'$' will give extra life to snake (through wall); '&' will decrease size of tail\n";
        cout << "Game Mode 1 or 2 or 3: ";
        cin >> mode;

        if (mode == 2)
        {
            slow = 10;
        }
        if (mode == 3)
        {
            life = 0.2;
            slow = 15;
        }
        if (mode != 1 && mode != 2 && mode != 3) // if user enters wrong number
        {
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore(1);
            continue;
        }
        if (cin.fail())
        {
            break;
        }

        while (endgame == false)
        {
            box();
            move();
            Sleep(slow); // speeds up game as the game progresses
            if (endgame == true)
            {
                cout << "Game End\n";
            }
        }

        if (mode == 1)
        {
            if (score > greatest1)
            {
                cout << "New High Score!\n";
                greatest1 = score;
            }
            ofstream score_file1;
            score_file1.open("High Score 1.txt");
            score_file1 << greatest1;
            score_file1.close();
        }
        else if (mode == 2)
        {
            if (score > greatest2)
            {
                cout << "New High Score!\n";
                greatest2 = score;
            }
            ofstream score_file2;
            score_file2.open("High Score 2.txt");
            score_file2 << greatest2;
            score_file2.close();
        }
        else if (mode == 3)
        {
            if (score > greatest3)
            {
                cout << "New High Score!\n";
                greatest3 = score;
            }
            ofstream score_file3;
            score_file3.open("High Score 3.txt");
            score_file3 << greatest3;
            score_file3.close();
        }
        system("pause");
    } while (input != 'e');

    return 0;
}

void box()
{
    system("cls"); // so game can be dynamic

    for (int i = 0; i <= width + 1; i++) // prints top wall
    {
        cout << "_";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (j == 0) // prints left walls
            {
                cout << "|";
            }
            if (j == width) // prints right wall
            {
                cout << "|";
            }
            if (i == v && j == h) // prints snake head in middle
            {
                cout << "#";
            }
            else if (i == fruitv && j == fruith) // prints a fruit at a random location
            {
                cout << "o";
            }
            else
            {
                int condition = 0;
                if (mode == 3)
                {
                    if (i == heartv && j == hearth) // prints a heart at a random location
                    {
                        cout << "$";
                        condition = 1;
                    }
                    else if (i == lessv && j == lessh) // prints a lesser at a random location
                    {
                        cout << "&";
                        condition = 1;
                    }
                }
                for (int k = 0; k < length; k++)
                {
                    if (lengthh[k] == j && lengthv[k] == i) // prints tail
                    {
                        cout << "*";
                        condition = 1;
                    }
                }
                if (condition == 0)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i <= width + 1; i++) // prints bottom wall
    {
        cout << "^";
    }
    cout << endl;
    cout << "Score:" << score << endl;
    cout << "Lives:" << life << endl;
}

void move()
{
    if (kbhit()) // Checks if a key has been hit does not ask for input everytime
    {
        key_pressed = getch(); // so char pressed is not displayed on screen and no need to press enter
        if (key_pressed == 'd' && direction != "Left")
        {
            direction = "Right";
        }
        else if (key_pressed == 'a' && direction != "Right")
        {
            direction = "Left";
        }
        else if (key_pressed == 'w' && direction != "Down")
        {
            direction = "Up";
        }
        else if (key_pressed == 's' && direction != "Up")
        {
            direction = "Down";
        }
        else if (key_pressed == 'e')
        {
            endgame = true;
        }
    }

    int lh2 = 0;
    int lv2 = 0;
    int lh1 = *lengthh;
    int lv1 = *lengthv;
    *lengthh = h;
    *lengthv = v;

    for (int i = 1; i < length; i++) // loop so tail will follow the head
    {
        lh2 = lengthh[i];
        lv2 = lengthv[i];
        lengthh[i] = lh1;
        lengthv[i] = lv1;
        lh1 = lh2;
        lv1 = lv2;
    }
    if (direction == "Left")
    {
        h--;
    }
    else if (direction == "Right")
    {
        h++;
    }
    else if (direction == "Up")
    {
        v--;
    }
    else if (direction == "Down")
    {
        v++;
    }

    if (mode == 1 || mode == 3) // game ends when snake head hits box
    {
        if (mode == 1)
        {
            life = 1;
        }
        if (h == width || h < 0 || v == height || v < 0)
        {
            if (life <= 1)
            {
                endgame = true;
            }
            else
            {
                life--;
            }
        }
    }

    if (mode == 2 || mode == 3) // snake reappears when hits boxs
    {
        if (h >= width)
        {
            h = 0;
        }
        else if (h < 0)
        {
            h = width - 1;
        }
        if (v >= height)
        {
            v = 0;
        }
        else if (v < 0)
        {
            v = height - 1;
        }
    }

    if (mode == 1)
    {
        cout << "Your highest score for game mode " << mode << " is " << greatest1 << endl;
    }
    else if (mode == 2)
    {
        cout << "Your highest score for game mode " << mode << " is " << greatest2 << endl;
    }
    else if (mode == 3)
    {
        cout << "Your highest score for game mode " << mode << " is " << greatest3 << endl;
    }

    for (int i = 0; i < length; i++) // game ends when snake head hits tail
    {
        if (lengthh[i] == h && lengthv[i] == v)
        {
            if (life <= 1)
            {
                endgame = true;
            }
            else
            {
                life--;
            }
        }
    }

    if (h == hearth && v == heartv)
    {
        life += 0.2;
        hearth = rand() % width;
        heartv = rand() % height;
    }
    if (h == lessh && v == lessv)
    {
        length--;
        lessh = rand() % width;
        lessv = rand() % height;
    }

    if (h == fruith && v == fruitv) // progression of game when snake eats fruit
    {
        size++;
        int *arr1 = lengthh;
        int *arr2 = lengthv;
        lengthh = new int[size];
        lengthv = new int[size];
        for (int i = 0; i < size - 1; i++)
        {
            lengthh[i] = arr1[i];
            lengthv[i] = arr2[i];
        }
        delete[] arr1;
        delete[] arr2;
        arr1 = NULL;
        arr2 = NULL;
        score++;
        length++;
        fruith = rand() % width;
        fruitv = rand() % height;
        if (slow > 0)
        {
            slow--;
        }
    }
}