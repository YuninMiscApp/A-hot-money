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


//! [0]
Window::Window(QWidget *parent)
    : QWidget(parent)
{

    /*********************** targetGroup ************************/
    QGroupBox *targetGroup = new QGroupBox(tr("目标价"));
    //[目标价1]
    QLabel *targetMinLabel = new QLabel(tr("目标价1(min):"));
    tOb1ValEdit_ = new QLineEdit("0");
    tOb1ValEdit_->setReadOnly(true);
    tOb1ValEdit_->setAlignment(Qt::AlignRight);
    tOb1ValEdit_->setMaxLength(15);
    //[目标价2]
    QLabel *targetMaxLabel = new QLabel(tr("目标价2(max):"));
    tOb2ValEdit_ = new QLineEdit("0");
    tOb2ValEdit_->setReadOnly(true);
    tOb2ValEdit_->setAlignment(Qt::AlignRight);
    tOb2ValEdit_->setMaxLength(15);
    //[最低价]
    QLabel *lowestValLabel = new QLabel(tr("请输入最低价:"));
    lowestValEdit_ = new QLineEdit("0");
    lowestValEdit_->setAlignment(Qt::AlignRight);
    lowestValEdit_->setMaxLength(15);

    //[]
    QGridLayout *targetLayout = new QGridLayout;
    targetLayout->addWidget(targetMinLabel, 0, 0);
    targetLayout->addWidget(tOb1ValEdit_, 0, 1);
    targetLayout->addWidget(targetMaxLabel, 1, 0);
    targetLayout->addWidget(tOb2ValEdit_, 1, 1);
    targetLayout->addWidget(lowestValLabel, 2, 0);
    targetLayout->addWidget(lowestValEdit_, 2, 1);
    targetGroup->setLayout(targetLayout);
    /*********************** targetGroup ************************/
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
    double targetMinVal = 0,targetMaxVal = 0;
    targetMinVal = lowestVal*BR_OB1;
    targetMaxVal = lowestVal*BR_OB2;
    tOb1ValEdit_->setText(QString::number(targetMinVal));
    tOb2ValEdit_->setText(QString::number(targetMaxVal));
}

