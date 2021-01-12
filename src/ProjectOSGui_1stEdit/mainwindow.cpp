#include "mainwindow.h"

using namespace std;


MainWindow::MainWindow(vector<node> ans,string ParentOfDirectories,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //cout<<"This is a test that ans vector has passed successfully to the mainwindow class --> "<< ans[2].name<<endl;
    // cout<<ans.size()<<endl;
   //  string  hello=ans[0].name;
    //string hello="hello";
     //string str=ans[0].name;
     QString InitalDirPrint= QString::fromStdString(ParentOfDirectories);

   //for (int i=0; i<ans.size();i++)
    QString text = QString("List of Directories inside %1 ").arg(InitalDirPrint);
    ui->label->setText(text);
   QStringList List;
  // cout<<"Parentt of argv1 is"<<ParentOfDirectories<<endl;
    ParentDirectories=ParentOfDirectories;
    for (int i=0; i<ans.size();i++)
    {
        string teststr=ans[i].name;
        QString QSTR= QString::fromStdString(teststr);//string to Qstring
        List.append(QSTR);//add Qstring element to Qstringlist
        if(ans[i].type=="D" && ans[i].parent==ParentOfDirectories)
             { //ui->comboBox->addItem(QIcon("/home/chris/Desktop/ProjectOSGui_1stEdit/images/FolderIcon.png"),QSTR);
                ui->comboBox->addItem(QIcon(":/images/images/FolderIcon.png"),List[i]);
            NDirectoriesShown++;
             }
        else
             if(ans[i].type=="F" && ans[i].parent==ParentOfDirectories)
             {  ui->comboBox->addItem(QIcon(":/images/images/FileIcon.png"),QSTR);
                 NDirectoriesShown++;
             }

    }
    temp=ans;

    const unsigned int GB = (1024 * 1024) * 1024;
    struct statvfs buffer;
    const char * c = ParentOfDirectories.c_str();
    int ret = statvfs(c, &buffer);

    if (!ret) {
        const float total = (double)(buffer.f_blocks * buffer.f_frsize) / GB;
        const float available = (double)(buffer.f_bfree * buffer.f_frsize) / GB;
        const float used = total - available;
        const float usedPercentage = (double)(used / total) * (double)100;
       int totalINT=int(total)*100;
       int availableINT=int(available)*100;
       int usedINT=totalINT-availableINT;
      // cout<<totalINT<<endl;

        QPixmap pic(":/images/images/logo02.png");
        ui->label_7->setPixmap(pic);
    ui->progressBar->setMaximum(totalINT);
    ui->progressBar->setValue(usedINT);
    ui->progressBar->setTextVisible(false);

    QString availableStr=QString::number(available);
    QString AvailFinal=QString("Available: %1 GB").arg(availableStr);
    ui->label_4->setText(AvailFinal);

    QString totalStr=QString::number(total);
    QString TotalFinal=QString("Total: %1 GB").arg(totalStr);
    ui->label_6->setText(TotalFinal);

    QString usedStr=QString::number(used);
    QString UsedFinal=QString("Used: %1 GB").arg(usedStr);
    ui->label_5->setText(UsedFinal);

    QString usedpercStr=QString::number(usedPercentage);
    QString UsedPercFinal=QString("Used Percentage: %1 %").arg(usedpercStr);
    ui->label_3->setText(UsedPercFinal);


   QPieSeries *series = new QPieSeries();
   // QString value =ui->comboBox->currentText();
   // cout <<value.toStdString()<<endl;
    int k=0;
        for(int i=0;i<ans.size();i++)
        {
            stringstream ss;
            ss << float(ans[i].size/1048576.0);
            string str = ss.str();

         QString QSTR= QString::fromStdString(ans[i].filename + " , " + str);//string to Qstring
             if(ans[i].parent==ParentOfDirectories )
               {
                 series->append(QSTR+" MB \n",ans[i].size);
                 //series->setLabelsVisible(true);
                // series->setPieSize(0.1);
                 k++;
               }
        }

        for(int j=0;j<k;j++)
        {
            stringstream ss;
                              ss << float(ans[j].size/1048576.0);
                              string str = ss.str();
                              QString QSTR= QString::fromStdString(ans[j].filename + " ," + str + " MB");//string to Qstring
                             // Add label to 1st slice Add label, explode and define brush for 2nd slice
                             QPieSlice *slice1 = series->slices().at(j);
                             slice1->setLabelVisible(false);
                             QFont font;
                             slice1->setLabel(QSTR);

                             //font.
                            // font.setPixelSize(10);
                           //  slice1->setLabelFont(font);
                            //  slice1->setLabelPosition(QPieSlice::LabelOutside);
                             //slice1->setLabelPosition(QPieSlice::LabelPosition(0.8));




                             slice1->setExploded();
                             slice1->setPen(QPen(Qt::white, 2));


        }

           // Create the chart widget
          QChart *chart = new QChart();

           // Add data to chart with title and hide legend
           chart->addSeries(series);
           chart->setTitle("File sizes per Directory");
           QFont font;
           font.setPixelSize(15);
           chart->setTitleFont(font);

           chart->legend()->setVisible(true);
            chart->resize(950,400);
           chart->legend()->setAlignment(Qt::AlignLeft);
           //QCategoryAxis *axisX = new QCategoryAxis(); QCategoryAxis *axisY = new QCategoryAxis();



           QChartView *chartView = new QChartView(chart);


           chartView->setParent(ui->horizontalFrame);
           chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1300,590);
           //chartView->setMidLineWidth(1000);
            //chartView->resize(500,500);
             // chartView->show();
             //   QMainWindow window;
               //     window.setCentralWidget(chartView);
                    //chart->resize(1000,300);
            //  chart->setScale(0.5);
            //  chart->update();
                   // window.show();

         }

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

    QString value =ui->comboBox->currentText();

    string test=value.toStdString();
    const char * c = test.c_str();

    if (is_regular_file(c)==true)// if selected is a file
        QMessageBox::information(this,"Operation Invalid","You can't zoom into a file!");
    else
        if(QDir(c).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
        {
            QMessageBox::information(this,"Directory is empty","This Directory is Empty");
        }
    else
    {
            ui->comboBox->clear();
         //  cout<<"asdfsdfs "<<value.toStdString()<<endl;
            QString str1="List of Directories inside";
            QString text=QString("%1 %2").arg(str1,value);
            ui->label->setText(text);

            QStringList List;
            for (int i=0; i<temp.size();i++)
            {
                string teststr=temp[i].name;
                QString QSTR= QString::fromStdString(teststr);//string to Qstring
                List.append(QSTR);//add Qstring element to Qstringlist
                if(temp[i].type=="D" && ((temp[i].parent)== value.toStdString()))//filters the directories to the needed ones
                     { //ui->comboBox->addItem(QIcon("images/FolderIcon.png"),QSTR);
                        ui->comboBox->addItem(QIcon(":/images/images/FolderIcon.png"),List[i]);

                     }
                else
                     if(temp[i].type=="F" && temp[i].parent== value.toStdString())
                     {  ui->comboBox->addItem(QIcon(":/images/images/FileIcon.png"),QSTR);//filters the directories to the needed one

                     }


            }
            //ui->
            QPieSeries *series = new QPieSeries();
            // QString value =ui->comboBox->currentText();
            // cout <<value.toStdString()<<endl;
             int k=0;
                 for(int i=0;i<temp.size();i++)
                 {
                     stringstream ss;
                     ss << float(temp[i].size/1048576.0);
                     string str = ss.str();

                  QString QSTR= QString::fromStdString(temp[i].filename + " , " + str);//string to Qstring
                      if((temp[i].parent)== value.toStdString() )
                        {
                          series->append(QSTR+" MB \n",temp[i].size);
                          //series->setLabelsVisible(true);
                         // series->setPieSize(0.1);
                          k++;
                        }
                 }

                 for(int j=0;j<k;j++)
                 {
                     stringstream ss;
                                       ss << float(temp[j].size/1048576.0);
                                       string str = ss.str();
                                       QString QSTR= QString::fromStdString(temp[j].filename + " ," + str + " MB");//string to Qstring
                                      // Add label to 1st slice Add label, explode and define brush for 2nd slice
                                      QPieSlice *slice1 = series->slices().at(j);
                                      slice1->setLabelVisible(false);
                                      QFont font;
                                      slice1->setLabel(QSTR);

                                      //font.
                                     // font.setPixelSize(10);
                                    //  slice1->setLabelFont(font);
                                     //  slice1->setLabelPosition(QPieSlice::LabelOutside);
                                      //slice1->setLabelPosition(QPieSlice::LabelPosition(0.8));




                                      slice1->setExploded();
                                      slice1->setPen(QPen(Qt::white, 2));


                 }

                    // Create the chart widget
                   QChart *chart = new QChart();

                    // Add data to chart with title and hide legend
                    chart->addSeries(series);
                    chart->setTitle("File sizes per Directory");
                    QFont font;
                    font.setPixelSize(15);
                    chart->setTitleFont(font);

                    chart->legend()->setVisible(true);
                     chart->resize(950,400);
                    chart->legend()->setAlignment(Qt::AlignLeft);
                    //QCategoryAxis *axisX = new QCategoryAxis(); QCategoryAxis *axisY = new QCategoryAxis();



                    QChartView *chartView = new QChartView(chart);


                    chartView->setParent(ui->horizontalFrame);
                    chartView->setRenderHint(QPainter::Antialiasing);
                     chartView->resize(1300,590);
                    //chartView->setMidLineWidth(1000);
                     //chartView->resize(500,500);
                      // chartView->show();
                      //   QMainWindow window;
                        //     window.setCentralWidget(chartView);
                             //chart->resize(1000,300);
                     //  chart->setScale(0.5);
                     //  chart->update();
                             chartView->show();


       }
}

