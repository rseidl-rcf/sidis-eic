R__LOAD_LIBRARY(Sidis-eic)

// ratios of histograms with y-cut enabled to those with y-cut disabled
void analysis_yRatio(
    TString infiles="tutorial/delphes.config", /* list of input files */
    Double_t eleBeamEn=10, /* electron beam energy [GeV] */
    Double_t ionBeamEn=100, /* ion beam energy [GeV] */
    Double_t crossingAngle=-25, /* crossing angle [mrad] */
    TString outfilePrefix="yRatio" /* output filename prefix*/
) {

  // setup analysis ========================================
  AnalysisDelphes *A = new AnalysisDelphes(
      infiles,
      eleBeamEn,
      ionBeamEn,
      crossingAngle,
      outfilePrefix
      );

  //A->maxEvents = 30000; // use this to limit the number of events
  A->writeSimpleTree = true; // write SimpleTree (for one bin)
  A->SetReconMethod("Ele"); // set reconstruction method
  A->AddFinalState("pipTrack"); // pion final state
  //A->AddFinalState("KpTrack"); // kaon final state
  //A->AddFinalState("jet"); // jets


  // define cuts ====================================
  // - cuts are defined the same way as bins are defined; be mindful
  //   of what bins you are defining vs. what cuts you are defining.
  //   For example, if you define a Q2 minimum cut, and you also define
  //   Q2 bins below, you may be creating more bins than you actually
  //   need, since the Q2 minimum cut actually defines another bin;
  //   in this case, your Q2 bins effectively define a Q2 minimum.
  A->AddBinScheme("w");  A->BinScheme("w")->BuildBin("Min",3.0); // W > 3 GeV
  A->AddBinScheme("z");  A->BinScheme("z")->BuildBin("Range",0.2,0.9); // 0.2 < z < 0.9
  A->AddBinScheme("xF"); A->BinScheme("xF")->BuildBin("Min",0.0); // xF > 0
  A->AddBinScheme("ptLab");  A->BinScheme("ptLab")->BuildBin("Min",0.1); // pT_lab > 0.1 GeV (tracking limit)


  // set binning scheme ====================================
  // z ranges
  /*
  A->AddBinScheme("z");
  A->BinScheme("z")->BuildBin("Range", 0.2, 0.5 );
  A->BinScheme("z")->BuildBin("Range", 0.5, 0.8 );
  */

  // y minima
  A->AddBinScheme("y");
  A->BinScheme("y")->BuildBin("Max",0.95); // a bin with no minimum y-cut
  A->BinScheme("y")->BuildBin("Range",0.03,0.95);
  A->BinScheme("y")->BuildBin("Range",0.05,0.95);
  A->BinScheme("y")->BuildBin("Range",0.10,0.95);

  // perform the analysis ==================================
  A->Execute();
};
