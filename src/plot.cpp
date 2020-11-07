#include <plot.hpp>

/**
 * @brief Go to a special position
 * 
 * @param x 
 * @param y 
 */
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

/**
 * @brief char* length
 * 
 * @param aChar 
 * @return int 
 */
int c_size(char* aChar)
{
    int count = 0;
    while(aChar[count]!='\0') count++;
    return count;
}

/**
 * @brief Intuitive way to set colors
 * 
 * @param color 
 * @return int 
 */
int colorInt(char color)
{
    if(color=='b') return 9;
    else if(color == 'g') return 10;
    else if(color == 'c') return 11;
    else if(color == 'r') return 12;
    else if(color == 'v') return 13;
    else if(color == 'y') return 14;
    else return 15; 
}

plot::plot(Axis x, Axis y, std::vector<Point> data, char* title, char color)
{
    if (system("CLS")) system("clear");
    std::cout << "\033[2J";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(0, 0);
    //Title Part
    SetConsoleTextAttribute(hConsole, 15);
    int k = c_size(title);
    int marge = floor(2+(x.range[1]-x.range[0])*(1/x.step)) - k;
    if(marge >= 0)
    {
        for(int i = 0; i<marge/2; i++) std::cout << " ";
        std::cout << title;
        for(int i = 0; i<marge/2; i++) std::cout << " ";
    }
    std::cout << std::endl;
    //Graph Part
    if(data.empty())
    {
        SetConsoleTextAttribute(hConsole, colorInt(y.color));
        std::cout << "^" << std::endl;
        for(int row = 0; row < floor((y.range[1]-y.range[0])*(1/y.step)); row++)
        {
            std::cout << "|";
            if(row == floor(floor((y.range[1]-y.range[0])*(1/y.step))/2))
            {
                int av = floor((floor((x.range[1]-x.range[0])*(1/x.step))-7)/2);
                SetConsoleTextAttribute(hConsole, 15);
                for(int adv = 0; adv < av; adv++) std::cout << " ";
                std::cout << "NO DATA";
                SetConsoleTextAttribute(hConsole, y.color);
            }
            std::cout << std::endl;
        }
        std::cout << "+";
        SetConsoleTextAttribute(hConsole, colorInt(x.color));
        for(int col = 0; col < floor((x.range[1]-x.range[0])*(1/x.step)); col++)
            std::cout << "-";
        std::cout << ">" << std::endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        SetConsoleTextAttribute(hConsole, colorInt(y.color));
        std::cout << "^" << std::endl;
        for(int row = 0; row < floor((y.range[1]-y.range[0])*(1/y.step)); row++)
        {
            for(int col = 0; col < floor((x.range[1]-x.range[0])*(1/x.step)); col++)
            {
                bool isVal = false;
                Point crtPos = {x.range[0]+(col*x.step), y.range[1]-(row*y.step)};
                for(int i = 0; i<data.size(); i++)
                {
                    if((std::abs(data[i].x-crtPos.x)<std::abs(x.step/2)) 
                        && (std::abs(data[i].y-crtPos.y)<std::abs(y.step/2)))
                        {
                           SetConsoleTextAttribute(hConsole, colorInt(color));
                           std::cout << "+";
                           SetConsoleTextAttribute(hConsole, colorInt('w'));
                           isVal = true;
                           break;  
                        }   
                }
                if(!isVal)
                {
                    
                    if ((std::abs(crtPos.x) < std::abs(x.step/2))
                        && (std::abs(crtPos.y) < std::abs(y.step/2)))
                        {
                            SetConsoleTextAttribute(hConsole, colorInt('w'));
                            std::cout << "+";
                            SetConsoleTextAttribute(hConsole, colorInt('w'));
                        }
                    else if(std::abs(crtPos.x) < std::abs(x.step/2))
                    {
                            SetConsoleTextAttribute(hConsole, colorInt(y.color));
                            std::cout << "|";
                            SetConsoleTextAttribute(hConsole, colorInt('w'));
                    }
                    else if(std::abs(crtPos.y) < std::abs(y.step/2))
                    {
                            SetConsoleTextAttribute(hConsole, colorInt(x.color));
                            std::cout << "-";
                            SetConsoleTextAttribute(hConsole, colorInt('w'));
                    } 
                    else
                    {
                            SetConsoleTextAttribute(hConsole, colorInt('w'));
                            std::cout << " ";
                    } 
                } 
            }
            std::cout << std::endl;
        }
    }
}

plot::~plot()
{

}


