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

	total_boxes = 0;

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
	
	
	LoadBPPFileToUI("C:/Users/nattaon2/Desktop/gl_bpp_rotation/box_all.txt");
	//LoadBPPFileToUI("C:/Users/Nattaon/Desktop/qt_bpp_rotate/box10.txt");

	ui->widget->SetInitialBin(GetBinWidth(), GetBinHeight(), GetBinDepth());
}
void MainWindow::AddNewIntItemToList(int item1,int item2,int item3,string name)
{
	
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
	total_boxes++;

    item->setText(0, QString::number(total_boxes));
	item->setText(1, QString::number(item1));
	item->setText(2, QString::number(item2));
	item->setText(3, QString::number(item3));
	item->setText(4, QString::fromStdString(name));

	item->setTextAlignment(0, Qt::AlignHCenter);
	item->setTextAlignment(1, Qt::AlignHCenter);
	item->setTextAlignment(2, Qt::AlignHCenter);
	item->setTextAlignment(3, Qt::AlignHCenter);

	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
	

	ui->treeWidget->addTopLevelItem(item);

}
void MainWindow::AddNewStringItemToList(QString item1, QString item2, QString item3)
{

	QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
	total_boxes++;

	item->setText(0, QString::number(total_boxes));
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
void MainWindow::GetBoxesSize()
{
	boxes_w = new int[total_boxes];
	boxes_h = new int[total_boxes];
	boxes_d = new int[total_boxes];

	for (int i = 0; i < total_boxes; ++i)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);

		boxes_w[i] = item->text(1).toInt();
		boxes_h[i] = item->text(2).toInt();
		boxes_d[i] = item->text(3).toInt();

	}

}

void MainWindow::InitialBoxedPacking()
{
	boxes_x_pos = new int[total_boxes];
	boxes_y_pos = new int[total_boxes];
	boxes_z_pos = new int[total_boxes];
	boxes_x_orient = new int[total_boxes];
	boxes_y_orient = new int[total_boxes];
	boxes_z_orient = new int[total_boxes];
	boxes_bin_num = new int[total_boxes];
	boxes_item_num = new int[total_boxes];
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

	if (last_select_item_index == total_boxes - 1)
	{
		last_select_item_index--;
	}

    total_boxes--;

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
		tr("Open Image"), "../", tr("Iext Files (*.txt)"));

	
	if (!fileName.trimmed().isEmpty()) // no file selected
	{
		std::cout << "Got filename: " << fileName.toStdString() << std::endl;
		LoadBPPFileToUI(fileName.toStdString());
		
	}

	
}


void MainWindow::LoadBPPFileToUI(string filename)
{
	
	ui->label_filename->setText(QString::fromStdString(filename));

	txtfile = new ReadWriteFile();
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
			txtfile->boxes_name.at(i));

	}
	ui->widget->Color->SetColor(
		txtfile->total_boxes,
		txtfile->color_r,
		txtfile->color_g,
		txtfile->color_b);
}

void MainWindow::PressedSaveDb()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Open Image"), "../", tr("Iext Files (*.txt)"));

	std::cout << "Set filename: " << fileName.toStdString() << std::endl;

	GetBoxesSize();

	txtfile->SaveTxtFileBoxes(fileName.toStdString(), GetTotalBox(),
		GetBinWidth(), GetBinHeight(), GetBinDepth(),
		boxes_w, boxes_h, boxes_d);
}
void MainWindow::PressedClearAll()
{
	for (int i = total_boxes-1; i >=0 ; i--)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
		delete item;
	}
	total_boxes = 0;
}

void MainWindow::PressedBinPacking()
{
	if (ui->widget->Color->is_color_set == false)
	{
		ui->widget->Color->SetRandomColor();
	}
	//0.set packing type
	//std::cout << "packtype " << ui->comboBox_packMethod->currentIndex() << std::endl;
	//binpack->SetPackingType(ui->comboBox_packMethod->currentIndex());

	cout << "total_boxes = " << total_boxes << endl;

    //1.set bin size
    int bin_width = GetBinWidth();
    int bin_height = GetBinHeight();
    int bin_depth = GetBinDepth();

	//2.set boxes size
	GetBoxesSize();

	
	//3.init box position	
	InitialBoxedPacking();




	//4.calc & get result box position
	cout << endl;
	cout << "input sent" << endl;


	for (int i = 0; i < total_boxes; i++)
	{
		std::cout
			<< i << ":"
			<< boxes_w[i] << " " << boxes_h[i] << " " << boxes_d[i] << " "
			<< "bin_num:" << boxes_bin_num[i] << " "
			<< "pos:"
			<< boxes_x_pos[i] << " " << boxes_y_pos[i] << " " << boxes_z_pos[i] << " "
			<< std::endl;

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
			std::cout
			<< i << ":"
			<< boxes_w[i] << " " << boxes_h[i] << " " << boxes_d[i] << " "
			<< "bin_num:" << boxes_bin_num[i] << " "
			<< "pos:"
			<< boxes_x_pos[i] << " " << boxes_y_pos[i] << " " << boxes_z_pos[i] << " "
			<< "orient:"
			<< boxes_x_orient[i] << " " << boxes_y_orient[i] << " " << boxes_z_orient[i] << " "
			<< std::endl;
			
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
			boxes_bin_num, boxes_item_num);


		for (int i = total_boxes - 1; i >= 0; i--)
		{
			if (boxes_bin_num[i] == 1)//pack
			{
				color_rgb = ui->widget->Color->GetColorIndex(i);
			}
			else//not pack
			{
				color_rgb[3] = 10;
				color_rgb[4] = 10;
				color_rgb[5] = 10;
			}
			//cout << "color_rgb " << color_rgb[3] << "," << color_rgb[4] << "," << color_rgb[5] << endl;

			QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
			item->setBackgroundColor(0, QColor(color_rgb[3], color_rgb[4], color_rgb[5]));
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
	total_boxes=ui->treeWidget->topLevelItemCount();
	return total_boxes;
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
}


