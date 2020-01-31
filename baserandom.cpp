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

#include "baserandom.h"

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ranbase::ran_short()
///******************************************************************
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
{
    int j;
    long k;
    static long iy=0;
    static long iv[NTAB];
    double Temp;
    long idum;

    idum=idum_internal[0];
    rcall_internal[0]++;
    if (idum <= 0 || !iy) {
        if (-idum < 1) idum=1;
        else idum = -idum;
        for (j=NTAB+7;j>=0;j--) {
            k=idum/IQ;
            idum=IA*(idum-k*IQ)-IR*k;
            if (idum < 0) idum += IM;
            if (j < NTAB) iv[j] = idum;
        }
        iy=iv[0];
    }
    k=idum/IQ;
    idum=IA*(idum-k*IQ)-IR*k;
    if (idum < 0) idum += IM;
    j=iy/NDIV;
    iy=iv[j];
    iv[j] = idum;
    idum_internal[0]=idum;
    if ((Temp=AM*iy) > RNMX) return RNMX;
    else return Temp;
}

#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

///second generator - long period

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ranbase::ran_long()
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
{
    int j;
    long k;
    static long idum2=123456789;
    static long iy=0;
    static long iv[NTAB];
    double temp;
    long idum;

    idum=idum_internal[1];
    rcall_internal[1]++;
    if (idum <= 0)
    {
        if (-idum < 1) idum=1;
        else idum = -idum;
        idum2=idum;
        for (j=NTAB+7;j>=0;j--)
        {
            k=idum/IQ1;
            idum=IA1*(idum-k*IQ1)-k*IR1;
            if (idum < 0) idum += IM1;
            if (j < NTAB) iv[j] = idum;
        }
        iy=iv[0];
    }

    k=idum/IQ1;
    idum=IA1*(idum-k*IQ1)-k*IR1;
    if (idum < 0) idum += IM1;
    k=idum2/IQ2;
    idum2=IA2*(idum2-k*IQ2)-k*IR2;
    if (idum2 < 0) idum2 += IM2;
    j=iy/NDIV;
    iy=iv[j]-idum2;
    iv[j] = idum;
    if (iy < 1) iy += IMM1;
    idum_internal[1]=idum;
    if ((temp=AM*iy) > RNMX) return RNMX;
    else return temp;
}

#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

void ranbase::initialize_random_generators(int rc)
///******************************************************************
/// INITIALIZE_RANDOM_GENERATORS
/// -----------------------------------------------------------------
/// this routine sets up both random number generators by initializing
/// the internal variables appropriately. A counter for the number of
/// calls to each random number generator is initialized likewise so
/// that it may be checked easily whether period exhaustion might have
/// occurred.
/// -----------------------------------------------------------------
/// rc      - IN: integer which specifies which random number generator
///               is called
/// -----------------------------------------------------------------
{
    int i;

    if(rc==1)
    {printf("ran_gauss: short-period generator for U[0,1] (period~10(8)) is used!\n");
        rchoice_internal=1;
    }
    else if(rc==2)
    {printf("ran_gauss: long-period generator for U[0,1] (period~10(18)) is used!\n");
        rchoice_internal=2;
    }
    else
    {printf("no recognized option for ran_gauss(either 1 or 2 !)\n");
        exit(0);}

    for(i=0;i<2;i++)
    {
        ///to count the number of calls for each respective subroutine
        rcall_internal[i]=0;
        ///the input numbers for the congruential random number generators
        idum_internal[i]=-1;
    }
    rcall_internal[2]=0;
}

void ranbase::get_num_calls()
///******************************************************************
/// GET_NUM_CALLS
/// -----------------------------------------------------------------
/// this routine returns the number of calls to each respective random
/// number generator and returns them so that one may check whether
/// period exhaustion might have occured.
/// -----------------------------------------------------------------
/// no input arguments
/// -----------------------------------------------------------------
{
    printf("# of calls to generator ran_short=%ld\n",rcall_internal[0]);
    printf("# of calls to generator ran_long=%ld\n",rcall_internal[1]);
    printf("# of calls to generator ran_gauss=%ld\n",rcall_internal[2]);
    if(rcall_internal[0]>=short_period)
    {printf("Warning (!) this implies period exhaustion(=%ld) for the generator ran_short !\n",short_period);}
}

double ranbase::ran(int rc)
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
{
    if(rc==0)
    {printf("Error in random number generation: no uniform random number generator set!\n");
        exit(0);}
    else if(rc==1)
    {return ran_short();}
    else
    {return ran_long();}
}

double ranbase::ran_gauss()
///******************************************************************
/// RAN_GAUSS
/// -----------------------------------------------------------------
/// computes a standard normal random number .e.g. X~N(0,1). It uses
/// the box-muller transform to generate the appropriate Random numbers
/// -----------------------------------------------------------------
/// no input arguments
/// -----------------------------------------------------------------
{
    static int iset=0;
    static double gset;
    double fac,rsq,v1,v2;

    rcall_internal[2]++;
    if  (iset == 0) {
        do {
            v1=2.0*ran(rchoice_internal)-1.0;
            v2=2.0*ran(rchoice_internal)-1.0;
            rsq=v1*v1+v2*v2;
        } while (rsq >= 1.0 || rsq == 0.0);
        fac=sqrt(-2.0*log(rsq)/rsq);
        gset=v1*fac;
        iset=1;
        return v2*fac;
    } else {
        iset=0;
        return gset;
    }
}
