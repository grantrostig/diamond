/**************************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
* All rights reserved.
*
* This file is part of Diamond Editor.
*
* Diamond Editor is free software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License version 3
* as published by the Free Software Foundation.
*
* Diamond Editor is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Diamond Editor.  If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#include "mainwindow.h"
#include "util.h"

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

static void showHelp();
static void showVersion();

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   app.setOrganizationName("CS");
   app.setApplicationName("Diamond Editor");

   int retval   = 0;
   bool okToRun = true;

   // passed parameters
   QStringList fileList;
   QStringList flagList;

   for (int k = 0; k < argc; ++k)   {
      QString value = argv[k];

      if (value.left(2) == "--") {
         flagList.append(value);
      } else {
         fileList.append(value);
      }

   }

   if (flagList.contains("--help", Qt::CaseInsensitive)) {
      showHelp();
      okToRun = false;

   } else if (flagList.contains("--version", Qt::CaseInsensitive)) {
      showVersion();
      okToRun = false;
   }

   if (okToRun) {

      try{
         MainWindow dw(fileList, flagList);
         dw.show();

         retval = app.exec();

      } catch (std::exception &e) {

         const char *what = e.what();

         if (strcmp(what, "abort_no_message") == 0)  {
            // do nothing

         } else {
            QString errMsg = "Exception: " + QString(what);

            QMessageBox msgB;
            msgB.setWindowTitle("Diamond / Issue");
            msgB.setIcon(QMessageBox::NoIcon);
            msgB.setMinimumWidth(100);

            msgB.setText(errMsg);
            msgB.exec();
         }
      }
   }

   return retval;
}

static void showHelp()
{
   QString textBody;
   textBody = "<table style=margin-right:25>"

              "<tr><td width=200>&minus;&minus;help</td><td width=240>Displays this message</td></tr>"
              "<tr><td width=200>&minus;&minus;version</td><td width=240>Displays the current version</td></tr>"

              "<tr></tr>"

              "<tr><td width=200>&minus;&minus;no_autoload</td><td width=240>Force no auto load of previously open files</td></tr>"
              "<tr><td>&minus;&minus;no_saveconfig</td><td>Do not save config file</td></tr>"
              "<tr></tr>"

              "<tr><td>[fileName] [fileName] ...</td><td>Files to open when starting Diamond</td></tr></table><br>";

   QDialog msgB;
   msgB.setWindowIcon(QIcon("://resources/diamond.png"));

   msgB.setWindowTitle("Diamond Editor Help");

   QLabel *label = new QLabel;

   QFont font = label->font();
   font.setPointSize(11);
   label->setFont(font);

   label->setText(textBody);

   QPushButton *button = new QPushButton();
   button->setText("Ok");

   QHBoxLayout *layoutButton = new QHBoxLayout();
   layoutButton->addStretch();
   layoutButton->addWidget(button);
   layoutButton->addStretch();

   QVBoxLayout *layoutMain = new QVBoxLayout();
   layoutMain->addWidget(label);
   layoutMain->addLayout(layoutButton);

   msgB.setLayout(layoutMain);

   QObject::connect(button, SIGNAL(clicked()), &msgB, SLOT(accept()));

   msgB.exec();
}


static void showVersion()
{
   // change mainwindow.cpp & main.cpp

   QString textBody = "<font color='#000080'><table style=margin-right:25>"
                      "<tr><td><nobr>Developed by Barbara Geller</nobr></td><td>barbara@copperspice.com</td></tr>"
                      "<tr><td style=padding-right:25><nobr>Developed by Ansel Sermersheim</nobr></td><td>ansel@copperspice.com</td></tr>"
                      "</table></font>"
                      "<br>"
                      "<p><small>Copyright 2012-2014 BG Consulting, All rights reserved.<br>"
                      "This program is provided AS IS with no warranty of any kind.<br></small></p>";

   QMessageBox msgB;
   msgB.setIcon(QMessageBox::NoIcon);
   msgB.setWindowIcon(QIcon("://resources/diamond.png"));

   msgB.setWindowTitle("About Diamond");
   msgB.setText("<p style=margin-right:25><center><h5>Version: 1.1.1<br>Build # 07.24.2014</h5></center></p>");
   msgB.setInformativeText(textBody);

   msgB.setStandardButtons(QMessageBox::Ok);
   msgB.setDefaultButton(QMessageBox::Ok);

   msgB.exec();
}
