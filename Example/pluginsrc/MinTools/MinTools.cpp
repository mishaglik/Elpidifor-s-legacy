#include "MinTools.hpp"

void DotTool::apply(booba::Image* image, const booba::Event* event) {
    if (!image) {
        return;
    }

    const size_t sqSize = 3;

    if (event->type == booba::EventType::MousePressed) {
        uint32_t pixelsAmount = 0;
        
        for (size_t curX = std::max(size_t(0), event->Oleg.mbedata.x - sqSize);     curX < std::min(image->getW(), event->Oleg.mbedata.x + sqSize); curX++) {
            for (size_t curY = std::max(size_t(0), event->Oleg.mbedata.y - sqSize); curY < std::min(image->getH(), event->Oleg.mbedata.y + sqSize); curY++) {
                image->setPixel(curX, curY, booba::APPCONTEXT->fgColor);
                pixelsAmount++;
            }
        }
    }   
}

void booba::init_module() {
    DotTool* dotTool = new DotTool();

    booba::addTool(dotTool);
}
