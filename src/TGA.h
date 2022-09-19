#pragma once
#include <string>
#include <vector>

using namespace std;

class TGA {
    //Header information
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    //Pixel information
    vector<unsigned char> pixels;

public:
    void LoadFile(string fileName);
    void WriteFile(string fileName);

    void Multiply(const TGA &object);
    void Subtract(const TGA &object);
    void Screen(const TGA &object);
    void Overlay(const TGA &object);
    void AddGreen();
    void RedUpBlueDown();
    void ColorSeparationB();
    void ColorSeparationG();
    void ColorSeparationR();
    void Combine(string redFile, string greenFile);
    void Rotate();
    void ExtraCredit();

};





