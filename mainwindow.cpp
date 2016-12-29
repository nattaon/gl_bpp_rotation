#include "mainwindow.h"
#include "build/ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
/*
REMAIN ISSUE
-some case ording is not in order
-light when rotate to back
-color item in tree list+sort them by order?
-memory management (free pointer?)
-load and append funtion?
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	last_select_item_index = 0;


	ui->treeWidget->header()->show();
	ui->treeWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

	//some initial 
	//bin

	//box
	/*AddNewIntItemToList(142, 89, 58);
	AddNewIntItemToList(108, 138, 51);
	AddNewIntItemToList(139, 87, 62);
	AddNewIntItemToList(95, 162, 54);
	AddNewIntItemToList(86, 148, 62);
	ui->in_bin_w->setText("305");
	ui->in_bin_h->setText("244");
	ui->in_bin_d->setText("121");
	*/
	/*
	AddNewIntItemToList(200, 100, 50);
	AddNewIntItemToList(200, 100, 50);
	AddNewIntItemToList(200, 100, 50);
	AddNewIntItemToList(200, 50, 100);
	AddNewIntItemToList(100, 200, 50);
	AddNewIntItemToList(100, 50, 200);
	AddNewIntItemToList(50, 100, 200);
	AddNewIntItemToList(50, 200, 100);
	ui->in_bin_w->setText("200");
	ui->in_bin_h->setText("200");
	ui->in_bin_d->setText("200");
	*/
	/////////////////
	connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(PressedTreeItem(QTreeWidgetItem *, int)));


	connect(ui->bt_add_box, SIGNAL(pressed()), this, SLOT(PressedAddBox()));
	connect(ui->bt_remove, SIGNAL(pressed()), this, SLOT(PressedRemoveBox()));
	connect(ui->bt_load, SIGNAL(pressed()), this, SLOT(PressedLoadDb()));
	connect(ui->bt_save, SIGNAL(pressed()), this, SLOT(PressedSaveDb()));
	connect(ui->bt_clearall, SIGNAL(pressed()), this, SLOT(PressedClearAll()));

	connect(ui->bt_binpacking, SIGNAL(pressed()), this, SLOT(PressedBinPacking()));
    connect(ui->bt_reset, SIGNAL(pressed()), this, SLOT(PressedReset()));
	connect(ui->bt_showorder, SIGNAL(pressed()), this, SLOT(PressedShowOrder()));
	connect(ui->bt_previous_order, SIGNAL(pressed()), this, SLOT(PressedPreviousOrder()));
	connect(ui->bt_next_order, SIGNAL(pressed()), this, SLOT(PressedNextOrder()));


    binpack = new CalculateBppErhan();
	txtfile = new ReadWriteFile();
	
	//LoadBPPFileToUI("C:/Users/nattaon2/Desktop/gl_bpp_rotation/box_all.txt");
	LoadBPPFileToUI("C:/Users/Nattaon/Desktop/qt_bpp_rotate/box_22.txt");

	ui->widget->SetInitialBin(GetBinWidth(), GetBinHeight(), GetBinDepth());
	ui->treeWidget->header()->resizeSection(0, 45);//No
	ui->treeWidget->header()->resizeSection(1, 45);//w
	ui->treeWidget->header()->resizeSection(2, 45);//h
	ui->treeWidget->header()->resizeSection(3, 45);//d
	ui->treeWidget->header()->resizeSection(4, 100);//name
	ui->treeWidget->header()->resizeSection(5, 45);//r
	ui->treeWidget->header()->resizeSection(6, 45);//g
	ui->treeWidget->header()->resizeSection(7, 45);//b
	
}
void MainWindow::AddNewIntItemToList(int item1, int item2, int item3, string name, int r, int g, int b)
{
	int total_boxes = ui->treeWidget->topLevelItemCount();

	QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);

    item->setText(0, QString::number(total_boxes+1));
	item->setText(1, QString::number(item1));
	item->setText(2, QString::number(item2));
	item->setText(3, QString::number(item3));
	item->setText(4, QString::fromStdString(name));
	item->setText(5, QString::number(r));
	item->setText(6, QString::number(g));
	item->setText(7, QString::number(b));

	item->setBackgroundColor(0, QColor(r, g, b));

	item->setTextAlignment(0, Qt::AlignHCenter);
	item->setTextAlignment(1, Qt::AlignHCenter);
	item->setTextAlignment(2, Qt::AlignHCenter);
	item->setTextAlignment(3, Qt::AlignHCenter);

	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
	

	ui->treeWidget->addTopLevelItem(item);

}
void MainWindow::AddNewStringItemToList(QString item1, QString item2, QString item3)
{
	int total_boxes = ui->treeWidget->topLevelItemCount();

	QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);

	item->setText(0, QString::number(total_boxes+1));
	item->setText(1, item1);
	item->setText(2, item2);
	item->setText(3, item3);

	item->setTextAlignment(0, Qt::AlignHCenter);
	item->setTextAlignment(1, Qt::AlignHCenter);
	item->setTextAlignment(2, Qt::AlignHCenter);
	item->setTextAlignment(3, Qt::AlignHCenter);

	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);

	ui->treeWidget->addTopLevelItem(item);

}
/*
void MainWindow::CopyBoxesInfoFromUI(
	int **_boxes_w, int **_boxes_h, int **_boxes_d,
	vector<string> _boxes_name,
	int **_boxes_r, int **_boxes_g, int **_boxes_b)
{
	int total_boxes = ui->treeWidget->topLevelItemCount();

	for (int i = 0; i < total_boxes; ++i)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);

		*_boxes_w[i] = item->text(1).toInt();
		*_boxes_h[i] = item->text(2).toInt();
		*_boxes_d[i] = item->text(3).toInt();
		_boxes_name.push_back(item->text(4).toStdString());
		*_boxes_r[i] = item->text(5).toInt();
		*_boxes_g[i] = item->text(6).toInt();
		*_boxes_b[i] = item->text(7).toInt();
	}
}

void MainWindow::GetBoxesInfoFromUI()
{
	int total_boxes = ui->treeWidget->topLevelItemCount();
	//cout << "boxes_name.size()=" << boxes_name.size() << endl;
	if (boxes_name.size() != 0)
	{
	QMessageBox::information(0, QString("boxes_name size !=0"),
	QString("This should be 0 in order to copy new value"),
	QMessageBox::Ok);
	return;
	}
	for (int i = 0; i < total_boxes; ++i)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);

		boxes_w[i] = item->text(1).toInt();
		boxes_h[i] = item->text(2).toInt();
		boxes_d[i] = item->text(3).toInt();
		boxes_name.push_back(item->text(4).toStdString());
		boxes_r[i] = item->text(5).toInt();
		boxes_g[i] = item->text(6).toInt();
		boxes_b[i] = item->text(7).toInt();
	}

}
*/
void MainWindow::InitialBoxedPacking()
{
	int total_boxes = ui->treeWidget->topLevelItemCount();


	/*
	for (int i = 0; i < total_boxes; ++i)  //if set 0 bpp output position willbe at 0
	{
		boxes_x_pos[i] = 0;
		boxes_y_pos[i] = 0;
		boxes_z_pos[i] = 0;
		boxes_x_orient[i] = 0;
		boxes_y_orient[i] = 0;
		boxes_z_orient[i] = 0;
		boxes_bin_num[i] = 0;
		boxes_item_num[i] = 0;
	}*/
}

