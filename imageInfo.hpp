#pragma once

class ImageInfo {
public:
    int width;
    int height;

    ImageInfo(const int n): width(n), height(n) {}
    ImageInfo(const int width, const int height): width(width), height(height) {}
};