void MainWindow::on_pushButton_2_clicked()
{

    QString value =ui->comboBox->currentText();
    string test=value.toStdString();
    string ParentOfSelected;
    const size_t last_slash_idx_3 = test.rfind("/");
    if (std::string::npos != last_slash_idx_3)
    {
        ParentOfSelected = test.substr(0, last_slash_idx_3);

    }
   // cout<<"Parent Of selected is "<<ParentOfSelected<<endl;
  //cout<<"Parent Of directories is "<<ParentDirectories<<endl;
    if (ParentOfSelected == ParentDirectories)
        QMessageBox::information(this,"This is Root Directory!","This is the Root directory, You can not zoom out of Root Directory");
        //cout<<"<fdafsdfsdf"<<endl;
    else
      {
            string filename = value.toStdString();
            string directory,Test;
            const size_t last_slash_idx = filename.rfind("/");
            //const size_t last_slash_idx2 = last_slash_idx.rfind("/");
            if (std::string::npos != last_slash_idx)
            {
                directory = filename.substr(0, last_slash_idx);

            }
        cout<<directory<<endl;
            string directory2,Test2;
            const size_t last_slash_idx2 = directory.rfind("/");
            //const size_t last_slash_idx2 = last_slash_idx.rfind("/");
            if (std::string::npos != last_slash_idx2)
            {
                directory2 = directory.substr(0, last_slash_idx2);

            }
            QString str1="List of Directories inside";
            QString CurrentDir= QString::fromStdString(directory2);
            QString text=QString("%1 %2").arg(str1,CurrentDir);
            ui->label->setText(text);
            //label_2=setText(CurrentDir);
            cout<<directory<<endl;
             ui->comboBox->clear();
             QStringList List;

            for (int i=0; i<temp.size();i++)
            {
                string teststr=temp[i].name;
                QString QSTR= QString::fromStdString(teststr);//string to Qstring
                List.append(QSTR);//add Qstring element to Qstringlist
                if(temp[i].type=="D" && (temp[i].parent)== (directory2))
                     { //ui->comboBox->addItem(QIcon(":/images/images/FolderIcon.png"),QSTR);
                        ui->comboBox->addItem(QIcon(":/images/images/FolderIcon.png"),List[i]);

                     }
                else
                     if(temp[i].type=="F" && temp[i].parent== (directory2))
                     {  ui->comboBox->addItem(QIcon(":/images/images/FileIcon.png"),QSTR);

                     }

            }
            //ui->
            //ui->
            QPieSeries *series = new QPieSeries();
            // QString value =ui->comboBox->currentText();
            // cout <<value.toStdString()<<endl;
             int k=0;
                 for(int i=0;i<temp.size();i++)
                 {
                     stringstream ss;
                     ss << float(temp[i].size/1048576.0);
                     string str = ss.str();

                  QString QSTR= QString::fromStdString(temp[i].filename + " , " + str);//string to Qstring
                      if((temp[i].parent)== (directory2) )
                        {
                          series->append(QSTR+" MB \n",temp[i].size);
                          //series->setLabelsVisible(true);
                         // series->setPieSize(0.1);
                          k++;
                        }
                 }

                 for(int j=0;j<k;j++)
                 {
                     stringstream ss;
                                       ss << float(temp[j].size/1048576.0);
                                       string str = ss.str();
                                       QString QSTR= QString::fromStdString(temp[j].filename + " ," + str + " MB");//string to Qstring
                                      // Add label to 1st slice Add label, explode and define brush for 2nd slice
                                      QPieSlice *slice1 = series->slices().at(j);
                                      slice1->setLabelVisible(false);
                                      QFont font;
                                      slice1->setLabel(QSTR);

                                      //font.
                                     // font.setPixelSize(10);
                                    //  slice1->setLabelFont(font);
                                     //  slice1->setLabelPosition(QPieSlice::LabelOutside);
                                      //slice1->setLabelPosition(QPieSlice::LabelPosition(0.8));




                                      slice1->setExploded();
                                      slice1->setPen(QPen(Qt::white, 2));


                 }

                    // Create the chart widget
                   QChart *chart = new QChart();

                    // Add data to chart with title and hide legend
                    chart->addSeries(series);
                    chart->setTitle("File sizes per Directory");
                    QFont font;
                    font.setPixelSize(15);
                    chart->setTitleFont(font);

                    chart->legend()->setVisible(true);
                     chart->resize(950,400);
                    chart->legend()->setAlignment(Qt::AlignLeft);
                    //QCategoryAxis *axisX = new QCategoryAxis(); QCategoryAxis *axisY = new QCategoryAxis();



                    QChartView *chartView = new QChartView(chart);


                    chartView->setParent(ui->horizontalFrame);
                    chartView->setRenderHint(QPainter::Antialiasing);
                     chartView->resize(1300,590);
                    //chartView->setMidLineWidth(1000);
                     //chartView->resize(500,500);
                      // chartView->show();
                      //   QMainWindow window;
                        //     window.setCentralWidget(chartView);
                             //chart->resize(1000,300);
                     //  chart->setScale(0.5);
                     //  chart->update();
                             chartView->show();
    }



}

int MainWindow::is_regular_file(const char *path)
    {
        struct stat path_stat;
        stat(path, &path_stat);
        return S_ISREG(path_stat.st_mode);
    }


