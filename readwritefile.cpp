#include "readwritefile.h"
#include <fstream>
#include <iostream>

ReadWriteFile::ReadWriteFile()
{

}
void ReadWriteFile::OpenTxtFileBoxes(string filename)
{
	ifstream infile;
	infile.open(filename);

	if (!infile.is_open())
	{
		cout << "cannot open file" << endl;
		return;
	}

	string sLine,sLine2,sLine3;

	//1.get bin size


	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	int index4 = 0;
	
	getline(infile, sLine);
	index1 = sLine.find(" ");
	bin_w = stod(sLine.substr(0, index1));

	sLine2 = sLine.substr(index1+1);
	index2 = sLine2.find(" ");
	bin_h = stod(sLine2.substr(0, index2));

	sLine3 = sLine2.substr(index2 + 1);
	index3 = sLine3.find(" ");
	bin_d = stod(sLine3.substr(0, index3));

	//2.get boxes total
	getline(infile, sLine);
	total_boxes=stod(sLine);


	//3.get array of boxes
	int *boxes_width = new int[total_boxes];
	int *boxes_height = new int[total_boxes];
	int *boxes_depth = new int[total_boxes];



	int c_width, c_height, c_depth;

	for (int i = 0; i < total_boxes; i++)
	{
		

		//cout << "sLine=" << sLine << "*" << endl;

		getline(infile, sLine);
		index1 = sLine.find(" ");
		c_width = stod(sLine.substr(0, index1));

		sLine2 = sLine.substr(index1 + 1);
		index2 = sLine2.find(" ");
		c_height = stod(sLine2.substr(0, index2));

		sLine3 = sLine2.substr(index2 + 1);
		index3 = sLine3.find(" ");
		c_depth = stod(sLine3.substr(0, index3));

		index4 = sLine3.find("//");
		if (index4!=-1)
		{ 
			//cout << index4 << ":" << sLine3.substr(index4 + 2) << endl;
		}
		//cout << i << ":" << c_width << "," << c_height << "," << c_depth << endl;

		boxes_width[i] = c_width;
		boxes_height[i] = c_height;
		boxes_depth[i] = c_depth;

	}
	boxes_w = boxes_width; //save value in this class parameter
	boxes_h = boxes_height;
	boxes_d = boxes_depth;


}
void ReadWriteFile::SaveTxtFileBoxes(string filename, int total,
	int bin_width, int bin_height, int bin_depth,
	int *width, int *height, int *depth)
{
	cout << "SaveTxtFileBoxes" << endl;
	
	ofstream outfile;
	outfile.open(filename);

	outfile
		<< bin_width << " " << bin_height << " " << bin_depth << endl
		<< total << endl;

	for (int i = 0; i < total; i++)
	{
		outfile << width[i] << " " << height[i] << " " << depth[i] << endl;
	}


	outfile.close();
}

int ReadWriteFile::GetTotalBox()
{
	return total_boxes;
}
int ReadWriteFile::GetBinWidth()
{
	return bin_w;
}
int ReadWriteFile::GetBinHeight()
{
	return bin_h;
}
int ReadWriteFile::GetBinDepth()
{
	return bin_d;
}

int *ReadWriteFile::GetBoxesWidth()
{
	return boxes_w;
}
int *ReadWriteFile::GetBoxesHeight()
{
	return boxes_h;
}
int *ReadWriteFile::GetBoxesDepth()
{
	return boxes_d;
}
