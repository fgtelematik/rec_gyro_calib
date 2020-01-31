//
// Created by stefan on 30.01.20.
//
// Copyright by Technical University Wildau, Research Group Telematics, fgtelematik[at]th-wildau.de
// This Software is based on the Publication
// "Optimization of MEMS-Gyroscope Calibration using Properties of Sums of Random Variables" by Kupper et al.
//
// the following License applies:
//
// this software may be freely distributed and changed provided that the following two conditions are met:
// a) this copyright notice is retained.
// b) the software is used for private and scientific or educational purposes only
//
// For commercial usage please contact fgtelematik[at]th-wildau.de for inquiries

#ifndef PUBLICATION_RECURSIVE_MEAN_EXPDATA_H
#define PUBLICATION_RECURSIVE_MEAN_EXPDATA_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include "math.h"

class expdata {

private:

public:

    //data structure for storage
    typedef struct state_vector
    {
        double x;
        double y;
        double z;
    } state;

    //parameters for the computations following Tedaldi et al.
    double static_time=0.0;           //length of initial timespan in Tedaldi et al.
    int static_int=0;                 //corresponding index of Tedaldi et al.


    //global data-structure for the data which is read out
    typedef struct dynamic_data {
        double t;
        double x;
        double y;
        double z;
    } dynamic;

    //storage_arrays for the data which has been read
    std::vector<dynamic> gyro_store;  //storage for the gyroscopic data
    state gyro_off;                   //storage for the offset of the gyroscope after the static period
    double  *global_times;            //storage for the readout times
    int data_size;                    //number of data points that have been read

    //*******************************************************************
    //declarations follow below
    //*******************************************************************
    ///******************************************************************
    /// READ_DATA
    /// -----------------------------------------------------------------
    /// loads data from the files that are given by name in the file
    /// "dnames" this data is then stored in the global arrays acc_store
    /// and gyro_store. Additionally a global time-array is used.
    /// -----------------------------------------------------------------
    /// no (direct) input arguments
    /// -----------------------------------------------------------------

    void read_data();

    ///******************************************************************
    /// SET_STATIC_INT
    /// -----------------------------------------------------------------
    /// compute the length of the initial static period by bisection on
    /// the table of input-times
    /// -----------------------------------------------------------------
    /// no input argument
    /// -----------------------------------------------------------------

    void set_static_int();

    ///******************************************************************
    /// STATIC_CALIBRATION
    /// -----------------------------------------------------------------
    /// this routine computes iteratively the relevant statistical
    /// properties from the gyro- and acceleration data which has been
    /// recorded in the initial static period
    /// -----------------------------------------------------------------
    /// no input argument
    /// -----------------------------------------------------------------


    void static_calibration();

};

#endif //PUBLICATION_RECURSIVE_MEAN_EXPDATA_H
