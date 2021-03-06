import FWCore.ParameterSet.Config as cms


muonsPt10 = cms.EDFilter("MuonSelector",
    src = cms.InputTag('muons'),
    cut = cms.string(
        'isGlobalMuon &'
        'isTrackerMuon &'
        'numberOfMatches > 1 &'
        'globalTrack.hitPattern.numberOfValidMuonHits > 0 &'
        'abs(eta) < 2.5 &'
        'pt > 10'
    ),
    filter = cms.bool(False)
)


import SimMuon.MCTruth.MuonTrackProducer_cfi
muonInnerTrack = SimMuon.MCTruth.MuonTrackProducer_cfi.muonTrackProducer.clone()
#muonInnerTrack.muonsTag = cms.InputTag("muons")
muonInnerTrack.muonsTag = cms.InputTag("muonsPt10")
muonInnerTrack.selectionTags = ('All',)
muonInnerTrack.trackType = "innerTrack"

import DQM.TrackingMonitor.TrackingMonitor_cfi
MonitorTrackMuonsInnerTrack = DQM.TrackingMonitor.TrackingMonitor_cfi.TrackMon.clone()
MonitorTrackMuonsInnerTrack.TrackProducer = 'muonInnerTrack'
MonitorTrackMuonsInnerTrack.AlgoName = 'inner'
MonitorTrackMuonsInnerTrack.FolderName = 'Muons/Tracking/innerTrack'
MonitorTrackMuonsInnerTrack.doBeamSpotPlots = True
MonitorTrackMuonsInnerTrack.BSFolderName = 'Muons/Tracking/innerTrack/BeamSpotParameters'
MonitorTrackMuonsInnerTrack.doSeedParameterHistos = False
MonitorTrackMuonsInnerTrack.doProfilesVsLS = False
MonitorTrackMuonsInnerTrack.doAllPlots = False
MonitorTrackMuonsInnerTrack.doGeneralPropertiesPlots = True
MonitorTrackMuonsInnerTrack.doHitPropertiesPlots = True
MonitorTrackMuonsInnerTrack.doTrackerSpecific = True
MonitorTrackMuonsInnerTrack.doDCAPlots = True
MonitorTrackMuonsInnerTrack.doDCAwrtPVPlots = True
MonitorTrackMuonsInnerTrack.doDCAwrt000Plots = False
MonitorTrackMuonsInnerTrack.doSIPPlots  = True
MonitorTrackMuonsInnerTrack.doEffFromHitPatternVsPU = True
MonitorTrackMuonsInnerTrack.doEffFromHitPatternVsBX = False
MonitorTrackMuonsInnerTrack.TkSizeBin = 10
MonitorTrackMuonsInnerTrack.TkSizeMax = 10.
MonitorTrackMuonsInnerTrack.phiErrMax = 0.001
MonitorTrackMuonsInnerTrack.etaErrMax = 0.001
MonitorTrackMuonsInnerTrack.PVBin = 40
MonitorTrackMuonsInnerTrack.PVMin = -0.5
MonitorTrackMuonsInnerTrack.PVMax = 79.5 ## it might need to be adjust if CMS asks to have lumi levelling at lower values


from Configuration.Eras.Modifier_phase1Pixel_cff import phase1Pixel
from Configuration.Eras.Modifier_phase2_tracker_cff import phase2_tracker
phase1Pixel.toModify(MonitorTrackMuonsInnerTrack, EtaBin=31, EtaMin=-3., EtaMax=3.)
phase2_tracker.toModify(MonitorTrackMuonsInnerTrack, EtaBin=46, EtaMin=-4.5, EtaMax=4.5)
phase2_tracker.toModify(MonitorTrackMuonsInnerTrack, PVBin=125, PVMin=-0.5, PVMax=249.5)


#MonitorTrackINNMuons = cms.Sequence(muonInnerTrack+MonitorTrackMuonsInnerTrack)
MonitorTrackINNMuons = cms.Sequence(cms.ignore(muonsPt10)+muonInnerTrack+MonitorTrackMuonsInnerTrack)
