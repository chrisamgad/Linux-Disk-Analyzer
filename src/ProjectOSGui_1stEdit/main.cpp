
#include "mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include "node.h"
#include <QString>
#include <QtCharts/QChartView>         // Widget used to display charts
#include <QtCharts/QPieSeries>         // Used to make Pie Charts
#include <QtCharts/QPieSlice>
#include<sstream>
#include <QPointF>
QT_CHARTS_USE_NAMESPACE
using namespace std;





void listdir(const char *name, vector<node> &ans, bool lastSlash)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;


    if (!(dir = opendir(name)))
    {
        cout<<"Couldn't open the file or dir"<<name<<"\n";
        return;
    }
    if (!(entry = readdir(dir)))
    {
        cout<<"Couldn't read the file or dir"<<name<<"\n";
        return;
    }

    do
    {
        string slash="";
        if(!lastSlash)
          slash = "/";

        string parent(name);
        string file(entry->d_name);
        string filename=file;
        string final = parent + slash + file;
        if(stat(final.c_str(), &statbuf)==-1)
        {
            cout<<"Couldn't get the stat info of file or dir: "<<final<<"\n";
            return;
        }

        if (entry->d_type == DT_DIR) //its a directoru
        {

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)//skip the . and .. directory
                continue;
            struct node tmp;
            tmp.name = final;
            tmp.type = "D";
            tmp.size = 0;
            tmp.filename=file;
            tmp.parent=parent;
            int temp=ans.size();// fiha elsize bta3 elvector elfilat/directores TILL NOW
            ans.push_back(tmp);
            listdir(final.c_str(), ans, false);
            for(int i=temp+1;i<ans.size();i++)
            {
                if (ans[i].type != "D")
                   ans[temp].size=ans[temp].size+ans[i].size;

            }
        }
        else // it is a file
        {
            struct node tmp;
            tmp.name = final;
            tmp.type = "F";
            tmp.size = statbuf.st_size;
            tmp.filename=file;
            tmp.parent=parent;
            ans.push_back(tmp);
        }
    } while (entry = readdir(dir));
    closedir(dir);
}

/*int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
*/
int main(int argc,  char *argv[])
{   //argv[1]="/home";
    string ParentOfDirectories=argv[1];
    vector<node> ans;
    int NDirectoriesShown=0;
    bool lastSlash = false;
    //check the last slash if any to avoid redundant /
    if(argv[1][strlen(argv[1])-1]=='/')
      lastSlash = true;

    //store all the subdirectories in the vector
    listdir(argv[1], ans, lastSlash);


    //output the result to standard output
    for(int i=0; i<ans.size(); i++)
    {  // cout<<"Chris"<<endl;
      //cout<<"PATH: "<<ans[i].name<<",TYPE:"<<ans[i].type<<", SIZE: "<<ans[i].size<<"\n";
       //cout<<"Parent of this path is"<<ans[i].parent<<endl;
    }
    //cout<<"Parent is"<<ParentOfDirectories<<endl;
    QApplication a(argc, argv);

    MainWindow w(ans,ParentOfDirectories);
    w.show();
   // cout<<ans[0].parent<<endl;
    //cout<<NDirectoriesShown<<endl;
    return a.exec();
}
