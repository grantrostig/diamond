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

#ifndef DIALOG_BUFFER_H
#define DIALOG_BUFFER_H

#include "ui_dialog_buffer.h"
#include "mainwindow.h"

#include <QDialog>

class Dialog_Buffer : public QDialog
{
   CS_OBJECT(Dialog_Buffer)

   public:
      Dialog_Buffer(QList<QString> copyBuffer);
      ~Dialog_Buffer();
      int get_Index();       

   protected:
      bool eventFilter(QObject *object, QEvent *event);

   private :     
      Ui::Dialog_Buffer *m_ui;

      CS_SLOT_1(Private, void Select())
      CS_SLOT_2(Select) 

      CS_SLOT_1(Private, void Cancel())
      CS_SLOT_2(Cancel)      
};

#endif
