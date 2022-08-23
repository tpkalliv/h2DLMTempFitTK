const int nbins_mult = 6; // different multiplicity
const int nbins_pt = 15;

double Mult_HMT_min[nbins_mult] = {0,15,35,80,105,0};
double Mult_HMT_max[nbins_mult] = {15,35,80,105,1000,1000};

// Trigger and associate particle minimum p_T
double pTMin[nbins_pt] = {
0.1, 0.5, 1.0, 1.5, 2.0,
2.5, 3.0, 4.0, 6.0, 0.2,
0.1, 1.0, 2.0, 3.0, 1.0
};

// Trigger and associate particle maximum p_T
double pTMax[nbins_pt] =	{
0.5, 1.0, 1.5, 2.0,  2.5,
3.0, 4.0, 6.0, 14.0, 14.0,
1.0, 2.0, 3.0, 4.0, 3.0
};

const int Negap = 4;
double etamin[Negap] = {1.4,1.5,1.6,1.7};
