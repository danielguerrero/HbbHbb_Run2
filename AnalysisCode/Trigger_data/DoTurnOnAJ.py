import ROOT
import copy
from math import *
import array

runName      = ""
fitName      = "_1B"

ffName = "fittedFunctions3_.h"
f = open( ffName , 'w')

ROOT.gROOT.LoadMacro("tdrstyleTrigger.C")
ROOT.gROOT.LoadMacro("test.h")
ROOT.setTDRStyle()

minTurnOn_funct   = 0
maxTurnOn_funct   = 1.05

minRatio    = 0.8
maxRatio    = 1.2

functionMin = 80
functionMax = 500

ped = "function"

title = "aaa"

var           ="Jet_pt[3]"
trigger       ="ntrgObjects_hltQuadPFCentralJetLooseID45>=4"
binning       =(40,0,120)
preselection  ="1"

maxev=100000000

def getTitle(fileName):
    file_ = ROOT.TFile.Open(fileName)
    file_.cd()
    name = file_.GetListOfKeys().First().GetName()
    canvas =  file_.Get(name)
    pad =  canvas.GetPrimitive("unten")
    title =  pad.GetPrimitive("Ratio").GetXaxis().GetTitle()
    return title
    
def DivideTGraph(num,den):
    Ns_den   = den.GetN()
    Xs_den   = den.GetX()
    Ys_den   = den.GetY()
    EXLs_den = den.GetEXlow()
    EXHs_den = den.GetEXhigh()
    EYLs_den = den.GetEYlow()
    EYHs_den = den.GetEYhigh()

    print "den.GetN()",den.GetN()
    print "num.GetN()",num.GetN()

    Ys_num   = num.GetY()
    EYLs_num = num.GetEYlow()
    EYHs_num = num.GetEYhigh()

    print "DivideTGraph: new"
    
    bins   = [ i for i in range( Ns_den) if Ys_den[i]>0]

    print "Xs_den",Xs_den
    Xs_new   = [ Xs_den[i] for i in bins]
    print "Xs_new",Xs_new
    Ys_new   = [ Ys_num[i]/(Ys_den[i]) for i in bins]
    EXLs_new = [ EXLs_den[i] for i in bins]
    EXHs_new = [ EXHs_den[i] for i in bins]
    [ EYLs_num[i] for i in bins]
    [ ((EYLs_num[i]/(Ys_num[i]+1E-3))**2) for i in bins]
    [ Ys_new[i]*sqrt((EYLs_num[i]/(Ys_num[i]+1E-3))**2) for i in bins]
    EYLs_new = [ Ys_new[i]*sqrt((EYLs_num[i]/(Ys_num[i]+1E-3))**2+(EYHs_den[i]/(Ys_den[i]+1E-3))**2) for i in bins]
    EYHs_new = [ Ys_new[i]*sqrt((EYHs_num[i]/(Ys_num[i]+1E-3))**2+(EYLs_den[i]/(Ys_den[i]+1E-3))**2) for i in bins]

    print "DivideTGraph: len"

    n = len(Xs_new)

    print "DivideTGraph: array"

    Xs_new = array.array('f',Xs_new)
    Ys_new = array.array('f',Ys_new)
    EXLs_new = array.array('f',EXLs_new)
    EXHs_new = array.array('f',EXHs_new)
    EYLs_new = array.array('f',EYLs_new)
    EYHs_new = array.array('f',EYHs_new)

    print "DivideTGraph: ratio"

    ratio = ROOT.TGraphAsymmErrors(n, Xs_new, Ys_new, EXLs_new, EXHs_new, EYLs_new, EYHs_new)
    print "DivideTGraph: done"

    return ratio

def makeHistos():
    tree = ROOT.TChain("tree")
    tree.Add(fileName)
    print "fileName=",fileName
    print "var=",var
    print "trigger=",trigger
    print "preselection=",preselection
    print "binning=",str(binning)
    tree.Draw(var+">>num"+str(binning),str(preselection+"&&"+trigger),"",maxev)
    print "Draw:\t",var+">>num"+str(binning),str(preselection+"&&"+trigger)
    num = ROOT.gDirectory.Get("num")
    num = copy.copy(num)
    tree.Draw(var+">>den"+str(binning),str(preselection),"",maxev)
    print "Draw:\t",var+">>den"+str(binning),str(preselection)
    den = ROOT.gDirectory.Get("den")
    den = copy.copy(den)
    print "num,den = ",num.Integral(),den.Integral()
    return num,den
    
    

