#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TF1.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLine.h>


// Plot cosmetics
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos = 11;

#include "CMS_lumi.h"
#include <iostream>

void
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  if( iPosX == 0  ) relPosX = 0.14;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }
  else if ( iPeriod==0 )
    {
      lumiText += lumi_sqrtS;
    }

  std::cout << lumiText << endl;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11);
      latex.SetTextSize(cmsTextSize*t);
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }

  pad->cd();

  float posX_=0;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
        {
          posX_ =   l + 0.045*(1-l-r)*W/H;
          posY_ = 1-t - 0.045*(1-t-b);
          float xl_0 = posX_;
          float yl_0 = posY_ - 0.15;
          float xl_1 = posX_ + 0.15*H/W;
          float yl_1 = posY_;
          TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
          TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
          pad_logo->Draw();
          pad_logo->cd();
          CMS_logo->Draw("X");
          pad_logo->Modified();
          pad->cd();
        }
      else
        {
          latex.SetTextFont(cmsTextFont);
          latex.SetTextSize(cmsTextSize*t);
          latex.SetTextAlign(align_);
          latex.DrawLatex(posX_, posY_, cmsText);
          if( writeExtraText )
            {
              latex.SetTextFont(extraTextFont);
              latex.SetTextAlign(align_);
              latex.SetTextSize(extraTextSize*t);
              latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
            }
        }
    }
  else if( writeExtraText )
    {
      if( iPosX==0)
        {
          posX_ =   l +  relPosX*(1-l-r);
          posY_ =   1-t+lumiTextOffset*t;
        }
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, extraText);
    }
  return;
}


