#include <iostream>
#include <Windows.h>

struct Vector2
{
    int x;
    int y;

};

int FindElement(char* arr, char target) 
{
    int i;
    i = 0;
    while (arr[i] > -1)
    {
        if (arr[i] == target)
            return i;
        i++;
    }
    return -1;
}

void GenerateMap(char* map, char* trg) 
{

    int i;
    i = 0;
    
    while (map[i] > -1)
    {
        if (map[i] == '0')
            trg[i] = ' ';
        else if (map[i] == '1')
            trg[i] = '~';
        else if (map[i] == 'B')
            trg[i] = 'O';
        else if (map[i] == 'P')
            trg[i] = '_';
        else
            trg[i] = map[i];
        i++;
    }

}

int DrawMap(char* map) 
{
    system("cls");
    int i;
    i = 1;
    while (map[i] > -1)
    {
        std::cout << map[i]<< "  ";
        if (!((i) % map[0]))
            std::cout << "\n";
        i++;
    }

    return i;
}

void Input(Vector2& dir) 
{
    if (GetKeyState('D') & 0x8000)
        dir.x = 1;
    else if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        dir.x = -1;

}

int PlayerMovement(char* map, Vector2& v, int playerSize = 1) 
{
    int pPos = FindElement(map, 'P');
    if ((map[pPos + v.x + (v.y * map[0])] == '0' || map[pPos + v.x + (v.y * map[0])] == 'P') && ( map[pPos + v.x + (v.y * map[0]) + playerSize - 1] == '0'|| map[pPos + v.x + (v.y * map[0]) + playerSize - 1] == 'P'))
    {
        for (int i = 0; i < playerSize; i++)
        {
            map[pPos + i] = '0';
            map[pPos + v.x + (v.y * map[0]) + i] = 'P';
        }
    }
    v.x = 0;
    v.y = 0;
    return pPos + v.x + (v.y * map[0]);
}

int BallMovement(char* map, Vector2& v,Vector2 pV)
{
    int bPos = FindElement(map, 'B');
    int nextPosX = bPos + v.x;
    int nextPosY = bPos + (v.y * map[0]);

    if (((map[nextPosX] == '0' || v.x == 0) && (map[nextPosY] == '0' || v.y == 0) && (map[nextPosX + nextPosY - bPos] == '0' || map[nextPosX + nextPosY - bPos] == 'B')))
    {
        map[bPos] = '0';
        map[nextPosX + nextPosY - bPos] = 'B';
    }
    else 
    {
        if (map[nextPosX] != '0' )
            v.x *= -1;

        if (map[nextPosY] != '0')
            v.y *= -1;

        if (!(map[nextPosY] != '0' || map[nextPosX] != '0') && map[nextPosX + nextPosY - bPos] != '0') 
        {
            v.x *= -1;
            v.y *= -1;
            if (map[nextPosX + nextPosY - bPos] == '=')
                map[nextPosX + nextPosY - bPos] = '0';
            else if (map[nextPosX + nextPosY - bPos] == 'P')
                v.x += pV.x;
        }
            
        if (map[nextPosX] == '=')
            map[nextPosX] = '0';
        else if (map[nextPosX] == 'P')
            v.x += pV.x;

        if (map[nextPosY] == '=')
            map[nextPosY] = '0';
        else if (map[nextPosY] == 'P')
            v.x += pV.x;

        BallMovement(map, v, pV);
    }

    return bPos;
}

bool GameMode(int bPos, int xsMap, int sMap ) 
{
    if (bPos < 0)
        return false;
    return (int)(sMap / xsMap)-1 != (int)(bPos / xsMap);
}

int main()
{
    long time = 0;
    Vector2 ballV;
    ballV.x = 0;
    ballV.y = -1;
    Vector2 dir;
    dir.x = 0;
    dir.y = 0;
    bool gm;
    gm = true;
    char gameMap[] = {14, '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
                          '1', '=', '=', '=', '=', '=', '=', '=', '=', '=', '0', '=', '=', '1',
                          '1', '0', '=', '=', '0', '0', '=', '=', '=', '0', '=', '=', '=', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', 'B', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
                          '1', '0', '0', '0', '0', '0', 'P', 'P','0', '0', '0', '0', '0',  '1' };

    char GUImap[512];
    
    DrawMap(gameMap);
    while (gm)
    {
        
            
        
        
        if(time  % 200000 == 0)
        {
            GenerateMap(gameMap, GUImap);
            Input(dir);
            gm = GameMode(BallMovement(gameMap, ballV, dir), gameMap[0], DrawMap(GUImap) );
            PlayerMovement(gameMap, dir,2);
            std::cout << dir.x;
        }
        

        time++;
    }
    system("exit");
}