#include "TROOT.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
#include "bininfo.h"

TH1D* hSig;
TH1D* hSub;

void chi2(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t flag){
	double chi2 = 0.0;
	double delta;
	for(int i=0;i<hSig->GetNbinsX();i++){
		delta = hSig->GetBinContent(i+1) - hSub->GetBinContent(i+1) * par[0] -
			( 2.0*par[2]*TMath::Cos( hSig->GetBinCenter(i+1)*2.0 ) +
			2.0*par[3]*TMath::Cos( hSig->GetBinCenter(i+1)*3.0 ) + 1.0 ) * par[1];
		chi2 += pow(delta,2) / 
			( pow(hSig->GetBinError(i+1),2) + pow( hSub->GetBinError(i+1)*par[0],2 ) );
	}
       cout << chi2 << endl;
	f = chi2;
}
// par[0] F
// par[1] G
// par[2] v2
// par[3] v3

const int nFourierTerm = 4;

double Fourier(double *x, double *p){
 double f=0;
 f += p[0];
 for(int i=1;i<nFourierTerm;i++){ f += p[0]*2.0*p[i]*cos(x[0]*(double)i); }
 return f;
}

void h2dLMTempFitOne(int ic, int iptt);
void h2dLMTempFit();

//---------------------------------------
// Test with ALICE data
//---------------------------------------
void h2dLMTempFit(){

 	// Loading data
	TFile *fIn = new TFile ("input/fout_long_range_correlation.root", "read");
	hSig = (TH1D*) fIn->Get("hDphiHM_1");
	hSub = (TH1D*) fIn->Get("hDphiLM_1");
	h2dLMTempFitOne(0, 0);

}
//---------------------------------------
// Two inputs : HM and LM-template, need ic and iptt for multiplicity bin and pt bins
//---------------------------------------
void h2dLMTempFitOne(int ic, int iptt) {

	Double_t Gpar, GparErr;
	Double_t Fpar, FparErr;
	Double_t vn[NH];
	Double_t vnError[NH];
	TF1 *fitvn_s[NH];
	TH1D* hY_a_G;
	
	TF1 *fFourier = new TF1("f1",Fourier,-10.0,10.0,nFourierTerm);

 	TMinuit* gMinuit = new TMinuit(nFourierTerm);
 	
 	Double_t arglist[8];
 	int ierflg = 0;
  	gMinuit->SetFCN(chi2);
	
	gMinuit->mnexcm("SET ERR", arglist, 1, ierflg );
    gMinuit->mnparm(0, "F",     0,1e-5,0.5,2,ierflg);
    gMinuit->mnparm(1, "G",        0,1e-5,0,5,ierflg);
    gMinuit->mnparm(2, "v2",       0,1e-5,0,0.3,ierflg);
    gMinuit->mnparm(3, "v3",       0,1e-5,0,0.3,ierflg);
	gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);

	gMinuit->GetParameter( 0, Gpar, GparErr );
	gMinuit->GetParameter( 1, Fpar, FparErr );
	gMinuit->GetParameter( 2, vn[0], vnError[0] );
	gMinuit->GetParameter( 3, vn[1], vnError[1] );

	double reduced_chi2 = gMinuit->fAmin / ( hSig->GetNbinsX() - gMinuit->fNpar );
    cout << "Saving results in to the ROOT file" << endl;

	// F*Y_LM + G DISTRIBUTION
    hY_a_G = (TH1D*) hSub->Clone(); 
	for (int k = 1; k <= hY_a_G->GetNbinsX(); k++) {
			double value = hY_a_G->GetBinContent(k);
			value = value*Fpar + Gpar;
			hY_a_G->SetBinContent(k, value);
	}
	hY_a_G->SetMarkerStyle(24);

	// SAVINGS (Signal, Fit, F*Y_LM+G)
	TFile *fOut = new TFile (Form("2.output_LMfits/out_LMtemplate_C%02dPTT%02d.root",ic,iptt), "recreate");
	hSig->Write("hDphiHM"); // SIGNAL
	fFourier->Write("fFit_best"); 
	hY_a_G->Write("hY_a_G"); // F*Y_LM+G
	//hFitTotal->Write("hFitTotal");
	//hchiq2->Write();

	// PRODUCING V2 AND V3 HARMONICS AND SAVING 
	Double_t Y_LM_min = hSub->GetMinimum(0);
	Double_t ScaleFYmin = Fpar*Y_LM_min;
	// Saving vn results to text file
	fstream file;
	TString outtextname = Form("2.output_LMfits/out_LMtemplate_C%02dPTT%02d.txt",ic,iptt);
    file.open(outtextname.Data(), ios_base::out);

	for (Int_t n=0; n<NH; n++)
	{
		TString formula = Form("[0]*(1 + 2*[1]*TMath::Cos(%d*x)) + [2]",n+2);					
		fitvn_s[n]= new TF1(Form("fit_s_v%d", n+2),formula, -TMath::Pi()/2.0, 3.0*TMath::Pi()/2.0);													
		fitvn_s[n]->SetParameter(1, vn[n]);
		fitvn_s[n]->SetParameter(0, Gpar);
		fitvn_s[n]->SetParameter(2, ScaleFYmin);
		fitvn_s[n]->Write();
	}
	

	TString texttmp = Form("%d %d %.5f %.5f %.5f %.5f\n",ic, iptt, vn[0], vnError[0], vn[1], vnError[1]);
	file << texttmp.Data();
	file.close();

	TCanvas *c2 = new TCanvas ("hFit", "hHM", 1);
	hSig->SetMinimum(hSig->GetMinimum()*0.98);
	hSig->Draw();
	hY_a_G->SetLineColor(2);
	hY_a_G->Draw("same");
	fitvn_s[0]->Draw("same");
	fitvn_s[1]->Draw("same");
	//hFitTotal->SetLineColor(4);
	//hFitTotal->Draw("same");
}	
