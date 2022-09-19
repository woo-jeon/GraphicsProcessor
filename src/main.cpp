#include <iostream>
#include <fstream>
#include <vector>
#include "TGA.h"

using namespace std;

int main() {
    //Part 1
    TGA part1;
    part1.LoadFile("pattern1.tga");
    TGA layer1;
    layer1.LoadFile("layer1.tga");
    part1.Multiply(layer1);
    part1.WriteFile("part1.tga");

    //Part 2
    TGA part2;
    part2.LoadFile("car.tga");
    TGA layer2;
    layer2.LoadFile("layer2.tga");
    part2.Subtract(layer2);
    part2.WriteFile("part2.tga");

    //Part 3
    TGA part3;
    part3.LoadFile("text.tga");
    TGA layer1Pattern2;
    layer1Pattern2.LoadFile("pattern2.tga");
    layer1Pattern2.Multiply(layer1);
    part3.Screen(layer1Pattern2);
    part3.WriteFile("part3.tga");

    //Part 4
    TGA layer2Circle;
    layer2Circle.LoadFile("circles.tga");
    layer2Circle.Multiply(layer2);
    TGA part4;
    part4.LoadFile("pattern2.tga");

    layer2Circle.Subtract(part4);
    layer2Circle.WriteFile("part4.tga");

    //Part 5
    TGA part5;
    part5.LoadFile("layer1.tga");
    TGA part5pattern1;
    part5pattern1.LoadFile("pattern1.tga");
    part5.Overlay(part5pattern1);
    part5.WriteFile("part5.tga");

    //Part 6
    TGA part6;
    part6.LoadFile("car.tga");
    part6.AddGreen();
    part6.WriteFile("part6.tga");

    //Part 7
    TGA part7;
    part7.LoadFile("car.tga");
    part7.RedUpBlueDown();
    part7.WriteFile("part7.tga");

    //Part 8
    TGA part8R;
    part8R.LoadFile("car.tga");
    TGA part8G;
    part8G.LoadFile("car.tga");
    TGA part8B;
    part8B.LoadFile("car.tga");

    part8B.ColorSeparationB();
    part8G.ColorSeparationG();
    part8R.ColorSeparationR();

    part8B.WriteFile("part8_b.tga");
    part8G.WriteFile("part8_g.tga");
    part8R.WriteFile("part8_r.tga");

    //Part 9
    TGA combined;
    combined.LoadFile("layer_blue.tga");
    combined.Combine("layer_red.tga", "layer_green.tga");
    combined.WriteFile("part9.tga");

    //Part 10
    TGA part10;
    part10.LoadFile("text2.tga");
    part10.Rotate();
    part10.WriteFile("part10.tga");

    //Extra Credit
    TGA extraCredit;
    extraCredit.LoadFile("text.tga");
    extraCredit.ExtraCredit();
    extraCredit.WriteFile("extracredit.tga");

    return 0;
}