def getMCAndData(fileName):
    file_ = ROOT.TFile.Open(fileName)
    file_.cd()
    name = file_.GetListOfKeys().First().GetName()
    canvas =  file_.Get(name)
    pad =  canvas.GetPrimitive("oben")
    mystack =  pad.GetPrimitive(name)
    MC_tmp =  mystack.GetStack().Last()
    data_tmp =  pad.GetPrimitive("noData")
    MC =  MC_tmp.Clone("MC")
    data =  data_tmp.Clone("data")
    MC.SetTitle("MC")
    data.SetTitle("data")
    MC.GetXaxis().SetTitle(title)
    data.GetXaxis().SetTitle(title)
    MC.SetMarkerStyle(20)
    data.SetMarkerStyle(20)
    MC.SetMarkerColor(ROOT.kBlack)
    data.SetMarkerColor(ROOT.kBlack)
    MC = copy.copy(MC)
    data = copy.copy(data)
    file_.Close()
    return MC,data

def doRatio(num, den, option=""):
#    mratio =  den.Clone("mratio")
#    mratio.SetTitle("Ratio")
#    mratio.Reset()
#    if option is "b":
#        mratio.Divide(num,den,1,1,"b")
#    else:
#        mratio.Divide(num,den)
#    return mratio
        mratio = ROOT.TGraphAsymmErrors()
        mratio.SetMarkerColor(ROOT.kBlack)
        mratio.SetLineColor(ROOT.kBlack)
        mratio.SetName("ratio")
        mratio.GetXaxis().SetTitle(title)
#        mratio = histo.Clone(triggerName+"_eff")
#        mratio.Divide(histo,inclusive,1.,1.,"B")
#        mratio.Divide(histo,inclusive,1.,1.,"cl=0.683 b(1,1) mode")
#        print num.GetNbinsX(),num.GetXaxis().GetXmin(),num.GetXaxis().GetXmax()
#        print den.GetNbinsX(),den.GetXaxis().GetXmin(),den.GetXaxis().GetXmax()
        for i in range(num.GetNbinsX()):print num.GetBinLowEdge(i),
        print ""
        for i in range(den.GetNbinsX()): print den.GetBinLowEdge(i),
        print ""

        for i in range(den.GetNbinsX()+2):
            if den.GetBinContent(i)<=0:
                den.SetBinError(i,1.)
                den.SetBinContent(i,0)
                num.SetBinContent(i,0)
#        for i in range(num.GetNbinsX()+2):
#            if num.GetBinContent(i)<=0:
#                num.SetBinError(i,10.)
#                num.SetBinContent(i,1.E-7)
        for i in range(den.GetNbinsX()+2):
            if num.GetBinContent(i)>den.GetBinContent(i):
                print "WARNING!"
                print num.GetBinContent(i),den.GetBinContent(i)
                num.SetBinContent(i,den.GetBinContent(i))
#            num.SetBinContent(i,num.GetBinContent(i))
#            den.SetBinContent(i,den.GetBinContent(i))

        mratio.Divide(num,den,"cl=0.683 b(1,1) mode")
        print "End ratio. bins:",mratio.GetN()," num:",num.GetNbinsX()," den:",den.GetNbinsX()
        return mratio

def confidenceInterval(graph, function):
    fit = function.Clone("fit")
    fitUp = function.Clone("fitUp")
    fitUp.SetLineColor(ROOT.kRed)
    fitUp.SetLineStyle(2)
    fitDown = function.Clone("fitDown")
    fitDown.SetLineStyle(2) 
    print "Fit1"
    fit.FixParameter(4,0)
    fit.FixParameter(5,0)
    graph.Fit(fit,"","",fit.GetXmin(),fit.GetXmax())
