TF1* QuaJet_L1 = new TF1("QuaJet_L1","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-257.077)/85.9832)*(x>257.077))+(((x-257.077)/(85.9832-20.2196))*(x<=257.077)))*0.9927))))+0.000500647)");
TF1* QuaJet_L1Up = new TF1("QuaJet_L1Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-256.796)/85.9832)*(x>256.796))+(((x-256.796)/(85.9832-20.2196))*(x<=256.796)))*0.9927))))+0.0205006)");
TF1* QuaJet_L1Down = new TF1("QuaJet_L1Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-257.445)/85.9832)*(x>257.445))+(((x-257.445)/(85.9832-20.2196))*(x<=257.445)))*0.9927))))-0.0194994)");
TF1* QuaJet_CaloPt4 = new TF1("QuaJet_CaloPt4","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-35.6744)/20.0039)*(x>35.6744))+(((x-35.6744)/(20.0039+18.8909))*(x<=35.6744)))*1.48577))))-0.256576)");
TF1* QuaJet_CaloPt4Up = new TF1("QuaJet_CaloPt4Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-35.5778)/20.0039)*(x>35.5778))+(((x-35.5778)/(20.0039+18.8909))*(x<=35.5778)))*1.48577))))-0.236576)");
TF1* QuaJet_CaloPt4Down = new TF1("QuaJet_CaloPt4Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-35.7712)/20.0039)*(x>35.7712))+(((x-35.7712)/(20.0039+18.8909))*(x<=35.7712)))*1.48577))))-0.276576)");
TF1* QuaJet_CSV3 = new TF1("QuaJet_CSV3","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x+1.02185)/1.50209)*(x>-1.02185))+(((x+1.02185)/(1.50209-0.720143))*(x<=-1.02185)))*2))))-0.560513)");
TF1* QuaJet_CSV3Up = new TF1("QuaJet_CSV3Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x+1.13112)/1.50209)*(x>-1.13112))+(((x+1.13112)/(1.50209-0.720143))*(x<=-1.13112)))*2))))-0.540513)");
TF1* QuaJet_CSV3Down = new TF1("QuaJet_CSV3Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x+0.911636)/1.50209)*(x>-0.911636))+(((x+0.911636)/(1.50209-0.720143))*(x<=-0.911636)))*2))))-0.580513)");
TF1* QuaJet_PFPt4 = new TF1("QuaJet_PFPt4","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-43.8322)/10.5812)*(x>43.8322))+(((x-43.8322)/(10.5812-7.40534))*(x<=43.8322)))*0.37301))))+0.310956)");
TF1* QuaJet_PFPt4Up = new TF1("QuaJet_PFPt4Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-43.4891)/10.5812)*(x>43.4891))+(((x-43.4891)/(10.5812-7.40534))*(x<=43.4891)))*0.37301))))+0.330956)");
TF1* QuaJet_PFPt4Down = new TF1("QuaJet_PFPt4Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-44.1693)/10.5812)*(x>44.1693))+(((x-44.1693)/(10.5812-7.40534))*(x<=44.1693)))*0.37301))))+0.290956)");
