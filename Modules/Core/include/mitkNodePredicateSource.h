/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef mitkNodePredicateSource_h
#define mitkNodePredicateSource_h

#include "mitkDataNode.h"
#include "mitkDataStorage.h"
#include "mitkNodePredicateBase.h"
#include "mitkWeakPointer.h"

namespace mitk
{
  //##Documentation
  //## @brief Predicate that evaluates if the given node is a direct or indirect source node of a specific node
  //##
  //## @warning Calling CheckNode() can be computationally quite expensive for a large DataStorage.
  //##          Alternatively mitk::StandaloneDataStorage::GetSources() can be used
  //##
  //## @ingroup DataStorage
  class MITKCORE_EXPORT NodePredicateSource : public NodePredicateBase
  {
  public:
    mitkClassMacro(NodePredicateSource, NodePredicateBase);
    mitkNewMacro3Param(NodePredicateSource, mitk::DataNode *, bool, mitk::DataStorage *);

    //##Documentation
    //## @brief Standard Destructor
    ~NodePredicateSource() override;

    //##Documentation
    //## @brief Checks, if m_BaseNode is a source node of childNode  (e.g. if childNode "was created from" m_BaseNode)
    bool CheckNode(const mitk::DataNode *childNode) const override;

  protected:
    //##Documentation
    //## @brief Constructor - This class can either search only for direct source objects or for all source objects
    NodePredicateSource(mitk::DataNode *n, bool allsources, mitk::DataStorage *ds);

    mitk::WeakPointer<mitk::DataNode> m_BaseNode;
    bool m_SearchAllSources;
    mitk::WeakPointer<mitk::DataStorage> m_DataStorage;
  };

} // namespace mitk

#endif