#    fit.ReleaseParameter(4)
#    fit.ReleaseParameter(5)
    print "Fit2"
    graph.Fit(fit,"","",fit.GetXmin(),fit.GetXmax()) #was WW
    print "Fit3"
    graph.Fit(fit,"","",fit.GetXmin(),fit.GetXmax())
    parameters = [0]*function.GetNpar()
    for i in range(len(parameters)):
        parameters[i] = fit.GetParameter(i)

    parametersUp = parameters[:]
    parametersDown = parameters[:]

    looseRange=10.
    tightRange=10.

    print "Up/down fit"

    ## FixParameters
    for i in range(len(parameters)):
#        fit.ReleaseParameter(i)
#        function.SetParLimits(4,0,10)

#        if i in [0]: #  x0 can go down
#            pass
#        elif i in [3]: # global efficiency can go up
#            pass
        if i in [0,2]: #  x0 can go down
            pass
        else: # fix the other parameters
            fit.FixParameter( i, parameters[i] )
    fitResult = graph.Fit(fit,"SEV0","",fit.GetXmin(),fit.GetXmax())
    for i in range(len(parameters)):

        parameters[i] = fit.GetParameter(i)
      #  if i in [0]: #  x0 can go down
      #      parametersUp[i] = fit.GetParameter(i)   + fitResult.LowerError(i)
      #      parametersDown[i] = fit.GetParameter(i) + fitResult.UpperError(i)
        # el
       # if i in [1]: # check-me!
      #      parametersUp[i] = fit.GetParameter(i)   + fitResult.UpperError(i)
       #     parametersDown[i] = fit.GetParameter(i) + fitResult.LowerError(i)
       # el
        if i in [2]: # check-me!
            parametersUp[i] = fit.GetParameter(i)   + min(fitResult.LowerError(i),-0.02)
            parametersDown[i] = fit.GetParameter(i) + max(fitResult.UpperError(i),+0.02)
        #elif i in [3]: # global efficiency can go up
        #parametersUp[i] = fit.GetParameter(i)   + min(fitResult.LowerError(i),-0.02)*nsigma
        #parametersDown[i] = fit.GetParameter(i) + max(fitResult.UpperError(i),+0.02)*nsigma
        else: # fix the other parameters
            parametersUp[i] = fit.GetParameter(i)
            parametersDown[i] = fit.GetParameter(i)

    if (fit.GetParameter(3)<0): ##if [3]<0, I have to exchange [0],[1] min/max
        for i in [0,1]:
            print "CHANGE"
            print parametersUp[i],parametersDown[i]
            tmp = parametersUp[i]
            parametersUp[i] = parametersDown[i]
            parametersDown[i] = tmp
            print parametersUp[i],parametersDown[i]

    for i in range(len(parameters)):
        print "i=,",i,"\t",parameters[i],"\t",parametersUp[i],"\t",parametersDown[i]
        fit.SetParameter(i,parameters[i])
        fitUp.SetParameter(i,parametersUp[i])
        fitDown.SetParameter(i,parametersDown[i])

    return fit,fitUp,fitDown



def doPlots():

    num,den =  makeHistos()
    turnOn = doRatio(num,den,"b")

    #function = ROOT.TF1("turnonPt","1-(0.5-0.5*erf( (x-[0])/[1]))*([3])-[2] ",functionMin,functionMax)
#    function = ROOT.TF1("turnonPt","1-(0.5-0.5*TMath::Erf( (x-[0])/[1]))*[3]-[2] ",functionMin,functionMax)
    function = ROOT.TF1("turnonPt","1-(0.5-0.5*TMath::Erf( (x-[0])/[1]))*[3]-[2] ",functionMin,functionMax)