std::string itoa(int i) 
{
  char res[10];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void BackgroundPrediction_Kinematic_Bern(double plot_lo, double plot_hi, double rebin,
                                             double fit_lo, double fit_hi, 
					     double crystalball_mean_lo, double crystalball_mean_hi,
                                             double crystalball_width_lo, double crystalball_width_hi,
                                             double crystalball_exp_lo, double crystalball_exp_hi,
                                             double crystalball_switch_lo, double crystalball_switch_hi,
					      /*double gaussexp_mean_lo, double gaussexp_mean_hi,
                                             double gaussexp_width_lo, double gaussexp_width_hi,
                                             double gaussexp_exp_lo, double gaussexp_exp_hi,	
                                             */std::string hist="h_mX_SB_kinFit", 
                                             std::string log="lin")
{

  gROOT->SetStyle("Plain");
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gStyle->SetOptStat(0000);
  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV  = "35.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  
  TFile *f_data=new TFile("Histograms_BTagall.root");
  TH1F *h_mX_SR=(TH1F*)f_data->Get(hist.c_str());
  h_mX_SR->Rebin(rebin);
  double nEventsSR=((TH1F*)f_data->Get("h_mX_SR_kinFit"))->GetSumOfWeights();
  
  RooRealVar *x;
  x=new RooRealVar("x", "m_{X} (GeV)", plot_lo, plot_hi);
  RooDataHist pred("pred", "Data", RooArgList(*x), h_mX_SR);
/*

  bg_p0=new RooRealVar("bg_p0", "bg_p0", 0., 10.);
  bg_p1=new RooRealVar("bg_p1", "bg_p1", 0., 10.);
  bg_p2=new RooRealVar("bg_p2", "bg_p2", 0., 12.);

i*/  bg_p3=new RooRealVar("bg_p3", "bg_p3", 5.);
  bg_p3->setConstant(1);
  bg_p4=new RooRealVar("bg_p4", "bg_p4", -10., 10.);
  	
  bg_p5=new RooRealVar("bg_p5", "bg_p5", -10., 10.);
  bg_p6=new RooRealVar("bg_p6", "bg_p6", -10., 10.);
  bg_p7=new RooRealVar("bg_p7", "bg_p7", -10., 10.);
  bg_p8=new RooRealVar("bg_p8", "bg_p8", -10., 5.);
  /*//bg_p9=new RooRealVar("bg_p9", "bg_p9", 0., 5.);
  // bg_p10=new RooRealVar("bg_p10", "bg_p10", 0., 5.);
  */ // RooBernstein bg_pol("bg_pol", "bg_pol", *x, RooArgList(*bg_p4, *bg_p5, *bg_p6));

  /*RooRealVar bg_p00("bg_p00", "bg_p00", gaussexp_mean_lo, gaussexp_mean_hi);
  RooRealVar bg_p11("bg_p11", "bg_p11", gaussexp_width_lo, gaussexp_width_hi);
  RooRealVar bg_p22("bg_p22", "bg_p22", gaussexp_exp_lo, gaussexp_exp_hi);
*/


  RooRealVar bg_p0("bg_p0", "bg_p0", 0.); //gaussexp_mean_lo, gaussexp_mean_hi);
  bg_p0.setConstant(1); 
  RooRealVar bg_p1("bg_p1", "bg_p1",1. , 100.);//gaussexp_width_lo, gaussexp_width_hi);
  RooRealVar bg_p2("bg_p2", "bg_p2", 210., 300. );//310., 600.); ///210., 300. 
//  RooRealVar bg_p3("bg_p3", "bg_p3",  -5., 5.);
//  RooRealVar bg_p4("bg_p4", "bg_p4",   -5., 5.);
/*  bg_p3.setConstant(1);
  bg_p4.setConstant(1);
  RooRealVar bg_p5("bg_p5", "bg_p5", -10., 10.);
  RooRealVar bg_p6("bg_p6", "bg_p6", -10., 10.);
  RooRealVar bg_p7("bg_p7", "bg_p7", -10., 10.);
  RooRealVar bg_p8("bg_p8", "bg_p8", -10., 10.);
  *//*bg_p5.setConstant(1);
  bg_p6.setConstant(1);
  bg_p7.setConstant(1);
  bg_p8.setConstant(1);
  */


  //RooGaussian bg_gauss("background", "Background Prediction PDF", *x, bg_p0, bg_p1);	
  //GaussExp bg("background", "Background Prediction PDF", *x, bg_p0, bg_p1, bg_p2);
  //GaussExpPol bg("bg", "bg", *x, bg_p0, bg_p1, bg_p2, bg_p3, bg_p4, bg_p5,bg_p6,bg_p7,bg_p8);
  RooGaussStepBernstein bg("bg","bg",*x, bg_p0, bg_p1, bg_p2, RooArgList(*bg_p3, *bg_p4, *bg_p5, *bg_p6));
  //RooGenericPdf bg("bg","bg",bg_gauss*bg_pol,RooArgSet( *x, bg_p0, bg_p1, bg_p2,*bg_p3, *bg_p4, *bg_p5));	
  //RooAddPdf bg("bg", "bg", RooArgList(bg_gauss, bg_pol), *bg_p7);  	
  //bg.fitTo(pred, RooFit::Range(fit_lo, fit_hi), RooFit::Save(), RooFit::Minimizer("Minuit","simplex"));
  RooFitResult *r_bg=bg.fitTo(pred, RooFit::Range(fit_lo, fit_hi), RooFit::Save());
  /*bg_p1.setConstant(1);
  bg_p2.setConstant(1);
  bg_p4->setConstant(1);
  bg_p5->setConstant(1);
  bg_p6->setConstant(1);
  bg_p7->setConstant(1);
 */

  //GaussExp bg_exp("bg_exp", "Background Prediction PDF", *x, bg_p00, bg_p11, bg_p22);
  RooRealVar bg_p00("bg_p00", "bg_p00", crystalball_switch_lo, crystalball_switch_hi);
  RooRealVar bg_p11("bg_p11", "bg_p11", crystalball_exp_lo, crystalball_exp_hi);
  RooRealVar bg_p22("bg_p22", "bg_p22", crystalball_mean_lo, crystalball_mean_hi);
  RooRealVar bg_p33("bg_p33", "bg_p33", crystalball_width_lo, crystalball_width_hi);
  RevCrystalBall bg_exp("bg_exp", "Background Prediction PDF", *x, bg_p00, bg_p11, bg_p22, bg_p33);

  RooPlot *data_plot2=x->frame();
  RooFitResult *r_bg_exp=bg_exp.fitTo(pred, RooFit::Range(fit_lo, fit_hi), RooFit::Save());
  pred.plotOn(data_plot2);

  //bg_exp.plotOn(data_plot2, RooFit::VisualizeError(*r_bg_exp, 1, kFALSE), RooFit::FillColor(kCyan+1), RooFit::FillStyle(3001));
  bg_exp.plotOn(data_plot2, RooFit::LineColor(kBlue+1));
  pred.plotOn(data_plot2, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));



  RooPlot *data_plot=x->frame();
  pred.plotOn(data_plot);
  bg.plotOn(data_plot, RooFit::VisualizeError(*r_bg, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
  bg.plotOn(data_plot, RooFit::LineColor(kBlack));
  pred.plotOn(data_plot, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));

  double fitChi2=data_plot->chiSquare();
  std::cout<<"Fit chi2 = "<<fitChi2<<std::endl;

  RooAbsReal* chi2_data    = bg.createChi2(pred);
  double pvalue=TMath::Prob(chi2_data->getVal(),int((fit_hi-fit_lo)/rebin)-3);
  std::cout<<"p-value = "<<TMath::Prob(chi2_data->getVal(),int((fit_hi-fit_lo)/rebin)-3)<<std::endl; 

  /*TCanvas *c_Background=new TCanvas("c_Background", "c_Background", 700, 700);
    TPad *p_1=new TPad("p_1", "p_1", 0, 0.35, 1, 1);
  //p_1->SetBottomMargin(0.05);
  //p_2->SetBottomMargin(-.5);
  // p_1->SetFillStyle(4000);
  // p_1->SetFrameFillColor(0);
  TPad *p_2 = new TPad("p_2", "p_2", 0, 0, 1., 0.35);
  p_2->SetFillColor(0);
  p_2->SetBorderMode(0);
  p_2->SetBorderSize(2);
  p_2->SetTopMargin(0.018);
  p_2->SetBottomMargin(0.30);
  p_2->SetFrameBorderMode(0);
  */


  double xPad = 0.3;
  TCanvas *c_Background=new TCanvas("c_Background", "c_Background", 700*(1.-xPad), 700);
  c_Background->SetFillStyle(4000);
  c_Background->SetFrameFillColor(0);

 TPad *p_1=new TPad("p_1", "p_1", 0, xPad, 1, 1);
        p_1->SetFillStyle(4000);
        p_1->SetFrameFillColor(0);
        p_1->SetBottomMargin(0.02);

        TPad* p_2 = new TPad("p_2", "p_2",0,0,1,xPad);
        p_2->SetBottomMargin((1.-xPad)/xPad*0.13);
        p_2->SetTopMargin(0.03);
        p_2->SetFillColor(0);
        p_2->SetBorderMode(0);
        p_2->SetBorderSize(2);
        p_2->SetFrameBorderMode(0);
        p_2->SetFrameBorderMode(0);

  p_1->Draw();
  p_2->Draw();
  p_1->cd();



  if (log=="log") data_plot->GetYaxis()->SetRangeUser(1e-4, h_mX_SR->GetMaximum()*5.);
  else data_plot->GetYaxis()->SetRangeUser(0, h_mX_SR->GetMaximum()*1.5);
  data_plot->Draw();
  data_plot->GetXaxis()->SetLabelOffset(0.03);
  data_plot->GetYaxis()->SetLabelFont(42);
  data_plot->GetYaxis()->SetTitleFont(42); 
  data_plot2->Draw("same");
  data_plot->GetYaxis()->SetTitleOffset(1.25);
  data_plot->SetTitle(("; m_{X} (GeV); Events / "+itoa(h_mX_SR->GetBinWidth(1))+" GeV").c_str());
  if (log=="log") p_1->SetLogy();

  TPaveText *pave = new TPaveText(0.86,0.6,0.67,0.7,"NDC");
  pave->SetBorderSize(0);
  pave->SetTextSize(0.03);
  pave->SetLineColor(1);
  pave->SetLineStyle(1);
  pave->SetLineWidth(2);
  pave->SetFillColor(0);
  pave->SetFillStyle(0);
  char name[1000];
  char name1[1000];
  if (hist.substr(0,7)=="h_mX_SB") {
		sprintf(name,"SB #chi^{2}/n = %.2f",fitChi2);
		sprintf(name1,"p-value = %.2f",pvalue);
	}
  else sprintf(name,"SR #chi^{2}/n = %.2f",fitChi2);  
  pave->AddText(name);
  pave->AddText(name1);
  pave->Draw(); 

  TLatex * tPrel = new TLatex();
  tPrel->SetNDC();
  tPrel->SetTextColor(kBlack);
  tPrel->SetTextSize(0.04);

  TLegend *leg = new TLegend(0.85625,0.721654,0.6165625,0.8903839,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  h_mX_SR->SetMarkerStyle(20);
  if (hist.substr(0,7)=="h_mX_SB"){
	 h_mX_SR->SetLineColor(kBlack);
	 h_mX_SR->SetMarkerColor(kBlack);
	 leg->AddEntry(h_mX_SR, "Data in SB", "ep"); 
	
	}
  else leg->AddEntry(h_mX_SR, "Data in SR", "ep"); 
  TH1F * temp = new TH1F("temp", "temp", 100, 0,1); temp->SetLineWidth(2);  temp->SetLineColor(kBlack);
  leg->AddEntry(temp, "GaussBern fit", "l");
  TH1F * temp1 = new TH1F("temp1", "temp1", 100, 0,1); temp1->SetLineWidth(2); 	
  temp1->SetLineColor(kBlue+1);
  leg->AddEntry(temp1, "CrystalBall fit", "l");
  leg->Draw();

  CMS_lumi( p_1, iPeriod, iPos );

  p_2->cd();
  RooHist *hpull;
  hpull = data_plot->pullHist();
  RooPlot* frameP = x->frame() ;

  frameP->SetTitle("; m_{X} (GeV); Pull");
  frameP->addPlotable(hpull,"P");
  frameP->GetYaxis()->SetTitleSize(0.07);
  frameP->GetYaxis()->SetTitleOffset(0.5);
  frameP->GetXaxis()->SetTitleSize(0.09);
  frameP->GetXaxis()->SetTitleOffset(1.0);
  frameP->GetXaxis()->SetLabelSize(0.07);
  frameP->GetYaxis()->SetLabelSize(0.06);
  frameP->Draw();


  TLine *line=new TLine(fit_lo, 0, fit_hi, 0);
  line->SetLineWidth(2);
  line->Draw();

  string tag;
  if (hist.substr(0,7)=="h_mX_SB") tag="SB";
  else tag="SR";
  c_Background->SaveAs(("BackgroundFit_"+tag+"_Bern.png").c_str());
  c_Background->SaveAs(("BackgroundFit_"+tag+"_Bern.pdf").c_str());

  // --- Ratio of function to data points ---
  /*
     RooCurve *f_bg_pred=(RooCurve*)aS_plot->findObject("r_bg_prediction");
     TH1F *h_ratio=(TH1F*)h_mX_SR->Clone("h_ratio");
     for (unsigned int i=0; i<h_ratio->GetNbinsX(); ++i)
     {
     double fEval=f_bg_pred->Eval(h_mX_SR->GetBinCenter(i));
     double data=h_mX_SR->GetBinContent(i);
  // std::cout<<"i = "<<i<<", fEval = "<<fEval<<", data = "<<data<<std::endl;
  double binContent=(h_mX_SR->GetBinContent(i))/(f_bg_pred->Eval(h_mX_SR->GetBinCenter(i)));
  double binError=(h_mX_SR->GetBinError(i))/(f_bg_pred->Eval(h_mX_SR->GetBinCenter(i)));
  h_ratio->SetBinContent(i, binContent);
  h_ratio->SetBinError(i, binError);
  }
  h_ratio->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
  h_ratio->SetMaximum(2.5); h_ratio->SetMinimum(-0.5);
  h_ratio->SetTitle("Data/Fit in SR; m_{X} (GeV); Data/Fit");
  h_ratio->Fit("pol1", "", "", SR_lo, SR_hi);
  TCanvas *c_DataFit=new TCanvas("c_DataFit", "c_DataFit", 1000, 700);
  h_ratio->Draw();
  c_DataFit->SaveAs(("c_DataFit_"+tags+"SR.png").c_str());
  */
  // ------------------------------------------


  RooWorkspace *w_background=new RooWorkspace("HbbHbb");

  w_background->import(bg);
  w_background->import(bg_exp);	

  // Normalize h_mX_SB to SR for pretend data
  TH1F *h_mX_SR_fakeData=(TH1F*)h_mX_SR->Clone("h_mX_SR_fakeData");
  h_mX_SR_fakeData->Scale(nEventsSR/h_mX_SR_fakeData->GetSumOfWeights());
  RooDataHist data_obs("data_obs", "Data", RooArgList(*x), h_mX_SR_fakeData);

  w_background->import(data_obs);
  w_background->SaveAs("w_background_Bern.root"); 
  // For the datacard
  std::cout<<" === RooFit data fit result to be entered in datacard === "<<std::endl;
  std::cout<<" Background number of events = "<<nEventsSR<<std::endl;
    std::cout<< "bg_p0   param   "<<bg_p0.getVal()<<" "<<bg_p0.getError()<<std::endl;
      std::cout<< "bg_p1   param   "<<bg_p1.getVal()<<" "<<bg_p1.getError()<<std::endl;
      std::cout<< "bg_p2   param   "<<bg_p2.getVal()<<" "<<bg_p2.getError()<<std::endl;
      std::cout<< "bg_p3   param   "<<bg_p3->getVal()<<" "<<bg_p3->getError()<<std::endl;
      std::cout<< "bg_p4   param   "<<bg_p4->getVal()<<" "<<bg_p4->getError()<<std::endl;
      std::cout<< "bg_p5   param   "<<bg_p5->getVal()<<" "<<bg_p5->getError()<<std::endl;
	std::cout<< "bg_p6   param   "<<bg_p6->getVal()<<" "<<bg_p6->getError()<<std::endl;
    
      
}




