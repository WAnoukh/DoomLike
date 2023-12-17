#include "InputManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void InputManager::KeyboardKeyCallBackEvent(int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        pressedKeys.push_front(key);
    }
    else if(action == GLFW_RELEASE)
    {
        pressedKeys.remove(key);
    }
}

bool InputManager::IsKeyPressed(int key) const
{
    for(auto& pressedKey : pressedKeys)
    {
        if(pressedKey == key)
        {
            return true;
        }
    }
    return false;
}
