## InputFormDialog
InputFormDialog is a simple module that provides a multi-type input dialog for Qt5.

The purpose of the InputFormDialog is to compliment the static get methods of the [QInputDialog](https://doc-snapshots.qt.io/qtforpython/PySide2/QtWidgets/QInputDialog.html) such as `QInputDialog.getText` or `QInputDialog.getInt`.

### Details
Using InputFormDialog is simple. First create a dictionary that will define the form entries and their default values. If the order of input widgets is important, use `OrderedDict`.

Currently the following input queries are supported:
- boolean
- color
- numeric
- text
- options list
- 2d/3d vector

Second, call the `get_input()` function and pass the data object as an argument. If the user accepts the dialog then the data object will hold the new values chosen by the user.

Additionally, you might want to create `FormOptions` object and specify some of the options that control the properties of widgets used by the dialog.

Currently the following options are available:
- set numeric limits, step and decimal precision
- set whether combo box or radio button group is used
- set whether the combo box / radio button group returns current item text or index

### Example
```python
# QApplication must be running prior to calling get_input
from collectictions import OrderedDict
from Qt import QtGui, QtWidgets

from input_form_dialog import FormOptions, get_input

# Define form inputs
data = OrderedDict()
data["Bool"] = True
data['Color'] = QtGui.QColor('red')
data['Int'] = 1
data['String'] = 'Test'
data['ComboBox'] = ['One', 'Two']
data['Vector2'] = QtGui.QVector2D(10.0, 5.0)

# Define form options
options = FormOptions()
options.list_displays_as_radios = True
options.list_returns_index = True

# Ask user for input and retrieve data
if get_input('Example', data, options):
    print(data['Bool'])
    print(data['Color'])
    print(data['Int'])
    print(data['String'])
    print(data['ComboBox'])
    print(data['Vector2'])
```
<img src="https://www.dropbox.com/s/tvl6itcmzxb7hlb/input-form-dialog.jpg?raw=1" width="250" height="250"/>
