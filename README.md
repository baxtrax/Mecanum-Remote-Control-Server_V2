# QT Remote Control Server V2

This is a QT Gui / Application that was made in QT Creator to be used as a bridge between a computer and a robot. This is the second iteration of this software and has greatly improved in look, functionality, and performance over the previous iteration. This is the "brains" of the remote control for a remote control mechanum car. The server-side counter-part to this application can be found [here](https://github.com/baxtrax/QT-Remote-Control-Server). Although at the momment this program does not have networking funcionality as it is still a work in progress. Still use the previous iterration until this one is complete. Some parts of the redesign are heavily inspired off of Mithi's Hexpod Simulation 2, which can be found [here](https://github.com/mithi/hexapod).

## Details

This section will show current features of the GUI and up to date pictures of the GUI its self.

### Pictures of Current state of GUI
Main GUI (3D Render is still a work in progress):

![alt text](https://github.com/baxtrax/QT-Remote-Control-Server_V2/blob/master/GUI-PIC/Showcase.gif)
Settings GUI:

![alt text](https://github.com/baxtrax/QT-Remote-Control-Server_V2/blob/master/GUI-PIC/RemoteControlV2_2.PNG)

Info GUI:

![alt text](https://github.com/baxtrax/QT-Remote-Control-Server_V2/blob/master/GUI-PIC/RemoteControlV2_3.PNG)

### Features
* Has retainable settings between launches.
* Easy to understand input sliders.
* Keyboard and Joystick compatable (Can even combine them together!).
* Connection status and other detailed info displayed. (Camera and Communication now!)
* Simulation of movements in 3D
* A Kinematics graph to show how outputs are calculated.
* and much more to come!

~~More details of how parts of this program work and why design decisions where made can be found on this repositorys respective wiki.~~ (Not started yet)

## Built With

* [QT Creator](https://www.qt.io/download) - The main framework used / application
* [QMake](https://doc.qt.io/archives/3.3/qmake-manual-2.html) - C++ Build tool

## Authors

* **Bradley G** - *Original Creator* - [Baxtrax](https://github.com/baxtrax)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
