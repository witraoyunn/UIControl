#include "UIControldefine.h"

CKeyState::CKeyState()
{
    for (int i = 0; i<28; i++)
    {
        state[i] = IniState;
    }
}

CKeyState::~CKeyState()
{

}

bool CKeyState::AllStateNor()
{
    for (int i = 0; i<28; i++)
    {
        if (state[i] == ErrorState)
        {
            return false;
        }
    }
    return true;
}

CKeyState CKeyState::operator =(const CKeyState &keyState)
{
    CKeyState keyRet;

    for (int i = 0; i<28; i++)
    {
        keyRet.state[i] = keyState.state[i];
    }
    return keyRet;
}
