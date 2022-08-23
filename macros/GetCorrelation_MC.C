void GetCorrelation_MC(){

 gStyle->SetTitleFont(22,"y");
 gStyle->SetTitleFont(22,"z");
 gStyle->SetLabelFont(22,"x");
 gStyle->SetLabelFont(22,"y");
 gStyle->SetLabelFont(22,"z");
 gStyle->SetTitleSize(0.06,"x");
 gStyle->SetTitleSize(0.06,"y");
 gStyle->SetLabelSize(0.05,"x");
 gStyle->SetLabelSize(0.05,"y");
 gStyle->SetTitleOffset(0.9,"x");
 gStyle->SetTitleOffset(0.8,"y");
 gStyle->SetNdivisions(505);
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 gStyle->SetOptFit(1);

 const int nfiles = 1;
 
 const int nbins_nsel=2; // Event selection criteria, leading particle or jet

 // List of files to be laoded.
 char fname[nfiles][1000]={
	"../../legotrainoutputs_junlee/EPOSLHC_pp_13TeV/AnalysisResults_EPOS_outputoption.root" // merged file 
	// "../../legotrainoutputs_junlee/EPOSLHC_pp_13TeV/AnalysisResults-1338_20200617-1307-EPOSLHC_pp_13TeV.root", // commented when merged file used
	// "../../legotrainoutputs_junlee/EPOSLHC_pp_13TeV/AnalysisResults-1340_20200619-0938-EPOSLHC_pp_13TeV.root", // commented when merged file used
	// "../../legotrainoutputs_junlee/EPOSLHC_pp_13TeV/AnalysisResults-1342_20200622-1128-EPOSLHC_pp_13TeV.root", // commented when merged file used
	// "../../legotrainoutputs_junlee/EPOSLHC_pp_13TeV/AnalysisResults-1344_20200623-0916-EPOSLHC_pp_13TeV.root", // commented when merged file used
	// "../../legotrainoutputs_junlee/EPOSLHC_pp_13TeV/AnalysisResults-1346_20200624-0743-EPOSLHC_pp_13TeV.root" // commented when merged file used
//	"../../legotrainoutputs_junlee/EPOSLHC_pp_13TeV/AnalysisResults-1380_20201107-1307-EPOSLHC_pp_13TeV.root" //has a different folder naming. Needs to be check whether same data as file(s) before.
 };
 
 // Signal names
 char sname[nfiles][nbins_nsel][1000]={
	// {"hRidgeLH", "hRidgeJet"}, // commented when merged file used
	// {"hRidgeLH", "hRidgeJet"}, // commented when merged file used
	// {"hRidgeLH", "hRidgeJet"}, // commented when merged file used
	// {"hRidgeLH", "hRidgeJet"}, // commented when merged file used
	// {"hRidgeLH", "hRidgeJet"}, // commented when merged file used
	{"hRidgeLH", "hRidgeJet"}
 };

  // Background names
 char bname[nfiles][nbins_nsel][1000]={
        // {"hRidgeMixingLH", "hRidgeMixingJet"}, // commented when merged file used
        // {"hRidgeMixingLH", "hRidgeMixingJet"}, // commented when merged file used
        // {"hRidgeMixingLH", "hRidgeMixingJet"}, // commented when merged file used
        // {"hRidgeMixingLH", "hRidgeMixingJet"}, // commented when merged file used
        // {"hRidgeMixingLH", "hRidgeMixingJet"}, // commented when merged file used
        {"hRidgeMixingLH", "hRidgeMixingJet"}
 };

  // Trigger names
 char tname[nfiles][nbins_nsel][1000]={
	// {"hNTrigLH", "hNTrigJet"}, // commented when merged file used
	// {"hNTrigLH", "hNTrigJet"}, // commented when merged file used
	// {"hNTrigLH", "hNTrigJet"}, // commented when merged file used
	// {"hNTrigLH", "hNTrigJet"}, // commented when merged file used
	// {"hNTrigLH", "hNTrigJet"}, // commented when merged file used
	{"hNTrigLH", "hNTrigJet"}
 };

 // Use CMS or ALICE eta definition 
 bool IsCMS[nfiles]={
	// true,
	// false,
	// false,
	// false,
	// false,
	false
 };

 const int nbins_mult=6; // different multiplicity
 const int nbins_pt=15;
 const int nbins_ltpt=7;

 const double Mult_HMT_min[nbins_mult]={
	0,15,35,80,105,0};
 const double Mult_HMT_max[nbins_mult]={
	15,35,80,105,1000,1000};

 // Trigger and associate particle minimum p_T
 const double pTMin[nbins_pt]={
	0.1, 0.5, 1.0, 1.5, 2.0,
	2.5, 3.0, 4.0, 6.0, 0.2,
	0.1, 1.0, 2.0, 3.0, 1.0 };

 // Trigger and associate particle maximum p_T
 const double pTMax[nbins_pt]={
	0.5, 1.0, 1.5, 2.0,  2.5,
	3.0, 4.0, 6.0, 14.0, 14.0,
	1.0, 2.0, 3.0, 4.0, 3.0 };

 const double LTpT[nbins_nsel][nbins_ltpt]={
	{0.2, 3.0, 5.0, 7.0, 9.0, 13.0, 20.0 }, 	// Event selection based on leading particle momentum 
	{0, 10, 20, 30, 40, 50, 60 }		// Event selection based on jet momentum
 };

//'''''''''''''''' Create histograms ''''''''''''''''''// 
 TH1D* hNTrig[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 double NTrig[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];

 TH2D* hRIDGESignal[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TH2D* hRIDGEBackground[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TH2D* hRIDGECorr[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TH1D* hRIDGEBackgroundNorm[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];


 TH1D* hNearEtaDist[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TH1D* hFarEtaDist[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TH1D* hFarPhiDist[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TH1D* hNearPhiDist[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];

 TH1D* hNPhiJet[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TH1D* hNEtaJet[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];

 TH1D* hEtaDist[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TH1D* hPhiDist[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];

 TH1D* hFarPhiDistCMS[nfiles][nbins_nsel][nbins_ltpt][nbins_mult][nbins_pt];
 TDirectory* outputdir;
//'''''''''''''''' Create histograms ''''''''''''''''''//


 for(int i=0;i<nfiles;i++){	 
	auto fin = new TFile(Form("%s",fname[i]),"read");
	outputdir = (TDirectory*)fin->Get("outputoption"); 
	outputdir->cd();



	for(int s=0;s<nbins_nsel;s++){
		THnSparse* H = (THnSparse*)outputdir->Get( sname[i][s] );
		THnSparse* B = (THnSparse*)outputdir->Get( bname[i][s] );
		THnSparse* T = (THnSparse*)outputdir->Get( tname[i][s] );

		if( !H || !T ) continue;

		for(int j=0;j<nbins_ltpt;j++){
			H->GetAxis(5)->SetRangeUser( LTpT[s][j],1e4 );
			T->GetAxis(3)->SetRangeUser( LTpT[s][j],1e4 );
			for(int k=0;k<nbins_mult;k++){

				H->GetAxis(0)->SetRangeUser( Mult_HMT_min[k],Mult_HMT_max[k] );
				B->GetAxis(0)->SetRangeUser( Mult_HMT_min[k],Mult_HMT_max[k] );
				T->GetAxis(0)->SetRangeUser( Mult_HMT_min[k],Mult_HMT_max[k] );

				for(int l=0;l<nbins_pt;l++){
					H->GetAxis(3)->SetRangeUser( pTMin[l],pTMax[l] );
					H->GetAxis(4)->SetRangeUser( pTMin[l],pTMax[l] );

					B->GetAxis(3)->SetRangeUser( pTMin[l],pTMax[l] );
					B->GetAxis(4)->SetRangeUser( pTMin[l],pTMax[l] );

					T->GetAxis(1)->SetRangeUser( pTMin[l],pTMax[l] );
					
					hNTrig[i][s][j][k][l] = (TH1D*)T->Projection( 2 );
					NTrig[i][s][j][k][l] = hNTrig[i][s][j][k][l]->GetBinContent(1);
					if( NTrig[i][j][k][l] == 0 ) continue;

					hRIDGESignal[i][s][j][k][l] = (TH2D*)H->Projection(2,1);
					hRIDGESignal[i][s][j][k][l]->Scale( 1.0/NTrig[i][s][j][k][l] );
					hRIDGESignal[i][s][j][k][l]->GetXaxis()->SetTitle("#Delta #varphi");
					hRIDGESignal[i][s][j][k][l]->GetYaxis()->SetTitle("#Delta #eta");
					hRIDGESignal[i][s][j][k][l]->GetZaxis()->SetTitle("#frac{1}{N_{#font[22]{trig}}} #frac{d^{2}N_{#font[22]{same}}}{d#Delta#eta d#Delta#varphi}");
					hRIDGESignal[i][s][j][k][l]->GetYaxis()->SetTitleSize(0.05);
					hRIDGESignal[i][s][j][k][l]->GetXaxis()->SetTitleOffset(0.75);
					hRIDGESignal[i][s][j][k][l]->GetYaxis()->SetTitleOffset(0.85);
					hRIDGESignal[i][s][j][k][l]->GetZaxis()->SetTitleOffset(1.20);
					hRIDGESignal[i][s][j][k][l]->GetXaxis()->SetLabelSize(0.06);
					hRIDGESignal[i][s][j][k][l]->GetYaxis()->SetLabelSize(0.06);
					hRIDGESignal[i][s][j][k][l]->Scale(1.0,"width");
				
					hRIDGESignal[i][s][j][k][l]->GetXaxis()->CenterTitle();
	                                hRIDGESignal[i][s][j][k][l]->GetYaxis()->CenterTitle();
	                                hRIDGESignal[i][s][j][k][l]->GetZaxis()->CenterTitle();
	                                hRIDGESignal[i][s][j][k][l]->SetLineColor(kBlack);
	                                hRIDGESignal[i][s][j][k][l]->SetNdivisions(505,"Z");
	                                hRIDGESignal[i][s][j][k][l]->SetNdivisions(505,"X");
	                                hRIDGESignal[i][s][j][k][l]->SetNdivisions(505,"Y");

					hRIDGEBackground[i][s][j][k][l] = (TH2D*)B->Projection(2,1);;
					hRIDGEBackground[i][s][j][k][l]->Scale( 1.0/hRIDGEBackground[i][s][j][k][l]->GetMaximum() );

	                                hRIDGEBackground[i][s][j][k][l]->GetXaxis()->SetTitle("#Delta #varphi");
	                                hRIDGEBackground[i][s][j][k][l]->GetYaxis()->SetTitle("#Delta #eta");
	                                hRIDGEBackground[i][s][j][k][l]->GetZaxis()->SetTitle("B(#Delta #varphi, #Delta #eta)/B(0,0)");
	                                hRIDGEBackground[i][s][j][k][l]->GetYaxis()->SetTitleSize(0.05);
	                                hRIDGEBackground[i][s][j][k][l]->GetXaxis()->SetTitleOffset(0.75);
	                                hRIDGEBackground[i][s][j][k][l]->GetYaxis()->SetTitleOffset(0.85);
	                                hRIDGEBackground[i][s][j][k][l]->GetZaxis()->SetTitleOffset(1.20);
	                                hRIDGEBackground[i][s][j][k][l]->GetXaxis()->SetLabelSize(0.06);
	                                hRIDGEBackground[i][s][j][k][l]->GetYaxis()->SetLabelSize(0.06);

	                                hRIDGEBackground[i][s][j][k][l]->GetXaxis()->CenterTitle();
	                                hRIDGEBackground[i][s][j][k][l]->GetYaxis()->CenterTitle();
	                                hRIDGEBackground[i][s][j][k][l]->GetZaxis()->CenterTitle();
	                                hRIDGEBackground[i][s][j][k][l]->SetLineColor(kBlack);
	                                hRIDGEBackground[i][s][j][k][l]->SetNdivisions(505,"Z");
	                                hRIDGEBackground[i][s][j][k][l]->SetNdivisions(505,"X");
	                                hRIDGEBackground[i][s][j][k][l]->SetNdivisions(505,"Y");



					hRIDGECorr[i][s][j][k][l] = (TH2D*)hRIDGESignal[i][s][j][k][l]->Clone(0);
					hRIDGECorr[i][s][j][k][l]->Divide( hRIDGEBackground[i][s][j][k][l] );

	                                hRIDGECorr[i][s][j][k][l]->GetXaxis()->SetTitle("#Delta #varphi");
	                                hRIDGECorr[i][s][j][k][l]->GetYaxis()->SetTitle("#Delta #eta");
	                                hRIDGECorr[i][s][j][k][l]->GetZaxis()->SetTitle("#frac{1}{N_{#font[22]{trig}}} #frac{d^{2}N_{#font[22]{pair}}}{d#Delta#eta d#Delta#varphi}");
	                                hRIDGECorr[i][s][j][k][l]->GetYaxis()->SetTitleSize(0.05);
	
	                                hRIDGECorr[i][s][j][k][l]->GetXaxis()->SetTitleOffset(0.75);
	                                hRIDGECorr[i][s][j][k][l]->GetYaxis()->SetTitleOffset(0.85);
	                                hRIDGECorr[i][s][j][k][l]->GetZaxis()->SetTitleOffset(1.20);

	                                hRIDGECorr[i][s][j][k][l]->GetXaxis()->SetLabelSize(0.06);
	                                hRIDGECorr[i][s][j][k][l]->GetYaxis()->SetLabelSize(0.06);

	                                hRIDGECorr[i][s][j][k][l]->GetXaxis()->CenterTitle();
	                                hRIDGECorr[i][s][j][k][l]->GetYaxis()->CenterTitle();
	                                hRIDGECorr[i][s][j][k][l]->GetZaxis()->CenterTitle();
	                                hRIDGECorr[i][s][j][k][l]->SetLineColor(kBlack);
	                                hRIDGECorr[i][s][j][k][l]->SetNdivisions(505,"Z");
	                                hRIDGECorr[i][s][j][k][l]->SetNdivisions(505,"X");
					hRIDGECorr[i][s][j][k][l]->SetNdivisions(505,"Y");

					hNearEtaDist[i][s][j][k][l] = (TH1D*)hRIDGECorr[i][s][j][k][l]->ProjectionY(Form("hNETAProjY_%d_%d_%d_%d_%d",i,s,j,k,l),6,12,"e");
					hFarEtaDist[i][s][j][k][l] = (TH1D*)hRIDGECorr[i][s][j][k][l]->ProjectionY(Form("hFETAProjY_%d_%d_%d_%d_%d",i,s,j,k,l),22,28,"e");
					hNearPhiDist[i][s][j][k][l] = (TH1D*)hRIDGECorr[i][s][j][k][l]->ProjectionX(Form("hNPhiProjX_%d_%d_%d_%d_%d",i,s,j,k,l),40-3,41+3,"e");


					if( !IsCMS[i] ){
						hFarPhiDist[i][s][j][k][l] = (TH1D*)hRIDGECorr[i][s][j][k][l]->ProjectionX(Form("hFPhiProjX_%d_%d_%d_%d_%d",i,s,j,k,l),40-18,40-16,"e");
						hFarPhiDist[i][s][j][k][l]->Add( hRIDGECorr[i][s][j][k][l]->ProjectionX(Form("hFPhiA_%d_%d_%d_%d_%d",i,s,j,k,l),41+16,41+18,"e"), 1.0 );
						hFarPhiDist[i][s][j][k][l]->Scale( 1.0/0.2 );
					}
					else{
						hFarPhiDist[i][s][j][k][l] = (TH1D*)hRIDGECorr[i][s][j][k][l]->ProjectionX(Form("hFPhiProjX_%d_%d_%d_%d_%d",i,s,j,k,l),1,20,"e");
						hFarPhiDist[i][s][j][k][l]->Add( hRIDGECorr[i][s][j][k][l]->ProjectionX(Form("hFPhiA_%d_%d_%d_%d_%d",i,s,j,k,l),61,80,"e"), 1.0 );
						hFarPhiDist[i][s][j][k][l]->Scale( 1.0/2.0 );
					}

	                                hNEtaJet[i][s][j][k][l] = (TH1D*)hRIDGECorr[i][s][j][k][l]->ProjectionY(Form("hNETAJetProjY_%d_%d_%d_%d_%d",i,s,j,k,l),5,12,"e");
	                                hNPhiJet[i][s][j][k][l] = (TH1D*)hRIDGECorr[i][s][j][k][l]->ProjectionX(Form("hNPhiJetProjX_%d_%d_%d_%d_%d",i,s,j,k,l),40-7,41+7,"e");

					//x = deltaphi, y = deltaeta
					hNearEtaDist[i][s][j][k][l]->Scale( hRIDGECorr[i][s][j][k][l]->GetXaxis()->GetBinWidth(1) );
					hNearEtaDist[i][s][j][k][l]->SetName(Form("hNearEta_%d_%d_%d_%d_%d",i,s,j,k,l));

					hFarEtaDist[i][s][j][k][l]->Scale( hRIDGECorr[i][s][j][k][l]->GetXaxis()->GetBinWidth(1) );
					hFarEtaDist[i][s][j][k][l]->SetName(Form("hFarEta_%d_%d_%d_%d_%d",i,s,j,k,l));
				
					hNearPhiDist[i][s][j][k][l]->Scale( hRIDGECorr[i][s][j][k][l]->GetYaxis()->GetBinWidth(1) );
					hNearPhiDist[i][s][j][k][l]->SetName(Form("hNearPhi_%d_%d_%d_%d_%d",i,s,j,k,l));

					hFarPhiDist[i][s][j][k][l]->Scale( hRIDGECorr[i][s][j][k][l]->GetYaxis()->GetBinWidth(1) );
					hFarPhiDist[i][s][j][k][l]->SetName(Form("hFarPhi_%d_%d_%d_%d_%d",i,s,j,k,l));

					hNearEtaDist[i][s][j][k][l]->GetXaxis()->SetTitle("#Delta #eta");
					hNearEtaDist[i][s][j][k][l]->GetYaxis()->SetTitle("#frac{1}{N_{#font[22]{trig}}} #frac{dN^{#font[22]{pair}}}{d#Delta #eta}");

					hFarEtaDist[i][s][j][k][l]->GetXaxis()->SetTitle("#Delta #eta");
	                                hFarEtaDist[i][s][j][k][l]->GetYaxis()->SetTitle("#frac{1}{N_{#font[22]{trig}}} #frac{dN^{#font[22]{pair}}}{d#Delta #eta}");
                                
					hNearPhiDist[i][s][j][k][l]->GetXaxis()->SetTitle("#Delta #varphi");
	                                hNearPhiDist[i][s][j][k][l]->GetYaxis()->SetTitle("#frac{1}{N_{#font[22]{trig}}} #frac{dN^{#font[22]{pair}}}{d#Delta #varphi}");
                                
					hFarPhiDist[i][s][j][k][l]->GetXaxis()->SetTitle("#Delta #varphi");
	                                hFarPhiDist[i][s][j][k][l]->GetYaxis()->SetTitle("#frac{1}{N_{#font[22]{trig}}} #frac{dN^{#font[22]{pair}}}{d#Delta #varphi}");

        	                        hNEtaJet[i][s][j][k][l]->Scale( hRIDGECorr[i][s][j][k][l]->GetXaxis()->GetBinWidth(1) );
        	                        hNPhiJet[i][s][j][k][l]->Scale( hRIDGECorr[i][s][j][k][l]->GetYaxis()->GetBinWidth(1) );

	                                hNEtaJet[i][s][j][k][l]->Scale( 1.0 / (  8.0*hRIDGECorr[i][s][j][k][l]->GetXaxis()->GetBinWidth(1) ) );
	                                hNPhiJet[i][s][j][k][l]->Scale( 1.0 / ( 16.0*hRIDGECorr[i][s][j][k][l]->GetYaxis()->GetBinWidth(1) ) );

				}
			}
		}
	}
 }

 TFile* fout = new TFile("../outResults_junlee/CorrelationsMC2OutAsMC_merged.root","recreate");

 for(int i=0;i<nfiles;i++){
	for(int s=0;s<nbins_nsel;s++){
		for(int j=0;j<nbins_ltpt;j++){
			for(int k=0;k<nbins_mult;k++){
				for(int l=0;l<nbins_pt;l++){
					if( NTrig[i][s][j][k][l] == 0 ) continue;
					if( !hRIDGECorr[i][s][j][k][l] ) continue;
					hRIDGECorr[i][s][j][k][l]->SetName(Form("hC_%d_%d_%d_%d_%d",i,s,j,k,l));
					hRIDGECorr[i][s][j][k][l]->Write();


					hRIDGESignal[i][s][j][k][l]->SetName(Form("hS_%d_%d_%d_%d_%d",i,s,j,k,l));
					hRIDGEBackground[i][s][j][k][l]->SetName(Form("hB_%d_%d_%d_%d_%d",i,s,j,k,l));
					hRIDGESignal[i][s][j][k][l]->Write();
					hRIDGEBackground[i][s][j][k][l]->Write();

						
					hNearEtaDist[i][s][j][k][l]->Write();
					hFarEtaDist[i][s][j][k][l]->Write();
					hNearPhiDist[i][s][j][k][l]->Write();
					hFarPhiDist[i][s][j][k][l]->Write();
	

	                                hNEtaJet[i][s][j][k][l]->Write();
	                                hNPhiJet[i][s][j][k][l]->Write();
				}
			}
		}
	}
 }



}
