#include<iostream>
class CalculateBppErhan
{
public:
	CalculateBppErhan();
	~CalculateBppErhan();

	void CalculateBinpack(
		int total_box_to_pack,
		int bin_w, int bin_h, int bin_d,
		int *box_w, int *box_h, int *box_d,
		int *box_x, int *box_y, int *box_z,
		int *orien_x, int *orien_y, int *orien_z,
		int *bin_no, int *item_no);

	void SortBoxesOrder();
	bool CheckAllCanFit();

	void quickSort(int *arr, int left, int right);
	void swap_xyzwhd(int i, int j);
	void swap_pare(int *a, int *b);
	void printboxes_array();

private:
	int total_boxes;
	int b_w, b_h, b_d;
	int *w, *h, *d;
	int *x, *y, *z;
	int *bno;

};

