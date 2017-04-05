#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"

#include "RecoLocalCalo/HGCalRecAlgos/interface/RecHitTools.h"

#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"
#include "Geometry/HGCalGeometry/interface/HGCalGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "DataFormats/ForwardDetId/interface/HGCEEDetId.h"
#include "DataFormats/ForwardDetId/interface/HGCHEDetId.h"
#include "DataFormats/ForwardDetId/interface/ForwardSubdetector.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoLocalCalo/HGCalRecAlgos/interface/ClusterTools.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFwd.h" 
#include "DataFormats/ParticleFlowReco/interface/PFRecHit.h" 
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFraction.h" 

class HGCalIDTool {    
  public:
    HGCalIDTool(const edm::ParameterSet&, edm::ConsumesCollector&);
    ~HGCalIDTool() {}

    void getEvent(const edm::Event&);
    void getEventSetup(const edm::EventSetup&);
    
    bool setClusterPtr(const reco::CaloCluster *);

    math::XYZPoint getStartPosition();
    math::XYZPoint getShowerPosition() { return showerPos_; }
    math::XYZVector getShowerAxis() { return showerDir_; }

    double getHadronFraction();
    double getSigmaEtaEta();
    double getLengthCompatibility();

  private:
    void rebuildRecHitFractions();
    void calculateShowerPositionAndAxis();

    hgcal::RecHitTools rhtools_;
    const edm::EDGetTokenT<HGCRecHitCollection> eetok, fhtok, bhtok;
    const edm::EDGetTokenT<reco::PFRecHitCollection> hgcPftok;
    const HGCRecHitCollection *eerh_, *fhrh_, *bhrh_;
    const reco::PFRecHitCollection *pfRecHits_;

    bool withPileup_;

    double mip_;
    double minenergy_;
    double rmax_;
    double hovereConesize_;
    double cutStartPosition_;
    double cutSigmaetaeta_;
    double cutHoverem_;
    double cutLengthCompatibility_;
    
    // longitudinal parametrisation
    double criticalEnergy_;
    double radiationLength_;
    double meant0_;
    double meant1_;
    double meanalpha0_;
    double meanalpha1_;
    double sigmalnt0_;
    double sigmalnt1_;
    double sigmalnalpha0_;
    double sigmalnalpha1_;
    double corrlnalphalnt0_;
    double corrlnalphalnt1_;

    const reco::CaloCluster * cluster_;
    std::vector<reco::PFRecHitFraction> recHitFractions_;
    math::XYZPoint showerPos_;
    math::XYZVector showerDir_;

};