#    function = ROOT.TF1("turnonPt","1-(0.5-0.5*TMath::Erf( (x-[0])/([1])*(x-[0]>[5]) + ((x-[0])/([1]+[4]) + [5]*(1/[1]+[4]-1/[1]))*(x-[0]<=[5]) ))*[3]-[2] ",functionMin,functionMax)
#    function = ROOT.TF1("turnonPt","1-(0.5-0.5*TMath::Erf( (x-[0])*(1+[4]*x**2)/([1]+[5]*x**2)))*([3])-[2] ",functionMin,functionMax)
#    function = ROOT.TF1("turnonPt","(0.5+0.5*TMath::Erf( (x-[0])*(x-[0]>[5])/[1] + (x-[0])*(x-[0]<[5])/[2] + [5]*(1/[1]-1/[2])*(x-[0]<[5]) ))*[4]+[3] ",functionMin,functionMax)
#    function = ROOT.TF1("turnonPt","1-(0.5-0.5*TMath::Erf( (x-[0])/[1]))*([3])-(0.5-0.5*TMath::Erf( (x-[4])/[5]))*([6])-[2]  ",functionMin,functionMax)

#    function = ROOT.TF1("turnonPt","TMath::Erf( (x-[0])/[1]*(([4]+[5]*x)) )*[2]-[3]",functionMin,functionMax)

    print "Using:",parametersTurnOn_funct
    function.SetParameters(*parametersTurnOn_funct)
#    function.SetParLimits(1,0,100)
    function.SetParLimits(2,0,1)
    function.SetParLimits(3,-1,2)
#    function.SetParLimits(4,0,1)
#    function.SetParLimits(5,0,1)
    function.SetLineWidth(2)


    TurnOn_funct = function.Clone("TurnOn_funct")

    c1 = ROOT.TCanvas("c1","",1280,720)

    TurnOn_funct,TurnOn_functUp,TurnOn_functDown = confidenceInterval(turnOn,TurnOn_funct)

    turnOn.SetMaximum(maxTurnOn_funct)
    turnOn.SetMinimum(minTurnOn_funct)
    turnOn.GetXaxis().SetTitle(title)
    turnOn.GetYaxis().SetTitle("Efficiency")

    turnOn.Draw("AP")
    TurnOn_funct.Draw("same")
    TurnOn_functUp.Draw("same")
    TurnOn_functDown.Draw("same")

    #c1.SaveAs("turnOn_"+ped+".C")
    c1.SaveAs("turnOn_"+ped+"_"+runName+fitName+".pdf")
    #c1.SaveAs("turnOn_"+ped+".root")
    f.write(('TF1* %s = new TF1("%s","'%(ped,ped)           + str(TurnOn_funct.GetExpFormula("P"))+'");\n'))
    f.write(('TF1* %sUp = new TF1("%sUp","'%(ped,ped)       + str(TurnOn_functUp.GetExpFormula("P"))+'");\n'))
    f.write(('TF1* %sDown = new TF1("%sDown","'%(ped,ped)   + str(TurnOn_functDown.GetExpFormula("P"))+'");\n'))
	

ROOT.gROOT.SetBatch()
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)


minRatio    = 0.5
maxRatio    = 1.5

fileName    ="SingleMuonSkimmed"+runName+".root"
#fileName     = "root://cmseos.fnal.gov//store/user/lpchbb/HeppyNtuples/V23/SingleMuon" + runName + ".root"
#fileName    = "ZvvHighPt_V20_SingleMuon.root"
#fileName    = "ZvvHighPt_V20_TT_TuneCUETP8M1_13TeV-powheg-pythia8.root"
#fileData    = "/gpfs/ddn/srm/cms/store/user/arizzi/VHBBHeppyV20/SingleMuon/VHBB_HEPPY_V20_SingleMuon__Run2015D-16Dec2015-v1/160210_081323/0000/tree*.root"

#preselection = "HLT_BIT_HLT_IsoMu24_v  && Vtype==2  && CSVsorted[2]>0.6"
preselection = "HLT_BIT_HLT_IsoMu24_v&& Vtype==2 && CMVAVsorted[3]>0.185&& diHiggs"#s && LPt_mass > 400"
parametersTurnOn_funct = ()
#################### L1 low #########################
parametersTurnOn_funct = (200,100,0.01,1,1E-3,1E-3)

Nbins       = 30#50
functionMin = 10#100
functionMax = 320#200
var             = "Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3]"
#var             = "Jet_pt[1]+Jet_pt[2]+Jet_pt[3]"
trigger         = "ntrgObjects_hltQuadCentralJet30>=1"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_DoubleJet_L1l"
title           = "p^{T}_{2}+p^{T}_{3}+p^{T}_{4}"
#doPlots()

