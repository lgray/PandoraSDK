/**
 *  @file   PandoraSDK/src/Api/PandoraApiImpl.cc
 * 
 *  @brief  Implementation of the pandora api class.
 * 
 *  $Log: $
 */

#include "Api/PandoraApi.h"
#include "Api/PandoraApiImpl.h"

#include "Managers/AlgorithmManager.h"
#include "Managers/CaloHitManager.h"
#include "Managers/ClusterManager.h"
#include "Managers/GeometryManager.h"
#include "Managers/MCManager.h"
#include "Managers/ParticleFlowObjectManager.h"
#include "Managers/PluginManager.h"
#include "Managers/TrackManager.h"
#include "Managers/VertexManager.h"

#include "Pandora/PandoraSettings.h"

#include "Plugins/EnergyCorrectionsPlugin.h"
#include "Plugins/ParticleIdPlugin.h"

namespace pandora
{

template <>
StatusCode PandoraApiImpl::Create(const PandoraApi::MCParticle::Parameters &parameters) const
{
    const MCParticle *pMCParticle(NULL);
    return m_pPandora->m_pMCManager->Create(parameters, pMCParticle);
}

template <>
StatusCode PandoraApiImpl::Create(const PandoraApi::Track::Parameters &parameters) const
{
    const Track *pTrack(NULL);
    return m_pPandora->m_pTrackManager->Create(parameters, pTrack);
}

template <>
StatusCode PandoraApiImpl::Create(const PandoraApi::RectangularCaloHit::Parameters &parameters) const
{
    const CaloHit *pCaloHit(NULL);
    return m_pPandora->m_pCaloHitManager->Create(parameters, pCaloHit);
}

template <>
StatusCode PandoraApiImpl::Create(const PandoraApi::PointingCaloHit::Parameters &parameters) const
{
    const CaloHit *pCaloHit(NULL);
    return m_pPandora->m_pCaloHitManager->Create(parameters, pCaloHit);
}

template <>
StatusCode PandoraApiImpl::Create(const PandoraApi::Geometry::SubDetector::Parameters &parameters) const
{
    return m_pPandora->m_pGeometryManager->CreateSubDetector(parameters);
}

template <>
StatusCode PandoraApiImpl::Create(const PandoraApi::Geometry::BoxGap::Parameters &parameters) const
{
    return m_pPandora->m_pGeometryManager->CreateBoxGap(parameters);
}

template <>
StatusCode PandoraApiImpl::Create(const PandoraApi::Geometry::ConcentricGap::Parameters &parameters) const
{
    return m_pPandora->m_pGeometryManager->CreateConcentricGap(parameters);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::ProcessEvent() const
{
    return m_pPandora->ProcessEvent();
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::ReadSettings(const std::string &xmlFileName) const
{
    return m_pPandora->ReadSettings(xmlFileName);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::RegisterAlgorithmFactory(const std::string &algorithmType, AlgorithmFactory *const pAlgorithmFactory) const
{
    return m_pPandora->m_pAlgorithmManager->RegisterAlgorithmFactory(algorithmType, pAlgorithmFactory);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::RegisterAlgorithmToolFactory(const std::string &algorithmToolType, AlgorithmToolFactory *const pAlgorithmToolFactory) const
{
    return m_pPandora->m_pAlgorithmManager->RegisterAlgorithmToolFactory(algorithmToolType, pAlgorithmToolFactory);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetMCParentDaughterRelationship(const void *const pParentAddress, const void *const pDaughterAddress) const
{
    return m_pPandora->m_pMCManager->SetMCParentDaughterRelationship(pParentAddress, pDaughterAddress);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetTrackParentDaughterRelationship(const void *const pParentAddress, const void *const pDaughterAddress) const
{
    return m_pPandora->m_pTrackManager->SetTrackParentDaughterRelationship(pParentAddress, pDaughterAddress);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetTrackSiblingRelationship(const void *const pFirstSiblingAddress, const void *const pSecondSiblingAddress) const
{
    return m_pPandora->m_pTrackManager->SetTrackSiblingRelationship(pFirstSiblingAddress, pSecondSiblingAddress);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetCaloHitToMCParticleRelationship(const void *const pCaloHitParentAddress, const void *const pMCParticleParentAddress,
    const float mcParticleWeight) const
{
    return m_pPandora->m_pMCManager->SetCaloHitToMCParticleRelationship(pCaloHitParentAddress, pMCParticleParentAddress, mcParticleWeight);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetTrackToMCParticleRelationship(const void *const pTrackParentAddress, const void *const pMCParticleParentAddress,
    const float mcParticleWeight) const
{
    return m_pPandora->m_pMCManager->SetTrackToMCParticleRelationship(pTrackParentAddress, pMCParticleParentAddress, mcParticleWeight);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::GetCurrentPfoList(const PfoList *&pPfoList, std::string &pfoListName) const
{
    return m_pPandora->m_pPfoManager->GetCurrentList(pPfoList, pfoListName);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::GetPfoList(const std::string &pfoListName, const PfoList *&pPfoList) const
{
    return m_pPandora->m_pPfoManager->GetList(pfoListName, pPfoList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetHitTypeGranularity(const HitType hitType, const Granularity granularity) const
{
    return m_pPandora->m_pGeometryManager->SetHitTypeGranularity(hitType, granularity);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetBFieldPlugin(BFieldPlugin *const pBFieldPlugin) const
{
    return m_pPandora->m_pPluginManager->SetBFieldPlugin(pBFieldPlugin);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetPseudoLayerPlugin(PseudoLayerPlugin *const pPseudoLayerPlugin) const
{
    return m_pPandora->m_pPluginManager->SetPseudoLayerPlugin(pPseudoLayerPlugin);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::SetShowerProfilePlugin(ShowerProfilePlugin *const pShowerProfilePlugin) const
{
    return m_pPandora->m_pPluginManager->SetShowerProfilePlugin(pShowerProfilePlugin);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::RegisterEnergyCorrectionPlugin(const std::string &name, const EnergyCorrectionType energyCorrectionType,
    EnergyCorrectionPlugin *const pEnergyCorrectionPlugin) const
{
    return m_pPandora->m_pPluginManager->m_pEnergyCorrections->RegisterPlugin(name, energyCorrectionType, pEnergyCorrectionPlugin);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::RegisterParticleIdPlugin(const std::string &name, ParticleIdPlugin *const pParticleIdPlugin) const
{
    return m_pPandora->m_pPluginManager->m_pParticleId->RegisterPlugin(name, pParticleIdPlugin);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PandoraApiImpl::ResetEvent() const
{
    return m_pPandora->ResetEvent();
}

//------------------------------------------------------------------------------------------------------------------------------------------

PandoraApiImpl::PandoraApiImpl(Pandora *const pPandora) :
    m_pPandora(pPandora)
{
}

} // namespace pandora
