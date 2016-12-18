#ifndef MYCOLOR_H
#define MYCOLOR_H
#define MAX_COLOR 20

class MyColor
{
public:
    MyColor();
	void SetRandomColor(int index);
	float *GetColorIndex(int index);

private:
	float color_table[MAX_COLOR][6];


};

#endif // MYCOLOR_H