#################### L1 high#########################
parametersTurnOn_funct = (200,100,0.01,1,1E-3,1E-3)

Nbins       = 15#50
functionMin = 100#200
functionMax = 400#350
var             = "Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3]"
#var             = "Jet_pt[1]+Jet_pt[2]+Jet_pt[3]"
trigger         = "ntrgObjects_hltQuadCentralJet30>=1"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_DoubleJet_L1h"
title           = "p^{T}_{2}+p^{T}_{3}+p^{T}_{4}"
#doPlots()
##################### CaloPt4 low ###et######################
parametersTurnOn_funct = (100,20,0.01,1,1E-3,1E-3)

Nbins       = 30#60
functionMin = 15#25
functionMax = 145#85
var             = "Jet_pt[3]"
#var             = "Sum$(Pt4(Jet_pt,Jet_eta,Jet_puId,3,Iteration$,Length$))"
preselection    = preselection + "&&"+ trigger
trigger         = "ntrgObjects_hltQuadCentralJet30>=4"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_DoubleJet_CaloPt4l"
title           = "p^{T}_{4}"
#doPlots()

##################### CaloPt4 high ###et######################
parametersTurnOn_funct = (100,20,0.01,1,1E-3,1E-3)

Nbins       = 15
functionMin = 20
functionMax = 110
var             = "Jet_pt[3]"
#var             = "Sum$(Pt4(Jet_pt,Jet_eta,Jet_puId,3,Iteration$,Length$))"
#preselection    = preselection + "&&"+ trigger
trigger         = "ntrgObjects_hltQuadCentralJet30>=4"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_DoubleJet_CaloPt4h"
title           = "p^{T}_{4}"
#doPlots()


##################### CaloPt2 #########################
parametersTurnOn_funct = (100,20,0.01,1,1E-3,1E-3)

Nbins       = 30
functionMin = 60
functionMax = 120
var             = "Jet_pt[1]"
#var             = "Sum$(Pt4(Jet_pt,Jet_eta,Jet_puId,1,Iteration$,Length$))"
preselection    = preselection + "&&"+ trigger
trigger         = "ntrgObjects_hltDoubleCentralJet90>=2"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_DoubleJet_CaloPt2"
title           = "p^{T}_{2}"
#doPlots()



##################### CSV3 #########################
parametersTurnOn_funct = (100,20,0.01,1,1E-3,1E-3)
Nbins       = 24
functionMin =  0.4 #CSVL =  0.460 
functionMax = 1
#var             = "-log(1-Jet_btagCSV[aJCidx[0]])"
#var             = "Jet_btagCSV[aJCidx[0]]"
var             = "MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)))"
#var             = "Sum$(CSV(Jet_btagCSV,Jet_eta,Jet_puId,2,Iteration$,Length$))"
preselection    = preselection + "&&"+ trigger
#trigger         = "ntrgObjects_hltTripleCSV0p67>=3"
trigger = "ntrgObjects_hltBTagCaloCSVp087Triple>=3"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_DoubleJet_CSV3"
title           = "CSV_{3}"
#doPlots()

###################### PFPt4 ########################
parametersTurnOn_funct = (0,20,0.01,1,1E-3,1E-3)

Nbins       = 30
functionMin = 20#25
functionMax = 80#125
var             = "Jet_pt[3]"
#var             = "Sum$(Pt4(Jet_pt,Jet_eta,Jet_puId,3,Iteration$,Length$))"
preselection    = preselection + "&&"+ trigger
trigger         = "ntrgObjects_hltQuadPFCentralJetLooseID30>=4"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_DoubleJet_PFPt4"
title           = "p^{T}_{4}"
#doPlots()

###################### PFPt2 ########################
parametersTurnOn_funct = (0,20,0.01,1,1E-3,1E-3)