void MainWindow::PressedTreeItem(QTreeWidgetItem *item, int col)
{

	
	//std::cout << "mousePressEvent " << ui->treeWidget->currentIndex().row() << std::endl;

	QTreeWidgetItem* last_selected_item = ui->treeWidget->topLevelItem(last_select_item_index);
	//last_selected_item->setBackgroundColor(0, QColor(255, 255, 255));
	last_selected_item->setBackgroundColor(1, QColor(255, 255, 255));
	last_selected_item->setBackgroundColor(2, QColor(255, 255, 255));
	last_selected_item->setBackgroundColor(3, QColor(255, 255, 255));


	//item->setBackgroundColor(0, QColor(200, 200, 200));
	item->setBackgroundColor(1, QColor(200, 200, 200));
	item->setBackgroundColor(2, QColor(200, 200, 200));
	item->setBackgroundColor(3, QColor(200, 200, 200));
	last_select_item_index = ui->treeWidget->currentIndex().row();

}

void MainWindow::PressedAddBox()
{
    QString txt_width = ui->in_box_w->text();
	QString txt_height = ui->in_box_h->text();
	QString txt_depth = ui->in_box_d->text();

	AddNewStringItemToList(txt_width, txt_height, txt_depth);
    
	//width.toDouble();
    //item->setText(0,QString("a"));
    //item->setBackgroundColor(0,QColor(185, 20, 120));

}
void MainWindow::PressedRemoveBox()
{
	

    QTreeWidgetItem* selected_item = ui->treeWidget->currentItem();
    delete selected_item;
	int total_boxes = ui->treeWidget->topLevelItemCount();

	if (last_select_item_index == total_boxes)
	{
		last_select_item_index--;
	}


    //rerun index number
	for (int i = 0; i < total_boxes; ++i)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        item->setText(0, QString::number(i + 1));

    }
}
void MainWindow::PressedLoadDb()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "../", tr("Text Files (*.txt)"));

	
	if (!fileName.trimmed().isEmpty()) // no file selected
	{
		std::cout << "Got filename: " << fileName.toStdString() << std::endl;
		LoadBPPFileToUI(fileName.toStdString());
		
	}

	
}


