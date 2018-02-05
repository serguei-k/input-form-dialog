// Copyright (c) 2018 Serguei Kalentchouk. All rights reserved.
// Use of this source code is governed by an MIT license that can be found in the LICENSE file.
#include "SetColorButton.h"

#include <QColorDialog>

SetColorButton::SetColorButton() : QPushButton()
{
    setAutoFillBackground(true);
    setFlat(true);
    
    connect(this, SIGNAL(clicked()), this, SLOT(changeColor()));
}

void
SetColorButton::changeColor()
{
    auto newColor = QColorDialog::getColor(color_, parentWidget());
    if (newColor != color_)
    {
        setColor(newColor);
    }
}

void
SetColorButton::setColor(const QColor& color)
{
    auto pal = palette();
    pal.setColor(QPalette::Button, color);
    setPalette(pal);
    update();
    
    this->color_ = color;
}

const QColor&
SetColorButton::color() const
{
    return color_;
}
