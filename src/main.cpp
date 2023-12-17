#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Application/Application.h"

#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    Application& app = Application::GetInstance();
    app.Init();
    return app.Run();
}
