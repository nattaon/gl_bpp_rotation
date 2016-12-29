#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QKeyEvent>

#include <vector>

#include "glwidget.h"
#include "CalculateBppErhan.h"
#include "readwritefile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	//void mousePressEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent * event);
//	bool eventFilter(QObject *object, QEvent *event);
	

private slots:
	void PressedTreeItem(QTreeWidgetItem *item, int col);

    void PressedAddBox();
    void PressedRemoveBox();
    void PressedLoadDb();
    void PressedSaveDb();
    void PressedClearAll();

    void PressedBinPacking();
	void PressedReset();
    void PressedShowOrder();
    void PressedPreviousOrder();
    void PressedNextOrder();
	

private:
    Ui::MainWindow *ui;
	int last_select_item_index;

	float *color_rgb;
/*	int *boxes_w, *boxes_h, *boxes_d;
	int *boxes_r, *boxes_g, *boxes_b;
	vector<string> boxes_name;*/
/*	int *boxes_x_pos, *boxes_y_pos, *boxes_z_pos;
	int *boxes_x_orient, *boxes_y_orient, *boxes_z_orient;
	int *boxes_bin_num;
	int *boxes_item_num;*/

	CalculateBppErhan *binpack;
	ReadWriteFile *txtfile;

    int GetTotalBox();
    int GetBinWidth();
    int GetBinHeight();
    int GetBinDepth();

    int GetNodeLimit();
    int GetIterLimit();
    int GetTimeLimit();
	/*
	void CopyBoxesInfoFromUI(
		int **_boxes_w, int **_boxes_h, int **_boxes_d,
		vector<string> _boxes_name,
		int **_boxes_r, int **_boxes_g, int **_boxes_b);
		
	void GetBoxesInfoFromUI();
*/

	void InitialBoxedPacking();

	void AddNewIntItemToList(int item1, int item2, int item3, string name, int r, int g, int b);
    void AddNewStringItemToList(QString item1, QString item2, QString item3);


	void LoadBPPFileToUI(string filename);
};

#endif // MAINWINDOW_H
