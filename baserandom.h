//
// Author: Stefan Kupper, stefan.kupper[at]th-wildau.de
//
// Created by stefan on 26.08.19.
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

#ifndef PUBLICATION_RECURSIVE_MEAN_BASERANDOM_H
#define PUBLICATION_RECURSIVE_MEAN_BASERANDOM_H

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class ranbase
        {
        private:

        public:

    const long short_period=100000000;
    long idum_internal[2];
    long rcall_internal[3];
    int rchoice_internal=0;


    double ran_short();

///**********************************************************************
/// RAN_SHORT
/// -----------------------------------------------------------------
/// this is the "short"-period random number generator from the book
/// Numerical Recipes of press et al., with maximal period ~10(8). It
/// generates uniform random numbers on the Interval [0,1]. It is
/// important to note that idum needs to be negative on intializing
/// while only been changed through the routine thereafter.
/// -----------------------------------------------------------------
/// no input arguments
/// -----------------------------------------------------------------

    double ran_long();

///******************************************************************
/// RAN_LONG
/// -----------------------------------------------------------------
/// this is the long-period random number generator from the book
/// Numerical Recipes of press et al., with maximal period ~10(18)
/// which effectively combines two congruential in a very effective way.
/// It generates uniform random numbers on the Interval [0,1]. It is
/// important to note that idum needs to be negative on intializing
/// while only been changed through the routine thereafter.
/// -----------------------------------------------------------------
/// no input arguments
/// -----------------------------------------------------------------

    void initialize_random_generators(int rc);

///******************************************************************
/// INITIALIZE_RANDOM_GENERATORS
/// -----------------------------------------------------------------
/// this routine sets up both random number generators by initializing
/// the internal variables appropriately. A counter for the number of
/// calls to each random number generator is initialized likewise so
/// that it may be checked easily whether period exhaustion might have
/// occurred. Call with rc=1 for short-peroid generator and with rc=2
/// for long period random number generator
/// -----------------------------------------------------------------
/// rc      - IN: integer which specifies which random number generator
///               is called
/// -----------------------------------------------------------------

    void get_num_calls();

///******************************************************************
/// GET_NUM_CALLS
/// -----------------------------------------------------------------
/// this routine returns the number of calls to each respective random
/// number generator and returns them so that one may check whether
/// period exhaustion might have occured.
/// -----------------------------------------------------------------
/// no input arguments
/// -----------------------------------------------------------------

    double ran(int rc);

///******************************************************************
/// RAN
/// -----------------------------------------------------------------
/// this is a wrapper for the calls to the uniform random number
/// generators. It calls the short-period random number generator if
/// rc is equal to 1 and the long period random generator otherwise.
/// it is used in connection with the global choice for the uniform
/// random number generator
/// -----------------------------------------------------------------
/// rc      - IN: integer which specifies which random number generator
///               is called
/// -----------------------------------------------------------------

    double ran_gauss();

///******************************************************************
/// RAN_GAUSS
/// -----------------------------------------------------------------
/// computes a standard normal random number .e.g. X~N(0,1). It uses
/// the box-muller transform to generate the appropriate Random numbers
/// -----------------------------------------------------------------
/// no input arguments
/// -----------------------------------------------------------------


        };



#endif //PUBLICATION_RECURSIVE_MEAN_BASERANDOM_H
