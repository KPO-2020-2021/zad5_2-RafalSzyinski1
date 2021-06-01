## Rotation

### Building

To build this project:
```
git submodule init
git submodule update
mkdir build && cd build
cmake ..
make
```
This should generate:
* Rotation3D_run - actual program
* Rotation3D_tst - testing program
* doc_doxygen - documentation of code

## Program

### Doxygen and graph

* I make graph to zad5_2 because this code is mess and I will rewrite this later. 

### VectorAction 

* Doesn't count vectors because I use std::vector and I can't modify the constructor and destructors. 

### Hierarchy

* There are two class inherits Drone class and Figure class.

### Transforming

* Every thing transform right.

### Drone class

* Can be colored on different color.
* Have 4 propellers that can rotate in correct direction depend on rotation and flying.
* Drone can rotate and move in straight line.
 
### Scene

* Draw every element in other thread so you can operate on menu and fly at the same time.
* Draw drone path.
* There are 4 drones that can fly at the same time.