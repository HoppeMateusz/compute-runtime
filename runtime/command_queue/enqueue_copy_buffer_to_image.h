/*
 * Copyright (C) 2017-2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "runtime/built_ins/built_ins.h"
#include "runtime/command_queue/command_queue_hw.h"
#include "runtime/command_stream/command_stream_receiver.h"
#include "runtime/helpers/kernel_commands.h"
#include "runtime/helpers/mipmap.h"
#include "runtime/helpers/surface_formats.h"
#include "runtime/mem_obj/buffer.h"
#include "runtime/mem_obj/image.h"
#include "runtime/memory_manager/surface.h"

#include "hw_cmds.h"

#include <new>

namespace NEO {

template <typename GfxFamily>
cl_int CommandQueueHw<GfxFamily>::enqueueCopyBufferToImage(
    Buffer *srcBuffer,
    Image *dstImage,
    size_t srcOffset,
    const size_t *dstOrigin,
    const size_t *region,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event) {

    MultiDispatchInfo di;

    auto &builder = getDevice().getExecutionEnvironment()->getBuiltIns()->getBuiltinDispatchInfoBuilder(EBuiltInOps::CopyBufferToImage3d,
                                                                                                        this->getContext(), this->getDevice());
    BuiltInOwnershipWrapper builtInLock(builder, this->context);

    MemObjSurface srcBufferSurf(srcBuffer);
    MemObjSurface dstImgSurf(dstImage);
    Surface *surfaces[] = {&srcBufferSurf, &dstImgSurf};

    BuiltinDispatchInfoBuilder::BuiltinOpParams dc;
    dc.srcMemObj = srcBuffer;
    dc.dstMemObj = dstImage;
    dc.srcOffset = {srcOffset, 0, 0};
    dc.dstOffset = dstOrigin;
    dc.size = region;
    if (dstImage->getImageDesc().num_mip_levels > 0) {
        dc.dstMipLevel = findMipLevel(dstImage->getImageDesc().image_type, dstOrigin);
    }
    builder.buildDispatchInfos(di, dc);

    enqueueHandler<CL_COMMAND_COPY_BUFFER_TO_IMAGE>(
        surfaces,
        false,
        di,
        numEventsInWaitList,
        eventWaitList,
        event);

    return CL_SUCCESS;
}
} // namespace NEO
