# rec_gyro_calib
Author: Stefan Kupper, stefan.kupper[at]th-wildau.de

Implementation of a recursive and effective method for gyroscope sensor calibration.

These source files implement the algorithm for the gyroscope calibration by recursively computing key statistical properties of the time series of gyroscopic output data. The underlying mathematical approach is described in the paper "Optimization of MEMS-Gyroscope calibration using properties of sums of random variables" by Kupper et al.

To use the algorithm simply go to the appropriate Home Directory and run cmake - first configure, then generate and the application can be run. To be more precise:

git clone:https://github.com/fgtelematik/rec_gyro_calib.git

build using CMake:

cd into directory rec_gyro_calib
run: cmake .
make

the executable rec_gyro_calib is generated and can be run with:

./rec_gyro_calib

As a verification method, the following output is generated from the run:

#STARTING TEST WITH SYNTHETIC DATA...
ran_gauss: short-period generator for U[0,1] (period~10(8)) is used!
component(2),converged after (i=100) runs, 35634.374557 with relative tolerance(x 10(6)): 2.341640
component(1),converged after (i=211) runs, 35864.285267 with relative tolerance(x 10(6)): 3274.414659
RESULTS**********************:
for fractional accuracy 0.005000 and acceptance probability 0.900000 the following results are obtained:
Result [1]:minimum acceptance probability of all components is: 0.900024
Result [2]:component: 35864.285267, true value: 35747.234000, relative tolerance( x 10(4)): 32.744147
Result [3]:component: 35634.376179, true value: 35634.458000, relative tolerance( x 10(7)): 22.961073
END OF RESULTS************
# of calls to generator ran_short=472
# of calls to generator ran_long=0
# of calls to generator ran_gauss=210
#END OF TEST WITH SYNTHETIC DATA...
####################################
#START OF TEST WITH EXPERIMENTAL DATA...
loading gyro-data from file: test_data/xsens_gyro.mat
component(1),converged after (i=100) runs, 32777.074957 with relative tolerance(x 10(6)): 2.303523
component(2),converged after (i=100) runs, 32457.804798 with relative tolerance(x 10(6)): 61.975954
component(3),converged after (i=100) runs, 32512.404852 with relative tolerance(x 10(6)): 17.098757
RESULTS**********************:
for fractional accuracy 0.005000 and acceptance probability 0.900000 the following results are obtained:
Result [1]:minimum acceptance probability of all components is: 1.000000
Result [2]:component: 32777.074957, true value: 32777.150460, relative tolerance( x 10(4)): 0.023035
Result [3]:component: 32457.804798, true value: 32459.816527, relative tolerance( x 10(4)): 0.619760
Result [4]:component: 32512.404852, true value: 32511.848940, relative tolerance( x 10(4)): 0.170988
Result [5]:average relative accuracy achieved( x 10(4)): 0.156659
END OF RESULTS************
#END OF TEST WITH EXPERIMENTAL DATA...

There are no external dependencies in the source code and thus the code should compile without problems on any reasonably recent linux distribution. Alternatively all source files are given and the project can be compiled based on the main.cpp file.

The implemented method simply reproduces the simulations for the above mentioned paper but can be easily customized for other uses in particular gyroscopic calibration, of course. There are several ways in which the code can be used: The core algorithm is condensed into two routines which are called in sequence: first the routine seq_update of the class recstats and second seq_accept_probability of the same class. Upon the returned probability value it can be decided whether convergence has been achieved. By default in the code, the file "test_data/xsens_gyro.mat" is read and stored into memory and the algorithm works with this data. The data stems from the output of a gyroscope as given by tedaldi et al. - the data in the file "test_data/xsens_gyro.mat" has the format "timestamp x-component y-component z-component" and the name of the file is read from the file "dnames". So if the same data format is used the name of the file needs only be changed in the file "dnames" and the code can be used without any changes. In all other cases, the user has to supply the above mentioned algorithms with data on his own.

Some parts of the software (not the calibration itself but only the verification of the method) are based on algorithms taken from "Numerical Recipes" by Press et al. meaning that the license is restricted in part to what Press et al. require. However for any direct calibrations for a gyroscope the following license - which, of course can also be found in the source files - applies

License-------------------------------------------------------------------------------------------
Copyright by Technical University Wildau, Research Group Telematics, fgtelematik[at]th-wildau.de
This Software is based on the Publication
"Optimization of MEMS-Gyroscope Calibration using Properties of Sums of Random Variables" by Kupper et al.

the following License applies:

this software may be freely distributed and changed provided that the following two conditions are met:
a) this copyright notice is retained.
b) the software is used for private and scientific or educational purposes only

For commercial usage please contact fgtelematik[at]th-wildau.de for inquiries
End of License--------------------------------------------------------------------------------------
