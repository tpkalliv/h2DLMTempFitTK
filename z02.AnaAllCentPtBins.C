//#include "bininfo.h"
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

// 


void loadingData() {

	TFile *fIn = new TFile ("1.output_projections/fout_long_range_correlation_projections_legotrain_EPOSLHC_pp13TeV.root", "read"); // input file

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
	for (int ig = 0; ig < Negap; ig++) {
		for (int ic = 0; ic < nbins_mult; ic++) {
			for (int iptt = 0; iptt < nbins_pt; iptt++) {
				cout << "-------------------------------------------------" << endl;
				cout << Form("ic:%02d_iptt:%02d", ic, iptt) << endl;
				h2dLMTempFitOne(hDeltaphi[ic][iptt][ig],hDeltaphi[0][iptt][ig], ic, iptt, ig); // ic is multiplicity, NOT PERCENTILE
				cout << "-------------------------------------------------" << endl;
			}
		}
	}

}

