R__LOAD_LIBRARY(Sidis-eic)

/* template analysis macro
 * - runs an analysis and nothing more (e.g., it does not define bins)
 * - useful if you want to use your own analysis code
 */
void analysis_template(
    TString infiles="tutorial/delphes.config", /* list of input files */
    Double_t eleBeamEn=10, /* electron beam energy [GeV] */
    Double_t ionBeamEn=100, /* ion beam energy [GeV] */
    Double_t crossingAngle=-25, /* crossing angle [mrad] */
    TString outfilePrefix="tutorial.template" /* output filename prefix*/
) {

  // setup analysis ========================================
  AnalysisDelphes *A = new AnalysisDelphes(
      infiles,
      eleBeamEn,
      ionBeamEn,
      crossingAngle,
      outfilePrefix
      );
  //A->maxEvents = 10000; // use this to limit the number of events
  /* this `maxEvents` limit should only be applied for quick tests;
   * you should not set it if you are using the number of events
   * column in `infiles` (the input files table)
   */
  A->writeSimpleTree = true; // write SimpleTree (for one bin)

  // set reconstruction method =============================
  // - see `Analysis` constructor for methods
  A->SetReconMethod("Ele");

  // define cuts ====================================
  // - cuts are defined the same way as bins are defined; be mindful
  //   of what bins you are defining vs. what cuts you are defining.
  //   For example, if you define a Q2 minimum cut, and you also define
  //   Q2 bins below, you may be creating more bins than you actually
  //   need, since the Q2 minimum cut actually defines another bin;
  //   in this case, your Q2 bins effectively define a Q2 minimum.
  A->AddBinScheme("w");  A->BinScheme("w")->BuildBin("Min",3.0); // W > 3 GeV
  A->AddBinScheme("y");  A->BinScheme("y")->BuildBin("Range",0.01,0.95); // 0.01 < y < 0.95
  A->AddBinScheme("z");  A->BinScheme("z")->BuildBin("Range",0.2,0.9); // 0.2 < z < 0.9
  A->AddBinScheme("xF"); A->BinScheme("xF")->BuildBin("Min",0.0); // xF > 0
  A->AddBinScheme("ptLab");  A->BinScheme("ptLab")->BuildBin("Min",0.1); // pT_lab > 0.1 GeV (tracking limit)

  // set binning scheme ====================================
  // - see `Analysis` constructor for available bin variables
  /* do nothing -> single bin histograms */

  // final states =========================================
  // - define final states; if you define none, default sets will
  //   be defined
  A->AddFinalState("pipTrack");
  //A->AddFinalState("pimTrack");
  //A->AddFinalState("KpTrack");
  //A->AddFinalState("KmTrack");
  A->AddFinalState("jet");

  // perform the analysis ==================================
  A->Execute();
};
