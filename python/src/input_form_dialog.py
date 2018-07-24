# Copyright (c) 2018 Serguei Kalentchouk. All rights reserved.
# Use of this source code is governed by an MIT license that can be found in the LICENSE file.
from collections import OrderedDict
from Qt import QtGui, QtWidgets


class FormOptions(object):
    """Form Options
    
    Attributes:
        list_returns_index (bool): If True, combo box query returns current index,
            otherwise returns current text
        list_displays_as_radios (bool): If True, combo box query is presented as radio button group
        numeric_min (int): Minimum value for numeric queries
        numeric_max (int): Maximum value for numeric queries
        numeric_precision (int): Decimal percision for numeric queries
    """
    def __init__(self):
        self.list_returns_index = False
        self.list_displays_as_radios = False
        
        self.numeric_min = -100
        self.numeric_max = 100
        self.numeric_precision = 2


class ColorSwatchButton(QtWidgets.QPushButton):
    """Collor Swatch Button"""
    def __init__(self):
        super(ColorSwatchButton, self).__init__()
        
        self.setAutoFillBackground(True);
        self.setFlat(True);
        
        self._color = QtGui.QColor()
        
        self.clicked.connect(self.change_color)
    
    def color(self):
        """Get current color
        
        Returns:
            QtGui.QColor: Return current color
        """
        return self._color
    
    def set_color(self, color):
        """
        Set current color
        
        Args:
            color (QtGui.QColor): New color value
        """
        palette = self.palette()
        palette.setColor(QtGui.QPalette.Button, color)
        
        self.setPalette(palette)
        self.update()
        
        self._color = color
    
    def change_color(self):
        """Change color callback"""
        new_color = QtWidgets.QColorDialog.getColor(self._color, self.parentWidget())
        
        if new_color != self._color:
            self.set_color(new_color)


