// Copyright (c) 2017-2018 Serguei Kalentchouk. All rights reserved.
// Use of this source code is governed by an MIT license that can be found in the LICENSE file.
#include "InputFormDialog.h"

#include <QCheckBox>
#include <QColor>
#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QVector2D>
#include <QVector3D>

namespace InputFormDialog
{

QVariant& FormData::operator[](const QString& key)
{
    for (auto& pair : data_)
    {
        if (pair.first == key)
        {
            return pair.second;
        }
    }
    
    data_.push_back(std::make_pair(key, QVariant()));
    return data_.back().second;
}

std::vector<std::pair<QString, QVariant>>::iterator
FormData::begin()
{
    return data_.begin();
}

std::vector<std::pair<QString, QVariant>>::iterator
FormData::end()
{
    return data_.end();
}

QVariant
FormData::getValue(const QString &key) const
{
    QVariant result;
    
    for (auto& pair : data_)
    {
        if (pair.first == key)
        {
            result = pair.second;
        }
    }
    
    return result;
}

bool
getInput(const QString& title, FormData& data, const FormOptions& options)
{
    auto dialog = new QDialog();
    dialog->setWindowTitle(title);

    auto layout = new QGridLayout(dialog);
    layout->setMargin(2);
    layout->setSpacing(4);
    
    QMap<QString, QWidget*> widgetMap;
    
    auto row = 0;
    for (auto& pair : data)
    {
        auto label = new QLabel(pair.first);
        layout->addWidget(label, row, 0);
        
        switch (pair.second.type())
        {
            case QVariant::Bool:
            {
                auto widget = new QCheckBox();
                widget->setChecked(pair.second.toBool());
                layout->addWidget(widget, row, 1);
                widgetMap[pair.first] = widget;
                break;
            }
            case QVariant::Double:
            {
                auto widget = new QDoubleSpinBox();
                widget->setButtonSymbols(QAbstractSpinBox::NoButtons);
                widget->setMaximum(double(options.numericMax));
                widget->setMinimum(double(options.numericMin));
                widget->setDecimals(options.numericPrecision);
                widget->setValue(pair.second.toDouble());
                layout->addWidget(widget, row, 1);
                widgetMap[pair.first] = widget;
                break;
            }
            case QVariant::Int:
            {
                auto widget = new QSpinBox();
                widget->setButtonSymbols(QAbstractSpinBox::NoButtons);
                widget->setMaximum(options.numericMax);
                widget->setMinimum(options.numericMin);
                widget->setValue(pair.second.toInt());
                layout->addWidget(widget, row, 1);
                widgetMap[pair.first] = widget;
                break;
            }
            case QVariant::String:
            {
                auto widget = new QLineEdit(pair.second.toString());
                layout->addWidget(widget, row, 1);
                widgetMap[pair.first] = widget;
                break;
            }
            case QVariant::StringList:
            {
                if (options.listDisplaysAsRadios)
                {
                    auto values = pair.second.toStringList();
                    
                    auto widget = new QWidget();
                    auto wlayout = new QHBoxLayout(widget);
                    wlayout->setMargin(2);
                    wlayout->setSpacing(2);
                    
                    auto isChecked = false;
                    for (const auto& value : values)
                    {
                        auto button = new QRadioButton(value);
                        wlayout->addWidget(button);
                        
                        if (!isChecked)
                        {
                            button->setChecked(true);
                            isChecked = true;
                        }
                    }
                    
                    layout->addWidget(widget, row, 1);
                    widgetMap[pair.first] = widget;
                }
                else
                {
                    auto widget = new QComboBox();
                    widget->addItems(pair.second.toStringList());
                    layout->addWidget(widget, row, 1);
                    widgetMap[pair.first] = widget;
                }
                break;
            }
            case QVariant::Vector2D:
            {
                auto value = pair.second.value<QVector2D>();
                
                auto widget = new QWidget();
                auto wlayout = new QHBoxLayout(widget);
                wlayout->setMargin(2);
                wlayout->setSpacing(2);
                
                auto xwidget = new QDoubleSpinBox();
                xwidget->setButtonSymbols(QAbstractSpinBox::NoButtons);
                xwidget->setValue(value.x());
                wlayout->addWidget(xwidget);
                
                auto ywidget = new QDoubleSpinBox();
                ywidget->setButtonSymbols(QAbstractSpinBox::NoButtons);
                ywidget->setValue(value.y());
                wlayout->addWidget(ywidget);
                
                layout->addWidget(widget, row, 1);
                widgetMap[pair.first] = widget;
                break;
            }
            case QVariant::Vector3D:
            {
                auto value = pair.second.value<QVector3D>();
                
                auto widget = new QWidget();
                auto wlayout = new QHBoxLayout(widget);
                wlayout->setMargin(2);
                wlayout->setSpacing(2);
                
                auto xwidget = new QDoubleSpinBox();
                xwidget->setButtonSymbols(QAbstractSpinBox::NoButtons);
                xwidget->setValue(value.x());
                wlayout->addWidget(xwidget);
                
                auto ywidget = new QDoubleSpinBox();
                ywidget->setButtonSymbols(QAbstractSpinBox::NoButtons);
                ywidget->setValue(value.y());
                wlayout->addWidget(ywidget);
                
                auto zwidget = new QDoubleSpinBox();
                zwidget->setButtonSymbols(QAbstractSpinBox::NoButtons);
                zwidget->setValue(value.z());
                wlayout->addWidget(zwidget);
                
                layout->addWidget(widget, row, 1);
                widgetMap[pair.first] = widget;
                break;
            }
            default:
                break;
        }
        
        row++;
    }
    
    auto btnLayout = new QHBoxLayout();
    btnLayout->setMargin(2);
    btnLayout->setSpacing(4);
    layout->addLayout(btnLayout, row, 0, 1, 2);

    auto ok = new QPushButton("Ok", dialog);
    ok->setDefault(true);
    QObject::connect(ok, SIGNAL(clicked(bool)), dialog, SLOT(accept()));
    btnLayout->addWidget(ok);

    auto cancel = new QPushButton("Cancel", dialog);
    QObject::connect(cancel, SIGNAL(clicked(bool)), dialog, SLOT(reject()));
    btnLayout->addWidget(cancel);
    
    if (dialog->exec() == QDialog::Accepted)
    {
        for (auto& pair : data)
        {
            switch (pair.second.type())
            {
                case QVariant::Bool:
                {
                    const auto widget = qobject_cast<QCheckBox*>(widgetMap[pair.first]);
                    pair.second = widget->isChecked();
                    break;
                }
                case QVariant::Double:
                {
                    const auto widget = qobject_cast<QDoubleSpinBox*>(widgetMap[pair.first]);
                    pair.second = widget->value();
                    break;
                }
                case QVariant::Int:
                {
                    const auto widget = qobject_cast<QSpinBox*>(widgetMap[pair.first]);
                    pair.second = widget->value();
                    break;
                }
                case QVariant::String:
                {
                    const auto widget = qobject_cast<QLineEdit*>(widgetMap[pair.first]);
                    pair.second = widget->text();
                    break;
                }
                case QVariant::StringList:
                {
                    if (options.listDisplaysAsRadios)
                    {
                        const auto children = widgetMap[pair.first]->children();
                        
                        auto index = 0;
                        for (const auto& child : children)
                        {
                            const auto widget = qobject_cast<QRadioButton*>(child);
                            if (!widget) continue;
                            
                            if (widget->isChecked())
                            {
                                if (options.listReturnsIndex)
                                {
                                    pair.second = index;
                                }
                                else
                                {
                                    pair.second = widget->text();
                                }
                            }
                            
                            index++;
                        }
                    }
                    else
                    {
                        const auto widget = qobject_cast<QComboBox*>(widgetMap[pair.first]);
                        if (options.listReturnsIndex)
                        {
                            pair.second = widget->currentIndex();
                        }
                        else
                        {
                            pair.second = widget->currentText();
                        }
                    }
                    break;
                }
                case QVariant::Vector2D:
                {
                    const auto children = widgetMap[pair.first]->children();
                    const auto xwidget = qobject_cast<QDoubleSpinBox*>(children.at(1));
                    const auto ywidget = qobject_cast<QDoubleSpinBox*>(children.at(2));
                    pair.second = QVector2D(xwidget->value(), ywidget->value());
                    break;
                }
                case QVariant::Vector3D:
                {
                    const auto children = widgetMap[pair.first]->children();
                    const auto xwidget = qobject_cast<QDoubleSpinBox*>(children.at(1));
                    const auto ywidget = qobject_cast<QDoubleSpinBox*>(children.at(2));
                    const auto zwidget = qobject_cast<QDoubleSpinBox*>(children.at(3));
                    pair.second = QVector3D(xwidget->value(), ywidget->value(), zwidget->value());
                    break;
                }
                default:
                    break;
            }
        }
        
        return true;
    }
    
    return false;
}

}
