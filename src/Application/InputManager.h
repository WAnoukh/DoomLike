#pragma once
#include <list>
#include <map>

class InputManager
{
public:
    void KeyboardKeyCallBackEvent(int key, int scancode, int action, int mods);

    bool IsKeyPressed(int key) const;
private:
    std::list<int> pressedKeys;
};
