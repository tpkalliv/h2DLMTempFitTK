import numpy as np
import ROOT
import matplotlib.pyplot as plt

import scipy
from scipy import interpolate

import sys
sys.path.append("JPyPlotRatio");


import JPyPlotRatio


'''

For drawing figs on EPOS projection files

TO run type: python3 1.output_projections/fout_long_range_correlation_projections.root <rootfile_name>

'''



file = sys.argv[1];

print(file);


f = ROOT.TFile(file,"read");

dataTypePlotParams = {'plotType':'data','color':'b','fmt':'o', 'linestyle':'dashdot', 'markersize':5.0};

nrow = 1;
ncol = 1;
title = "EPOS pp data projection";
datatitle = "$\\sqrt{s}$ = 13TeV"; # EPOS
#paramsinfo = ["80 < $N_{ch}$ < 105", "1.8 < $\\Delta\\eta$ < 2.0", "1.0 < $p_T$ < 1.5 GeV"]; # HM
paramsinfo = ["0 < $N_{ch}$ < 15", "1.8 < $\\Delta\\eta$ < 2.0", "1.0 < $p_T$ < 1.5 GeV"]; # LM
xtitle = ["$\\Delta\\varphi (\\mathrm{rad})$"]; # EPOS
ytitle = ["$\\frac{1}{N_{trig}}\\frac{dN^{pairs}}{d\\Delta\\varphi}$"]; # EPOS

plot = JPyPlotRatio.JPyPlotRatio(panels=(nrow,ncol),
	panelsize=(12,12), # change the size
	#rowBounds=ylimits,  # for nrow
	#colBounds=xlimits,  # for ncol
	#panelLabel=plables,  # nrowxncol
	disableRatio=[0],
	panelLabelLoc=(0.1,0.87),panelLabelSize=10,panelLabelAlign="left",
	legendPanel=0,
	legendLoc=(0.16,0.75),legendSize=11, xlabel=xtitle,ylabel=ytitle);


gr = f.Get("{}".format("h2dETAG01C00PTT02")); #file[2].readString()));
data = plot.Add(0,gr,**dataTypePlotParams);
plot.GetPlot().text(0.20,0.83,title,fontsize=11);
plot.GetPlot().text(0.38,0.83,datatitle,fontsize=11);
plot.GetPlot().text(0.38,0.80,paramsinfo[0],fontsize=11);
plot.GetPlot().text(0.38,0.77,paramsinfo[1],fontsize=11);
plot.GetPlot().text(0.38,0.74,paramsinfo[2],fontsize=11);
plot.Plot();
plt.savefig("input/" + "h2dETAG01C00PTT02" + ".png", dpi=300);
plot.Show();