def get_input(title, data, options=FormOptions()):
    """
    Get input from user
    
    If the user accepts the dialog then the current values will be
    written back to the data object.
    Note that for list queries this will change the value type!
    
    Args:
       title (str): Dialog title
       data (OrderedDict): Input data to build tha dialog for
       options(FormOptions): Options to control dialog behavior
    
    Returns:
        bool: Returns True if dialog is accepted, False otherwise
    """
    dialog = QtWidgets.QDialog()
    dialog.setWindowTitle(title)
    
    layout = QtWidgets.QGridLayout(dialog)
    layout.setMargin(2)
    layout.setSpacing(4)
    
    widgets = {}
    
    for row, key in enumerate(data):
        label = QtWidgets.QLabel(key + ':')
        layout.addWidget(label)
        
        value = data[key]
        if isinstance(value, bool):
            widget = QtWidgets.QCheckBox()
            widget.setChecked(value)
            layout.addWidget(widget, row, 1)
            widgets[key] = widget
        elif isinstance(value, QtGui.QColor):
            widget = ColorSwatchButton()
            widget.set_color(value)
            layout.addWidget(widget, row, 1)
            widgets[key] = widget
        elif isinstance(value, float):
            widget = QtWidgets.QDoubleSpinBox()
            widget.setButtonSymbols(QtWidgets.QAbstractSpinBox.NoButtons)
            widget.setMaximum(options.numeric_max)
            widget.setMinimum(options.numeric_min)
            widget.setDecimals(options.numeric_precision)
            widget.setValue(value)
            layout.addWidget(widget, row, 1)
            widgets[key] = widget
        elif isinstance(value, int):
            widget = QtWidgets.QSpinBox()
            widget.setButtonSymbols(QtWidgets.QAbstractSpinBox.NoButtons)
            widget.setMaximum(options.numeric_max)
            widget.setMinimum(options.numeric_min)
            widget.setValue(value)
            layout.addWidget(widget, row, 1)
            widgets[key] = widget
        elif isinstance(value, basestring):
            widget = QtWidgets.QLineEdit(value)
            layout.addWidget(widget, row, 1)
            widgets[key] = widget
        elif isinstance(value, list):
            if options.list_displays_as_radios:
                widget = QtWidgets.QWidget()
                widget_layout = QtWidgets.QHBoxLayout(widget)
                widget_layout.setMargin(2)
                widget_layout.setSpacing(2)
                
                is_checked = False
                for item in value:
                    button = QtWidgets.QRadioButton(item)
                    widget_layout.addWidget(button)
                    
                    if not is_checked:
                        button.setChecked(True)
                        is_checked = True
            
                layout.addWidget(widget, row, 1)
                widgets[key] = widget
            else:
                widget = QtWidgets.QComboBox()
                widget.addItems(value)
                layout.addWidget(widget, row, 1)
                widgets[key] = widget
        elif isinstance(value, QtGui.QVector2D) or isinstance(value, QtGui.QVector3D):
            widget = QtWidgets.QWidget()
            widget_layout = QtWidgets.QHBoxLayout(widget)
            widget_layout.setMargin(2)
            widget_layout.setSpacing(2)
            
            x_widget = QtWidgets.QDoubleSpinBox()
            x_widget.setButtonSymbols(QtWidgets.QAbstractSpinBox.NoButtons)
            x_widget.setMaximum(options.numeric_max)
            x_widget.setMinimum(options.numeric_min)
            x_widget.setDecimals(options.numeric_precision)
            x_widget.setValue(value.x())
            
            y_widget = QtWidgets.QDoubleSpinBox()
            y_widget.setButtonSymbols(QtWidgets.QAbstractSpinBox.NoButtons)
            y_widget.setMaximum(options.numeric_max)
            y_widget.setMinimum(options.numeric_min)
            y_widget.setDecimals(options.numeric_precision)
            y_widget.setValue(value.y())
            
            widget_layout.addWidget(x_widget)
            widget_layout.addWidget(y_widget)
            
            if isinstance(value, QtGui.QVector3D):
                z_widget = QtWidgets.QDoubleSpinBox()
                z_widget.setButtonSymbols(QtWidgets.QAbstractSpinBox.NoButtons)
                z_widget.setMaximum(options.numeric_max)
                z_widget.setMinimum(options.numeric_min)
                z_widget.setDecimals(options.numeric_precision)
                z_widget.setValue(value.y())
                widget_layout.addWidget(z_widget)
            
            layout.addWidget(widget, row, 1)
            widgets[key] = widget
        else:
            raise ValueError('Data of type "{}" is not supported!'.format(value_type))
    
    button_layout = QtWidgets.QHBoxLayout()
    button_layout.setMargin(2)
    button_layout.setSpacing(2)
    layout.addLayout(button_layout, row + 1, 0, 1, 2)
    
    ok_button = QtWidgets.QPushButton('Ok')
    ok_button.setDefault(True)
    ok_button.clicked.connect(dialog.accept)
    button_layout.addWidget(ok_button)

    cancel_button = QtWidgets.QPushButton('Cancel')
    cancel_button.clicked.connect(dialog.reject)
    button_layout.addWidget(cancel_button)
    
    if dialog.exec_() == QtWidgets.QDialog.Rejected:
        return False
    
    for key in data:
        value = data[key]
        if isinstance(value, bool):
            data[key] = widgets[key].isChecked()
        elif isinstance(value, QtGui.QColor):
            data[key] = widgets[key].color()
        elif isinstance(value, float) or isinstance(value, int):
            data[key] = widgets[key].value()
        elif isinstance(value, basestring):
            data[key] = widgets[key].text()
        elif isinstance(value, list):
            if options.list_displays_as_radios:
                children = widgets[key].children()
                for index, child in enumerate(children):
                    if not isinstance(child, QtWidgets.QRadioButton):
                        continue
                    
                    if child.isChecked():
                        if options.list_returns_index:
                            data[key] = index
                        else:
                            data[key] = child.text()
            else:
                if options.list_returns_index:
                    data[key] = widgets[key].currentIndex()
                else:
                    data[key] = widgets[key].currentText()
        elif isinstance(value, QtGui.QVector2D):
            children = widgets[key].children()
            data[key] = QtGui.QVector2D(children[1].value(), children[2].value())
        elif isinstance(value, QtGui.QVector3D):
            children = widgets[key].children()
            data[key] = QtGui.QVector3D(children[1].value(),
                                        children[2].value(),
                                        children[3].value())     
    
    return True
