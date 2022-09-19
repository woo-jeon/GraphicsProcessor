#include "TGA.h"
#include <fstream>
#include <iostream>
#include <algorithm>

void TGA::LoadFile(string fileName) {
    ifstream inFile("input/"+fileName, ios_base::binary);
    if (inFile.is_open()) {
        //Reads header information
        inFile.read(&idLength, sizeof(idLength));
        inFile.read(&colorMapType, sizeof(colorMapType));
        inFile.read(&dataTypeCode, sizeof(dataTypeCode));
        inFile.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));
        inFile.read((char*)&colorMapLength, sizeof(colorMapLength));
        inFile.read(&colorMapDepth, sizeof(colorMapDepth));
        inFile.read((char*)&xOrigin, sizeof(xOrigin));
        inFile.read((char*)&yOrigin, sizeof(yOrigin));
        inFile.read((char*)&width, sizeof(width));
        inFile.read((char*)&height, sizeof(height));
        inFile.read(&bitsPerPixel, sizeof(bitsPerPixel));
        inFile.read(&imageDescriptor, sizeof(imageDescriptor));
        //Reads pixel information
        char temp;
        for (int i = 0; i < width*height*3; i++) {
            inFile.read((char*)&temp, sizeof(char));
            pixels.push_back(temp);
        }
    }
}

void TGA::WriteFile(string fileName) {
    ofstream outFile("output/"+fileName, ios_base::binary);
    //Writes header information
    outFile.write(&idLength, sizeof(idLength));
    outFile.write(&colorMapType, sizeof(colorMapType));
    outFile.write(&dataTypeCode, sizeof(dataTypeCode));
    outFile.write((char*)&colorMapOrigin, sizeof(colorMapOrigin));
    outFile.write((char*)&colorMapLength, sizeof(colorMapLength));
    outFile.write(&colorMapDepth, sizeof(colorMapDepth));
    outFile.write((char*)&xOrigin, sizeof(xOrigin));
    outFile.write((char*)&yOrigin, sizeof(yOrigin));
    outFile.write((char*)&width, sizeof(width));
    outFile.write((char*)&height, sizeof(height));
    outFile.write(&bitsPerPixel, sizeof(bitsPerPixel));
    outFile.write(&imageDescriptor, sizeof(imageDescriptor));


    //Writes pixel information
    for (int i = 0; i < width*height*3; i++) {
        outFile.write((char*)&pixels.at(i),1);
    }
}

void TGA::Multiply(const TGA &object) {
    for (int i = 0; i < width*height*3; i++) {
        pixels.at(i) = (((float)pixels.at(i)/255)*((float)object.pixels.at(i)/255))*255+0.5f;
    }
}

void TGA::Subtract(const TGA &object) {
    for (int i = 0; i < width*height*3; i++) {
        int number;
        number = (int)pixels.at(i)-(int)object.pixels.at(i);
        if ( number < 0) {
            pixels.at(i) = 0;
        } else {
            pixels.at(i) = number;
        }
    }
}

void TGA::Screen(const TGA &object) {
    for (int i = 0; i < width*height*3; i++) {
        pixels.at(i) = (1-(1-(float)pixels.at(i)/255)*(1-(float)object.pixels.at(i)/255))*255+0.5f;
    }
}

void TGA::Overlay(const TGA &object) {
    for (int i = 0; i < width*height*3; i++) {
        if ((float)object.pixels.at(i)/255 <= 0.5) {
            pixels.at(i) = (2*((float)pixels.at(i)/255 * (float)object.pixels.at(i)/255))*255+0.5f;
        } else {
            pixels.at(i) = (1-2*((1-(float)pixels.at(i)/255) * (1-(float)object.pixels.at(i)/255)))*255+0.5f;
        }
    }

}

void TGA::AddGreen() {
    for (int i = 1; i < width*height*3; i=i+3) {
        if ((int)pixels.at(i) + 200 < 255) {
            pixels.at(i) = (int)pixels.at(i)+200;
        } else {
            pixels.at(i) = 255;
        }
    }

}

void TGA::RedUpBlueDown() {
    for (int i = 0; i < width*height*3; i++) {
        //Blue
        pixels.at(i) = 0;
        i++;
        //Green stays same
        i++;
        //Red
        if (pixels.at(i) * 4 <= 255) {
            pixels.at(i) = ((float) pixels.at(i) / 255) * 4 * 255 + 0.5f;
        } else {
            pixels.at(i) = 255;
        }
    }
}

void TGA::ColorSeparationB() {
    for (int i = 0; i < width*height*3; i++) {
        i++;
        pixels.at(i) = pixels.at(i-1);
        i++;
        pixels.at(i) = pixels.at(i-1);
    }
}

void TGA::ColorSeparationG() {
    for (int i = 0; i < width*height*3; i++) {
        pixels.at(i) = pixels.at(i+1);
        i=i+2;
        pixels.at(i) = pixels.at(i-1);
    }
}

void TGA::ColorSeparationR() {
    for (int i = 0; i < width*height*3; i++) {
        pixels.at(i) = pixels.at(i+2);
        i++;
        pixels.at(i) = pixels.at(i+1);
        i++;
    }
}

void TGA::Combine(string redFile, string greenFile) {

    TGA red;
    red.LoadFile(redFile);
    TGA green;
    green.LoadFile(greenFile);

    for (int i = 0; i < width*height*3; i++) {
        i++;
        pixels.at(i) = green.pixels.at(i);
        i++;
        pixels.at(i) = red.pixels.at(i);
    }
}

void TGA::Rotate() {
    reverse(pixels.begin(), pixels.end());
    unsigned char temp;
    for(int i = 0; i < pixels.size(); i=i+3) {
        temp = pixels.at(i);
        pixels.at(i) = pixels.at(i+2);
        pixels.at(i+2) = temp;
    }
}

void TGA::ExtraCredit() {
    width *=2;
    height *=2;
    pixels.clear();

    TGA text;
    text.LoadFile("text.tga");

    TGA car;
    car.LoadFile("car.tga");

    TGA circle;
    circle.LoadFile("circles.tga");

    TGA pattern1;
    pattern1.LoadFile("pattern1.tga");

    int pixelPositionLeft = 0;
    int pixelPositionRight = 0;
    for (int j = 0; j < height/2; j++) {
        for (int i = 0; i < width*3 / 2; i++) {
            pixels.push_back(text.pixels.at(pixelPositionLeft));
            pixelPositionLeft++;
        }
        for (int i = 0; i < width*3 / 2; i++) {
            pixels.push_back(pattern1.pixels.at(pixelPositionRight));
            pixelPositionRight++;
        }
    }
    pixelPositionLeft=0;
    pixelPositionRight=0;
    for (int j = 0; j < height/2; j++) {
        for (int i = 0; i < width*3 / 2; i++) {
            pixels.push_back(car.pixels.at(pixelPositionLeft));
            pixelPositionLeft++;
        }
        for (int i = 0; i < width*3 / 2; i++) {
            pixels.push_back(circle.pixels.at(pixelPositionRight));
            pixelPositionRight++;
        }
    }
}
