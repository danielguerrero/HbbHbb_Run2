TF1* QaD_DoubleJet_L1 = new TF1("QaD_DoubleJet_L1","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-164.741)/100.87)*(x>164.741))+(((x-164.741)/(100.87+101.322))*(x<=164.741)))*0.999839))))-7.4591e-11)");
TF1* QaD_DoubleJet_L1Up = new TF1("QaD_DoubleJet_L1Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-161.291)/100.87)*(x>161.291))+(((x-161.291)/(100.87+101.322))*(x<=161.291)))*0.999839))))+0.02)");
TF1* QaD_DoubleJet_L1Down = new TF1("QaD_DoubleJet_L1Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-167.992)/100.87)*(x>167.992))+(((x-167.992)/(100.87+101.322))*(x<=167.992)))*0.999839))))-0.02)");
TF1* QaD_DoubleJet_CaloPt2 = new TF1("QaD_DoubleJet_CaloPt2","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-86.9582)/19.6484)*(x>86.9582))+(((x-86.9582)/(19.6484-2.41426))*(x<=86.9582)))*0.983679))))-8.34377e-12)");
TF1* QaD_DoubleJet_CaloPt2Up = new TF1("QaD_DoubleJet_CaloPt2Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-86.703)/19.6484)*(x>86.703))+(((x-86.703)/(19.6484-2.41426))*(x<=86.703)))*0.983679))))+0.02)");
TF1* QaD_DoubleJet_CaloPt2Down = new TF1("QaD_DoubleJet_CaloPt2Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-87.2142)/19.6484)*(x>87.2142))+(((x-87.2142)/(19.6484-2.41426))*(x<=87.2142)))*0.983679))))-0.02)");
TF1* QaD_DoubleJet_PFPt2 = new TF1("QaD_DoubleJet_PFPt2","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-84.9239)/14.9955)*(x>84.9239))+(((x-84.9239)/(14.9955+16.626))*(x<=84.9239)))*0.995706))))-0)");
TF1* QaD_DoubleJet_PFPt2Up = new TF1("QaD_DoubleJet_PFPt2Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-84.6353)/14.9955)*(x>84.6353))+(((x-84.6353)/(14.9955+16.626))*(x<=84.6353)))*0.995706))))+0.02)");
TF1* QaD_DoubleJet_PFPt2Down = new TF1("QaD_DoubleJet_PFPt2Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-85.2135)/14.9955)*(x>85.2135))+(((x-85.2135)/(14.9955+16.626))*(x<=85.2135)))*0.995706))))-0.02)");
