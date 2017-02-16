// Copyright (c) 2017 Serguei Kalentchouk
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once

#include <cassert>
#include <iterator>
#include <vector>
#include <utility>

#include <QAbstractSpinBox>
#include <QtGlobal>
#include <QString>
#include <QVariant>

namespace InputFormDialog
{

class FormData
{
public:
    QVariant& operator[](const QString& key);
    
    std::vector<std::pair<QString, QVariant>>::iterator begin();
    std::vector<std::pair<QString, QVariant>>::iterator end();
    
    template <typename T>
    T at(const QString& key) const
    {
        auto value = getValue(key);
        
        Q_ASSERT_X(!value.isNull(), "FormTemplate::at", "invalid key");
        Q_ASSERT_X(value.canConvert<T>(), "FormTemplate::at", "invalid type");
        
        return value.value<T>();
    }
    
private:
    QVariant getValue(const QString& key) const;
    
    std::vector<std::pair<QString, QVariant>> data_;
};

struct FormOptions
{
    bool listReturnsIndex = false;
    bool listDisplaysAsRadios = false;
    
    int numericMin = -100;
    int numericMax = 100;
    int numericPercision = 2;
};

bool getInput(const QString& title, FormData& data, const FormOptions& options = FormOptions());

}
