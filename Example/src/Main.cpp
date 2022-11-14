#include "Main.hpp"

// Definition of extern var from tools.hpp
booba::ApplicationContext* booba::APPCONTEXT = nullptr;

int main() {
    RealWindow mainWindow(1600, 900);

    // Initialization of appcontext
    booba::APPCONTEXT = new booba::ApplicationContext(); 

    // Red is a standart color of min example
    booba::APPCONTEXT->fgColor = 0xFF000000;

    ToolPalette* toolPalette = new ToolPalette(10, 20);
    mainWindow += toolPalette;
    mainWindow += new Canvas(80, 20, 1500, 800, toolPalette);

    while (mainWindow.IsOpen()) {
        mainWindow.Clear();

        mainWindow.PollEvent();

        mainWindow.Display();
    }

    delete booba::APPCONTEXT;
}