void MainWindow::LoadBPPFileToUI(string filename)
{
	
	ui->label_filename->setText(QString::fromStdString(filename));

	
	txtfile->OpenTxtFileBoxes(filename);

	//PressedClearAll();

	ui->in_bin_w->setText(QString::number(txtfile->bin_w));
	ui->in_bin_h->setText(QString::number(txtfile->bin_h));
	ui->in_bin_d->setText(QString::number(txtfile->bin_d));


	for (int i = 0; i < txtfile->total_boxes; i++)
	{
		AddNewIntItemToList(
			txtfile->boxes_w[i], 
			txtfile->boxes_h[i], 
			txtfile->boxes_d[i],
			txtfile->boxes_name.at(i),
			txtfile->color_r[i],
			txtfile->color_g[i],
			txtfile->color_b[i]);

	}

}

void MainWindow::PressedSaveDb()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Open Image"), "../", tr("Text Files (*.txt)"));

	std::cout << "Set filename: " << fileName.toStdString() << std::endl;

	int total_boxes = ui->treeWidget->topLevelItemCount();
	int *save_boxes_w = new int[total_boxes];
	int *save_boxes_h = new int[total_boxes];
	int *save_boxes_d = new int[total_boxes];
	vector<string> save_boxes_name;
	int *save_boxes_r = new int[total_boxes];
	int *save_boxes_g = new int[total_boxes];
	int *save_boxes_b = new int[total_boxes];
	

	for (int i = 0; i < total_boxes; ++i)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);

		save_boxes_w[i] = item->text(1).toInt();
		save_boxes_h[i] = item->text(2).toInt();
		save_boxes_d[i] = item->text(3).toInt();
		save_boxes_name.push_back(item->text(4).toStdString());
		save_boxes_r[i] = item->text(5).toInt();
		save_boxes_g[i] = item->text(6).toInt();
		save_boxes_b[i] = item->text(7).toInt();
	}


	txtfile->SaveTxtFileBoxes(fileName.toStdString(), GetTotalBox(),
		GetBinWidth(), GetBinHeight(), GetBinDepth(),
		save_boxes_w, save_boxes_h, save_boxes_d,
		save_boxes_name,
		save_boxes_r, save_boxes_g, save_boxes_b);
}
void MainWindow::PressedClearAll()
{
	int total_boxes = ui->treeWidget->topLevelItemCount();

	for (int i = total_boxes-1; i >=0 ; i--)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
		delete item;
	}

}

