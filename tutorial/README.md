# Tutorials

Here is a collection of tutorial macros. If you are learning this software,
it is recommended to go through these tutorials in the numerical order given below.

- **Note**: execute macros from the `sidis-eic` top directory, not from
this tutorial directory, e.g., `root -b -q tutorial/analysis_template.C`

## Generate or Obtain Simulation Output Trees 

To run tutorials, you need to generate or obtain ROOT files, from fast or full simulation
- the `datarec/` directory is provided for storage of these files,
  but is not required to use
- the following sub-sections describe how to obtain these files from the common
  storage area
  - this requires access to S3, the common storage area
  - environment variables `$S3_ACCESS_KEY` and `$S3_SECRET_KEY` must contain
    the login and password; follow [s3tools documentation](../s3tools/README.md) for guidance

### Fast Simulation
- run `tutorial/makeSampleDelphesFiles.sh` to download HEPMC files from S3,
  and run them through Delphes
  - edit the settings in this script, such as beam energy
  - change the maximum number of files to process, to limit disk space
    consumption

### Full Simulation
- full simulation files are streamed from S3 using `tutorial/s3files.config`


## Introductory Notes

### Switching between Fast and Full Simulations
- many of these examples focus on fast simulations; to switch between fast and
  full simulations, change the `Analysis`-derived class in the macro:
  - `AnalysisDelphes` is used for fast simulation
  - `AnalysisDD4hep` is used for full simulation from DD4hep+Juggler
- note: some extra settings and features differ between these

### Input File Lists (Config Files)
- in the analysis macros, the input files are specified by a list, a "config
  file", with the additional columns
  - see [documentation here](../s3tools/README.md) for the formatting of these
    files, as well as scripts to help generate them
  - for example, this file allows one to combine different Q2 regions together
    using relative weights 


# Tutorials:

Each of these examples has two macros:
  - analysis macro, to run an `Analysis`-derived class, which will analyze 
    simulated data in an event loop, and generate a variety of output
    data structures
  - postprocessor macro, to process the output from the analysis macro,
    such as drawing plots
  - the analysis macro will take some time to run, since it runs
    the event loop; the postprocessor macro is typically fast, since
    it analyzes the resulting data structures


1. Template
  - `analysis_template.C`: minimal analysis macro to demonstrate how
    to run `Analysis`; no bins are specified
  - there is no postprocessor macro (see other examples); instead, inspect
    the output root file from the analysis macro, to learn what objects
    are stored

2. (x,Q2) Binning
  - `analysis_xqbins.C`: bin the analysis in a few 2D bins of x and Q2
    - there is a `switch` statement to allow the choice of various
      example binning schemes
    - this example also describes how cuts are defined
  - `postprocess_xqbins_draw.C`: draws a couple sample histograms for
    the given binning scheme

3. Full Simulations (all other tutorials are for fast simulations)
  - `analysis_dd4hep.C`: basically a copy of `analysis_xqbins.C`,
    but shows how to analyze full simulation data; the main difference
    is using `AnalysisDD4hep` instead of `AnalysisDelphes`
  - `postprocess_dd4hep_draw.C`: clone of `postprocess_xqbins_draw.C`,
    specific for this example

4. Average kinematics table
  - `analysis_qbins.C`: bin the analysis in several Q2 bins, for a couple
    pT bins
  - `postprocess_qbins_tables.C`: produce a text file containing tables
    of averages of kinematics variables, where each row is for a Q2 bin;
    one table is produced for each pT bin

5. Draw ratio of histograms for different y-minima
  - `analysis_yRatio.C`: bins in 3 y-minima, along with a full-y bin
  - `postprocess_yRatio.C`: produces ratios of all histograms, with
    a y-minimum divided by no y-minimum

6. Test DAG lambda staging
  - `analysis_testDAG.C`: define multi-dimensional binning
  - `postprocess_testDAG.C`: contains various lambdas examples and
    describes how to stage them

7. Conditional Subloops
  - `analysis_coverage.C`: define 4-D binning scheme, including
    extra "full-range" bins
  - `postprocess_coverage.C`: draw certain plots, while restricting
    certain bins to be "full-range", i.e., "integrated over"; in order
    to restrict the execution of certain subloops, conditional control
    functions are used
