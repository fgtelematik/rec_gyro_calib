//
// Author: Stefan Kupper, stefan.kupper[at]th-wildau.de
//
// Created by stefan on 26.08.19.
// refurbished on 29.01.20
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

#include "recstats.h"
#include <math.h>


void recstat::mean(double &mm, double x, int n)
///******************************************************************
/// MEAN
/// -----------------------------------------------------------------
/// this subroutine calculates the mean incrementally by using only
/// the current value x of the time series at index n to update the
/// value of the mean mm accordingly
/// -----------------------------------------------------------------
/// mm    - INOUT: the value of the mean which is updated by each call
/// x     - IN   : the current input value of the time series
/// n     - IN   : the index of the input value (being the n-th data
///                point)
/// -----------------------------------------------------------------
{
    double nd1,nd2;

    nd1=(double) (n);
    nd2=(double) (n-1);

    mm=(nd2*mm +x)/nd1;
}

void recstat::var(double &var, double &mm, double x, int n)
///******************************************************************
/// VAR
/// -----------------------------------------------------------------
/// computes the variance of the given time series using the input
/// data point x at time of call n
/// -----------------------------------------------------------------
/// var   - INOUT: the value of the variance updated in each call
/// mm    - IN   : the current value of the mean
/// x     - IN   : the current input value of the time series
/// n     - IN   : the index of the input value (being the n-th data
///                point)
/// -----------------------------------------------------------------
{
    double nd1,nd2,nd;

    if(n<=1)
    {
       var=0.0;
    }
    else
    {
        nd=(double) (n);
        nd1=(double) (n-1);
        nd2=(double) (n-2);

        var=(nd2/nd1)*var+(nd/(nd1*nd1))*pow((x-mm),2.0);
    }

}

void recstat::seq_update(double stat[], double x, int n)
///******************************************************************
/// SEQ_UPDATE
/// -----------------------------------------------------------------
/// computes the sequential update of the relevant statistical
/// variables, that is computes in sequence mean, variance, mean of
/// mean and variance of mean
/// -----------------------------------------------------------------
/// stat  - INOUT: storage array for all relevant values
/// x     - IN   : newly collected datapoint
/// n     - IN   : the index of the input value (being the n-th data
///                point)
/// -----------------------------------------------------------------
{
    mean(stat[0],x,n);                //mean
    var(stat[1],stat[0],x,n);         //variance
    mean(stat[2],stat[0],n);          //mean of mean
    var(stat[3],stat[2],stat[0],n);   //variance of mean
}

double recstat::seq_accept_probability(double stat[], double f)
///******************************************************************
/// SEQ_ACCEPT_PROBABILITY
/// -----------------------------------------------------------------
/// computes the sequential update of the acceptance probability using
/// the known and desired fractional accuracyn and returns the output
/// as functional return variable.
/// -----------------------------------------------------------------
/// stat  - INOUT: storage array for all relevant statistical values
/// f     - IN   : required fractional accuracy
/// -----------------------------------------------------------------
{
    return (erf((f*stat[2])/(sqrt(2*stat[3]))));
}