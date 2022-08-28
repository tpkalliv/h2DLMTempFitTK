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
// cat 2.output_LMfits/out_LMtemplate_C0*.txt > out_LMtemplate_allbins.txt

TGraphErrors *grVnCentDep[NH][nbins_pt][Negap];
TGraphErrors *grVnpTDep[NH][nbins_mult][Negap];
void creategraphs(); // create to fill
void writegraphsToroot();// write out root
double xnch[nbins_mult];
double xpt[nbins_pt];

void creategraphs(){

	for (int ic = 0; ic < nbins_mult; ic++) xnch[ic] = (Mult_HMT_min[ic]+Mult_HMT_min[ic])/2.;
	for (int iptt = 0; iptt < nbins_pt; iptt++) xpt[iptt] = (pTMin[iptt] + pTMax[iptt])/2.;

	cout <<"Creating graphs..." << endl;
	for (int ih = 0; ih < NH; ih++) {
		for (int ig = 0; ig < Negap; ig++) {
			for (int iptt = 0; iptt < nbins_pt; iptt++) {
				grVnCentDep[ih][iptt][ig] = new TGraphErrors(nbins_mult,xnch,0,0,0);
            } // iptt	
		} // ig
	} // ih

	for (int ih = 0; ih < NH; ih++) {
		for (int ig = 0; ig < Negap; ig++) {
			for (int ic = 0; ic < nbins_mult; ic++) {
				grVnpTDep[ih][ic][ig] = new TGraphErrors(nbins_pt, xpt,0,0,0);
            } // ic	
		} // ig
	} // ih
}

void makegraphs() {
	creategraphs();
    ifstream infile("out_LMtemplate_allbins.txt");
    cout <<"making graphs..." << endl;
    int i = 0;
    int ic= 0;
    int ipt=0;
    double v2, v2_err;
    double v3, v3_err;
    while (1) {
            if(!infile.good()) break;

            infile >>  ic >> ipt >> v2 >> v2_err >> v3>> v3_err;
            cout << Form("%d %d %.5f %.5f %.5f %.5f\n", ic, ipt ,v2 , v2_err , v3, v3_err);
            grVnCentDep[0][ipt][0]->SetPoint(ic, xnch[ic] , v2);
            grVnCentDep[0][ipt][0]->SetPointError(ic, 0, v2_err);
            grVnCentDep[1][ipt][0]->SetPoint(ic, xnch[ic] , v3);
            grVnCentDep[1][ipt][0]->SetPointError(ic, 0, v3_err);
            grVnpTDep[0][ic][0]->SetPoint(ipt, xpt[ipt] , v2);
            grVnpTDep[0][ic][0]->SetPointError(ipt, 0 , v2_err);
            grVnpTDep[1][ic][0]->SetPoint(ipt, xpt[ipt] , v3);
            grVnpTDep[1][ic][0]->SetPointError(ipt, 0 , v3_err);
            i++;
    }
    cout << "Number of lines = " << i << endl;
    infile.close();
    writegraphsToroot();

}

void writegraphsToroot() {
	TFile *fout = new TFile("out_LMtemplate_allbins.root","recreate");
	fout->cd();

	for (int ih = 0; ih < NH; ih++) {
		for (int ig = 0; ig < Negap; ig++) {
			for (int iptt = 0; iptt < nbins_pt; iptt++) {
				TString grname = Form("grVnCentDepH%02dG%02dPTT%02d",ih, ig, iptt);
				if(grVnCentDep[ih][iptt][ig]) grVnCentDep[ih][iptt][ig]->Write(grname);
            } // iptt	
		} // ig
	} // ih

	for (int ih = 0; ih < NH; ih++) {
		for (int ig = 0; ig < Negap; ig++) {
			for (int ic = 0; ic < nbins_mult; ic++) {
				TString grname = Form("grVnpTDepC%02dH%02dG%02d",ic, ih, ig);
				if(grVnpTDep[ih][ic][ig]) grVnpTDep[ih][ic][ig]->Write(grname);
            } // ic	
		} // ig
	} // ih
	fout->Close();
}	




