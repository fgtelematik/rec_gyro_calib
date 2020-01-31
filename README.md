# rec_gyro_calib
Implementation of a recursive and effective method for gyroscope sensor calibration.

These source files implement the algorithm for the gyroscope calibration by recursively computing key statistical properties of the time series of gyroscopic output data. The underlying mathematical approach is described in the paper "Optimization of MEMS-Gyroscope calibration using properties of sums of random variables" by Kupper et al.

To use the algorithm simply go to the appropriate Home Directory and run cmake - first configure, then generate. Once these steps have been successfully completed, simply run make and the executable rec_gyro_calib has been generated for use.

Alternatively all source files are given without any external dependency and the project can be compiled based on the main.cpp file.

The implemented method simply reproduces the simulations for the above mentioned paper but can be easily customized for other uses in particular gyroscopic calibration, of course.

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
