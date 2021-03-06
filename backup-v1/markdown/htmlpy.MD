#Notes for htmlpy

##Installation
**Platform**: Ubuntu 16.04 LTS

1) Installing python package manager: pip
```
sudo apt-get install python-pip
```

2) Installing htmlPy
```
pip install htmlPy
```

3) Installing PySide
```
sudo apt-get install python-pyside
```
4) Installing jinja2, which is depended by htmlPy.
```
sudo pip install jinja2
```

5) Installing PyQt4
```
sudo apt-get install python-qt4
```

##A simple demo
Assume that there is a file named "index.html" in the same path.
```python
import htmlPy
import os

app = htmlPy.AppGUI(title=u"htmlPy Quickstart", maximized=True)

app.template_path = os.path.abspath(".")
app.static_path = os.path.abspath(".")

app.template = ("index.html", {"username": "htmlPy_user"})

app.start()
```

##Modularization
The driver file structure should be:

1. Initial configurations
2. htmlPy GUI initialization
3. htmlPy GUI configuration
4. Binding of back-end functionalities with GUI
    a. Import back-end functionalities
	b. Bind imported functionalities
5. Instructions for running front-end in if \_\_name\_\_ \=\= "\_\_main\_\_": conditional. Always keep the GUI starter code in the ``if __name__ == “__main__”:`` conditional. The GUI has to be started only when the driver file is running, not when it is being imported

```python
import os
import htmlPy
from PyQt4 import QtGui


# Initial confiurations
BASE_DIR = os.path.abspath(os.path.dirname(__file__))


# GUI initializations
app = htmlPy.AppGUI(title=u"Application", maximized=True, plugins=True)


# GUI configurations
app.static_path = os.path.join(BASE_DIR, "static/")
app.template_path = os.path.join(BASE_DIR, "templates/")

app.web_app.setMinimumWidth(1024)
app.web_app.setMinimumHeight(768)
app.window.setWindowIcon(QtGui.QIcon(BASE_DIR + "/static/img/icon.png"))

# Binding of back-end functionalities with GUI

# Import back-end functionalities
from html_to_python import ClassName

# Register back-end functionalities
app.bind(ClassName())


# Instructions for running application
if __name__ == "__main__":
    # The driver file will have to be imported everywhere in back-end.
    # So, always keep app.start() in if __name__ == "__main__" conditional
    app.start()
```