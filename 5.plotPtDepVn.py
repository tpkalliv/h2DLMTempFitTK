# comparison to ALICE or ATLAS SP methods
import numpy as np
import ROOT

import scipy
from scipy import interpolate

import sys
sys.path.append("JPyPlotRatio");


import JPyPlotRatio

f = ROOT.TFile("out_LMtemplate_allbins.root","read");

#grVnCentDepH%02dG%02dPTT%02d",ih, ig, iptt
obsTypeStr  = ["grVnpTDepC00H00G00","grVnpTDepC02H00G00",
		"grVnpTDepC04H00G00","grVnpTDepC00H00G01"
		];

obsTypeStrEta1  = ["grVnpTDepC01H00G00","grVnpTDepC03H00G00",
		"grVnpTDepC05H00G00","grVnpTDepC01H00G01"
		];
obsN = len(obsTypeStr);
plabel = ["" for x in range(obsN)]
for i in range(0,obsN):
	gr = f.Get("{}".format(obsTypeStr[i]));
	plabel[i] = "{}".format(gr.GetTitle());
	print(plabel[i])		

print(plabel)
dataTypeStr = ["EPOS"];
dataTypePlotParams = [
        {'plotType':'data','color':'red','fmt':'o','markersize':5.0},
        {'plotType':'data','color':'#e580ff','fmt':'X','fillstyle':'none','markersize':5.5},
        {'plotType':'data','color':'#44aa11','fmt':'h','markersize':4.0},
        {'plotType':'data','color':'red','fmt':'D','fillstyle':'none','markersize':5.0},
        {'plotType':'data','color':'cyan','fmt':'d','fillstyle':'none','markersize':5.5}
];
modelTypePlotParams = [
	{'plotType':'theory','color':'#0051a2','linecolor':'#0051a2','alpha':0.5,'linestyle':'solid'},
	{'plotType':'theory','color':'#e580ff','linecolor':'#e580ff','alpha':0.5,'linestyle':'dotted'},
	{'plotType':'theory','color':'red','linecolor':'red','alpha':0.5,'linestyle':'solid'}
];
def RemovePoints(arrays, pointIndices):
	return tuple([np.delete(a,pointIndices) for a in arrays]);

# define panel/xaxis limits/titles
ny = 2;
nx = 2;
xlimits = [(0,3.)];
ylimits = [(-0.1,0.1),(-0.15,0.15)];


xtitle = ["$pT$"];
ytitle = ["$v_n$","$v_n$"];
ytitleRight = ["$v_n$"];
# Following two must be added
toptitle = "pp $\\sqrt{s}$ = 13 TeV"; # need to add on the top
#dataDetail = "$0.2 < p_\\mathrm{T} < 5.0\\,\\mathrm{GeV}/c$\n$|\\eta| < 0.8$";

plot = JPyPlotRatio.JPyPlotRatio(panels=(ny,nx),panelsize=(5,5),
	disableRatio=[0,1],
	rowBounds=ylimits, #only one row, add the shared ylims
	colBounds={0:xlimits[0],1:xlimits[0]}, #two columns, set xlimit for both of them
	ratioBounds={0:(-1,3),1:(-1,3)},
	#panelLabel={i:label for i,label in enumerate(plabel)},
	panelLabelLoc=(0.07,0.88),panelLabelSize=11,
	#panelLabel={0: plabel[0], 1:plabel[1]},
	#panelScaling={3:5},
	panelLabelAlign="left",
	systPatchWidth = 0.03,
	legendPanel=0,legendLoc=(0.70,0.26),legendSize=9,ylabel={0:ytitle[0],1:ytitle[1]});
plot.GetPlot().text(0.5,0.05,xtitle[0],size=plot.axisLabelSize,horizontalalignment="center");
plot.GetAxes(1).yaxis.tick_right();
plot.GetAxes(3).yaxis.tick_right();

#plot.EnableLatex(True);



#plot.EnableLatex(True);


#scale1 = {4:10,5:10};

plot.GetAxes(0).plot([0,50],[0,0],linestyle=":",color="gray");
plot.GetAxes(1).plot([0,50],[0,0],linestyle=":",color="gray");
plot.GetAxes(2).plot([0,50],[0,0],linestyle=":",color="gray");
plot.GetAxes(3).plot([0,50],[0,0],linestyle=":",color="gray");


for i in range(0,obsN):
	gr = f.Get("{}".format(obsTypeStr[i]));
	grEta1 = f.Get("{}".format(obsTypeStrEta1[i]));
	grEta1.Print()
	plot1 = plot.Add(i,gr,**dataTypePlotParams[0]);
	plot1 = plot.Add(i,grEta1,**dataTypePlotParams[1]);
	#plot.Ratio(plotModel,plot1);

f.Close();




plot.GetPlot().text(0.53,0.80,toptitle,fontsize=9);
#plot.GetPlot().text(0.30,0.75,dataDetail,fontsize=9);

plot.Plot();
plot.Show();

#plot.GetRatioAxes(3).remove();

plot.Save("figs/VnPtDep.pdf");