Nbins       = 50
functionMin = 80
functionMax = 380
var             = "Jet_pt[1]"
#var             = "Sum$(Pt4(Jet_pt,Jet_eta,Jet_puId,1,Iteration$,Length$))"
preselection    = preselection + "&&"+ trigger
trigger         = "ntrgObjects_hltDoublePFCentralJetLooseID90>=2"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_DoubleJet_PFPt2"
title           = "p^{T}_{2}"
#doPlots()

################### L1 low ###################
parametersTurnOn_funct = (200,100,0.01,1)

Nbins           =  20#50
functionMin     =  100#100
functionMax     =  500#200
var             = "Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3]"
#var             = "Jet_pt[1]+Jet_pt[2]+Jet_pt[3]"
trigger         = "ntrgObjects_hltQuadCentralJet45>=1"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_QuaJet_L1l"
title           = "p^{T}_{1}+p^{T}_{2}+p^{T}_{3}+p^{T}_{4}"
doPlots()

#################### L1 high #########################
parametersTurnOn_funct = (200,100,0.01,1)

Nbins           = 20#50
functionMin     =  300#120
functionMax     =  600#270
var             = "Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3]"
#var             = "Jet_pt[1]+Jet_pt[2]+Jet_pt[3]"
trigger         = "ntrgObjects_hltQuadCentralJet45>=1"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_QuaJet_L1h"
title           = "p^{T}_{1}+p^{T}_{2}+p^{T}_{3}+p^{T}_{4}"
doPlots()
##################### CaloPt4 low #########################
parametersTurnOn_funct = (100,20,0.01,1)

Nbins       = 8#140#70
functionMin = 47.5#30#35
functionMax = 63.5#105
var             = "Jet_pt[3]"
#var             = "Sum$(Pt4(Jet_pt,Jet_eta,Jet_puId,3,Iteration$,Length$))"
preselection    = preselection + "&&"+ trigger
trigger         = "ntrgObjects_hltQuadCentralJet45>=4"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_QuaJet_CaloPt4l"
title           = "p^{T}_{4}"
doPlots()


##################### CaloPt4 high #########################
parametersTurnOn_funct = (100,20,0.01,1)

Nbins       = 15#140#70
functionMin = 40#30#35
functionMax = 100#100#105
var             = "Jet_pt[3]"
#var             = "Sum$(Pt4(Jet_pt,Jet_eta,Jet_puId,3,Iteration$,Length$))"
#preselection    = preselection + "&&"+ trigger
trigger         = "ntrgObjects_hltQuadCentralJet45>=4"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_QuaJet_CaloPt4h"
title           = "p^{T}_{4}"
doPlots()


##################### CSV3 #########################
parametersTurnOn_funct = (100,20,0.01,1)
Nbins       = 10#80#24
functionMin = 0.6#0.2#0.4 #CSVL =  0.460 
functionMax = 1.0#1.0#1.0
#var             = "-log(1-Jet_btagCSV[aJCidx[0]])"
#var             = "Jet_btagCSV[aJCidx[0]]"
var             = "MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)))"
#var              = "CSVsorted[2]"
#var              = "Jet_btagCSV[2]"
#var             = "Sum$(CSV(Jet_btagCSV,Jet_eta,Jet_puId,2,Iteration$,Length$))"
preselection    = preselection + "&&"+ trigger
# old ! trigger         = "ntrgObjects_hltTripleCSV0p67>=3"
trigger = "ntrgObjects_hltBTagCaloCSVp087Triple>=3"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_QuaJet_CSV3"
title           = "CSV_{3}"
doPlots()

###################### PFPt4 ########################
parametersTurnOn_funct = (0,20,0.01,1)

Nbins       = 10#100#50
functionMin = 40#30#40
functionMax = 160#130#140
var             = "Jet_pt[3]"
#var             = "Sum$(Pt4(Jet_pt,Jet_eta,Jet_puId,3,Iteration$,Length$))"
preselection    = preselection + "&&"+ trigger
trigger         = "ntrgObjects_hltQuadPFCentralJetLooseID45>=4"
binning         = (Nbins,functionMin,functionMax)
ped             = "QaD_QuaJet_PFPt4"
title           = "p^{T}_{4}"
doPlots()

##############################################
##f.Close()
