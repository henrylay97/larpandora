/**
 *  @file   LArContent/include/LArThreeDReco/LArThreeDBase/ThreeDTracksBaseAlgorithm.h
 * 
 *  @brief  Header file for the three dimensional tracks algorithm base class.
 * 
 *  $Log: $
 */
#ifndef LAR_THREE_D_TRACKS_BASE_ALGORITHM_H
#define LAR_THREE_D_TRACKS_BASE_ALGORITHM_H 1

#include "LArObjects/LArTwoDSlidingFitResult.h"

#include "LArThreeDReco/LArThreeDBase/ThreeDBaseAlgorithm.h"

namespace lar
{

/**
 *  @brief  ThreeDTransverseTracksAlgorithm class
 */
template<typename T>
class ThreeDTracksBaseAlgorithm : public ThreeDBaseAlgorithm<T>
{
public:
    /**
     *  @brief  Get a sliding fit result from the algorithm cache
     * 
     *  @param  pCluster address of the relevant cluster
     */
    const TwoDSlidingFitResult &GetCachedSlidingFitResult(pandora::Cluster *const pCluster) const;

    /**
     *  @brief  Get the layer window for the sliding linear fits
     * 
     *  @return the layer window for the sliding linear fits
     */
    unsigned int GetSlidingFitWindow() const;

    virtual void UpdateForNewCluster(pandora::Cluster *const pNewCluster);
    virtual void UpdateUponDeletion(pandora::Cluster *const pDeletedCluster);
    virtual void SelectInputClusters(const pandora::ClusterList *const pInputClusterList, pandora::ClusterList &selectedClusterList) const;

protected:
    virtual void PreparationStep();
    virtual void TidyUp();

    /**
     *  @brief  Add a new sliding fit result, for the specified cluster, to the algorithm cache
     * 
     *  @param  pCluster address of the relevant cluster
     */
    void AddToSlidingFitCache(pandora::Cluster *const pCluster);

    /**
     *  @brief  Remova an existing sliding fit result, for the specified cluster, from the algorithm cache
     * 
     *  @param  pCluster address of the relevant cluster
     */
    void RemoveFromSlidingFitCache(pandora::Cluster *const pCluster);

    virtual pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    unsigned int                m_slidingFitWindow;         ///< The layer window for the sliding linear fits
    TwoDSlidingFitResultMap     m_slidingFitResultMap;      ///< The sliding fit result map    

    unsigned int                m_minClusterCaloHits;           ///< The min number of hits in base cluster selection method
    float                       m_minClusterLengthSquared;      ///< The min length (squared) in base cluster selection method
};

//------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
inline unsigned int ThreeDTracksBaseAlgorithm<T>::GetSlidingFitWindow() const
{
    return m_slidingFitWindow;
}

} // namespace lar

#endif // #ifndef LAR_THREE_D_TRACKS_BASE_ALGORITHM_H