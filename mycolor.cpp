#include "mycolor.h"
#include <iostream>

MyColor::MyColor()
{
	is_color_set = false;

}
void MyColor::SetColor(int total, int *color_r, int *color_g, int *color_b)
{

	for (int i = 0; i < total; i++)
	{
		color_table[i][3] = color_r[i];
		color_table[i][4] = color_g[i];
		color_table[i][5] = color_b[i];

		color_table[i][0] = color_r[i] / 255.0;
		color_table[i][1] = color_g[i] / 255.0;
		color_table[i][2] = color_b[i] / 255.0;
	}
	is_color_set = true;

}
void MyColor::SetRandomColor()
{
	for (int i = 0; i < MAX_COLOR; i++)
	{
		RandomColor(i);
	}
	is_color_set = true;
}

void MyColor::RandomColor(int index)
{
	// make new class for this
	//prevent alway random by random at first time new class
	float r = (rand() % 200 + 56);// / 255.0;
	float g = (rand() % 200 + 56);// / 255.0;
	float b = (rand() % 200 + 56);// / 255.0;

	//std::cout << "rgb " << r << "," << g << "," << b << std::endl;


	color_table[index][3] = r;
	color_table[index][4] = g;
	color_table[index][5] = b;

	color_table[index][0] = r / 255.0;
	color_table[index][1] = g / 255.0;
	color_table[index][2] = b / 255.0;
	//glColor3d(r, g, b);
}


float* MyColor::GetColorIndex(int index)
{
	return color_table[index];
}


