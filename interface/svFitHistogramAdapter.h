#ifndef TauAnalysis_ClassicSVfit_svFitHistogramAdapter_h
#define TauAnalysis_ClassicSVfit_svFitHistogramAdapter_h

#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"

#include <Math/Functor.h>
#include <TH1.h>

namespace classic_svFit
{
  class HistogramTools
  {
   public:
    static TH1* compHistogramDensity(TH1 const* histogram);
    static void extractHistogramProperties(
        TH1 const* histogram,
        double& xMaximum,
        double& xMaximum_interpol,
        double& xMean,
        double& xQuantile016,
        double& xQuantile050,
        double& xQuantile084
    );
    static double extractValue(TH1 const* histogram);
    static double extractUncertainty(TH1 const* histogram);
    static double extractLmax(TH1 const* histogram);
    static TH1* makeHistogram(const std::string& histogramName, double xMin, double xMax, double logBinWidth);
  };

  class SVfitQuantity
  {
   public:
    SVfitQuantity();
    virtual ~SVfitQuantity();

    virtual TH1* createHistogram(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const = 0;
    virtual double fitFunction(const LorentzVector& tau1P4, const LorentzVector& tau2P4, const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const = 0;

    void bookHistogram(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met);
    void writeHistograms() const;

    double eval(
        const LorentzVector& tau1P4, const LorentzVector& tau2P4,
        const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& measuredMET
    ) const;

    double extractValue() const;
    double extractUncertainty() const;
    double extractLmax() const;

    mutable TH1* histogram_ = nullptr;
  };

  class HiggsPtSVfitQuantity : public SVfitQuantity
  {
   public:
    virtual TH1* createHistogram(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
    virtual double fitFunction(const LorentzVector& tau1P4, const LorentzVector& tau2P4, const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
  };
  
  class HiggsEtaSVfitQuantity : public SVfitQuantity
  {
   public:
    virtual TH1* createHistogram(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
    virtual double fitFunction(const LorentzVector& tau1P4, const LorentzVector& tau2P4, const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
  };
  
  class HiggsPhiSVfitQuantity : public SVfitQuantity
  {
   public:
    virtual TH1* createHistogram(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
    virtual double fitFunction(const LorentzVector& tau1P4, const LorentzVector& tau2P4, const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
  };
  
  class HiggsMassSVfitQuantity : public SVfitQuantity
  {
   public:
    virtual TH1* createHistogram(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
    virtual double fitFunction(const LorentzVector& tau1P4, const LorentzVector& tau2P4, const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
  };
  
  class TransverseMassSVfitQuantity : public SVfitQuantity
  {
   public:
    virtual TH1* createHistogram(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
    virtual double fitFunction(const LorentzVector& tau1P4, const LorentzVector& tau2P4, const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;
  };
  
  class HistogramAdapter : public ROOT::Math::Functor
  {
   public:
    HistogramAdapter();
    ~HistogramAdapter();

    void setMeasurement(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met);
    void setTau1P4(const LorentzVector& tau1P4);
    void setTau2P4(const LorentzVector& tau2P4);

    void bookHistograms(const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met);

    /// get pT, eta, phi, mass and transverse mass of di-tau system
    double getPt() const;
    double getPtErr() const;
    double getPtLmax() const;
    double getEta() const;
    double getEtaErr() const;
    double getEtaLmax() const;
    double getPhi() const;
    double getPhiErr() const;
    double getPhiLmax() const;
    double getMass() const;
    double getMassErr() const;
    double getMassLmax() const;
    double getTransverseMass() const;
    double getTransverseMassErr() const;
    double getTransverseMassLmax() const;

    void writeHistograms(const std::string& likelihoodFileName) const;

   private:
    virtual double DoEval(const double* x) const;
    void fillHistograms(const LorentzVector& tau1P4, const LorentzVector& tau2P4,
                        const LorentzVector& vis1P4, const LorentzVector& vis2P4, const Vector& met) const;

   protected:
    LorentzVector vis1P4_;
    LorentzVector vis2P4_;
    Vector met_;
    
    LorentzVector tau1P4_;
    LorentzVector tau2P4_;

    mutable TH1* histogramPt_;
    mutable TH1* histogramEta_;
    mutable TH1* histogramPhi_;
    mutable TH1* histogramMass_;
    mutable TH1* histogramTransverseMass_;
  };
}

#endif
