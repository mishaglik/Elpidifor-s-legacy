#include <gtest/gtest.h>
#include <random>
#include <ctime>

#include "../tools.hpp"

using namespace booba;

std::mt19937 rnd(time(NULL));


inline static void checkPicture(const Picture &pic, uint32_t *image_data, size_t image_w)
{
    for (size_t x = 0; x < pic.getW(); ++x)
        for (size_t y = 0; y < pic.getH(); ++y)
            EXPECT_EQ(pic(x, y), image_data[(y + pic.getY()) * image_w + x + pic.getX()]);
};

TEST(Basic, ctor)
{
    size_t image_w = 20;
    size_t image_h = 10;

    uint32_t *image_data = new uint32_t[image_w * image_h];
    for (size_t i = 0; i < image_w * image_h; ++i)
        image_data[i] = i;

    size_t x = 0;
    size_t y = 0;
    Picture pic(x, y, image_w, image_h, image_data, image_w, image_w);

    for (size_t i = 0; i < image_w * image_h; ++i)
        EXPECT_EQ(pic.getData()[i], image_data[i]);


    pic = Picture(2, 4, 10, 4, image_data, image_w, image_h);

    checkPicture(pic, image_data, image_w);

    pic = Picture(2, 4, 18, 6, image_data, image_w, image_h);

    checkPicture(pic, image_data, image_w);

    delete[] image_data;
}

TEST(Basic, assign)
{
    size_t image_w = 20;
    size_t image_h = 10;

    uint32_t *image_data = new uint32_t[image_w * image_h];
    for (size_t i = 0; i < image_w * image_h; ++i)
        image_data[i] = i;

    size_t x = 0;
    size_t y = 0;
    Picture pic_1(x, y, image_w, image_h, image_data, image_w, image_w);

    for (size_t i = 0; i < image_w * image_h; ++i)
        EXPECT_EQ(pic_1.getData()[i], image_data[i]);

    size_t pic_x = 2;
    size_t pic_y = 4;
    size_t pic_w = 10;
    size_t pic_h = 4;

    Picture pic_2(pic_x, pic_y, pic_w, pic_h, image_data, image_w, image_h);

    checkPicture(pic_2, image_data, image_w);

    pic_1 = std::move(pic_2);
    EXPECT_EQ(pic_2.getData(), nullptr);

    EXPECT_NE(pic_1.getData(), nullptr);
    EXPECT_EQ(pic_1.getX(), pic_x);
    EXPECT_EQ(pic_1.getY(), pic_y);
    EXPECT_EQ(pic_1.getW(), pic_w);
    EXPECT_EQ(pic_1.getH(), pic_h);

    checkPicture(pic_1, image_data, image_w);

    delete[] image_data;
}

TEST(Stress, get)
{
    for (size_t round = 0; round < 50; ++round) {
        size_t image_w = rand() % 1000 + 1;
        size_t image_h = rand() % 1000 + 1;

        uint32_t *image_data = new uint32_t[image_w * image_h];
        for (size_t i = 0; i < image_w * image_h; ++i)
            image_data[i] = rand();

        for (size_t pic_round = 0; pic_round < 100; ++pic_round) {
            size_t pic_x = rand() % image_w;
            size_t pic_y = rand() % image_h;
            size_t pic_w = rand() % (image_w - pic_x);
            size_t pic_h = rand() % (image_h - pic_y);
            Picture pic(pic_x, pic_y, pic_w, pic_h, image_data, image_w, image_h);

            checkPicture(pic, image_data, image_w);
        }

        delete[] image_data;
    }
}