void MainWindow::PressedBinPacking()
{

	//0.set packing type
	//std::cout << "packtype " << ui->comboBox_packMethod->currentIndex() << std::endl;
	//binpack->SetPackingType(ui->comboBox_packMethod->currentIndex());
	int total_boxes = ui->treeWidget->topLevelItemCount();
	cout << "total_boxes = " << total_boxes << endl;

    //1.set bin size
    int bin_width = GetBinWidth();
    int bin_height = GetBinHeight();
    int bin_depth = GetBinDepth();


	//2.declare box 
	int *boxes_w = new int[total_boxes];
	int *boxes_h = new int[total_boxes];
	int *boxes_d = new int[total_boxes];
	//vector<string> boxes_name;
	int *boxes_r = new int[total_boxes];
	int *boxes_g = new int[total_boxes];
	int *boxes_b = new int[total_boxes];
	int *boxes_x_pos = new int[total_boxes];
	int *boxes_y_pos = new int[total_boxes];
	int *boxes_z_pos = new int[total_boxes];
	int *boxes_x_orient = new int[total_boxes];
	int *boxes_y_orient = new int[total_boxes];
	int *boxes_z_orient = new int[total_boxes];
	int *boxes_bin_num = new int[total_boxes];
	int *boxes_item_num = new int[total_boxes];

	//3.init value, copy boxes size
	for (int i = 0; i < total_boxes; ++i)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
		boxes_bin_num[i] = 0;
		boxes_item_num[i] = item->text(0).toInt();

		boxes_w[i] = item->text(1).toInt();
		boxes_h[i] = item->text(2).toInt();
		boxes_d[i] = item->text(3).toInt();
		//boxes_name.push_back(item->text(4).toStdString());
		boxes_r[i] = item->text(5).toInt();
		boxes_g[i] = item->text(6).toInt();
		boxes_b[i] = item->text(7).toInt();

		boxes_x_pos[i] = 0;
		boxes_y_pos[i] = 0;
		boxes_z_pos[i] = 0;

		boxes_x_orient[i] = 0;
		boxes_y_orient[i] = 0;
		boxes_z_orient[i] = 0;

	}

	





	//4.calc & get result box position
	cout << endl;
	cout << "input sent" << endl;


	for (int i = 0; i < total_boxes; i++)
	{
		cout
		<< "No." << boxes_item_num[i] << ", " 
		<< "bin_num:" << boxes_bin_num[i] << ", " 
		<< "whd:" << boxes_w[i] << "x" << boxes_h[i] << "x" << boxes_d[i] << ", " 
		<< "pos:" << boxes_x_pos[i] << "," << boxes_y_pos[i] << "," << boxes_z_pos[i] << ", " 
		<< "orient:" << boxes_x_orient[i] << "," << boxes_y_orient[i] << "," << boxes_z_orient[i] << ", " 
		<< endl;

	}
	

	binpack->CalculateBinpack(
		total_boxes,
		bin_width, bin_height, bin_depth,
		boxes_w, boxes_h, boxes_d,
		boxes_x_pos, boxes_y_pos, boxes_z_pos,
		boxes_x_orient, boxes_y_orient, boxes_z_orient,
		boxes_bin_num, boxes_item_num);

	cout << endl;
	cout << "output get" << endl;
		// check if use bin >1
		int item_not_fit = 0;
		for (int i = 0; i < total_boxes; i++)
		{
/*			cout
				<< "No." << boxes_item_num[i] << ", " 
				<< "bin_num:" << boxes_bin_num[i] << ", " 
				<< "whd:" << boxes_w[i] << "x" << boxes_h[i] << "x" << boxes_d[i] << ", " 
				<< "pos:" << boxes_x_pos[i] << "," << boxes_y_pos[i] << "," << boxes_z_pos[i] << ", " 
				<< "orient:" << boxes_x_orient[i] << "," << boxes_y_orient[i] << "," << boxes_z_orient[i] << ", "
				<< endl;
*/			
			if (boxes_bin_num[i] != 1)
			{
				item_not_fit++;
			}

		}
		cout << endl;
		cout << "packed " << total_boxes - item_not_fit << "/" << total_boxes << endl;
		/*
		if (item_not_fit != 0)
		{
			//std::cout << " cannot fit another " << item_not_fit << " boxes to bin" << std::endl;
			QString text = "Another " + QString::number(item_not_fit) + " boxes cannot fit in to bin"; // CORRECT
			QMessageBox::information(0, QString("Cannot fit all boxes"), text, QMessageBox::Ok);
		}*/
		//remove remain boxes

		//binpack->SortBoxesOrder();

		ui->widget->SetShowBinpacking(
			total_boxes,
			bin_width, bin_height, bin_depth,
			boxes_x_orient, boxes_y_orient, boxes_z_orient,
			boxes_x_pos, boxes_y_pos, boxes_z_pos,
			boxes_r, boxes_g, boxes_b,
			boxes_bin_num, boxes_item_num);


		for (int i = total_boxes - 1; i >= 0; i--)
		{
			QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
			if (boxes_bin_num[i] == 1)//pack
			{
				item->setBackgroundColor(0, QColor(item->text(5).toInt(), item->text(6).toInt(), item->text(7).toInt()));
			}
			else//not pack
			{
				item->setBackgroundColor(0, QColor(10, 10, 10));
			}

		}




	delete[] boxes_w;  // if delete error occur
	delete[] boxes_h;
	delete[] boxes_d;


	//delete[] boxes_x_pos;  //if delete display will reset to nothing
	//delete[] boxes_y_pos;
	//delete[] boxes_z_pos;
	//delete[] boxes_bin_num;
}
void MainWindow::PressedReset()
{
	ui->widget->SetInitialBin(GetBinWidth(), GetBinHeight(), GetBinDepth());
	ui->widget->ResetWindow();

}
void MainWindow::PressedShowOrder()
{
	//show animation?
	ui->widget->ShowFirstNumber();
}
void MainWindow::PressedPreviousOrder()
{
	ui->widget->DecreaseShowNumber();
}
void MainWindow::PressedNextOrder()
{
	ui->widget->IncreaseShowNumber();
}



int MainWindow::GetTotalBox()
{
	return 	ui->treeWidget->topLevelItemCount();
}
int MainWindow::GetBinWidth()
{
    QString txt_width = ui->in_bin_w->text();
    return txt_width.toInt();
}
int MainWindow::GetBinHeight()
{
    QString txt_height = ui->in_bin_h->text();
    return txt_height.toInt();
}
int MainWindow::GetBinDepth()
{
    QString txt_depth = ui->in_bin_d->text();
    return txt_depth.toInt();
}
int MainWindow::GetNodeLimit()
{
    QString txt = ui->in_node_limit->text();
    return txt.toInt();
}
int MainWindow::GetIterLimit()
{
    QString txt = ui->in_iter_limit->text();
    return txt.toInt();
}
int MainWindow::GetTimeLimit()
{
    QString txt = ui->in_time_limit->text();
    return txt.toInt();
}

MainWindow::~MainWindow()
{
    delete ui;
	delete txtfile;
	delete binpack;
}


