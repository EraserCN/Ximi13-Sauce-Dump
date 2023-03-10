/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// TODO(b/129481165): remove the #pragma below and fix conversion issues
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

// #define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "EffectLayer"

#include "EffectLayer.h"

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#include <compositionengine/CompositionEngine.h>
#include <compositionengine/LayerFECompositionState.h>
#include <renderengine/RenderEngine.h>
#include <ui/GraphicBuffer.h>
#include <utils/Errors.h>
#include <utils/Log.h>

#include "DisplayDevice.h"
#include "SurfaceFlinger.h"
#include "MiSurfaceFlingerStub.h"

namespace android {
// ---------------------------------------------------------------------------

EffectLayer::EffectLayer(const LayerCreationArgs& args)
      : Layer(args),
        mCompositionState{mFlinger->getCompositionEngine().createLayerFECompositionState()} {}

EffectLayer::~EffectLayer() = default;

std::vector<compositionengine::LayerFE::LayerSettings> EffectLayer::prepareClientCompositionList(
        compositionengine::LayerFE::ClientCompositionTargetSettings& targetSettings) {
    std::vector<compositionengine::LayerFE::LayerSettings> results;
    std::optional<compositionengine::LayerFE::LayerSettings> layerSettings =
            prepareClientComposition(targetSettings);
    // Nothing to render.
    if (!layerSettings) {
        return {};
    }
#ifdef MI_SF_FEATURE
    MiSurfaceFlingerStub::prepareMiuiShadowClientComposition(*layerSettings,
                                                targetSettings.viewport, this);
#endif
    // set the shadow for the layer if needed
    prepareShadowClientComposition(*layerSettings, targetSettings.viewport);

    // If fill bounds are occluded or the fill color is invalid skip the fill settings.
    if (targetSettings.realContentIsVisible && fillsColor()) {
        // Set color for color fill settings.
        layerSettings->source.solidColor = getColor().rgb;
        results.push_back(*layerSettings);
#ifdef MI_SF_FEATURE
    } else if (hasBlur() || drawShadows() || drawMiuiShadows()) {
#else
    } else if (hasBlur() || drawShadows()) {
#endif
        layerSettings->skipContentDraw = true;
        results.push_back(*layerSettings);
    }

    return results;
}

bool EffectLayer::isVisible() const {
    return !isHiddenByPolicy() && (getAlpha() > 0.0_hf || hasBlur()) && hasSomethingToDraw();
}

bool EffectLayer::setColor(const half3& color) {
    if (mDrawingState.color.r == color.r && mDrawingState.color.g == color.g &&
        mDrawingState.color.b == color.b) {
        return false;
    }

    mDrawingState.sequence++;
    mDrawingState.color.r = color.r;
    mDrawingState.color.g = color.g;
    mDrawingState.color.b = color.b;
    mDrawingState.modified = true;
    setTransactionFlags(eTransactionNeeded);
    return true;
}

bool EffectLayer::setDataspace(ui::Dataspace dataspace) {
    if (mDrawingState.dataspace == dataspace) {
        return false;
    }

    mDrawingState.sequence++;
    mDrawingState.dataspace = dataspace;
    mDrawingState.modified = true;
    setTransactionFlags(eTransactionNeeded);
    return true;
}

void EffectLayer::preparePerFrameCompositionState() {
    Layer::preparePerFrameCompositionState();

    auto* compositionState = editCompositionState();
    compositionState->color = getColor();
    compositionState->compositionType =
            aidl::android::hardware::graphics::composer3::Composition::SOLID_COLOR;
}

sp<compositionengine::LayerFE> EffectLayer::getCompositionEngineLayerFE() const {
    // There's no need to get a CE Layer if the EffectLayer isn't going to draw anything. In that
    // case, it acts more like a ContainerLayer so returning a null CE Layer makes more sense
    if (hasSomethingToDraw()) {
        return asLayerFE();
    } else {
        return nullptr;
    }
}

compositionengine::LayerFECompositionState* EffectLayer::editCompositionState() {
    return mCompositionState.get();
}

const compositionengine::LayerFECompositionState* EffectLayer::getCompositionState() const {
    return mCompositionState.get();
}

bool EffectLayer::isOpaque(const Layer::State& s) const {
    // Consider the layer to be opaque if its opaque flag is set or its effective
    // alpha (considering the alpha of its parents as well) is 1.0;
    return (s.flags & layer_state_t::eLayerOpaque) != 0 || (fillsColor() && getAlpha() == 1.0_hf);
}

ui::Dataspace EffectLayer::getDataSpace() const {
    return mDrawingState.dataspace;
}

sp<Layer> EffectLayer::createClone() {
    sp<EffectLayer> layer = mFlinger->getFactory().createEffectLayer(
            LayerCreationArgs(mFlinger.get(), nullptr, mName + " (Mirror)", 0, LayerMetadata()));
    layer->setInitialValuesForClone(this);
    return layer;
}

bool EffectLayer::fillsColor() const {
    return mDrawingState.color.r >= 0.0_hf && mDrawingState.color.g >= 0.0_hf &&
            mDrawingState.color.b >= 0.0_hf;
}

bool EffectLayer::hasBlur() const {
    return getBackgroundBlurRadius() > 0 || getDrawingState().blurRegions.size() > 0;
}

} // namespace android

// TODO(b/129481165): remove the #pragma below and fix conversion issues
#pragma clang diagnostic pop // ignored "-Wconversion"
