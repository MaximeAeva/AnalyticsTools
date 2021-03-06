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
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
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
 * @param color {b(lue), g(reen), c(yan), r(ed), p(urple), y(ellow), w(hite)}
 * @return int cmd color
 */
int colorInt(char color)
{
    if(color=='b') return 9;
    else if(color == 'g') return 10;
    else if(color == 'c') return 11;
    else if(color == 'r') return 12;
    else if(color == 'p') return 13;
    else if(color == 'y') return 14;
    else return 15; 
}

/**
 * @brief Auto size step to display full screen in range
 * 
 * @param ax 
 * @param x Is x axis ?
 * @param n Divide screen in n part (default 1)
 * @return float 
 */
float autoSize(Axis ax, bool x, int n = 1)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    int COLS = (csbiInfo.dwSize.X)/n;
    int LINES = (csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top-1)/n;
    if(x)
        return (ax.range[1]-ax.range[0])/COLS;
    else
        return (ax.range[1]-ax.range[0])/(LINES-2);
}

std::vector<float> autoRange(std::vector<data> dataCluster, char *mode) 
{
    float m, M;
    if(mode == "x")
    {
        m = dataCluster[0].values[0].x;
        M = dataCluster[0].values[0].x;
    }
    else
    {
        m = dataCluster[0].values[0].y;
        M = dataCluster[0].values[0].y;
    }
    for(int dl = 0; dl<dataCluster.size(); dl++)
    {
        for(int i = 0; i<dataCluster[dl].values.size(); i++)
        {
            if(mode == "x")
            {
                if(m > dataCluster[dl].values[i].x)
                    m = dataCluster[dl].values[i].x;
                if(M < dataCluster[dl].values[i].x)
                    M = dataCluster[dl].values[i].x;
            }
            else
            {
                if(m > dataCluster[dl].values[i].y)
                    m = dataCluster[dl].values[i].y;
                if(M < dataCluster[dl].values[i].y)
                    M = dataCluster[dl].values[i].y;
            }
        }
    }
    float k = 0.1*(M-m);
    std::vector<float> v;
    v.push_back(m-k);
    v.push_back(M+k);
    return v;
}

/**
 * @brief Plot functions on cmd
 * 
 * @param x Abscissa axis
 * @param y ordonnee axis
 * @param dataCluster A vector of data
 * @param title The graph title
 * @param legend Enable legend display
 * @param xStart Start pos (default 0)
 * @param yStart Start pos (default 0)
 */
void plot(Axis x, Axis y, std::vector<data> dataCluster, 
            char* title, bool legend, int xStart, int yStart)
{
    if(!(x.range[1]-x.range[0]))
    {
        std::vector<float> rng = autoRange(dataCluster, "x");
        x.range[0] = rng.front();
        x.range[1] = rng.back();
    }
    if(!(y.range[1]-y.range[0]))
    {
        std::vector<float> rng = autoRange(dataCluster, "y");
        y.range[0] = rng.front();
        y.range[1] = rng.back();
    }
    if(x.step == 'auto')
        x.step = autoSize(x, true);
    if(y.step == 'auto')
        y.step = autoSize(y, false);
    //if (system("CLS") && (xStart+yStart) == 0) system("clear");
    //std::cout << "\033[2J";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(0, yStart);
    //Title Part
    SetConsoleTextAttribute(hConsole, 15);
    int k = c_size(title);
    
    int marge = floor(2+(x.range[1]-x.range[0])*(1/x.step)) - k;
    int cnt = 0;
    while(cnt < xStart)
    {
        std::cout << " ";
        cnt++;
    }
    if(marge >= 0)
    {
        for(int i = 0; i<marge/2; i++) std::cout << " ";
        std::cout << title;
        for(int i = 0; i<marge/2; i++) std::cout << " ";
    }
    std::cout << std::endl;
    //Graph Part
    if(dataCluster.empty())
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
        for(int row = 0; row < floor((y.range[1]-y.range[0])*(1/y.step)); row++)
        {
            int cnt = 0;
            while(cnt < xStart)
            {
                std::cout << " ";
                cnt++;
            }
            for(int col = 0; col < floor((x.range[1]-x.range[0])*(1/x.step)); col++)
            {
                bool isVal = false;
                Point crtPos = {x.range[0]+(col*x.step), y.range[1]-(row*y.step)};
                for(int dl = 0; dl<dataCluster.size(); dl++)
                {
                    for(int i = 0; i<dataCluster[dl].values.size(); i++)
                    {
                        if((std::abs(dataCluster[dl].values[i].x-crtPos.x)<std::abs(x.step/2)) 
                            && (std::abs(dataCluster[dl].values[i].y-crtPos.y)<std::abs(y.step/2)))
                            {
                            SetConsoleTextAttribute(hConsole, colorInt(dataCluster[dl].color));
                            if(dataCluster[dl].style == '\0') 
                            {
                                std::ostringstream s;
                                s << "+->(x: " << dataCluster[dl].values[i].x;
                                s << ", y: ";
                                s << dataCluster[dl].values[i].y << ")";
                                std::cout << s.str();
                                col += s.str().length()-1;
                            }
                            else std::cout << dataCluster[dl].style;
                            SetConsoleTextAttribute(hConsole, colorInt('w'));
                            isVal = true;
                            break;  
                            }
                            if(isVal) break;
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
                            if(std::abs(crtPos.y-(y.range[1]))<std::abs(y.step/2)) std::cout << "^";
                            else std::cout << "|";
                            SetConsoleTextAttribute(hConsole, colorInt('w'));
                    }
                    else if(std::abs(crtPos.y) < std::abs(y.step/2))
                    {
                            SetConsoleTextAttribute(hConsole, colorInt(x.color));
                            if(std::abs(crtPos.x-(x.range[1]))<std::abs(x.step/2)) std::cout << ">";
                            else std::cout << "-";
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
        if(legend)
        {
            int u = 0;
            while(u<xStart)
            {
                std::cout << " ";
                u++;
            }
            for(int dl = 0; dl<dataCluster.size(); dl++)
            {
                SetConsoleTextAttribute(hConsole, colorInt(dataCluster[dl].color));
                std::cout << dataCluster[dl].legend;
                SetConsoleTextAttribute(hConsole, colorInt('w'));
                std::cout << " / ";
            }
        }
    }
}

/**
 * @brief 
 * 
 * @param x x Axis
 * @param y y Axis
 * @param dataCluster Data to plot 
 * @param title Plot title
 * @param legend Enable legend
 * @param pos Plot position
 * @param nH Plots number along Y axis
 * @param nW Plots number along X axis
 */
void subplot(Axis x, Axis y, std::vector<data> dataCluster, char* title, bool legend, int pos, int nH, int nW)
{
    
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    int COLS = (csbiInfo.dwSize.X-1)/nW;
    int LINES = (csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top-1)/nH;
    if(!(x.range[1]-x.range[0]))
    {
        std::vector<float> rng = autoRange(dataCluster, "x");
        x.range[0] = rng.front();
        x.range[1] = rng.back();
    }
    if(!(y.range[1]-y.range[0]))
    {
        std::vector<float> rng = autoRange(dataCluster, "y");
        y.range[0] = rng.front();
        y.range[1] = rng.back();
    }
    if(x.step == 'auto')
        x.step = autoSize(x, true, nW);
    if(y.step == 'auto')
        y.step = autoSize(y, false, nH);

    plot(x, y, dataCluster, title, legend, COLS*(pos%nW), LINES*(pos/nW)+(pos/nW));
}


