#include "bininfo.h"
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TString.h>

/*	
	Author: Teemu Kallio
	Version: 1.0
	Date: 23.8.2022

	Program info:
	Long-range correlation projections
*/

TH2D *h2D[nbins_mult][nbins_pt];
TH1D *hDeltaphi[nbins_mult][nbins_pt][Negap];
void load2DHistos(TString inputname);
void makeLongRangeCorr();
void writeToRoot(TString outname);

// Program starts here
void projection() {

	TString inputname = "outResults_junlee/h2DCorrelations_merged_legotrain_EPOSLHC_pp13TeV.root";
	load2DHistos(inputname);
	makeLongRangeCorr();
	TString outname = "1.output_projections/fout_long_range_correlation_projections_legotrain_EPOSLHC_pp13TeV.root";
	writeToRoot(outname);

	/* ptt=2, ic=0,4 (LM,HM) 
	TCanvas *c1 = new TCanvas ("hLM", "hLM", 1);
	h2D[0][2]->Draw("colz");
	TCanvas *c2 = new TCanvas ("hHM", "hHM", 1);
	h2D[4][2]->Draw("colz");
	*/
}

void load2DHistos(TString inputname = "outResults_junlee/h2DCorrelations_merged_legotrain_EPOSLHC_pp13TeV.root"){

	TFile *fIn = new TFile (inputname, "read"); // input file

	for (int ic = 0; ic < nbins_mult; ic++) {
		for (int iptt = 0; iptt < nbins_pt; iptt++) {

			//	hC_file_jet_0thbin_centrality_pT (pT is the trigger particle)
			//	Associate and trigger particle has the same momentum range and the range is given by (pT_min[], pT_maxı[])
			h2D[ic][iptt] = (TH2D*) fIn->Get(Form("hC_0_0_0_%d_%d", ic, iptt));

		}
	}
}

/* 
	How makeLongRangeCorr() works

	For every TH2D histogram:
		- We save the [a, 1.8] and [-a, -1.8] gaps into two TH1D histograms using ProjectionY()-function
			* here variable a is [1.4, 1.7] or [-1.4, -1.7]
		- Then negative eta gap histogram is added to the positive eta gap histogram
*/
void makeLongRangeCorr() {
	// Creating projections for every variation of histogram
	for (int ic = 0; ic < nbins_mult; ic++){
		for (int iptt = 0; iptt < nbins_pt; iptt++){
				for(int ig = 0; ig < Negap; ig++){ 
					// Positive eta gap
					hDeltaphi[ic][iptt][ig] = (TH1D*) h2D[ic][iptt]->ProjectionX(Form("h2dETAG%02dC%02dPTT%02d", ig, ic, iptt), h2D[ic][iptt]->GetYaxis()->FindBin(etamax), h2D[ic][iptt]->GetYaxis()->FindBin(etamin[ig]));
					// Negative eta gap gets added to pos eta gap histos
					TH1D *hTemp =             (TH1D*) h2D[ic][iptt]->ProjectionX(Form("h2dETAG%02dC%02dPTT%02d", ig, ic, iptt), h2D[ic][iptt]->GetYaxis()->FindBin(-etamax), h2D[ic][iptt]->GetYaxis()->FindBin(-etamin[ig]));
					hDeltaphi[ic][iptt][ig]->Add(hTemp, 1);
				} // ig pos
		} // iptt
	} // ic
}

void writeToRoot(TString outname = "1.output_projections/fout_long_range_correlation_projections.root") {

	TFile* fOut = new TFile (outname, "recreate");
	TString htitle;
	for (int ic = 0; ic < nbins_mult; ic++){
		for (int iptt = 0; iptt < nbins_pt; iptt++){
				for(int ig = 0; ig < Negap; ig++){ 
					htitle = Form("%.0f< N_{ch}<%.0f, %.3f< p_{T} <%.3f, %.1f< |#Delta#eta| <%.1f",Mult_HMT_min[ic],Mult_HMT_max[ic],pTMin[iptt],pTMax[iptt], etamin[ig], etamax);
					hDeltaphi[ic][iptt][ig]->SetTitle(htitle);
					hDeltaphi[ic][iptt][ig]->Write(Form("h2dETAG%02dC%02dPTT%02d", ig, ic, iptt));

				} // ig 
		} // iptt
	} // ic
}

