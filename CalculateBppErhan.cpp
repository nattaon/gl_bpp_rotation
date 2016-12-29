#include "CalculateBppErhan.h"

int binpacking(int total_box_to_pack,
	int bin_w, int bin_h, int bin_d,
	int *box_w, int *box_h, int *box_d,
	int *_box_x, int *_box_y, int *_box_z,
	int *_orien_x, int *_orien_y, int *_orien_z,
	int *_bin_no, int *_item_no);

CalculateBppErhan::CalculateBppErhan()
{
}


CalculateBppErhan::~CalculateBppErhan()
{
}

void CalculateBppErhan::CalculateBinpack(
	int total_box_to_pack,
	int bin_w, int bin_h, int bin_d,
	int *box_w, int *box_h, int *box_d,
	int *box_x, int *box_y, int *box_z,
	int *orien_x, int *orien_y, int *orien_z,
	int *bin_no, int *item_no)
{


	binpacking(total_box_to_pack,
		bin_w, bin_h, bin_d,
		box_w, box_h, box_d,
		box_x, box_y, box_z,
		orien_x, orien_y, orien_z,
		bin_no, item_no);

	x = box_x;
	y = box_y;
	z = box_z;
	bno = bin_no;

	//SortBoxesOrder();
}

void CalculateBppErhan::SortBoxesOrder()
{
	//first, sort by z position
	quickSort(z, 0, total_boxes - 1);

	//find each same z range
	int z_start_index = 0;
	int x_start_index = 0;
	for (int i = z_start_index; i<total_boxes; i++)
	{
		if (z[i] != z[i + 1])
		{
			quickSort(x, z_start_index, i);
			//printboxes_array();
			x_start_index = z_start_index;
			for (int j = x_start_index; j<i + 1; j++)
			{
				if (x[j] != x[j + 1])
				{
					quickSort(y, x_start_index, j);
					//printboxes_array();

					x_start_index = j + 1;
				}
			}
			z_start_index = i + 1;
		}
	}
}

void CalculateBppErhan::quickSort(int *arr, int left, int right) //int *arr = int arr[]
{

	int i = left, j = right;
	int pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;

		if (i <= j) {

			swap_xyzwhd(i, j);
			//tmp = arr[i];
			//arr[i] = arr[j];
			//arr[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);

}

void CalculateBppErhan::swap_xyzwhd(int i, int j)
{
	swap_pare(&x[i], &x[j]);
	swap_pare(&y[i], &y[j]);
	swap_pare(&z[i], &z[j]);
	swap_pare(&w[i], &w[j]);
	swap_pare(&h[i], &h[j]);
	swap_pare(&d[i], &d[j]);

}
void CalculateBppErhan::swap_pare(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}



void CalculateBppErhan::printboxes_array()
{
	std::cout << "print box array" << std::endl;
	for (int i = 0; i < total_boxes; i++) {
		std::cout
			<< i << ":"
			<< w[i] << " " << h[i] << " " << d[i] << " "
			<< "bin_num:" << bno[i] << " "
			<< "pos:"
			<< x[i] << " " << y[i] << " " << z[i] << " "
			<< std::endl;
	}

}

bool CalculateBppErhan::CheckAllCanFit()
{
	int boxes_volumn = 0;
	int bin_volumn = b_w*b_h*b_d;
	for (int i = 0; i < total_boxes; i++)
	{
		boxes_volumn += (w[i] * h[i] * d[i]);
	}

	std::cout << "boxes:" << boxes_volumn << std::endl;
	std::cout << "bin:" << bin_volumn << std::endl;

	if (boxes_volumn > bin_volumn) return false;
	else return true;
}

