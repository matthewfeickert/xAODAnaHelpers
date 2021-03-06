#ifndef xAODAnaHelpers_TauJetMatching_H
#define xAODAnaHelpers_TauJetMatching_H

// EDM include(s):
#include "xAODTau/TauJet.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/Jet.h"

// algorithm wrapper
#include "xAODAnaHelpers/Algorithm.h"

class TauJetMatching : public xAH::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.

public:

  // configuration variables
  /* input container name */
  std::string    m_inContainerName = "";
  /* output container name */
  std::string    m_outContainerName;
  /* output auxiliary container name */
  std::string    m_outAuxContainerName;
  std::string    m_inputAlgoSystNames = "";
  std::string    m_outputAlgoSystNames = "TauJetMatching_Syst";

  std::string    m_inJetContainerName = "";
  float          m_DeltaR = 0.2;

private:

  int m_numEvent;           //!
  int m_numObject;          //!

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)

public:
  // Tree *myTree; //!
  // TH1 *myHist; //!

  // this is a standard constructor
  TauJetMatching ();

  ~TauJetMatching();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // added functions not from Algorithm
  bool executeDecoration( std::unordered_map<int, std::pair<const xAOD::TauJet*, const xAOD::Jet* > >, const xAOD::TauJetContainer* tauCont);
  float getDR(float eta1, float eta2, float phi1, float phi2);
  std::unordered_map<int, std::pair<const xAOD::TauJet*, const xAOD::Jet* > > findBestMatchDR(const xAOD::JetContainer* jetCont,
                                                                                              const xAOD::TauJetContainer* tauCont,
                                                                                              float best_DR);

  /// @cond
  // this is needed to distribute the algorithm to the workers
  ClassDef(TauJetMatching, 1);
  /// @endcond

};

#endif
