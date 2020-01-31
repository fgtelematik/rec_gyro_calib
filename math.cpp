//
// Created by stefan on 30.01.20.
//
//
// Author: Stefan Kupper, stefan.kupper[at]th-wildau.de
//
// Copyright by Technical University Wildau, Research Group Telematics, fgtelematik[at]th-wildau.de
// This Software is based on the Publication
// "Optimization of MEMS-Gyroscope Calibration using Properties of Sums of Random Variables" by Kupper et al.
//
// these Algorithms are based in part on the Algorithms presented and given by "Numerical Recipes" by Press et al. hence
// the license applicable to the part of the code given in this particular source file is subject to the licensing
// condition of Press et al. -> If any usage beyond pure scientific research is desired please contact press et al.
// accordingly.
//
// Subject to the licensing condition of Press et al., the following License applies:
//
// this software may be freely distributed and changed provided that the following two conditions are met:
// a) this copyright notice is retained.
// b) the software is used for private and scientific or educational purposes only
//
// For commercial usage please contact fgtelematik[at]th-wildau.de for inquiries

#include "math.h"

int mathb::check_bounds(double x,double x1, double x2)
///******************************************************************
/// CHECK_BOUNDS
/// -----------------------------------------------------------------
/// checks whether a given number x lies within a given intervall
/// which in turn is given by the input-numers x1,x2 such that
/// it is referred to [x1:x2]
/// -----------------------------------------------------------------
/// x    - IN: input number
/// x1   - IN: first endpoint of interval
/// x2   - IN: second endpoint of interval
/// -----------------------------------------------------------------
{
    double xt,abs1=1.0,abs2=1.0;
    if((x-x1)!=0.0) abs1=fabs(x-x1);
    if((x-x2)!=0.0) abs2=fabs(x-x2);
    xt=((x-x1)/abs1)*((x-x2)/abs2);

    if(xt<=0) {return 1;}
    else {return 0;}

}

int mathb::locate(double x, double xx[], int n)
///******************************************************************
/// LOCATE
/// -----------------------------------------------------------------
/// computes the position of an entry via bisection on the table
/// indices of the tabulated array xx[]. this array may be either
/// top-down or vice versa.
/// -----------------------------------------------------------------
/// x    - IN: input number
/// xx   - IN: array containing the ordered, tabulated values
/// n    - IN: size of the array
/// -----------------------------------------------------------------
/// !!! NOTE: this subroutine is used under the licensing conditions
/// !!! of numerical recipes of Press et al.
{
    int ju,jm,jl;
    int ascnd;

    if(check_bounds(x,xx[0],xx[n-1])==0)
    {printf("locate: value=%f is not in [%f:%f]!\n",x,xx[0],xx[n-1]);
        return 0;}

    jl=0;
    ju=n;
    ///determine whether the array is ordered from
    ///low to high or vice versa;
    ascnd=(xx[n-1] >= xx[0]);

    while (ju-jl > 1)
    {
        jm=(ju+jl) >> 1;
        ///replace either the lower or the upper limit
        ///as fits to the ordering of the array
        if ((x >= xx[jm]) == ascnd) jl=jm;
        else ju=jm;
    }
    if(x == xx[0])
    {return 0;}
    else if(x == xx[n-1])
    {return (n-2);}
    else
    {return jl;}

}
