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

	string sLine, sLine2, sLine3, sLine4, sLine5, sLine6;

	//1.get bin size


	int index1, index2, index3, index4, index5, index6, index7;
	
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
	boxes_w = new int[total_boxes];
	boxes_h = new int[total_boxes];
	boxes_d = new int[total_boxes];

	color_r = new int[total_boxes];
	color_g = new int[total_boxes];
	color_b = new int[total_boxes];

	boxes_name.clear();
	if (boxes_name.size() != 0)
	{
		cout << "\n !!!ReadWriteFile::OpenTxtFileBoxes  boxes_name.size() != 0" << endl;
	}

	for (int i = 0; i < total_boxes; i++)
	{
		

		//cout << "sLine=" << sLine << "*" << endl;
		//157 95 60 (179,115,69)//01brown_chocoship
		getline(infile, sLine);
		index1 = sLine.find(" ");
		boxes_w[i] = stod(sLine.substr(0, index1));

		sLine2 = sLine.substr(index1 + 1);
		index2 = sLine2.find(" ");
		boxes_h[i] = stod(sLine2.substr(0, index2));

		sLine3 = sLine2.substr(index2 + 1);
		index3 = sLine3.find(" ");
		boxes_d[i] = stod(sLine3.substr(0, index3));


		index4 = sLine3.find('(');
		index5 = sLine3.find(')');
		if (index4 != -1 )//has color value
		{		
			boxes_name.push_back(sLine3.substr(index5+3));


			sLine4 = sLine3.substr(index4 + 1, index5 - index4 -1);
			//cout << "sLine4=" << sLine4 << endl;
			index6 = sLine4.find(',');
			index7 = sLine4.find_last_of(',');
			//cout << "index6=" << index6 << endl;
			//cout << "index7=" << index7 << endl;
			color_r[i] = stod(sLine4.substr(0, index6));
			color_g[i] = stod(sLine4.substr(index6 + 1, index7 - index6 - 1));
			color_b[i] = stod(sLine4.substr(index7 + 1));

			//cout << index5 << ":" << sLine3.substr(index5 + 3) << endl;
			
		}
		else
		{
			boxes_name.push_back("-");
			color_r[i] = (rand() % 128 + 128);
			color_g[i] = (rand() % 128 + 128);
			color_b[i] = (rand() % 128 + 128);
		}



	}



}
void ReadWriteFile::SaveTxtFileBoxes(string filename, int total,
	int bin_width, int bin_height, int bin_depth,
	int *width, int *height, int *depth,
	vector<string> name,
	int *r, int *g, int *b)
{
	cout << "SaveTxtFileBoxes" << endl;
	
	ofstream outfile;
	outfile.open(filename);

	outfile
		<< bin_width << " " << bin_height << " " << bin_depth << endl
		<< total << endl;

	for (int i = 0; i < total; i++)
	{
		outfile << width[i] << " " << height[i] << " " << depth[i] << " ";// endl;
		outfile << "(" << r[i] << "," << g[i] << "," << b[i] << ")";
		outfile << "//" << name.at(i) << endl;
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
