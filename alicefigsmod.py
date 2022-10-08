import numpy as np
import ROOT
import matplotlib.pyplot as plt

import scipy
from scipy import interpolate

import sys
sys.path.append("JPyPlotRatio");


import JPyPlotRatio

'''
For figs

To run ALICE data: python3 alicefigsmod.py input/fout_corr_pp13TeV.root
To run EPOS data: python3 alicefigsmod.py outResults_junlee/h2DCorrelations_merged_legotrain_EPOSLHC_pp13TeV.root
'''

file = sys.argv[1];
# data set is manual
outfigname = file.replace(".root","_fit.png")

f = ROOT.TFile(file,"read");
dataTypePlotParams = [
        {'cmap':'viridis'},
        {'cmap':'viridis'}
];


# define panel/xaxis limits/titles
nrow = 1;
ncol = 1;
xlimits = {0:(-1.5,4.5)};
ylimits = {0:(-1.8,1.8)};
#rlimits = [(0.99,1.01)];
#ytitle = ["$\\Delta\\varphi (\\mathrm{rad})$"]; # ALICE
#xtitle = ["$\\Delta\\eta$"]; # ALICE
xtitle = ["$\\Delta\\varphi (\\mathrm{rad})$"]; # EPOS
ytitle = ["$\\Delta\\eta$"]; # EPOS

#datatitle = "ALICE pp $\\sqrt{s}$ = 13TeV"; # ALICE
datatitle = "EPOS pp $\\sqrt{s}$ = 13TeV"; # EPOS
#paramsinfo = ["Signal 0-0.1%, 1.0 < $p_T$ < 2.0 GeV", "Signal 60-100%, 1.0 < $p_T$ < 2.0 GeV"]; # ALICE
paramsinfo = ["Signal 0-0.1%, 1.0 < $p_T$ < 1.5 GeV", "Signal 60-100%, 1.0 < $p_T$ < 1.5 GeV"]; # EPOS

#histnames = ["hC_6_0_0_2_11","hC_0_0_0_4_11"]; # ALICE
histnames = ["hC_0_0_0_3_2","hC_0_0_0_0_2"]; # EPOS


plot = JPyPlotRatio.JPyPlotRatio(panels=(nrow,ncol),
	panelsize=(12,12), # change the size
	rowBounds=ylimits,  # for nrow
	colBounds=xlimits,  # for ncol
	#panelLabel=plables,  # nrowxncol
	#ratioBounds=rlimits,# for nrow
	disableRatio=[0],
	#ratioPlot=True,
	panelLabelLoc=(0.1,0.87),panelLabelSize=10,panelLabelAlign="left",
	legendPanel=0,
	legendLoc=(0.16,0.75),legendSize=11, xlabel=xtitle[0],ylabel=ytitle[0]);

#plot.EnableLatex(True);

plotMatrix = np.empty((nrow,ncol),dtype=int);

gr = f.Get("{}".format(histnames[0]));
data = plot.Add2D(0,gr,**dataTypePlotParams[0]); # ,label=TypeName[d]);
plot.GetPlot().text(0.38,0.83,datatitle,fontsize=11);
plot.GetPlot().text(0.38,0.81,paramsinfo[0],fontsize=11);
plot.Plot();
plt.savefig("input/" + histnames[0] + ".png", dpi=300);

'''
grr = f.Get("{}".format(histnames[1]));
data = plot.Add2D(0,grr,**dataTypePlotParams[1]); # ,label=TypeName[d]);
plot.GetPlot().text(0.38,0.83,datatitle,fontsize=11);
plot.GetPlot().text(0.38,0.81,paramsinfo[1],fontsize=11);
plot.Plot();
plt.savefig("input/" + histnames[1] + ".png", dpi=300);
'''
f.Close();
