// Copyright (c) 2018 Serguei Kalentchouk. All rights reserved.
// Use of this source code is governed by an MIT license that can be found in the LICENSE file.
#include <QApplication>

#include <QColor>
#include <QDebug>
#include <QPushButton>
#include <QVector2D>
#include <QVector3D>

#include "../src/InputFormDialog.h"

void ask()
{
    // Define form inputs
    InputFormDialog::FormData data;
    data["Bool"] = true;
    data["Color"] = QColor("red");
    data["Int"] = 1;
    data["String"] = "Test";
    data["ComboBox"] = QStringList() << "One" << "Two";
    data["Vector2"] = QVector2D(10.0, 5.0);
    
    // Define form options
    InputFormDialog::FormOptions options;
    options.listDisplaysAsRadios = true;
    options.listReturnsIndex = true;
    
    // Ask user for input and retrieve data
    if (InputFormDialog::getInput("Example", data, options))
    {
        qDebug() << data.at<bool>("Bool");
        qDebug() << data.at<QColor>("Color");
        qDebug() << data.at<int>("Int");
        qDebug() << data.at<QString>("String");
        qDebug() << data.at<int>("ComboBox");
        qDebug() << data.at<QVector2D>("Vector2");
    }
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    auto button = new QPushButton("Ask Me");
    QObject::connect(button, &QPushButton::clicked, ask);
    button->show();
    
    return app.exec();
}
