{
  std::vector<double> masses={260, 270, 300, 350, 400, 450, 500, 550};
  gROOT->LoadMacro("../../DrawLimitPlot.cc++");
  DrawLimitPlot(masses, 10, 1e5);
}
