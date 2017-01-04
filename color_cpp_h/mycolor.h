#ifndef MYCOLOR_H
#define MYCOLOR_H
#define MAX_COLOR 60

class MyColor
{
public:
    MyColor();
	void SetRandomColor();
	void SetColor(int total, int *color_r, int *color_g, int *color_b);
	void RandomColor(int index);
	float *GetColorIndex(int index);

	bool is_color_set;

	float color_table[MAX_COLOR][6];


};

#endif // MYCOLOR_H