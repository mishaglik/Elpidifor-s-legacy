#pragma once

#include <cmath>
#include <stack>
#include <chrono>
#include <cstdio>

#include "tools.hpp"

const char DotTexture[]   = "./Icons/min/Dot.png";

struct CordsPair {
    int32_t x;
    int32_t y;
};

int64_t GetTimeMiliseconds();

class AbstractTool : public booba::Tool {
    protected:
        const char* toolImage_;
        uint32_t toolIdx_;

    public:
        AbstractTool() :
        toolImage_(nullptr),
        toolIdx_(0)
        {}

        virtual ~AbstractTool() {

        }

        AbstractTool(const AbstractTool& tool) = default;
        AbstractTool& operator=(const AbstractTool& tool) = default;

        uint32_t GetIdx() {
            return toolIdx_;
        }

        virtual const char* getTexture() override {
            return toolImage_;
        }
};

class DotTool : public AbstractTool {
    public:
        DotTool() :
        AbstractTool()
        {
            toolImage_ = DotTexture;
        }

        virtual ~DotTool() {}

        virtual void apply(booba::Image* image, const booba::Event* event) override;
        virtual void buildSetupWidget() override {}
};
