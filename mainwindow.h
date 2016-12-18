#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTreeWidgetItem>

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


	int total_boxes;
	int bin_w, bin_h, bin_d;
	int *boxes_w, *boxes_h, *boxes_d;
	int *boxes_x_pos, *boxes_y_pos, *boxes_z_pos;
	int *boxes_x_orient, *boxes_y_orient, *boxes_z_orient;
	int *boxes_bin_num;
	int *boxes_item_num;

	CalculateBppErhan *binpack;
	ReadWriteFile *txtfile;

    int GetTotalBox();
    int GetBinWidth();
    int GetBinHeight();
    int GetBinDepth();

    int GetNodeLimit();
    int GetIterLimit();
    int GetTimeLimit();

	void GetBoxesSize();
	void InitialBoxedPacking();

    void AddNewIntItemToList(int item1, int item2, int item3);
    void AddNewStringItemToList(QString item1, QString item2, QString item3);
};

#endif // MAINWINDOW_H
