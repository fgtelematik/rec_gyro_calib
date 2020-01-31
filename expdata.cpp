//
// Created by stefan on 30.01.20.
//
//
// Created by stefan on 19.06.19.
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

#include "expdata.h"
#include "math.h"
#include "recstats.h"

void expdata::read_data()
///******************************************************************
/// READ_DATA
/// -----------------------------------------------------------------
/// loads data from the files that are given by name in the file
/// "dnames" this data is then stored in the global arrays acc_store
/// and gyro_store. Additionally a global time-array is used.
/// -----------------------------------------------------------------
/// no (direct) input arguments
/// -----------------------------------------------------------------
{
    char fname[150],fname2[150];
    string line;
    dynamic gyro_in;

    //read the name of the files from which the gyroscopic
    // (and potentially) the acceleration data is extracted
    ifstream data2;
    data2.open("dnames");
    data2>>fname;
    data2>>fname2;
    data2.close();

    //source files for acceleration and gyro-values
    ifstream data3,data4;
    //we only need the gyroscopic data
    data4.open(fname2);

    //load the content of the gyro-file into memory
    data_size=0;
    if(data4.is_open())
    {
        printf("loading gyro-data from file: %s\n",fname2);
        while(getline(data4,line))
        {
            istringstream in(line);
            data_size++;
            in >> gyro_in.t;
            in >> gyro_in.x;
            in >> gyro_in.y;
            in >> gyro_in.z;
            gyro_store.push_back(gyro_in);
        }
    }
    else
    {
        printf("could not find file: %s\n",fname2);
        exit(0);
    }

    //store the size of the collected data and fill data into the storage array
    global_times=new double[data_size];
    for(int i=0;i<data_size;i++) global_times[i]=gyro_store[i].t;

    //close the input file stream
    data4.close();
}

void expdata::set_static_int()
///******************************************************************
/// SET_STATIC_INT
/// -----------------------------------------------------------------
/// compute the length of the initial static period by bisection on
/// the table of input-times
/// -----------------------------------------------------------------
/// no input argument
/// -----------------------------------------------------------------
{
    expdata::static_int=mathb::locate(static_time,global_times,data_size);
}

void expdata::static_calibration()
///******************************************************************
/// STATIC_CALIBRATION
/// -----------------------------------------------------------------
/// this routine computes iteratively the relevant statistical
/// properties from the gyro- and acceleration data which has been
/// recorded in the initial static period
/// -----------------------------------------------------------------
/// no input argument
/// -----------------------------------------------------------------
{
    int i;
    double mwa[3],ma[3];

    if(static_int==0)
    {
        printf("the length of the initial static period is not set !\n");
        exit(0);
    }

    for(i=0;i<=static_int;i++)
    {
        mwa[0]=gyro_store[i].x;
        mwa[1]=gyro_store[i].y;
        mwa[2]=gyro_store[i].z;
        for(int j=0;j<3;j++) recstat::mean(ma[j],mwa[j],i+1);
    }
    //store globally the result of the computations
    gyro_off.x=ma[0];
    gyro_off.y=ma[1];
    gyro_off.z=ma[2];

}

