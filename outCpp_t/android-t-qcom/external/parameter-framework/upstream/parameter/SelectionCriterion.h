/*
 * Copyright (c) 2011-2015, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include "Element.h"
#include "SelectionCriterionType.h"
#include "SelectionCriterionInterface.h"
#include <log/Logger.h>
#include <NonCopyable.hpp>

#include <string>

class CSelectionCriterion : public CElement,
                            public ISelectionCriterionInterface,
                            private utility::NonCopyable
{
public:
    CSelectionCriterion(const std::string &strName, const CSelectionCriterionType *pType,
                        core::log::Logger &logger);

    /// From ISelectionCriterionInterface
    // State
    void setCriterionState(uint64_t iState) override;
    uint64_t getCriterionState() const override;
    // Name
    std::string getCriterionName() const override;
    // Type
    const ISelectionCriterionTypeInterface *getCriterionType() const override;
    // Modified status
    bool hasBeenModified() const;
    void resetModifiedStatus();

    /// Match methods
    bool is(uint64_t iState) const;
    bool isNot(uint64_t iState) const;
    bool includes(uint64_t iState) const;
    bool excludes(uint64_t iState) const;

    /// User request
    std::string getFormattedDescription(bool bWithTypeInfo, bool bHumanReadable) const;

    /// From CElement
    std::string getKind() const override;

    /**
      * Export to XML
      *
      * @param[in] xmlElement The XML element to export to
      * @param[in] serializingContext The serializing context
      *
      */
    void toXml(CXmlElement &xmlElement, CXmlSerializingContext &serializingContext) const override;

private:
    // Current state
    uint64_t _iState{0};
    // Type
    const CSelectionCriterionType *_pType;

    /** Counter to know how many modifications have been applied to this criterion */
    uint32_t _uiNbModifications{0};

    /** Application logger */
    core::log::Logger &_logger;
};
