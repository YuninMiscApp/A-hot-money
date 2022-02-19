/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtWidgets>

#include "mainwindow.h"

/***********************************
 * 目标价：T
 * 下跌系数：fall
 * 上涨系数：rise
 * 双头系数：double
 * 爆发系数：outburst
 * 回调系数: callback
 ********************************
 * T(fall1) = Val * 0.7
 * T(fall2) = Val * 0.49
 * T(fall3) = Val * 0.343
 * T(r1) = Val * 1.7
 * T(r2) = Val * 2.2
 * T(OB1) = Val * 4.45
 * T(OB2) = Val * 5.76
 * T(CB1)=Val * 0.95
 * T(CB2)=Val * 0.88
***********************************/

#define BR_FALL1 0.7
#define BR_FALL2 0.49
#define BR_FALL3 0.343
#define BR_FALL4 0.168

#define BR_RISE1 1.7
#define BR_RISE2 2.2

#define BR_OB1 4.45
#define BR_OB2 5.76

#define BR_CB1 0.95
#define BR_CB2 0.88

//_edit_->setStyleSheet(_color_);\

#define EDIT_FUNC(_edit_,_val_,_ro_,_maxlen_,_color_) do { \
    _edit_ = new QLineEdit(tr(_val_));  \
    if(_ro_) \
    {\
        _edit_->setReadOnly(true); \
        _edit_->setStyleSheet("background-color:gray"); \
    }\
    _edit_->setStyleSheet(_color_);\
    _edit_->setAlignment(Qt::AlignRight); \
    _edit_->setMaxLength(_maxlen_);\
}while(0)

#define TARGET_LAYOUT_FUNC(_layout_,_label_,_color_,_edit_,_row_) do { \
    _label_->setStyleSheet(_color_);\
    _layout_->addWidget(_label_, _row_, 0); \
    _layout_->addWidget(_edit_, _row_, 1);\
}while(0)

//! [0]
Window::Window(QWidget *parent)
    : QWidget(parent)
{
    /*********************** targetGroup ************************/
    QGroupBox *targetGroup = new QGroupBox(tr("目标价"));
    //[目标价1]
    QLabel *targetMinLabel = new QLabel(tr("目标价1(min):"));
    EDIT_FUNC(tOb1ValEdit_,"0",true,15,"color:red;");
    //[目标价2]
    QLabel *targetMaxLabel = new QLabel(tr("目标价2(max):"));
    EDIT_FUNC(tOb2ValEdit_,"0",true,15,"color:purple;");
    //[暴跌价1]
    QLabel *fallVal1Label = new QLabel(tr("暴跌价1(F1):"));
    EDIT_FUNC(tFall1Edit_,"0",true,15,"color:aqua;");
    //[暴跌价2]
    QLabel *fallVal2Label = new QLabel(tr("暴跌价2(F2):"));
    EDIT_FUNC(tFall2Edit_,"0",true,15,"color:green;");
    //[暴跌价3]
    QLabel *fallVal3Label = new QLabel(tr("暴跌价3(F3):"));
    EDIT_FUNC(tFall3Edit_,"0",true,15,"color:blue;");

    //[最低价]
    QLabel *lowestValLabel = new QLabel(tr("请输入最低价:"));
    EDIT_FUNC(lowestValEdit_,"",false,15,"color:orange;");

    //[-----------------]
    QGridLayout *targetLayout = new QGridLayout;
    TARGET_LAYOUT_FUNC(targetLayout,targetMinLabel,"color:red;",tOb1ValEdit_,0);
    TARGET_LAYOUT_FUNC(targetLayout,targetMaxLabel,"color:purple;",tOb2ValEdit_,1);
    TARGET_LAYOUT_FUNC(targetLayout,fallVal1Label,"color:aqua;",tFall1Edit_,2);
    TARGET_LAYOUT_FUNC(targetLayout,fallVal2Label,"color:green;",tFall2Edit_,3);
    TARGET_LAYOUT_FUNC(targetLayout,fallVal3Label,"color:blue;",tFall3Edit_,4);
    TARGET_LAYOUT_FUNC(targetLayout,lowestValLabel,"color:orange;",lowestValEdit_,5);
    targetGroup->setLayout(targetLayout);

    /*********************** 按键事件 ************************/
    //[按键]
    QPushButton *targetButton = new QPushButton(tr("计算"));
    //[连接]
    connect(targetButton, SIGNAL(clicked()), this, SLOT(targetClicked()));
    /*************************** QGridLayout ********************/
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(targetGroup, 0, 0);
    mainLayout->addWidget(targetButton, 1, 1);
    setLayout(mainLayout);

    // ///////////////////////////
    setWindowTitle(tr("[A游资-财富自由]"));
}


Window::~Window()
{

}


void Window::targetClicked()
{
    //QMessageBox::about(NULL, "A游资", "发财-虎虎生威!!!");
    double lowestVal = lowestValEdit_->text().toDouble();
    double tOb1 = 0,tOb2 = 0;
     double tFall1 = 0,tFall2 = 0,tFall3 = 0;
    tOb1 = lowestVal*BR_OB1;
    tOb2 = lowestVal*BR_OB2;
    tFall1 = ((tOb1+tOb2)/2)*BR_FALL1;
    tFall2 = ((tOb1+tOb2)/2)*BR_FALL2;
    tFall3 = ((tOb1+tOb2)/2)*BR_FALL3;
    tOb1ValEdit_->setText(QString::number(tOb1));
    tOb2ValEdit_->setText(QString::number(tOb2));
    tFall1Edit_->setText(QString::number(tFall1));
    tFall2Edit_->setText(QString::number(tFall2));
    tFall3Edit_->setText(QString::number(tFall3));
}

