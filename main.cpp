//
// Author: Stefan Kupper, stefan.kupper[at]th-wildau.de
//
// Created by stefan on 26.08.19.
// refurbished on 30.01.20
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

#include "baserandom.h"
#include "recstats.h"
#include "expdata.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

//Details of the algorithm and especially the mathematical basis of the algorithm can be found in the paper:
// "Optimization of MEMS-Gyroscope Calibration using Properties of Sums of Random Variables" by Kupper et al.

int main()
{
    int i;
    int icheck[3];
    double rd[2],a,b;
    double tmean[3];
    double tvariance[2];
    double uran[4],gran[4];
    double pval[3],beta[3];
    double min,prop_chosen,fractional_chosen;
    ranbase randy;
    recstat recstats;
    expdata exp;

    //***********************************************
    //+++++++++++++++++++++++++++++++++++++++++++++++
    //***********************************************
    //First part: test with synthetic data is made:
    printf("#STARTING TEST WITH SYNTHETIC DATA...\n");

    //************************************************
    //set up and initialize the random number generator
    randy.initialize_random_generators(1);
    //*************************************************

    //*************************************************
    //set the desired acceptance probability(=prop_chosen)
    //and the chosen fractional accuracy(=fractional_chosen)
    //of the result
    prop_chosen=0.9;
    fractional_chosen=0.005;
    //*************************************************


    //*************************************************
    //parameters for the test with synthetic data
    //
    tmean[0]=35747.234;  //mean of gaussian random variable
    tmean[1]=35634.458;  //mean of uniform random variable
    tvariance[0]=987.34; //variance of gaussian random variable
    tvariance[1]=979.56; //variance of uniform random variable
    b=sqrt(12*tvariance[1]);
    a=tmean[1]-0.5*b;
    icheck[0]=0;icheck[1]=0;   //test-for-convergence parameters
    //************************************************

    //************************************************
    //iteration loop: run until mean and variance are
    //have been sufficiently converged...
    //************************************************
    i=1;
    for(;;)
    {
        //generate synthetic data -> gauss random and uniform random respectively
        rd[0]=tmean[0]+tvariance[0]*randy.ran_gauss();
        rd[1]=a+randy.ran_short()*b;
        //update the statistical properties with the computed value
        recstats.seq_update(gran,rd[0],i);
        recstats.seq_update(uran,rd[1],i);
        //compute the acceptance probability for each component and the lowest overall
        i++;
        min=1.1;
        pval[0]=recstats.seq_accept_probability(gran,fractional_chosen);
        pval[1]=recstats.seq_accept_probability(uran,fractional_chosen);
        for(int j=0;j<2;j++) { if(min>=pval[j]) min=pval[j];}  //store the lowest acceptance proability

        //store the mean of means for later usage
        beta[0]=gran[2];
        beta[1]=uran[2];

        //for test purposes: check and store at which iteration stage convergence is achieved
        for(int j=0;j<2;j++)
        {
            if(pval[j]>=prop_chosen && i>=100 && icheck[j]==0)
            {
                printf("component(%d),converged after (i=%d) runs, %f with relative tolerance(x 10(6)): %f\n",j+1,i,beta[j],1.0e6*fabs((beta[j]-tmean[j]))/tmean[j]);
                icheck[j]=1;
            }
        }
        if(min>=prop_chosen && i>=100) break;
    }

    //return results
    printf("RESULTS**********************:\n");
    printf("for fractional accuracy %f and acceptance probability %f the following results are obtained:\n",fractional_chosen, prop_chosen);
    printf("Result [1]:minimum acceptance probability of all components is: %f\n",min);

    //print results(with scale factors...)
    for(int j=0;j<2;j++) {pval[j]=pow(1.0e3,j)*1.0e4; icheck[j]=4+3*j;}
    //loop over the components...
    for(int j=0;j<2;j++)
    {
        printf("Result [%d]:component: %f, true value: %f, relative tolerance( x 10(%d)): %f\n",(j+2),beta[j],tmean[j],icheck[j],pval[j]*fabs((beta[j]-tmean[j])/tmean[j]));
    }
    printf("END OF RESULTS************\n");

    //gather runtime statistics for the random number generators...
    randy.get_num_calls();
    //
    printf("#END OF TEST WITH SYNTHETIC DATA...\n");
    printf("####################################\n");
    //***********************************************
    //+++++++++++++++++++++++++++++++++++++++++++++++
    //***********************************************
    //Second part: test with experimental data is made
    printf("#START OF TEST WITH EXPERIMENTAL DATA...\n");

    //load the experimentally collected data from tedaldi et al. into memory
    exp.read_data();
    exp.static_time=50.0;      //length of initial static period taken from tedaldi et al.
    exp.set_static_int();      //load the length of the initial period

    exp.static_calibration();  //compute the gyroscopic offsets statically

    //*************************************************
    //now-as before-we make these gyroscopic calculations
    //dynamically...
    double xstat[4],ystat[4],zstat[4];
    double gyro[3];

    //use the reference value...
    tmean[0]=exp.gyro_off.x;
    tmean[1]=exp.gyro_off.y;
    tmean[2]=exp.gyro_off.z;
    for(int j=0;j<3;j++) icheck[j]=0;

    i=1;
    for(;;)
    {
        //copy the obtained data into the work-array
        gyro[0]=exp.gyro_store[i-1].x;
        gyro[1]=exp.gyro_store[i-1].y;
        gyro[2]=exp.gyro_store[i-1].z;
        //update the statistical properties with the computed value
        recstats.seq_update(xstat,gyro[0],i);
        recstats.seq_update(ystat,gyro[1],i);
        recstats.seq_update(zstat,gyro[2],i);
        //compute the acceptance probability for each component and the lowest overall
        i++;
        min=1.1;
        pval[0]=recstats.seq_accept_probability(xstat,fractional_chosen);
        pval[1]=recstats.seq_accept_probability(ystat,fractional_chosen);
        pval[2]=recstats.seq_accept_probability(zstat,fractional_chosen);
        for(int j=0;j<3;j++) { if(min>=pval[j]) min=pval[j];}  //store the lowest acceptance proability

        //store the mean of means for later usage(!)
        beta[0]=xstat[2];
        beta[1]=ystat[2];
        beta[2]=zstat[2];

        //for test purposes: check and store at which iteration stage convergence is achieved
        for(int j=0;j<3;j++)
        {
            if(pval[j]>=prop_chosen && i>=100 && icheck[j]==0)
            {
                printf("component(%d),converged after (i=%d) runs, %f with relative tolerance(x 10(6)): %f\n",j+1,i,beta[j],1.0e6*fabs((beta[j]-tmean[j]))/tmean[j]);
                icheck[j]=1;
            }
        }
        if(min>=prop_chosen && i>=100) break;
    }
    printf("RESULTS**********************:\n");
    printf("for fractional accuracy %f and acceptance probability %f the following results are obtained:\n",fractional_chosen, prop_chosen);
    printf("Result [1]:minimum acceptance probability of all components is: %f\n",min);

    double gyro_total=0,comp_total=0.0;

    for(int j=0;j<3;j++)
    {
        pval[j]=1.0e4;
        icheck[j]=4;
        gyro_total+=tmean[j];   //average all reference components together
        comp_total+=beta[j];    //average all computed components together
        printf("Result [%d]:component: %f, true value: %f, relative tolerance( x 10(%d)): %f\n",(j+2),beta[j],tmean[j],icheck[j],pval[j]*fabs((beta[j]-tmean[j])/tmean[j]));
    }
    printf("Result [5]:average relative accuracy achieved( x 10(4)): %f\n",1.0e4*(fabs(gyro_total-comp_total)/gyro_total));
    printf("END OF RESULTS************\n");
    //***********************************************
    //+++++++++++++++++++++++++++++++++++++++++++++++
    //***********************************************
    printf("#END OF TEST WITH EXPERIMENTAL DATA...\n");

    return 0;

}