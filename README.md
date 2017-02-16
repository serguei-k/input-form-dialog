## InputFormDialog
InputFormDialog is a simple library that provides a multi-type input dialog for Qt.

The goal was to make it as easy to use as the static get methods in [QInputDialog](http://doc.qt.io/qt-5/qinputdialog.html) such as `QInputDialog::getText` or `QInputDialog::getInt`.

### Details
Using InputFormDialog is simple. First you need to create a `FormData` object that will define the form entries and their default values.

The `FormData` behaves similar to an `std::map`, new entries are added to it by using the subscript operator `FormData::operator[]`. The provided key will be used by the dialog as the label and the edit widget will be chosen based on the value type.

Currently the following input queries are supported:
- boolean
- numeric
- text
- options list
- 2d/3d vector

Second, you call the modal `FormData::getInput` function by passing the reference to the data object. If the user accepts the dialog then the data object will hold the new values chosen by the user.

To retrieve the new values from `FormData` you should use the templated `FormData::at` method. This method will try and cast the widget value to the desirared type. Note that in a debug build if the provided key does not exist or the cast is impossible then an assertion will be raised.

Additionally, you might want to create `FormOptions` object and specify some of the options that control the properties of widgets used by the dialog.

Currently the following options are available:
- set numeric limits, step and percision
- set whether combo box or radio button group is used
- set whether the combo box / radio button group returns current item text or index

### Example
```cpp
#include "InputFormDialog.h"

// Define form inputs
InputFormDialog::FormData data;
data["Bool:"] = true;
data["Int:"] = 1;
data["String:"] = "Test";
data["ComboBox:"] = QStringList() << "One" << "Two";
data["Vector2:"] = QVector2D(10.0, 5.0);

// Define form options
InputFormDialog::FormOptions options;
options.listDisplaysAsRadios = true;
options.listReturnsIndex = true;

// Ask user for input and retrieve data
if (InputFormDialog::getInput("Example", data, options))
{
    qDebug() << data.at<bool>("Bool:");
    qDebug() << data.at<int>("Int:");
    qDebug() << data.at<QString>("String:");
    qDebug() << data.at<int>("ComboBox:");
    qDebug() << data.at<QVector2D>("Vector2:");
}
```

<img src="https://dl.dropboxusercontent.com/u/37109838/dialog.png" width="150">

Finally, please note that the build has been tested only on OSX with Qt5!
