#include "bininfo.h"
#include "h2dLMTempFit.C"
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TString.h>

/*	
	Author: Teemu Kallio
	Version: 1.0
	Date: 23.8.2022

	Program info:

*/

TH1D *hDeltaphi[nbins_mult][nbins_pt][Negap];



void loadingData() {

	TFile *fIn = new TFile ("output/fout_long_range_correlation_projections.root", "read"); // input file

	for (int ic = 0; ic < nbins_mult; ic++) {
		for (int iptt = 0; iptt < nbins_pt; iptt++) {
			for (int ig = 0; ig < Negap; ig++) {

				hDeltaphi[ic][iptt][ig] = (TH1D*) fIn->Get(Form("h2dETAG%02dC%02dPTT%02d", ig, ic, iptt));

			} // ig
		} // iptt
	} // ic

}

void AnaAllCentPtBins() {

	loadingData();
	int ig = 2;
	for (int ic = 1; ic < nbins_mult; ic++) {
		for (int iptt = 0; iptt < nbins_pt; iptt++) {
			cout << Form("ic:%02d_iptt:%02d", ic, iptt) << endl;
			h2dLMTempFitOne(hDeltaphi[ic][iptt][ig],hDeltaphi[0][iptt][ig], ic, iptt); // ic is multiplicity, NOT PERCENTILE
			
		}
	}

}

